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
U 1 1 61BC36D1
P 3800 2500
F 0 "U1" H 3800 3081 50  0000 C CNN
F 1 "ICM7555xB" H 3800 2990 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 4650 2100 50  0001 C CNN
F 3 "http://www.intersil.com/content/dam/Intersil/documents/icm7/icm7555-56.pdf" H 4650 2100 50  0001 C CNN
	1    3800 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 61BC4409
P 3800 3200
F 0 "#PWR03" H 3800 2950 50  0001 C CNN
F 1 "GND" H 3805 3027 50  0000 C CNN
F 2 "" H 3800 3200 50  0001 C CNN
F 3 "" H 3800 3200 50  0001 C CNN
	1    3800 3200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR02
U 1 1 61BC48AD
P 3800 1650
F 0 "#PWR02" H 3800 1500 50  0001 C CNN
F 1 "+5V" H 3815 1823 50  0000 C CNN
F 2 "" H 3800 1650 50  0001 C CNN
F 3 "" H 3800 1650 50  0001 C CNN
	1    3800 1650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR01
U 1 1 61BC4BAE
P 3050 2700
F 0 "#PWR01" H 3050 2550 50  0001 C CNN
F 1 "+5V" H 3065 2873 50  0000 C CNN
F 2 "" H 3050 2700 50  0001 C CNN
F 3 "" H 3050 2700 50  0001 C CNN
	1    3050 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 2100 3800 1800
Wire Wire Line
	3800 2900 3800 3200
Wire Wire Line
	3300 2700 3050 2700
$Comp
L Device:R R2
U 1 1 61BC5AA7
P 4950 2600
F 0 "R2" H 5020 2646 50  0000 L CNN
F 1 "3.3M" H 5020 2555 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 4880 2600 50  0001 C CNN
F 3 "~" H 4950 2600 50  0001 C CNN
	1    4950 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 2500 4550 2500
Wire Wire Line
	4550 2500 4550 2450
Wire Wire Line
	4300 2700 4550 2700
Wire Wire Line
	4550 2700 4550 2750
$Comp
L Device:R R1
U 1 1 61BC76FC
P 4950 2150
F 0 "R1" H 5020 2196 50  0000 L CNN
F 1 "220k" H 5020 2105 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 4880 2150 50  0001 C CNN
F 3 "~" H 4950 2150 50  0001 C CNN
	1    4950 2150
	1    0    0    -1  
$EndComp
Connection ~ 3800 1800
Wire Wire Line
	3800 1800 3800 1650
$Comp
L Device:D D1
U 1 1 61BC8092
P 4700 2600
F 0 "D1" V 4746 2520 50  0000 R CNN
F 1 "D" V 4655 2520 50  0000 R CNN
F 2 "Diode_SMD:D_1206_3216Metric" H 4700 2600 50  0001 C CNN
F 3 "~" H 4700 2600 50  0001 C CNN
	1    4700 2600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4950 2300 4950 2450
Connection ~ 4950 2450
Wire Wire Line
	4950 2000 4950 1800
Wire Wire Line
	3800 1800 4950 1800
Connection ~ 4700 2750
Wire Wire Line
	4700 2750 4950 2750
Connection ~ 4700 2450
Wire Wire Line
	4700 2450 4950 2450
Wire Wire Line
	4550 2450 4700 2450
Wire Wire Line
	4550 2750 4700 2750
$Comp
L Device:C C1
U 1 1 61BCD26F
P 4700 3000
F 0 "C1" H 4815 3046 50  0000 L CNN
F 1 "10uf" H 4815 2955 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-1608-10_AVX-L_Pad1.25x1.05mm_HandSolder" H 4738 2850 50  0001 C CNN
F 3 "~" H 4700 3000 50  0001 C CNN
	1    4700 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 2850 4700 2750
Wire Wire Line
	3800 3200 4700 3200
Wire Wire Line
	4700 3200 4700 3150
