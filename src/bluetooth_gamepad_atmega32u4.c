/* Bluetooth Gamepad Firmware

The Circuit

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

NOTES AND METHODOLOGY

  The push buttons of the analog sticks are "active low" meaning when pushed their digital values is 0 while normally
  push buttons have a digital value of 1 when pushed. I've modified the read_shift_regs() function
  so the push buttons are active high

Shout out to the good people at SparkFun, Adafruit, Arduino and others I'm forgetting for being so helpful

*/

#define F_CPU 16000000
#define BAUD  115200
#define BRC   ((F_CPU/8/BAUD) - 1)

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>
#include <util/setbaud.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* How many shift register chips are daisy-chained.
*/
#define NUMBER_OF_SHIFT_CHIPS   2

/* Width of data (how many ext lines).
*/
#define DATA_WIDTH   NUMBER_OF_SHIFT_CHIPS * 8

/* Width of pulse to trigger the shift register to read and latch.
*/
#define PULSE_WIDTH_USEC   5

/* Optional delay between shift register reads.
*/
#define POLL_DELAY_MSEC   1

/* You will need to change the "int" to "long" If the
 * NUMBER_OF_SHIFT_CHIPS is higher than 2.
*/
#define BYTES_VAL_T unsigned int

/* Set up pins*/
const uint8_t ploadPin        = PD1;  // Connects to Parallel load pin of the shift register
const uint8_t clockEnablePin  = PD0;  // Connects to Clock Enable pin of the shift register
const uint8_t dataPin         = PD4; // Connects to the Q7 pin the of the shift register
const uint8_t clockPin        = PC6; // Connects to the Clock pin of the shift register

const uint8_t ANALOG_STICK_BUTTON_INPUTS[2] = {4,12};//these are the analog stick buttons that are active low

/*define joystick pins*/
const uint8_t axis1Pin   = PF7;//x1
const uint8_t axis2Pin   = PF6;//y1
const uint8_t axis3Pin   = PF5;//x2
const uint8_t axis4Pin   = PF4;//y2

/* set up variable values*/
BYTES_VAL_T pinValues;
signed char analogAxisValues[4] = {0, 0, 0, 0}; //represent X1,Y1,X2, and Y2 values
char leftControllerButtons  = 0;
char rightControllerButtons = 0;

/*intialize static bits of blueSMIRF*/
char startByte              = 0XFD;
char lengthByte             = 0x06;

/*prototype functions*/
BYTES_VAL_T read_shift_regs();
void USART_Init(uint32_t baud);
void USART_Transmit(signed char data);
void sendHIDreport();
signed char _map(long x, long in_min, long in_max, long out_min, long out_max);

