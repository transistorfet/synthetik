EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
Title "Synthetik"
Date ""
Rev "1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Connection ~ 2650 1400
$Comp
L power:GND #PWR?
U 1 1 604D9965
P 3000 1700
AR Path="/5FB17596/604D9965" Ref="#PWR?"  Part="1" 
AR Path="/604A78D6/604D9965" Ref="#PWR?"  Part="1" 
AR Path="/604AEF91/604D9965" Ref="#PWR036"  Part="1" 
F 0 "#PWR036" H 3000 1450 50  0001 C CNN
F 1 "GND" H 3005 1527 50  0000 C CNN
F 2 "" H 3000 1700 50  0001 C CNN
F 3 "" H 3000 1700 50  0001 C CNN
	1    3000 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 1700 3000 1600
Wire Wire Line
	3000 1600 3100 1600
Wire Wire Line
	2650 1400 3000 1400
$Comp
L Device:R_Small R?
U 1 1 604D996E
P 3350 1100
AR Path="/5FB17596/604D996E" Ref="R?"  Part="1" 
AR Path="/604A78D6/604D996E" Ref="R?"  Part="1" 
AR Path="/604AEF91/604D996E" Ref="R18"  Part="1" 
F 0 "R18" V 3275 1100 50  0000 C CNN
F 1 "10k" V 3425 1100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 3350 1100 50  0001 C CNN
F 3 "~" H 3350 1100 50  0001 C CNN
	1    3350 1100
	0    1    1    0   
$EndComp
Wire Wire Line
	3250 1100 3000 1100
Wire Wire Line
	3000 1100 3000 1400
Connection ~ 3000 1400
Wire Wire Line
	3000 1400 3100 1400
Wire Wire Line
	3450 1100 3700 1100
Wire Wire Line
	3700 1100 3700 1500
$Comp
L power:GND #PWR?
U 1 1 604D99AB
P 4450 2150
AR Path="/5FB17596/604D99AB" Ref="#PWR?"  Part="1" 
AR Path="/604A78D6/604D99AB" Ref="#PWR?"  Part="1" 
AR Path="/604AEF91/604D99AB" Ref="#PWR040"  Part="1" 
F 0 "#PWR040" H 4450 1900 50  0001 C CNN
F 1 "GND" H 4550 2050 50  0000 C CNN
F 2 "" H 4450 2150 50  0001 C CNN
F 3 "" H 4450 2150 50  0001 C CNN
	1    4450 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 604D99C9
P 2650 5000
AR Path="/5FB17596/604D99C9" Ref="C?"  Part="1" 
AR Path="/604A78D6/604D99C9" Ref="C?"  Part="1" 
AR Path="/604AEF91/604D99C9" Ref="C16"  Part="1" 
F 0 "C16" H 2742 5046 50  0000 L CNN
F 1 "0.1uF" H 2742 4955 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 2650 5000 50  0001 C CNN
F 3 "~" H 2650 5000 50  0001 C CNN
	1    2650 5000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 604D99CF
P 3450 5400
AR Path="/5FB17596/604D99CF" Ref="#PWR?"  Part="1" 
AR Path="/604A78D6/604D99CF" Ref="#PWR?"  Part="1" 
AR Path="/604AEF91/604D99CF" Ref="#PWR039"  Part="1" 
F 0 "#PWR039" H 3450 5150 50  0001 C CNN
F 1 "GND" H 3455 5227 50  0000 C CNN
F 2 "" H 3450 5400 50  0001 C CNN
F 3 "" H 3450 5400 50  0001 C CNN
	1    3450 5400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 604D99D5
P 3450 4550
AR Path="/5FB17596/604D99D5" Ref="#PWR?"  Part="1" 
AR Path="/604A78D6/604D99D5" Ref="#PWR?"  Part="1" 
AR Path="/604AEF91/604D99D5" Ref="#PWR038"  Part="1" 
F 0 "#PWR038" H 3450 4400 50  0001 C CNN
F 1 "+5V" H 3465 4723 50  0000 C CNN
F 2 "" H 3450 4550 50  0001 C CNN
F 3 "" H 3450 4550 50  0001 C CNN
	1    3450 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 604D99DB
P 3450 5000
AR Path="/5FB17596/604D99DB" Ref="C?"  Part="1" 
AR Path="/604A78D6/604D99DB" Ref="C?"  Part="1" 
AR Path="/604AEF91/604D99DB" Ref="C17"  Part="1" 
F 0 "C17" H 3542 5046 50  0000 L CNN
F 1 "0.1uF" H 3542 4955 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 3450 5000 50  0001 C CNN
F 3 "~" H 3450 5000 50  0001 C CNN
	1    3450 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 4550 3050 4700
Wire Wire Line
	3050 5400 3050 5300
Wire Wire Line
	2650 4900 2650 4550
Connection ~ 2650 4550
Wire Wire Line
	3450 4900 3450 4550
Wire Wire Line
	3450 4550 3050 4550
Connection ~ 3050 4550
Wire Wire Line
	3050 5400 3450 5400
Wire Wire Line
	3450 5400 3450 5100
Connection ~ 3050 5400
Wire Wire Line
	2650 5100 2650 5400
