EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L Timer:ICM7555xB U1
U 1 1 61D34067
P 5750 1950
F 0 "U1" H 5750 2531 50  0000 C CNN
F 1 "ICM7555xB" H 5750 2440 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 6600 1550 50  0001 C CNN
F 3 "http://www.intersil.com/content/dam/Intersil/documents/icm7/icm7555-56.pdf" H 6600 1550 50  0001 C CNN
	1    5750 1950
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J2
U 1 1 61D353DC
P 7400 1950
F 0 "J2" H 7372 1832 50  0000 R CNN
F 1 "Conn_01x04_Male" H 7372 1923 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 7400 1950 50  0001 C CNN
F 3 "~" H 7400 1950 50  0001 C CNN
	1    7400 1950
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x04_Male J1
U 1 1 61D36F61
P 4100 1900
F 0 "J1" H 4208 2181 50  0000 C CNN
F 1 "Conn_01x04_Male" H 4208 2090 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 4100 1900 50  0001 C CNN
F 3 "~" H 4100 1900 50  0001 C CNN
	1    4100 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 1900 4600 1900
Wire Wire Line
	4300 2000 4600 2000
Wire Wire Line
	4300 2100 4600 2100
Wire Wire Line
	7200 1950 6950 1950
Wire Wire Line
	7200 2050 6950 2050
Text GLabel 4600 1800 2    50   Input ~ 0
1
Text GLabel 5750 2350 3    50   Input ~ 0
1
Text GLabel 4600 1900 2    50   Input ~ 0
2
Text GLabel 4600 2000 2    50   Input ~ 0
3
Text GLabel 4600 2100 2    50   Input ~ 0
4
Text GLabel 6950 1750 0    50   Input ~ 0
5
Text GLabel 6950 1850 0    50   Input ~ 0
6
Text GLabel 6950 1950 0    50   Input ~ 0
7
Text GLabel 6950 2050 0    50   Input ~ 0
8
Text GLabel 5250 1750 0    50   Input ~ 0
2
Text GLabel 6250 1750 2    50   Input ~ 0
3
Text GLabel 5250 2150 0    50   Input ~ 0
4
Text GLabel 5250 1950 0    50   Input ~ 0
5
Text GLabel 6250 2150 2    50   Input ~ 0
6
Text GLabel 6250 1950 2    50   Input ~ 0
7
Text GLabel 5750 1550 1    50   Input ~ 0
8
$Comp
L Connector:Conn_01x04_Male J3
U 1 1 61D4360E
P 3650 1900
F 0 "J3" H 3758 2181 50  0000 C CNN
F 1 "Conn_01x04_Male" H 3758 2090 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 3650 1900 50  0001 C CNN
F 3 "~" H 3650 1900 50  0001 C CNN
	1    3650 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 1800 4300 1800
Connection ~ 4300 1800
Wire Wire Line
	4300 1800 4600 1800
Wire Wire Line
	3850 1900 4300 1900
Connection ~ 4300 1900
Wire Wire Line
	3850 2000 4300 2000
Connection ~ 4300 2000
Wire Wire Line
	3850 2100 4300 2100
Connection ~ 4300 2100
$Comp
L Connector:Conn_01x04_Male J4
U 1 1 61D44E60
P 7800 1950
F 0 "J4" H 7772 1832 50  0000 R CNN
F 1 "Conn_01x04_Male" H 7772 1923 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 7800 1950 50  0001 C CNN
F 3 "~" H 7800 1950 50  0001 C CNN
	1    7800 1950
	-1   0    0    1   
$EndComp
Wire Wire Line
	6950 1750 7200 1750
Connection ~ 7200 1750
Wire Wire Line
	7200 1750 7600 1750
Wire Wire Line
	6950 1850 7200 1850
Connection ~ 7200 1850
Wire Wire Line
	7200 1850 7600 1850
Wire Wire Line
	7600 1950 7200 1950
Connection ~ 7200 1950
Wire Wire Line
	7600 2050 7200 2050
Connection ~ 7200 2050
$EndSCHEMATC