uint8_t main(){
  /*intialize UART */
  USART_Init(BAUD);

  /*set pins as output*/
  DDRD = 0xFF;
  DDRB = 0XFF;
  DDRC = 0xFF;
  DDRE = 0xFF;
  DDRF = 0xFF;

  DDRD |= 1 << ploadPin;
  DDRD |= 1 << clockEnablePin;
  DDRD &= ~(1 << dataPin);
  DDRC |= 1 << clockPin;

  DDRF &= ~(1 << axis1Pin);
  DDRF &= ~(1 << axis2Pin);
  DDRF &= ~(1 << axis3Pin);
  DDRF &= ~(1 << axis4Pin);

  //intialize clockPin and ploadPin and pinValues
  PORTD &= ~(1 << clockEnablePin);
  PORTD |= 1 << ploadPin;

  pinValues = read_shift_regs();

  //loop forever
  while(1){
    /*read shift register and store the variables*/
    pinValues = read_shift_regs();

    /*read anlog axises*/
    ADMUX   = 0b01100000; // read from PC0
    ADCSRA  = 0b10000111; // Enable ADC and set the prescaler to max
    ADCSRA = ADCSRA | (1 << ADSC);
    while(ADCSRA & (1 << ADSC));// wait until the ADSC bit is clear
    analogAxisValues[0] = _map(ADCH, 0, 1023, -127, 127);

    ADMUX   = 0b01100001; // read from PC1
    ADCSRA  = 0b10000111;
    ADCSRA = ADCSRA | (1 << ADSC);
    while(ADCSRA & (1 << ADSC));
    analogAxisValues[1] = _map(ADCH, 0, 1023, -127, 127);

    ADMUX   = 0b01100010; // read from PC2
    ADCSRA  = 0b10000111;
    ADCSRA = ADCSRA | (1 << ADSC);
    while(ADCSRA & (1 << ADSC));
    analogAxisValues[2] = _map(ADCH, 0, 1023, -127, 127);

    ADMUX   = 0b01100011; // read from PC3
    ADCSRA  = 0b10000111;
    ADCSRA = ADCSRA | (1 << ADSC);
    while(ADCSRA & (1 << ADSC));
    analogAxisValues[3] = _map(ADCH, 0, 1023, -127, 127);

    /*split the button input into bytes that will be sent via bluetooth*/
    for (int i = 0; i < DATA_WIDTH; i++){
      if (i <= 7){
        if ((pinValues >> i) & 1){
          leftControllerButtons |= 1 << i;
        } else {
          leftControllerButtons &= ~(1 << i);
        }

      } else {
        if ((pinValues >> i) & 1){
          rightControllerButtons |= 1 << i;
        } else {
          rightControllerButtons &= ~(1 << i);
        }
      }
    }

    sendHIDreport();

    _delay_ms(POLL_DELAY_MSEC);
  }
  return 0;
}

/* This function is essentially a "shift-in" routine reading the
 * serial Data from the shift register chips and representing
 * the state of those pins in an unsigned integer (or long).
*/
BYTES_VAL_T read_shift_regs(){
  long bitVal;
  BYTES_VAL_T bytesVal = 0;

  PORTD |= 1 << clockEnablePin;
  PORTD &= ~(1<<ploadPin);
  _delay_us(PULSE_WIDTH_USEC);
  PORTD |= 1 << ploadPin;
  PORTD &= ~(1<<clockEnablePin);

  /* Loop to read each bit value from the serial out line of the SN74HC165N.*/
  for(int i = 0; i < DATA_WIDTH; i++){
    bitVal   = PIND & (1 << dataPin);

    /* Set the corresponding bit in bytesVal.*/
    bytesVal |= (bitVal << ((DATA_WIDTH-1) - i));

    /* Pulse the Clock (rising edge shifts the next bit).*/
    PORTC |= 1 << clockPin;
    _delay_us(PULSE_WIDTH_USEC);
    PORTC &= ~(1<<clockPin);
  }
  return bytesVal;
}

/*Intialize UART*/
void USART_Init(uint32_t baud){
  /* Set baud rate */
  UBRR1H = (unsigned char)(baud>>8);
  UBRR1L = (unsigned char) baud;

  /* Enable receiver and transmitter */
  UCSR1B = (1<<RXEN1)|(1<<TXEN1);

  /* Set frame format: 8data, 2stop bit */
  UCSR1C = (1<<USBS1)|(3<<UCSZ10);
}


//Transmit a single bit over UART
void USART_Transmit(signed char data){
  while(!UCSR1A & (1<<UDRE1));
  UDR1 = data;
}


/*
   Make and send the HID report that the bluetooth module will send
*/
void sendHIDreport()
{
  signed char gamepad_buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  gamepad_buffer[0] = startByte;
  gamepad_buffer[1] = lengthByte;
  gamepad_buffer[2] = analogAxisValues[0]; //X1 axis
  gamepad_buffer[3] = analogAxisValues[1]; //Y1 axis
  gamepad_buffer[4] = analogAxisValues[2]; //X2 axis
  gamepad_buffer[5] = analogAxisValues[3]; //Y2 axis
  gamepad_buffer[6] = leftControllerButtons; //Buttons 0-7
  gamepad_buffer[7] = rightControllerButtons; //Buttons 8-15

  for (int i = 0;  i < 8; i++){
    USART_Transmit(gamepad_buffer[i]);
  }
}

signed char _map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (signed char) (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