Connection ~ 2650 5400
$Comp
L Amplifier_Operational:TL074 U?
U 1 1 604D99FD
P 3400 1500
AR Path="/5FB17596/604D99FD" Ref="U?"  Part="3" 
AR Path="/604A78D6/604D99FD" Ref="U?"  Part="3" 
AR Path="/604AEF91/604D99FD" Ref="U5"  Part="1" 
F 0 "U5" H 3400 1867 50  0000 C CNN
F 1 "TL074" H 3400 1776 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm_Socket_LongPads" H 3350 1600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 3450 1700 50  0001 C CNN
	1    3400 1500
	1    0    0    1   
$EndComp
$Comp
L Amplifier_Operational:TL074 U?
U 5 1 604D9A0F
P 3150 5000
AR Path="/5FB17596/604D9A0F" Ref="U?"  Part="5" 
AR Path="/604A78D6/604D9A0F" Ref="U?"  Part="5" 
AR Path="/604AEF91/604D9A0F" Ref="U10"  Part="5" 
F 0 "U10" H 3100 5050 50  0000 L CNN
F 1 "TL074" H 3100 4950 50  0000 L CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 3100 5100 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 3200 5200 50  0001 C CNN
	5    3150 5000
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Audio:TDA1308 U?
U 3 1 604D9A15
P 3950 5000
AR Path="/5FB17596/604D9A15" Ref="U?"  Part="3" 
AR Path="/604A78D6/604D9A15" Ref="U?"  Part="3" 
AR Path="/604AEF91/604D9A15" Ref="U11"  Part="3" 
F 0 "U11" H 3908 5046 50  0000 L CNN
F 1 "TDA1308" H 3908 4955 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm_Socket_LongPads" H 3950 5000 50  0001 C CIN
F 3 "https://www.nxp.com/docs/en/data-sheet/TDA1308.pdf" H 3950 5000 50  0001 C CNN
	3    3950 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 604D9A21
P 4350 5000
AR Path="/5FB17596/604D9A21" Ref="C?"  Part="1" 
AR Path="/604A78D6/604D9A21" Ref="C?"  Part="1" 
AR Path="/604AEF91/604D9A21" Ref="C20"  Part="1" 
F 0 "C20" H 4442 5046 50  0000 L CNN
F 1 "0.1uF" H 4442 4955 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 4350 5000 50  0001 C CNN
F 3 "~" H 4350 5000 50  0001 C CNN
	1    4350 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 4550 3850 4700
Connection ~ 3450 4550
Wire Wire Line
	3850 4550 4350 4550
Wire Wire Line
	4350 4550 4350 4900
Wire Wire Line
	4350 5100 4350 5400
Wire Wire Line
	4350 5400 3850 5400
Connection ~ 3450 5400
Wire Wire Line
	3850 5300 3850 5400
$Comp
L Device:C_Small C?
U 1 1 604D9A33
P 4750 5000
AR Path="/5FB17596/604D9A33" Ref="C?"  Part="1" 
AR Path="/604A78D6/604D9A33" Ref="C?"  Part="1" 
AR Path="/604AEF91/604D9A33" Ref="C21"  Part="1" 
F 0 "C21" H 4842 5046 50  0000 L CNN
F 1 "100uF" H 4842 4955 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 4750 5000 50  0001 C CNN
F 3 "~" H 4750 5000 50  0001 C CNN
	1    4750 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 4550 4750 4900
Wire Wire Line
	4750 5100 4750 5400
Wire Wire Line
	4350 4550 4750 4550
Connection ~ 4350 4550
Wire Wire Line
	4750 5400 4350 5400
Connection ~ 4350 5400
Wire Wire Line
	2650 4550 3050 4550
Wire Wire Line
	2650 5400 3050 5400
$Comp
L Amplifier_Operational:TL074 U?
U 5 1 604D9A03
P 2350 5000
AR Path="/5FB17596/604D9A03" Ref="U?"  Part="5" 
AR Path="/604A78D6/604D9A03" Ref="U?"  Part="5" 
AR Path="/604AEF91/604D9A03" Ref="U5"  Part="5" 
F 0 "U5" H 2300 5050 50  0000 L CNN
F 1 "TL074" H 2300 4950 50  0000 L CNN
F 2 "Package_DIP:DIP-14_W7.62mm_Socket_LongPads" H 2300 5100 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 2400 5200 50  0001 C CNN
	5    2350 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 5400 2650 5400
Wire Wire Line
	2250 5300 2250 5400
Wire Wire Line
	2250 4550 2650 4550
Wire Wire Line
	2250 4700 2250 4550
Wire Wire Line
	3850 4550 3450 4550
Connection ~ 3850 4550
Wire Wire Line
	3450 5400 3850 5400
Connection ~ 3850 5400
$Comp
L power:GND #PWR?
U 1 1 604D997C
P 3000 3400
AR Path="/5FB17596/604D997C" Ref="#PWR?"  Part="1" 
AR Path="/604A78D6/604D997C" Ref="#PWR?"  Part="1" 
AR Path="/604AEF91/604D997C" Ref="#PWR037"  Part="1" 
F 0 "#PWR037" H 3000 3150 50  0001 C CNN
F 1 "GND" H 3005 3227 50  0000 C CNN
F 2 "" H 3000 3400 50  0001 C CNN
F 3 "" H 3000 3400 50  0001 C CNN
	1    3000 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 3400 3000 3300
Wire Wire Line
	3000 3300 3100 3300
