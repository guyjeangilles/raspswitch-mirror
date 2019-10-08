EESchema Schematic File Version 4
LIBS:DuinoCon-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 8
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
L DuinoCon-rescue:blueSMIRF-Silver-RF_Bluetooth U?
U 1 1 5C3D6A3D
P 5000 3250
AR Path="/5C3D6A3D" Ref="U?"  Part="1" 
AR Path="/5C3DCC04/5C3D6A3D" Ref="U3"  Part="1" 
F 0 "U3" H 5000 3150 50  0000 C CNN
F 1 "blueSMIRF-Silver" H 5000 3050 50  0000 C CNN
F 2 "" H 5000 3250 50  0001 C CNN
F 3 "" H 5000 3250 50  0001 C CNN
	1    5000 3250
	1    0    0    -1  
$EndComp
NoConn ~ 4450 3100
NoConn ~ 4450 3650
$Comp
L power:GND #PWR023
U 1 1 5C3D7747
P 5000 3850
F 0 "#PWR023" H 5000 3600 50  0001 C CNN
F 1 "GND" H 5005 3677 50  0000 C CNN
F 2 "" H 5000 3850 50  0001 C CNN
F 3 "" H 5000 3850 50  0001 C CNN
	1    5000 3850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR022
U 1 1 5C3D77D6
P 5000 2900
F 0 "#PWR022" H 5000 2750 50  0001 C CNN
F 1 "+5V" H 5015 3073 50  0000 C CNN
F 2 "" H 5000 2900 50  0001 C CNN
F 3 "" H 5000 2900 50  0001 C CNN
	1    5000 2900
	1    0    0    -1  
$EndComp
Text HLabel 5550 3100 2    50   Output ~ 0
blueSMIRF_Tx
Text HLabel 5550 3650 2    50   Input ~ 0
MCU_Tx
$EndSCHEMATC
