EESchema Schematic File Version 4
LIBS:DuinoCon-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 8
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Interface_HID:ThumbJoystick U4
U 1 1 5C3E1F29
P 4550 3450
F 0 "U4" H 5077 3496 50  0000 L CNN
F 1 "ThumbJoystick" H 5077 3405 50  0000 L CNN
F 2 "" H 4550 3450 50  0001 C CNN
F 3 "" H 4550 3450 50  0001 C CNN
	1    4550 3450
	1    0    0    -1  
$EndComp
$Comp
L Interface_HID:ThumbJoystick U5
U 1 1 5C3E1FA1
P 6800 3450
F 0 "U5" H 7327 3496 50  0000 L CNN
F 1 "ThumbJoystick" H 7327 3405 50  0000 L CNN
F 2 "" H 6800 3450 50  0001 C CNN
F 3 "" H 6800 3450 50  0001 C CNN
	1    6800 3450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR026
U 1 1 5C3E203F
P 6800 2500
F 0 "#PWR026" H 6800 2350 50  0001 C CNN
F 1 "+5V" H 6815 2673 50  0000 C CNN
F 2 "" H 6800 2500 50  0001 C CNN
F 3 "" H 6800 2500 50  0001 C CNN
	1    6800 2500
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR024
U 1 1 5C3E2067
P 4550 2500
F 0 "#PWR024" H 4550 2350 50  0001 C CNN
F 1 "+5V" H 4565 2673 50  0000 C CNN
F 2 "" H 4550 2500 50  0001 C CNN
F 3 "" H 4550 2500 50  0001 C CNN
	1    4550 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR025
U 1 1 5C3E20CE
P 4550 4350
F 0 "#PWR025" H 4550 4100 50  0001 C CNN
F 1 "GND" H 4555 4177 50  0000 C CNN
F 2 "" H 4550 4350 50  0001 C CNN
F 3 "" H 4550 4350 50  0001 C CNN
	1    4550 4350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR027
U 1 1 5C3E20E4
P 6800 4350
F 0 "#PWR027" H 6800 4100 50  0001 C CNN
F 1 "GND" H 6805 4177 50  0000 C CNN
F 2 "" H 6800 4350 50  0001 C CNN
F 3 "" H 6800 4350 50  0001 C CNN
	1    6800 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 2900 6800 2500
Wire Wire Line
	4550 2900 4550 2500
Wire Wire Line
	4550 4000 4550 4350
Wire Wire Line
	6800 4000 6800 4350
Text HLabel 6250 3300 0    50   Output ~ 0
Axis_0
Text HLabel 6250 3450 0    50   Output ~ 0
Axis_1
Text HLabel 6250 3600 0    50   Output ~ 0
Stick_Button0
Text HLabel 4000 3300 0    50   Output ~ 0
Axis_2
Text HLabel 4000 3450 0    50   Output ~ 0
Axis_3
Text HLabel 4000 3600 0    50   Output ~ 0
Stick_Button1
$EndSCHEMATC