$Comp
L Device:R_Small R?
U 1 1 604D9985
P 3350 2800
AR Path="/5FB17596/604D9985" Ref="R?"  Part="1" 
AR Path="/604A78D6/604D9985" Ref="R?"  Part="1" 
AR Path="/604AEF91/604D9985" Ref="R19"  Part="1" 
F 0 "R19" V 3275 2800 50  0000 C CNN
F 1 "10k" V 3425 2800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 3350 2800 50  0001 C CNN
F 3 "~" H 3350 2800 50  0001 C CNN
	1    3350 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	3250 2800 3000 2800
Wire Wire Line
	3000 3100 3100 3100
Wire Wire Line
	3450 2800 3700 2800
Wire Wire Line
	3700 2800 3700 3200
$Comp
L Amplifier_Operational:TL074 U?
U 2 1 604D9A09
P 3400 3200
AR Path="/5FB17596/604D9A09" Ref="U?"  Part="4" 
AR Path="/604A78D6/604D9A09" Ref="U?"  Part="4" 
AR Path="/604AEF91/604D9A09" Ref="U5"  Part="2" 
F 0 "U5" H 3400 3567 50  0000 C CNN
F 1 "TL074" H 3400 3476 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm_Socket_LongPads" H 3350 3300 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 3450 3400 50  0001 C CNN
	2    3400 3200
	1    0    0    1   
$EndComp
Text GLabel 1800 1200 0    50   Input ~ 0
A2-LEFT
Text GLabel 1800 800  0    50   Input ~ 0
A1-OUT
$Comp
L Device:R_Small R?
U 1 1 604D9947
P 2400 1200
AR Path="/5FB17596/604D9947" Ref="R?"  Part="1" 
AR Path="/604A78D6/604D9947" Ref="R?"  Part="1" 
AR Path="/604AEF91/604D9947" Ref="R11"  Part="1" 
F 0 "R11" V 2325 1200 50  0000 C CNN
F 1 "10k" V 2475 1200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 2400 1200 50  0001 C CNN
F 3 "~" H 2400 1200 50  0001 C CNN
	1    2400 1200
	0    1    1    0   
$EndComp
Wire Wire Line
	1800 1200 2000 1200
Wire Wire Line
	2500 1200 2650 1200
Wire Wire Line
	2500 800  2650 800 
Wire Wire Line
	1800 800  2000 800 
$Comp
L Device:R_Small R?
U 1 1 604D999E
P 2400 800
AR Path="/5FB17596/604D999E" Ref="R?"  Part="1" 
AR Path="/604A78D6/604D999E" Ref="R?"  Part="1" 
AR Path="/604AEF91/604D999E" Ref="R10"  Part="1" 
F 0 "R10" V 2325 800 50  0000 C CNN
F 1 "10k" V 2475 800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 2400 800 50  0001 C CNN
F 3 "~" H 2400 800 50  0001 C CNN
	1    2400 800 
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 606A1EC1
P 2100 800
AR Path="/5FB17596/606A1EC1" Ref="C?"  Part="1" 
AR Path="/604A78D6/606A1EC1" Ref="C?"  Part="1" 
AR Path="/604AEF91/606A1EC1" Ref="C8"  Part="1" 
F 0 "C8" V 1975 800 50  0000 C CNN
F 1 "10uF" V 2225 800 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 2100 800 50  0001 C CNN
F 3 "~" H 2100 800 50  0001 C CNN
	1    2100 800 
	0    -1   1    0   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 606A9B80
P 2100 1200
AR Path="/5FB17596/606A9B80" Ref="C?"  Part="1" 
AR Path="/604A78D6/606A9B80" Ref="C?"  Part="1" 
AR Path="/604AEF91/606A9B80" Ref="C9"  Part="1" 
F 0 "C9" V 1975 1200 50  0000 C CNN
F 1 "10uF" V 2225 1200 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 2100 1200 50  0001 C CNN
F 3 "~" H 2100 1200 50  0001 C CNN
	1    2100 1200
	0    -1   1    0   
$EndComp
Wire Wire Line
	2200 800  2300 800 
Wire Wire Line
	2300 1200 2200 1200
Wire Wire Line
	2650 1200 2650 1400
Connection ~ 2650 1200
Wire Wire Line
	2650 800  2650 1200
Text GLabel 1800 1600 0    50   Input ~ 0
A3-OUT
$Comp
L Device:R_Small R?
U 1 1 604D9936
P 2400 1600
AR Path="/5FB17596/604D9936" Ref="R?"  Part="1" 
AR Path="/604A78D6/604D9936" Ref="R?"  Part="1" 
AR Path="/604AEF91/604D9936" Ref="R12"  Part="1" 
F 0 "R12" V 2325 1600 50  0000 C CNN
F 1 "10k" V 2475 1600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 2400 1600 50  0001 C CNN
F 3 "~" H 2400 1600 50  0001 C CNN
	1    2400 1600
	0    1    1    0   
$EndComp
Wire Wire Line
	1800 1600 2000 1600
Wire Wire Line
	2500 1600 2650 1600
Wire Wire Line
	2650 1400 2650 1600
