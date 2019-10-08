EESchema Schematic File Version 4
LIBS:DuinoCon-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 8 8
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
L Connector:Screw_Terminal_01x04 J2
U 1 1 5D3FBE22
P 6550 3650
F 0 "J2" H 6630 3642 50  0000 L CNN
F 1 "Screw_Terminal_01x04" H 6630 3551 50  0000 L CNN
F 2 "" H 6550 3650 50  0001 C CNN
F 3 "~" H 6550 3650 50  0001 C CNN
	1    6550 3650
	1    0    0    -1  
$EndComp
$Comp
L Connector:AudioJack2_Ground_Switch J1
U 1 1 5D3FC244
P 4200 3750
F 0 "J1" H 3900 4200 50  0000 C CNN
F 1 "AudioJack2_Ground_Switch" H 3900 4100 50  0000 C CNN
F 2 "" H 4200 3950 50  0001 C CNN
F 3 "~" H 4200 3950 50  0001 C CNN
	1    4200 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:Speaker LS1
U 1 1 5D3FC39F
P 4850 2700
F 0 "LS1" V 4861 2420 50  0000 R CNN
F 1 "Speaker" V 4770 2420 50  0000 R CNN
F 2 "" H 4850 2500 50  0001 C CNN
F 3 "~" H 4840 2650 50  0001 C CNN
	1    4850 2700
	0    -1   -1   0   
$EndComp
$Comp
L Device:Speaker LS2
U 1 1 5D3FC476
P 5900 2700
F 0 "LS2" V 5911 2420 50  0000 R CNN
F 1 "Speaker" V 5820 2420 50  0000 R CNN
F 2 "" H 5900 2500 50  0001 C CNN
F 3 "~" H 5890 2650 50  0001 C CNN
	1    5900 2700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6350 3850 6350 4050
Wire Wire Line
	6350 4050 6000 4050
Wire Wire Line
	6350 3550 4400 3550
Wire Wire Line
	6350 3750 4400 3750
Wire Wire Line
	4400 3650 4850 3650
NoConn ~ 6350 3650
Text Label 6150 4050 0    50   ~ 0
GND
Text Label 6100 3750 0    50   ~ 0
Right
Text Label 6150 3550 0    50   ~ 0
Left
Wire Wire Line
	4850 2900 4850 3650
Wire Wire Line
	4950 2900 4950 4050
Connection ~ 4950 4050
Wire Wire Line
	4950 4050 4200 4050
Wire Wire Line
	6000 2900 6000 4050
Connection ~ 6000 4050
Wire Wire Line
	6000 4050 4950 4050
Wire Wire Line
	5900 3850 4400 3850
Wire Wire Line
	5900 2900 5900 3850
$EndSCHEMATC