Connection ~ 3800 3200
Wire Wire Line
	4700 2850 4400 2850
Connection ~ 4700 2850
Wire Wire Line
	3300 2300 3000 2300
Text Label 3000 2300 0    50   ~ 0
trig
Text Label 4400 2850 0    50   ~ 0
trig
Wire Wire Line
	4300 2300 4550 2300
Text Label 4550 2300 0    50   ~ 0
output
NoConn ~ 3300 2500
Wire Wire Line
	5500 2850 5750 2850
$Comp
L Device:R R3
U 1 1 61BD0324
P 5900 2850
F 0 "R3" V 5693 2850 50  0000 C CNN
F 1 "4.7k" V 5784 2850 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 5830 2850 50  0001 C CNN
F 3 "~" H 5900 2850 50  0001 C CNN
	1    5900 2850
	0    1    1    0   
$EndComp
Text Label 5500 2850 0    50   ~ 0
output
$Comp
L Transistor_BJT:BC817 Q1
U 1 1 61BD0B9E
P 6550 2850
F 0 "Q1" H 6741 2896 50  0000 L CNN
F 1 "BC817" H 6741 2805 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6750 2775 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BC818-D.pdf" H 6550 2850 50  0001 L CNN
	1    6550 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 2850 6350 2850
Wire Wire Line
	6650 3200 4700 3200
Connection ~ 4700 3200
$Comp
L Device:R R4
U 1 1 61BD1AE1
P 6650 2050
F 0 "R4" H 6580 2004 50  0000 R CNN
F 1 "51" H 6580 2095 50  0000 R CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.40x3.35mm_HandSolder" V 6580 2050 50  0001 C CNN
F 3 "~" H 6650 2050 50  0001 C CNN
	1    6650 2050
	-1   0    0    1   
$EndComp
Wire Wire Line
	4950 1800 5400 1800
Wire Wire Line
	6650 1800 6650 1900
Connection ~ 4950 1800
$Comp
L Device:R R5
U 1 1 61BD7A70
P 7000 2050
F 0 "R5" H 7070 2096 50  0000 L CNN
F 1 "330" H 7070 2005 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 6930 2050 50  0001 C CNN
F 3 "~" H 7000 2050 50  0001 C CNN
	1    7000 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 1800 7000 1800
Wire Wire Line
	7000 1800 7000 1900
Connection ~ 6650 1800
$Comp
L Device:LED D2
U 1 1 61BD8B6D
P 7000 2350
F 0 "D2" V 7039 2232 50  0000 R CNN
F 1 "LED" V 6948 2232 50  0000 R CNN
F 2 "LED_SMD:LED_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 7000 2350 50  0001 C CNN
F 3 "~" H 7000 2350 50  0001 C CNN
	1    7000 2350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6650 3200 6650 3050
Wire Wire Line
	7000 2500 6650 2500
Wire Wire Line
	6650 2500 6650 2650
Wire Wire Line
	6650 2200 6650 2500
Connection ~ 6650 2500
$Comp
L Device:C C2
U 1 1 61BE12BE
P 5400 1950
F 0 "C2" H 5515 1996 50  0000 L CNN
F 1 "4.7uf" H 5515 1905 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 5438 1800 50  0001 C CNN
F 3 "~" H 5400 1950 50  0001 C CNN
	1    5400 1950
	1    0    0    -1  
$EndComp
Connection ~ 5400 1800
Wire Wire Line
	5400 1800 5850 1800
$Comp
L power:GND #PWR04
U 1 1 61BE193A
P 5400 2100
F 0 "#PWR04" H 5400 1850 50  0001 C CNN
F 1 "GND" H 5405 1927 50  0000 C CNN
F 2 "" H 5400 2100 50  0001 C CNN
F 3 "" H 5400 2100 50  0001 C CNN
	1    5400 2100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female J1