$Comp
L Device:C_Small C?
U 1 1 604D99C3
P 2100 1600
AR Path="/5FB17596/604D99C3" Ref="C?"  Part="1" 
AR Path="/604A78D6/604D99C3" Ref="C?"  Part="1" 
AR Path="/604AEF91/604D99C3" Ref="C10"  Part="1" 
F 0 "C10" V 1975 1600 50  0000 C CNN
F 1 "10uF" V 2225 1600 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 2100 1600 50  0001 C CNN
F 3 "~" H 2100 1600 50  0001 C CNN
	1    2100 1600
	0    -1   1    0   
$EndComp
Wire Wire Line
	2200 1600 2300 1600
$Comp
L Device:R_Small R?
U 1 1 5FBAFBF5
P 2400 2000
AR Path="/5FB17596/5FBAFBF5" Ref="R?"  Part="1" 
AR Path="/604A78D6/5FBAFBF5" Ref="R?"  Part="1" 
AR Path="/604AEF91/5FBAFBF5" Ref="R13"  Part="1" 
F 0 "R13" V 2325 2000 50  0000 C CNN
F 1 "10k" V 2475 2000 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 2400 2000 50  0001 C CNN
F 3 "~" H 2400 2000 50  0001 C CNN
	1    2400 2000
	0    1    1    0   
$EndComp
Wire Wire Line
	1800 2000 2000 2000
Wire Wire Line
	2500 2000 2650 2000
$Comp
L Device:C_Small C?
U 1 1 5FBAFC01
P 2100 2000
AR Path="/5FB17596/5FBAFC01" Ref="C?"  Part="1" 
AR Path="/604A78D6/5FBAFC01" Ref="C?"  Part="1" 
AR Path="/604AEF91/5FBAFC01" Ref="C11"  Part="1" 
F 0 "C11" V 1975 2000 50  0000 C CNN
F 1 "10uF" V 2225 2000 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 2100 2000 50  0001 C CNN
F 3 "~" H 2100 2000 50  0001 C CNN
	1    2100 2000
	0    -1   1    0   
$EndComp
Wire Wire Line
	2200 2000 2300 2000
Connection ~ 2650 1600
Wire Wire Line
	2650 1600 2650 2000
Text GLabel 1800 2900 0    50   Input ~ 0
A2-RIGHT
Text GLabel 1800 3300 0    50   Input ~ 0
A3-OUT
$Comp
L Device:R_Small R?
U 1 1 604D993C
P 2400 3300
AR Path="/5FB17596/604D993C" Ref="R?"  Part="1" 
AR Path="/604A78D6/604D993C" Ref="R?"  Part="1" 
AR Path="/604AEF91/604D993C" Ref="R16"  Part="1" 
F 0 "R16" V 2325 3300 50  0000 C CNN
F 1 "10k" V 2475 3300 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 2400 3300 50  0001 C CNN
F 3 "~" H 2400 3300 50  0001 C CNN
	1    2400 3300
	0    1    1    0   
$EndComp
Wire Wire Line
	1800 3300 2000 3300
Wire Wire Line
	2500 3300 2650 3300
Text GLabel 1800 2500 0    50   Input ~ 0
A1-OUT
$Comp
L Device:R_Small R?
U 1 1 604D9952
P 2400 2900
AR Path="/5FB17596/604D9952" Ref="R?"  Part="1" 
AR Path="/604A78D6/604D9952" Ref="R?"  Part="1" 
AR Path="/604AEF91/604D9952" Ref="R15"  Part="1" 
F 0 "R15" V 2325 2900 50  0000 C CNN
F 1 "10k" V 2475 2900 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 2400 2900 50  0001 C CNN
F 3 "~" H 2400 2900 50  0001 C CNN
	1    2400 2900
	0    1    1    0   
$EndComp
Wire Wire Line
	1800 2900 2000 2900
Wire Wire Line
	2500 2900 2650 2900
$Comp
L Device:R_Small R?
U 1 1 604D995A
P 2400 2500
AR Path="/5FB17596/604D995A" Ref="R?"  Part="1" 
AR Path="/604A78D6/604D995A" Ref="R?"  Part="1" 
AR Path="/604AEF91/604D995A" Ref="R14"  Part="1" 
F 0 "R14" V 2325 2500 50  0000 C CNN
F 1 "10k" V 2475 2500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 2400 2500 50  0001 C CNN
F 3 "~" H 2400 2500 50  0001 C CNN
	1    2400 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	1800 2500 2000 2500
Wire Wire Line
	2500 2500 2650 2500
Wire Wire Line
	2650 2500 2650 2900
Connection ~ 2650 2900
$Comp
L Device:C_Small C?
U 1 1 606BB744
P 2100 2500
AR Path="/5FB17596/606BB744" Ref="C?"  Part="1" 
AR Path="/604A78D6/606BB744" Ref="C?"  Part="1" 
AR Path="/604AEF91/606BB744" Ref="C12"  Part="1" 
F 0 "C12" V 1975 2500 50  0000 C CNN
F 1 "10uF" V 2225 2500 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 2100 2500 50  0001 C CNN
F 3 "~" H 2100 2500 50  0001 C CNN
	1    2100 2500
	0    -1   1    0   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 606BBCD0
P 2100 2900
AR Path="/5FB17596/606BBCD0" Ref="C?"  Part="1" 
AR Path="/604A78D6/606BBCD0" Ref="C?"  Part="1" 
AR Path="/604AEF91/606BBCD0" Ref="C13"  Part="1" 
F 0 "C13" V 1975 2900 50  0000 C CNN
F 1 "10uF" V 2225 2900 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 2100 2900 50  0001 C CNN
F 3 "~" H 2100 2900 50  0001 C CNN
	1    2100 2900
	0    -1   1    0   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 606C2067
