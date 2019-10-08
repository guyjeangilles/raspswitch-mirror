EESchema Schematic File Version 4
LIBS:DuinoCon-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 8
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
L MCU_Module:ARDUINO_MICRO_SHIELD U2
U 1 1 5C3D9CB3
P 5250 2950
F 0 "U2" V 5053 3425 60  0000 C CNN
F 1 "ARDUINO_MICRO_SHIELD" V 5159 3425 60  0000 C CNN
F 2 "Package_DIP:DIP-40_W15.24mm_Socket_with_Arduino_Micro" H 5650 2900 60  0001 C CNN
F 3 "" H 5650 2900 60  0000 C CNN
	1    5250 2950
	0    1    1    0   
$EndComp
Text HLabel 5050 3600 0    50   Output ~ 0
Parallel_Load
Text HLabel 5050 3700 0    50   Output ~ 0
Clock_Enable
Text HLabel 5050 3800 0    50   Input ~ 0
Shift_Register0_Serial_Out
Text HLabel 5050 3900 0    50   Output ~ 0
Clock_Pin
Text HLabel 5050 3300 0    50   Input ~ 0
blueSMIRF_Tx
Text HLabel 5050 3200 0    50   Output ~ 0
MCU_Tx
NoConn ~ 5050 3000
NoConn ~ 5050 3100
NoConn ~ 5050 3400
NoConn ~ 5050 4000
NoConn ~ 5050 4100
NoConn ~ 5050 4200
NoConn ~ 5050 4300
NoConn ~ 5050 4400
NoConn ~ 5050 4500
NoConn ~ 5050 4600
NoConn ~ 6400 3000
NoConn ~ 6400 3100
NoConn ~ 6400 3200
NoConn ~ 6400 3400
NoConn ~ 6400 3800
NoConn ~ 6400 3900
NoConn ~ 6400 4400
NoConn ~ 6400 4500
NoConn ~ 6400 4600
$Comp
L power:+5V #PWR011
U 1 1 5C3D7C00
P 6600 2800
F 0 "#PWR011" H 6600 2650 50  0001 C CNN
F 1 "+5V" H 6615 2973 50  0000 C CNN
F 2 "" H 6600 2800 50  0001 C CNN
F 3 "" H 6600 2800 50  0001 C CNN
	1    6600 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 2800 6600 3500
Wire Wire Line
	6600 3500 6400 3500
NoConn ~ 6400 3300
$Comp
L power:GND #PWR010
U 1 1 5C3D7C51
P 3750 3950
F 0 "#PWR010" H 3750 3700 50  0001 C CNN
F 1 "GND" H 3755 3777 50  0000 C CNN
F 2 "" H 3750 3950 50  0001 C CNN
F 3 "" H 3750 3950 50  0001 C CNN
	1    3750 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 3500 3750 3500
Wire Wire Line
	3750 3500 3750 3950
Text HLabel 6400 4300 2    50   Input ~ 0
Axis_0
Text HLabel 6400 4200 2    50   Input ~ 0
Axis_1
Text HLabel 6400 4100 2    50   Input ~ 0
Axis_2
Text HLabel 6400 4000 2    50   Input ~ 0
Axis_3
$EndSCHEMATC