U 1 1 61BCFABB
P 2350 2200
F 0 "J1" H 2378 2176 50  0000 L CNN
F 1 "Conn_01x02_Female" H 2378 2085 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2350 2200 50  0001 C CNN
F 3 "~" H 2350 2200 50  0001 C CNN
	1    2350 2200
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female J2
U 1 1 61BCFDEC
P 2350 2500
F 0 "J2" H 2378 2476 50  0000 L CNN
F 1 "Conn_01x02_Female" H 2378 2385 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2350 2500 50  0001 C CNN
F 3 "~" H 2350 2500 50  0001 C CNN
	1    2350 2500
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0101
U 1 1 61BD07EE
P 2150 2200
F 0 "#PWR0101" H 2150 2050 50  0001 C CNN
F 1 "+5V" H 2165 2373 50  0000 C CNN
F 2 "" H 2150 2200 50  0001 C CNN
F 3 "" H 2150 2200 50  0001 C CNN
	1    2150 2200
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR0102
U 1 1 61BD16CD
P 2150 2500
F 0 "#PWR0102" H 2150 2350 50  0001 C CNN
F 1 "+5V" H 2165 2673 50  0000 C CNN
F 2 "" H 2150 2500 50  0001 C CNN
F 3 "" H 2150 2500 50  0001 C CNN
	1    2150 2500
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 61BD269E
P 2150 2600
F 0 "#PWR0103" H 2150 2350 50  0001 C CNN
F 1 "GND" H 2155 2427 50  0000 C CNN
F 2 "" H 2150 2600 50  0001 C CNN
F 3 "" H 2150 2600 50  0001 C CNN
	1    2150 2600
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 61BD351E
P 2150 2300
F 0 "#PWR0104" H 2150 2050 50  0001 C CNN
F 1 "GND" H 2155 2127 50  0000 C CNN
F 2 "" H 2150 2300 50  0001 C CNN
F 3 "" H 2150 2300 50  0001 C CNN
	1    2150 2300
	0    1    1    0   
$EndComp
$Comp
L Mechanical:MountingHole H1
U 1 1 61BD7754
P 4550 1400
F 0 "H1" H 4650 1446 50  0000 L CNN
F 1 "MountingHole" H 4650 1355 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_ISO7380_Pad_TopBottom" H 4550 1400 50  0001 C CNN
F 3 "~" H 4550 1400 50  0001 C CNN
	1    4550 1400
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 61BD9843
P 5300 1400
F 0 "H2" H 5400 1446 50  0000 L CNN
F 1 "MountingHole" H 5400 1355 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_ISO7380_Pad_TopBottom" H 5300 1400 50  0001 C CNN
F 3 "~" H 5300 1400 50  0001 C CNN
	1    5300 1400
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 61BD9D24
P 6000 1400
F 0 "H3" H 6100 1446 50  0000 L CNN
F 1 "MountingHole" H 6100 1355 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_ISO7380_Pad_TopBottom" H 6000 1400 50  0001 C CNN
F 3 "~" H 6000 1400 50  0001 C CNN
	1    6000 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 61BF0616
P 5850 1950
F 0 "C3" H 5965 1996 50  0000 L CNN
F 1 "4.7uf" H 5965 1905 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 5888 1800 50  0001 C CNN
F 3 "~" H 5850 1950 50  0001 C CNN
	1    5850 1950
	1    0    0    -1  
$EndComp
Connection ~ 5850 1800
Wire Wire Line
	5850 1800 6650 1800
$Comp
L power:GND #PWR0105
U 1 1 61BF0C7C
P 5850 2100
F 0 "#PWR0105" H 5850 1850 50  0001 C CNN
F 1 "GND" H 5855 1927 50  0000 C CNN
F 2 "" H 5850 2100 50  0001 C CNN
F 3 "" H 5850 2100 50  0001 C CNN
	1    5850 2100
	1    0    0    -1  
$EndComp
$EndSCHEMATC