P 2100 3300
AR Path="/5FB17596/606C2067" Ref="C?"  Part="1" 
AR Path="/604A78D6/606C2067" Ref="C?"  Part="1" 
AR Path="/604AEF91/606C2067" Ref="C14"  Part="1" 
F 0 "C14" V 1975 3300 50  0000 C CNN
F 1 "10uF" V 2225 3300 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 2100 3300 50  0001 C CNN
F 3 "~" H 2100 3300 50  0001 C CNN
	1    2100 3300
	0    -1   1    0   
$EndComp
Wire Wire Line
	2300 2500 2200 2500
Wire Wire Line
	2200 2900 2300 2900
Wire Wire Line
	2300 3300 2200 3300
$Comp
L Device:R_Small R?
U 1 1 5FBD408E
P 2400 3700
AR Path="/5FB17596/5FBD408E" Ref="R?"  Part="1" 
AR Path="/604A78D6/5FBD408E" Ref="R?"  Part="1" 
AR Path="/604AEF91/5FBD408E" Ref="R17"  Part="1" 
F 0 "R17" V 2325 3700 50  0000 C CNN
F 1 "10k" V 2475 3700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 2400 3700 50  0001 C CNN
F 3 "~" H 2400 3700 50  0001 C CNN
	1    2400 3700
	0    1    1    0   
$EndComp
Wire Wire Line
	1800 3700 2000 3700
Wire Wire Line
	2500 3700 2650 3700
Wire Wire Line
	2650 3300 2650 3700
$Comp
L Device:C_Small C?
U 1 1 5FBD409B
P 2100 3700
AR Path="/5FB17596/5FBD409B" Ref="C?"  Part="1" 
AR Path="/604A78D6/5FBD409B" Ref="C?"  Part="1" 
AR Path="/604AEF91/5FBD409B" Ref="C15"  Part="1" 
F 0 "C15" V 1975 3700 50  0000 C CNN
F 1 "10uF" V 2225 3700 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 2100 3700 50  0001 C CNN
F 3 "~" H 2100 3700 50  0001 C CNN
	1    2100 3700
	0    -1   1    0   
$EndComp
Wire Wire Line
	2300 3700 2200 3700
Connection ~ 2650 3300
Wire Wire Line
	2650 3100 3000 3100
Wire Wire Line
	2650 2900 2650 3100
Wire Wire Line
	2650 3100 2650 3300
Connection ~ 2650 3100
Connection ~ 3000 3100
Wire Wire Line
	3000 2800 3000 3100
Text GLabel 1800 2000 0    50   Input ~ 0
A4-LEFT
Text GLabel 1800 3700 0    50   Input ~ 0
A4-RIGHT
$Comp
L Amplifier_Audio:TDA1308 U?
U 1 1 604D9A1B
P 8400 1900
AR Path="/5FB17596/604D9A1B" Ref="U?"  Part="1" 
AR Path="/604A78D6/604D9A1B" Ref="U?"  Part="1" 
AR Path="/604AEF91/604D9A1B" Ref="U11"  Part="1" 
F 0 "U11" H 8500 1750 50  0000 C CNN
F 1 "TDA1308" H 8550 2050 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm_Socket_LongPads" H 8400 1900 50  0001 C CIN
F 3 "https://www.nxp.com/docs/en/data-sheet/TDA1308.pdf" H 8400 1900 50  0001 C CNN
	1    8400 1900
	1    0    0    1   
$EndComp
Wire Wire Line
	8100 2500 8000 2500
Wire Wire Line
	8000 2500 8000 2250
Wire Wire Line
	8000 2000 8100 2000
$Comp
L Device:R_Small R?
U 1 1 6055F831
P 8350 2950
AR Path="/5FB17596/6055F831" Ref="R?"  Part="1" 
AR Path="/604A78D6/6055F831" Ref="R?"  Part="1" 
AR Path="/604AEF91/6055F831" Ref="R25"  Part="1" 
F 0 "R25" V 8275 2950 50  0000 C CNN
F 1 "3.9k" V 8425 2950 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 8350 2950 50  0001 C CNN
F 3 "~" H 8350 2950 50  0001 C CNN
	1    8350 2950
	0    1    1    0   
$EndComp
Wire Wire Line
	8250 2950 8000 2950
Wire Wire Line
	8450 2950 8700 2950
Wire Wire Line
	8700 2950 8700 2600
Wire Wire Line
	8000 2950 8000 2700
Wire Wire Line
	8000 2700 8100 2700
$Comp
L Device:R_Small R?
U 1 1 6056562F
P 7800 2950
AR Path="/5FB17596/6056562F" Ref="R?"  Part="1" 
AR Path="/604A78D6/6056562F" Ref="R?"  Part="1" 
AR Path="/604AEF91/6056562F" Ref="R23"  Part="1" 
F 0 "R23" V 7725 2950 50  0000 C CNN
F 1 "3.9k" V 7875 2950 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 7800 2950 50  0001 C CNN
F 3 "~" H 7800 2950 50  0001 C CNN
	1    7800 2950
	0    1    1    0   
$EndComp
Wire Wire Line
	8000 2950 7900 2950
