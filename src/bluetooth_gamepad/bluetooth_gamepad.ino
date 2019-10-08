/* THE CIRCUIT
   Push Button (x14)
   -5V to push button
   -10k resistor from GND to pushbutton
   -SN74HC165N data input to 10K resistor

   Thumb Joystick (x2)
   -VCC to 5V
   -VERT to arduino analog pin
   -HORZ to arduino analog pin
   -SEL to arduino digital pin, 10k resistor to arduino digital pin from GND
   -GND to ground

   Shift register 0 [directly connected to arduino]
   -parrallel load to arduino digital pin
   -clock input to arduino digital pin
   -GND to ground
   -serial output to arduino digital pin
   -serial input to serial output of shift register 2
   -clock enable to arduino digital pin
   -VCC to 5V

   Shift register 1 [connected to shift register 0]
   -parrallel load to parralel load of shift register 0
   -clock input to clock input of shift register 0
   -GND to ground
   -serial output to serial input of shift register 0
   -clock enable to clock enable of shift register 0
   -VCC to 5V

   Bluesmirf
   -RX-I pin connected to pin 0
   -TX-o pin connected to pin 1
   -GND to ground
   -VCC to 5V

*/

/*  NOTES AND METHODOLOGY
  "Serial1" is the hardware serial port of the arduino micro, used to communicate with the BlueSmirf
  "Serial", is the virtual serial port of the arduino micro

  The push buttons of the analog sticks are "active low" meaning when pushed their digital values is 0 while normally
  push buttons have a digital value of 1 when pushed. I've modified the read_shift_regs() function
  so the push buttons are active high

  Hardware serial is used to communicate to the bluesmirf.
  The software serial is used to print to the serial monitor and upload code

*/

//how many shift register chips are daisy-chained.
const int NUMBER_OF_SHIFT_CHIPS = 2;

//width of data (how many ext lines).
const int DATA_WIDTH = NUMBER_OF_SHIFT_CHIPS * 8;

//width of pulse to trigger the shift register to read and latch.
const int PULSE_WIDTH_USEC = 5;

//optional delay between shift register reads.
const int POLL_DELAY_MSEC = 5;

//You will need to change the "int" to "long" If the
#define INPUT_DATA_TYPE unsigned int

//Store what shift register pins are connected to the
//analog stick push buttons. This is done to ensure they are active
//low.
const int ANALOG_STICK_BUTTON_INPUTS[2] = {4, 12};

//define shift register pins
const int ploadPin        = 2;  // Connects to Parallel load pin the 165
const int clockEnablePin  = 3;  // Connects to Clock Enable pin the 165
const int dataPin         = 4; // Connects to the Q7 pin the 165
const int clockPin        = 5; // Connects to the Clock pin the 165

//define joystick pins
const int analogAxisPins[4] = {0, 1, 2, 3}; //represent X1,Y1,X2, and Y2 values

//intialize input values
INPUT_DATA_TYPE pinValues;
INPUT_DATA_TYPE oldPinValues;

signed int analogAxisValues[4] = {0, 0, 0, 0}; //represent X1,Y1,X2, and Y2 values
signed int oldAnalogAxisValues[4] = {0, 0, 0, 0}; //represent X1,Y1,X2, and Y2 values

//intialize output of bluesmirf
byte startByte = 0XFD;
byte lengthByte = 0x06;
byte leftControllerButtons  = 0;
byte rightControllerButtons = 0;

void setup()
{
  //CONFIGURE BLUESMIRF
  Serial1.begin(115200);  // set hardware serial to 115200 baud rate (bluesmirf default)

  //enter command mode
  Serial1.print("$$$");
  delay(100);// Short delay, wait for the Mate to send back CMD
  Serial1.flush();

  // Temporarily Change the baudrate to 9600, no parity
  Serial1.print("U,9600,N");
  Serial1.print("\r");
  Serial1.print("\n");
  Serial1.flush();

  // Start bluetooth serial at 9600
  Serial1.begin(9600);

  //CONFIGURE SHIFT REGISTERS
  Serial.begin(9600);
  Serial.println("Virtual serial is open.");

  /* Initialize our digital pins...
  */
  pinMode(ploadPin, OUTPUT);
  pinMode(clockEnablePin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, INPUT);

  digitalWrite(clockPin, LOW);
  digitalWrite(ploadPin, HIGH);

  /* Read in and display the pin states at startup.
  */
  pinValues = read_shift_regs();
  display_pin_values();
  oldPinValues = pinValues;

}

