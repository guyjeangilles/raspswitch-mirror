EESchema Schematic File Version 4
LIBS:DuinoCon-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 8
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 7000 1050 2950 1400
U 5C3CC8C7
F0 "right_face_buttons" 50
F1 "right_face_buttons.sch" 50
F2 "Shift_Register1_Serial_Out" I L 7000 2350 50 
F3 "Shift_Register0_Serial_Out" O L 7000 1150 50 
F4 "Parallel_Load" I L 7000 1850 50 
F5 "Clock_Enable" I L 7000 1750 50 
F6 "Clock_Pin" I L 7000 1650 50 
F7 "Stick_Button0" I L 7000 2100 50 
$EndSheet
$Sheet
S 4100 900  2100 1550
U 5C3D9C9A
F0 "microcontroller" 50
F1 "microcontroller.sch" 50
F2 "Parallel_Load" O R 6200 1850 50 
F3 "Clock_Enable" O R 6200 1750 50 
F4 "Shift_Register0_Serial_Out" I R 6200 1150 50 
F5 "Clock_Pin" O R 6200 1650 50 
F6 "blueSMIRF_Tx" I L 4100 1350 50 
F7 "MCU_Tx" O L 4100 1550 50 
F8 "Axis_0" I L 4100 2000 50 
F9 "Axis_1" I L 4100 2100 50 
F10 "Axis_2" I L 4100 2200 50 
F11 "Axis_3" I L 4100 2300 50 
$EndSheet
$Sheet
S 7000 2650 2950 1400
U 5C3DAC44
F0 "left_face_buttons" 50
F1 "left_face_buttons.sch" 50
F2 "Shift_Register1_Serial_Out" O L 7000 2750 50 
F3 "Parallel_Load" I L 7000 3300 50 
F4 "Clock_Enable" I L 7000 3200 50 
F5 "Clock_Pin" I L 7000 3100 50 
F6 "Stick_Button1" I L 7000 3700 50 
$EndSheet
$Sheet
S 1700 900  2100 1650
U 5C3DCC04
F0 "blueSMIRF" 50
F1 "blueSMIRF.sch" 50
F2 "blueSMIRF_Tx" O R 3800 1350 50 
F3 "MCU_Tx" I R 3800 1550 50 
$EndSheet
Wire Wire Line
	3800 1350 4100 1350
Wire Wire Line
	3800 1550 4100 1550
$Sheet
S 1650 2850 2100 1100
U 5C3D8835
F0 "analog_sticks" 50
F1 "analog_sticks.sch" 50
F2 "Axis_0" O R 3750 2950 50 
F3 "Axis_1" O R 3750 3050 50 
F4 "Stick_Button0" O R 3750 3600 50 
F5 "Axis_2" O R 3750 3150 50 
F6 "Axis_3" O R 3750 3250 50 
F7 "Stick_Button1" O R 3750 3700 50 
$EndSheet
Wire Wire Line
	3750 2950 3850 2950
Wire Wire Line
	3750 3050 3900 3050
Wire Wire Line
	3900 3050 3900 2100
Wire Wire Line
	3900 2100 4100 2100
Wire Wire Line
	3750 3150 3950 3150
Wire Wire Line
	3950 3150 3950 2200
Wire Wire Line
	3950 2200 4100 2200
Wire Wire Line
	3750 3250 4000 3250
Wire Wire Line
	4000 3250 4000 2300
Wire Wire Line
	4000 2300 4100 2300
Wire Wire Line
	3850 2950 3850 2000
Wire Wire Line
	3850 2000 4100 2000
Wire Wire Line
	7000 1150 6200 1150
Wire Wire Line
	6200 1650 6900 1650
Wire Wire Line
	6200 1750 6850 1750
Wire Wire Line
	6200 1850 6800 1850
Wire Wire Line
	7000 2750 6950 2750
Wire Wire Line
	6950 2750 6950 2350
Wire Wire Line
	6950 2350 7000 2350
Wire Wire Line
	7000 3100 6900 3100
Wire Wire Line
	6900 3100 6900 1650
Connection ~ 6900 1650
Wire Wire Line
	6900 1650 7000 1650
Wire Wire Line
	6850 1750 6850 3200
Wire Wire Line
	6850 3200 7000 3200
Connection ~ 6850 1750
Wire Wire Line
	6850 1750 7000 1750
Wire Wire Line
	7000 3300 6800 3300
Wire Wire Line
	6800 3300 6800 1850
Connection ~ 6800 1850
Wire Wire Line
	6800 1850 7000 1850
Wire Wire Line
	3750 3600 6300 3600
Wire Wire Line
	6300 3600 6300 2100
Wire Wire Line
	6300 2100 7000 2100
Wire Wire Line
	3750 3700 7000 3700
$Sheet
S 5300 4400 2050 1300
U 5D3E6616
F0 "power" 50
F1 "powersch.sch" 50
$EndSheet
$Sheet
S 2950 4400 1850 1300
U 5D3FB9A2
F0 "audio" 50
F1 "audio.sch" 50
$EndSheet
$EndSCHEMATC