$Comp
L Connector:AudioJack3 J?
U 1 1 60595E21
P 9650 2000
AR Path="/5FB17596/60595E21" Ref="J?"  Part="1" 
AR Path="/604A78D6/60595E21" Ref="J?"  Part="1" 
AR Path="/604AEF91/60595E21" Ref="J3"  Part="1" 
F 0 "J3" H 9370 1933 50  0000 R CNN
F 1 "Headphones" H 9370 2024 50  0000 R CNN
F 2 "Connector_Audio:Jack_3.5mm_CUI_SJ1-3533NG_Horizontal" H 9650 2000 50  0001 C CNN
F 3 "~" H 9650 2000 50  0001 C CNN
	1    9650 2000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6059619F
P 9350 2150
AR Path="/5FB17596/6059619F" Ref="#PWR?"  Part="1" 
AR Path="/604A78D6/6059619F" Ref="#PWR?"  Part="1" 
AR Path="/604AEF91/6059619F" Ref="#PWR045"  Part="1" 
F 0 "#PWR045" H 9350 1900 50  0001 C CNN
F 1 "GND" H 9355 1977 50  0000 C CNN
F 2 "" H 9350 2150 50  0001 C CNN
F 3 "" H 9350 2150 50  0001 C CNN
	1    9350 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 2150 9350 2100
Wire Wire Line
	9350 2100 9450 2100
$Comp
L Device:C_Small C?
U 1 1 605A6CDE
P 8950 1900
AR Path="/5FB17596/605A6CDE" Ref="C?"  Part="1" 
AR Path="/604A78D6/605A6CDE" Ref="C?"  Part="1" 
AR Path="/604AEF91/605A6CDE" Ref="C25"  Part="1" 
F 0 "C25" V 8825 1900 50  0000 C CNN
F 1 "100uF" V 9075 1900 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 8950 1900 50  0001 C CNN
F 3 "~" H 8950 1900 50  0001 C CNN
	1    8950 1900
	0    -1   1    0   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 605A8304
P 8950 2600
AR Path="/5FB17596/605A8304" Ref="C?"  Part="1" 
AR Path="/604A78D6/605A8304" Ref="C?"  Part="1" 
AR Path="/604AEF91/605A8304" Ref="C26"  Part="1" 
F 0 "C26" V 8825 2600 50  0000 C CNN
F 1 "100uF" V 9075 2600 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 8950 2600 50  0001 C CNN
F 3 "~" H 8950 2600 50  0001 C CNN
	1    8950 2600
	0    -1   1    0   
$EndComp
Wire Wire Line
	8700 1900 8850 1900
Wire Wire Line
	8700 2600 8850 2600
Connection ~ 8700 2600
Wire Wire Line
	9050 1900 9450 1900
Wire Wire Line
	9050 2600 9200 2600
Wire Wire Line
	9200 2600 9200 2000
Wire Wire Line
	9200 2000 9450 2000
$Comp
L Device:R_Small R?
U 1 1 605B79B0
P 8350 1550
AR Path="/5FB17596/605B79B0" Ref="R?"  Part="1" 
AR Path="/604A78D6/605B79B0" Ref="R?"  Part="1" 
AR Path="/604AEF91/605B79B0" Ref="R24"  Part="1" 
F 0 "R24" V 8275 1550 50  0000 C CNN
F 1 "3.9k" V 8425 1550 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 8350 1550 50  0001 C CNN
F 3 "~" H 8350 1550 50  0001 C CNN
	1    8350 1550
	0    1    1    0   
$EndComp
Wire Wire Line
	8250 1550 8000 1550
Wire Wire Line
	8450 1550 8700 1550
Wire Wire Line
	8700 1550 8700 1900
Connection ~ 8700 1900
Wire Wire Line
	8000 1550 8000 1800
Wire Wire Line
	8000 1800 8100 1800
$Comp
L Device:R_Small R?
U 1 1 605C74FF
P 7800 1550
AR Path="/5FB17596/605C74FF" Ref="R?"  Part="1" 
AR Path="/604A78D6/605C74FF" Ref="R?"  Part="1" 
AR Path="/604AEF91/605C74FF" Ref="R22"  Part="1" 
F 0 "R22" V 7725 1550 50  0000 C CNN
F 1 "3.9k" V 7875 1550 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 7800 1550 50  0001 C CNN
F 3 "~" H 7800 1550 50  0001 C CNN
	1    7800 1550
	0    1    1    0   
$EndComp
Wire Wire Line
	8000 1550 7900 1550
Connection ~ 8000 1550
$Comp
L Device:C_Small C?
U 1 1 605CD161
P 7450 1550
AR Path="/5FB17596/605CD161" Ref="C?"  Part="1" 
AR Path="/604A78D6/605CD161" Ref="C?"  Part="1" 
AR Path="/604AEF91/605CD161" Ref="C23"  Part="1" 
F 0 "C23" V 7325 1550 50  0000 C CNN
F 1 "1uF" V 7575 1550 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 7450 1550 50  0001 C CNN
F 3 "~" H 7450 1550 50  0001 C CNN
	1    7450 1550
	0    -1   1    0   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 605CD8CF