void loop()
{
  //read button values
  pinValues = read_shift_regs();

  //read analog axis values
  for (int i = 0; i < 4; i++) {
    analogAxisValues[i] = map(analogRead(analogAxisPins[i]), 0, 1023, -127, 127);
  }

  //Split the button input into bytes that you'll send via bluetooth
  for (int i = 0; i < DATA_WIDTH; i++) {

    if (i <= 7)
    {
      bitWrite(leftControllerButtons, i, (pinValues >> i) & 1);
    }
    else
    {
      bitWrite(rightControllerButtons, i - 8, (pinValues >> i) & 1);
    }
  }

  sendHIDreport();

  /* If there was a chage in state, display which ones changed.
  */
  if (pinValues != oldPinValues /*|| analogAxisValues != oldAnalogAxisValues*/)
  {
    Serial.print("*Pin value change detected*\r\n");
    display_pin_values();
    Serial.print("Left Controller Byte: ");
    Serial.println(leftControllerButtons);
    Serial.print("Right Controller Byte: ");
    Serial.println(rightControllerButtons);

    oldPinValues = pinValues;
    for (int i = 0; i < 3; i++) {
      oldAnalogAxisValues[i] = analogAxisValues[i];
    }
  }

  //allow communication to the blueSMIRF via the serial monitor
  if (Serial1.available()) //If the bluetooth sent any characters
  {
    // Send any characters the bluetooth prints to the serial monitor
    Serial.print((char)Serial1.read());
  }
  else
  {
    //Clear the stream when there is not else to send
    Serial1.flush();
  }

  if (Serial.available()) // If stuff was typed in the serial monitor
  {
    // Send any characters the Serial monitor prints to the bluetooth
    Serial1.print((char)Serial.read());
  }
  else
  {
    //clear the stream when there is nothing else to print
    Serial1.flush();
  }

  delay(POLL_DELAY_MSEC);
}

/* This function is essentially a "shift-in" routine reading the
   serial Data from the shift register chips and representing
   the state of those pins in an unsigned integer (or long).
*/
INPUT_DATA_TYPE read_shift_regs()
{
  long bitVal;
  INPUT_DATA_TYPE bytesVal = 0;

  /* Trigger a parallel Load to latch the state of the data lines,
  */
  digitalWrite(clockEnablePin, HIGH);
  digitalWrite(ploadPin, LOW);
  delayMicroseconds(PULSE_WIDTH_USEC);
  digitalWrite(ploadPin, HIGH);
  digitalWrite(clockEnablePin, LOW);

  /* Loop to read each bit value from the serial out line
     of the SN74HC165N.
  */
  for (int i = 0; i < DATA_WIDTH; i++)
  {
    //make the analog stick buttons active high
    if (i == (ANALOG_STICK_BUTTON_INPUTS[0] - 1) || i == (ANALOG_STICK_BUTTON_INPUTS[1] - 1) ) {
      bitVal = not(digitalRead(dataPin));
    }
    else {
      bitVal = digitalRead(dataPin);
    }

    /* Set the corresponding bit in bytesVal.
    */
    bytesVal |= (bitVal << ((DATA_WIDTH - 1) - i));

    /* Pulse the Clock (rising edge shifts the next bit).
    */
    digitalWrite(clockPin, HIGH);
    delayMicroseconds(PULSE_WIDTH_USEC);
    digitalWrite(clockPin, LOW);
  }

  return (bytesVal);
}

/* Dump the list of zones along with their current status.
*/
void display_pin_values()
{
  Serial.print("Pin States:\r\n");

  for (int i = 0; i < DATA_WIDTH; i++)
  {
    Serial.print("  Pin-");
    Serial.print(i);
    Serial.print(": ");

    //if ((pinValues >> ((DATA_WIDTH - 1) - i)) & 1) {
    if ((pinValues >> i) & 1) {
      Serial.print("HIGH");
    }
    else {
      Serial.print("LOW");
    }

    Serial.print("\r\n");
  }
  Serial.print("PinValues equals: ");
  Serial.println(pinValues, BIN);
  Serial.print("X1: ");
  Serial.println(analogAxisValues[0]);
  Serial.print("Y1: ");
  Serial.println(analogAxisValues[1]);
  Serial.print("X2: ");
  Serial.println(analogAxisValues[2]);
  Serial.print("Y2: ");
  Serial.println(analogAxisValues[3]);

  Serial.print("\r\n");
}

/*
   Make and send the HID report that the bluetooth module will send
*/
void sendHIDreport()
{
  byte gamepad_buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  gamepad_buffer[0] = startByte;
  gamepad_buffer[1] = lengthByte;
  gamepad_buffer[2] = analogAxisValues[0]; //X1 axis
  gamepad_buffer[3] = analogAxisValues[1]; //Y1 axis
  gamepad_buffer[4] = analogAxisValues[2]; //X2 axis
  gamepad_buffer[5] = analogAxisValues[3]; //Y2 axis
  gamepad_buffer[6] = leftControllerButtons; //Buttons 0-7
  gamepad_buffer[7] = rightControllerButtons; //Buttons 8-15

  Serial1.write(gamepad_buffer, 8);
}