P 7450 2950
AR Path="/5FB17596/605CD8CF" Ref="C?"  Part="1" 
AR Path="/604A78D6/605CD8CF" Ref="C?"  Part="1" 
AR Path="/604AEF91/605CD8CF" Ref="C24"  Part="1" 
F 0 "C24" V 7325 2950 50  0000 C CNN
F 1 "1uF" V 7575 2950 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 7450 2950 50  0001 C CNN
F 3 "~" H 7450 2950 50  0001 C CNN
	1    7450 2950
	0    -1   1    0   
$EndComp
Wire Wire Line
	7550 2950 7700 2950
Wire Wire Line
	7700 1550 7550 1550
Text GLabel 6800 2950 0    50   Input ~ 0
AOUT-RIGHT
Text GLabel 6800 1550 0    50   Input ~ 0
AOUT-LEFT
Wire Wire Line
	6800 2950 6900 2950
$Comp
L Device:R_Small R?
U 1 1 6062EF83
P 7700 2400
AR Path="/5FB17596/6062EF83" Ref="R?"  Part="1" 
AR Path="/604A78D6/6062EF83" Ref="R?"  Part="1" 
AR Path="/604AEF91/6062EF83" Ref="R21"  Part="1" 
F 0 "R21" H 7759 2446 50  0000 L CNN
F 1 "10k" H 7759 2355 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 7700 2400 50  0001 C CNN
F 3 "~" H 7700 2400 50  0001 C CNN
	1    7700 2400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60631DAC
P 7700 2100
AR Path="/5FB17596/60631DAC" Ref="R?"  Part="1" 
AR Path="/604A78D6/60631DAC" Ref="R?"  Part="1" 
AR Path="/604AEF91/60631DAC" Ref="R20"  Part="1" 
F 0 "R20" H 7759 2146 50  0000 L CNN
F 1 "10k" H 7759 2055 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 7700 2100 50  0001 C CNN
F 3 "~" H 7700 2100 50  0001 C CNN
	1    7700 2100
	1    0    0    -1  
$EndComp
Connection ~ 8000 2950
Wire Wire Line
	7700 2300 7700 2250
Wire Wire Line
	7700 2250 8000 2250
Connection ~ 7700 2250
Wire Wire Line
	7700 2250 7700 2200
Connection ~ 8000 2250
Wire Wire Line
	8000 2250 8000 2000
$Comp
L Device:C_Small C?
U 1 1 60647A5D
P 7350 2400
AR Path="/5FB17596/60647A5D" Ref="C?"  Part="1" 
AR Path="/604A78D6/60647A5D" Ref="C?"  Part="1" 
AR Path="/604AEF91/60647A5D" Ref="C22"  Part="1" 
F 0 "C22" H 7442 2446 50  0000 L CNN
F 1 "22uF" H 7442 2355 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 7350 2400 50  0001 C CNN
F 3 "~" H 7350 2400 50  0001 C CNN
	1    7350 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 2300 7350 2250
Wire Wire Line
	7350 2250 7700 2250
$Comp
L power:GND #PWR?
U 1 1 60651F9C
P 7700 2600
AR Path="/5FB17596/60651F9C" Ref="#PWR?"  Part="1" 
AR Path="/604A78D6/60651F9C" Ref="#PWR?"  Part="1" 
AR Path="/604AEF91/60651F9C" Ref="#PWR044"  Part="1" 
F 0 "#PWR044" H 7700 2350 50  0001 C CNN
F 1 "GND" H 7705 2427 50  0000 C CNN
F 2 "" H 7700 2600 50  0001 C CNN
F 3 "" H 7700 2600 50  0001 C CNN
	1    7700 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 2550 7700 2500
Wire Wire Line
	7350 2500 7350 2550
Wire Wire Line
	7350 2550 7700 2550
Connection ~ 7700 2550
Wire Wire Line
	7700 2600 7700 2550
$Comp
L power:+5V #PWR?
U 1 1 606518B2
P 7700 2000
AR Path="/5FB17596/606518B2" Ref="#PWR?"  Part="1" 
AR Path="/604A78D6/606518B2" Ref="#PWR?"  Part="1" 
AR Path="/604AEF91/606518B2" Ref="#PWR043"  Part="1" 
F 0 "#PWR043" H 7700 1850 50  0001 C CNN
F 1 "+5V" H 7715 2173 50  0000 C CNN
F 2 "" H 7700 2000 50  0001 C CNN
F 3 "" H 7700 2000 50  0001 C CNN
	1    7700 2000
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Audio:TDA1308 U?
U 2 1 604D99F7
P 8400 2600
AR Path="/5FB17596/604D99F7" Ref="U?"  Part="2" 
AR Path="/604A78D6/604D99F7" Ref="U?"  Part="2" 
AR Path="/604AEF91/604D99F7" Ref="U11"  Part="2" 
F 0 "U11" H 8400 2967 50  0000 C CNN
F 1 "TDA1308" H 8400 2876 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm_Socket_LongPads" H 8400 2600 50  0001 C CIN
F 3 "https://www.nxp.com/docs/en/data-sheet/TDA1308.pdf" H 8400 2600 50  0001 C CNN
	2    8400 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 1550 6800 1550
Wire Wire Line
	7350 1550 7200 1550
$Comp
L Jumper:SolderJumper_2_Bridged JP2
U 1 1 5FB52769
P 7050 1550
F 0 "JP2" H 7050 1755 50  0000 C CNN
F 1 "." H 7050 1664 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Bridged_RoundedPad1.0x1.5mm" H 7050 1550 50  0001 C CNN
F 3 "~" H 7050 1550 50  0001 C CNN
	1    7050 1550
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Bridged JP3
U 1 1 5FB54FD4
P 7050 2950
F 0 "JP3" H 7050 3155 50  0000 C CNN
F 1 "." H 7050 3064 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Bridged_RoundedPad1.0x1.5mm" H 7050 2950 50  0001 C CNN
F 3 "~" H 7050 2950 50  0001 C CNN
	1    7050 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 2950 7350 2950
$Comp
L Connector:AudioJack3 J?
U 1 1 604D992C
P 5450 2250
AR Path="/5FB17596/604D992C" Ref="J?"  Part="1" 
AR Path="/604A78D6/604D992C" Ref="J?"  Part="1" 
AR Path="/604AEF91/604D992C" Ref="J2"  Part="1" 
F 0 "J2" H 5170 2183 50  0000 R CNN
F 1 "Line Out" H 5170 2274 50  0000 R CNN
F 2 "Connector_Audio:Jack_3.5mm_CUI_SJ1-3533NG_Horizontal" H 5450 2250 50  0001 C CNN
F 3 "~" H 5450 2250 50  0001 C CNN
	1    5450 2250
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 604D9993
P 5150 2350
AR Path="/5FB17596/604D9993" Ref="#PWR?"  Part="1" 
AR Path="/604A78D6/604D9993" Ref="#PWR?"  Part="1" 
AR Path="/604AEF91/604D9993" Ref="#PWR042"  Part="1" 
F 0 "#PWR042" H 5150 2100 50  0001 C CNN
F 1 "GND" H 5155 2177 50  0000 C CNN
F 2 "" H 5150 2350 50  0001 C CNN
F 3 "" H 5150 2350 50  0001 C CNN
	1    5150 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 2350 5250 2350
Wire Wire Line
	5000 2600 5000 2250
Wire Wire Line
	5000 2250 5250 2250
Wire Wire Line
	5250 2150 5000 2150
Wire Wire Line
	5000 2150 5000 1900
Wire Wire Line
	5000 1900 4800 1900
Text GLabel 5250 1900 2    50   Output ~ 0
AOUT-LEFT
Wire Wire Line
	5000 1900 5250 1900
Connection ~ 5000 1900
Wire Wire Line
	4800 2600 5000 2600
Text GLabel 5250 2600 2    50   Output ~ 0
AOUT-RIGHT
Wire Wire Line
	5000 2600 5250 2600
Connection ~ 5000 2600
$Comp
L Device:R_POT_Dual RV7
U 1 1 5FD5F6AF
P 4550 2250
F 0 "RV7" V 4504 2063 50  0000 R CNN
F 1 "10k Log" V 4595 2063 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Alpha_RD902F-40-00D_Dual_Vertical" H 4800 2175 50  0001 C CNN
F 3 "~" H 4800 2175 50  0001 C CNN
	1    4550 2250
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FD75168
P 4450 2650
AR Path="/5FB17596/5FD75168" Ref="#PWR?"  Part="1" 
AR Path="/604A78D6/5FD75168" Ref="#PWR?"  Part="1" 
AR Path="/604AEF91/5FD75168" Ref="#PWR041"  Part="1" 
F 0 "#PWR041" H 4450 2400 50  0001 C CNN
F 1 "GND" H 4450 2500 50  0000 C CNN
F 2 "" H 4450 2650 50  0001 C CNN
F 3 "" H 4450 2650 50  0001 C CNN
	1    4450 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 1500 3850 1500
Wire Wire Line
	4450 1500 4450 1850
Connection ~ 3700 1500
Wire Wire Line
	3700 2800 3700 2350
Wire Wire Line
	3700 2350 3850 2350
Connection ~ 3700 2800
Wire Wire Line
	4650 2000 4800 2000
Wire Wire Line
	4800 2000 4800 1900
Wire Wire Line
	4650 2500 4800 2500
Wire Wire Line
	4800 2500 4800 2600
$Comp
L Device:C_Small C?
U 1 1 5FFDA65F
P 3950 2350
AR Path="/5FB17596/5FFDA65F" Ref="C?"  Part="1" 
AR Path="/604A78D6/5FFDA65F" Ref="C?"  Part="1" 
AR Path="/604AEF91/5FFDA65F" Ref="C19"  Part="1" 
F 0 "C19" V 3825 2350 50  0000 C CNN
F 1 "10uF" V 4075 2350 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 3950 2350 50  0001 C CNN
F 3 "~" H 3950 2350 50  0001 C CNN
	1    3950 2350
	0    -1   1    0   
$EndComp
Wire Wire Line
	4050 2350 4450 2350
$Comp
L Device:C_Small C?
U 1 1 5FFDB2F3
P 3950 1500
AR Path="/5FB17596/5FFDB2F3" Ref="C?"  Part="1" 
AR Path="/604A78D6/5FFDB2F3" Ref="C?"  Part="1" 
AR Path="/604AEF91/5FFDB2F3" Ref="C18"  Part="1" 
F 0 "C18" V 3825 1500 50  0000 C CNN
F 1 "10uF" V 4075 1500 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 3950 1500 50  0001 C CNN
F 3 "~" H 3950 1500 50  0001 C CNN
	1    3950 1500
	0    -1   1    0   
$EndComp
Wire Wire Line
	4050 1500 4450 1500
$EndSCHEMATC
