EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
Title "ESP32 Garage Door Opener"
Date "2021-08-15"
Rev "1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L dk_RF-Transceiver-Modules:ESP32-WROOM-32 MOD?
U 1 1 6119F2C5
P 5850 2700
F 0 "MOD?" H 6050 3000 60  0000 C CNN
F 1 "ESP32-WROOM-32" H 6050 2894 60  0000 C CNN
F 2 "digikey-footprints:ESP32-WROOM-32D" H 6050 2900 60  0001 L CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf" H 6050 3000 60  0001 L CNN
F 4 "1904-1010-1-ND" H 6050 3100 60  0001 L CNN "Digi-Key_PN"
F 5 "ESP32-WROOM-32" H 6050 3200 60  0001 L CNN "MPN"
F 6 "RF/IF and RFID" H 6050 3300 60  0001 L CNN "Category"
F 7 "RF Transceiver Modules" H 6050 3400 60  0001 L CNN "Family"
F 8 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf" H 6050 3500 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/espressif-systems/ESP32-WROOM-32/1904-1010-1-ND/8544305" H 6050 3600 60  0001 L CNN "DK_Detail_Page"
F 10 "SMD MODULE, ESP32-D0WDQ6, 32MBIT" H 6050 3700 60  0001 L CNN "Description"
F 11 "Espressif Systems" H 6050 3800 60  0001 L CNN "Manufacturer"
F 12 "Active" H 6050 3900 60  0001 L CNN "Status"
	1    5850 2700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6119F34B
P 5850 5100
F 0 "#PWR?" H 5850 4850 50  0001 C CNN
F 1 "GND" H 5855 4927 50  0000 C CNN
F 2 "" H 5850 5100 50  0001 C CNN
F 3 "" H 5850 5100 50  0001 C CNN
	1    5850 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 4800 5850 4900
Wire Wire Line
	6150 4800 6150 5000
Wire Wire Line
	6150 5000 5850 5000
Connection ~ 5850 5000
Wire Wire Line
	5850 5000 5850 5100
Wire Wire Line
	6050 4800 6050 4950
Wire Wire Line
	6050 4950 5850 4950
Connection ~ 5850 4950
Wire Wire Line
	5850 4950 5850 5000
Wire Wire Line
	5950 4800 5950 4900
Wire Wire Line
	5950 4900 5850 4900
Connection ~ 5850 4900
Wire Wire Line
	5850 4900 5850 4950
$Comp
L power:+3.3V #PWR?
U 1 1 6119F402
P 6050 2150
F 0 "#PWR?" H 6050 2000 50  0001 C CNN
F 1 "+3.3V" H 6065 2323 50  0000 C CNN
F 2 "" H 6050 2150 50  0001 C CNN
F 3 "" H 6050 2150 50  0001 C CNN
	1    6050 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 2150 6050 2600
$Comp
L dk_Transistors-Bipolar-BJT-Single:2N2222 Q?
U 1 1 6119F5CE
P 7900 4200
F 0 "Q?" H 8088 4253 60  0000 L CNN
F 1 "2N2222" H 8088 4147 60  0000 L CNN
F 2 "digikey-footprints:TO-18-3" H 8100 4400 60  0001 L CNN
F 3 "https://my.centralsemi.com/get_document.php?cmp=1&mergetype=pd&mergepath=pd&pdf_id=2N2221.PDF" H 8100 4500 60  0001 L CNN
F 4 "2N2222CS-ND" H 8100 4600 60  0001 L CNN "Digi-Key_PN"
F 5 "2N2222" H 8100 4700 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 8100 4800 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 8100 4900 60  0001 L CNN "Family"
F 8 "https://my.centralsemi.com/get_document.php?cmp=1&mergetype=pd&mergepath=pd&pdf_id=2N2221.PDF" H 8100 5000 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/central-semiconductor-corp/2N2222/2N2222CS-ND/4806844" H 8100 5100 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 30V 0.8A TO-18" H 8100 5200 60  0001 L CNN "Description"
F 11 "Central Semiconductor Corp" H 8100 5300 60  0001 L CNN "Manufacturer"
F 12 "Active" H 8100 5400 60  0001 L CNN "Status"
	1    7900 4200
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LT1086-3.3 U?
U 1 1 6119F8A3
P 2200 6550
F 0 "U?" H 2200 6792 50  0000 C CNN
F 1 "LT1086-3.3" H 2200 6701 50  0000 C CNN
F 2 "" H 2200 6800 50  0001 C CIN
F 3 "http://cds.linear.com/docs/en/datasheet/1086ffs.pdf" H 2200 6550 50  0001 C CNN
	1    2200 6550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6119F94F
P 2200 7500
F 0 "#PWR?" H 2200 7250 50  0001 C CNN
F 1 "GND" H 2205 7327 50  0000 C CNN
F 2 "" H 2200 7500 50  0001 C CNN
F 3 "" H 2200 7500 50  0001 C CNN
	1    2200 7500
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 6119FA16
P 3100 6450
F 0 "#PWR?" H 3100 6300 50  0001 C CNN
F 1 "+3.3V" H 3115 6623 50  0000 C CNN
F 2 "" H 3100 6450 50  0001 C CNN
F 3 "" H 3100 6450 50  0001 C CNN
	1    3100 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 6450 3100 6550
Wire Wire Line
	3100 6550 2500 6550
$Comp
L pspice:CAP C?
U 1 1 6119FB61
P 3100 6800
F 0 "C?" H 3278 6846 50  0000 L CNN
F 1 "100uF" H 3278 6755 50  0000 L CNN
F 2 "" H 3100 6800 50  0001 C CNN
F 3 "" H 3100 6800 50  0001 C CNN
	1    3100 6800
	1    0    0    -1  
$EndComp
Connection ~ 3100 6550
Wire Wire Line
	3100 7050 3100 7250
Wire Wire Line
	3100 7250 2200 7250
Wire Wire Line
	2200 6850 2200 7250
Connection ~ 2200 7250
Wire Wire Line
	2200 7250 2200 7500
$Comp
L pspice:CAP C?
U 1 1 6119FE7D
P 1450 6800
F 0 "C?" H 1628 6846 50  0000 L CNN
F 1 "100uF" H 1628 6755 50  0000 L CNN
F 2 "" H 1450 6800 50  0001 C CNN
F 3 "" H 1450 6800 50  0001 C CNN
	1    1450 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 7250 1450 7250
Wire Wire Line
	1450 7250 1450 7050
Wire Wire Line
	1900 6550 1450 6550
$Comp
L power:+BATT #PWR?
U 1 1 611A02DD
P 950 6500
F 0 "#PWR?" H 950 6350 50  0001 C CNN
F 1 "+BATT" H 965 6673 50  0000 C CNN
F 2 "" H 950 6500 50  0001 C CNN
F 3 "" H 950 6500 50  0001 C CNN
	1    950  6500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 6550 950  6550
Wire Wire Line
	950  6550 950  6500
Connection ~ 1450 6550
$Comp
L Device:R R?
U 1 1 611A0A58
P 4600 2500
F 0 "R?" H 4670 2546 50  0000 L CNN
F 1 "10K" H 4670 2455 50  0000 L CNN
F 2 "" V 4530 2500 50  0001 C CNN
F 3 "~" H 4600 2500 50  0001 C CNN
	1    4600 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 2800 4600 2800
Wire Wire Line
	4600 2800 4600 2650
Wire Wire Line
	4600 2350 4600 2250
$Comp
L power:+3.3V #PWR?
U 1 1 611A1166
P 4600 2100
F 0 "#PWR?" H 4600 1950 50  0001 C CNN
F 1 "+3.3V" H 4615 2273 50  0000 C CNN
F 2 "" H 4600 2100 50  0001 C CNN
F 3 "" H 4600 2100 50  0001 C CNN
	1    4600 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 611A11F6
P 4300 2500
F 0 "R?" H 4370 2546 50  0000 L CNN
F 1 "10K" H 4370 2455 50  0000 L CNN
F 2 "" V 4230 2500 50  0001 C CNN
F 3 "~" H 4300 2500 50  0001 C CNN
	1    4300 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 3300 4300 3300
Wire Wire Line
	4300 3300 4300 2650
Wire Wire Line
	4300 2350 4300 2250
Wire Wire Line
	4300 2250 4600 2250
Connection ~ 4600 2250
Wire Wire Line
	4600 2250 4600 2100
$Comp
L Device:R R?
U 1 1 611A1A86
P 7350 4200
F 0 "R?" V 7143 4200 50  0000 C CNN
F 1 "1K" V 7234 4200 50  0000 C CNN
F 2 "" V 7280 4200 50  0001 C CNN
F 3 "~" H 7350 4200 50  0001 C CNN
	1    7350 4200
	0    1    1    0   
$EndComp
Wire Wire Line
	7700 4200 7500 4200
Wire Wire Line
	7200 4200 6750 4200
$Comp
L power:GND #PWR?
U 1 1 611A254F
P 8000 4900
F 0 "#PWR?" H 8000 4650 50  0001 C CNN
F 1 "GND" H 8005 4727 50  0000 C CNN
F 2 "" H 8000 4900 50  0001 C CNN
F 3 "" H 8000 4900 50  0001 C CNN
	1    8000 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 4400 8000 4900
$Comp
L dk_Transistors-Bipolar-BJT-Single:2N2222 Q?
U 1 1 611A2BB5
P 3350 4200
F 0 "Q?" H 3538 4253 60  0000 L CNN
F 1 "2N2222" H 3538 4147 60  0000 L CNN
F 2 "digikey-footprints:TO-18-3" H 3550 4400 60  0001 L CNN
F 3 "https://my.centralsemi.com/get_document.php?cmp=1&mergetype=pd&mergepath=pd&pdf_id=2N2221.PDF" H 3550 4500 60  0001 L CNN
F 4 "2N2222CS-ND" H 3550 4600 60  0001 L CNN "Digi-Key_PN"
F 5 "2N2222" H 3550 4700 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 3550 4800 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 3550 4900 60  0001 L CNN "Family"
F 8 "https://my.centralsemi.com/get_document.php?cmp=1&mergetype=pd&mergepath=pd&pdf_id=2N2221.PDF" H 3550 5000 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/central-semiconductor-corp/2N2222/2N2222CS-ND/4806844" H 3550 5100 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 30V 0.8A TO-18" H 3550 5200 60  0001 L CNN "Description"
F 11 "Central Semiconductor Corp" H 3550 5300 60  0001 L CNN "Manufacturer"
F 12 "Active" H 3550 5400 60  0001 L CNN "Status"
	1    3350 4200
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 611A2E13
P 4450 4200
F 0 "R?" V 4243 4200 50  0000 C CNN
F 1 "1K" V 4334 4200 50  0000 C CNN
F 2 "" V 4380 4200 50  0001 C CNN
F 3 "~" H 4450 4200 50  0001 C CNN
	1    4450 4200
	0    1    1    0   
$EndComp
Wire Wire Line
	4600 4200 5350 4200
Wire Wire Line
	4300 4200 3550 4200
$Comp
L power:GND #PWR?
U 1 1 611A4116
P 3250 5100
F 0 "#PWR?" H 3250 4850 50  0001 C CNN
F 1 "GND" H 3255 4927 50  0000 C CNN
F 2 "" H 3250 5100 50  0001 C CNN
F 3 "" H 3250 5100 50  0001 C CNN
	1    3250 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 4400 3250 5100
$Comp
L Relay:G5V-2 K?
U 1 1 611A4BFA
P 8400 3400
F 0 "K?" H 9030 3446 50  0000 L CNN
F 1 "HK19F-DC 5V-HSG" H 9030 3355 50  0000 L CNN
F 2 "" H 9050 3350 50  0001 L CNN
F 3 "http://omronfs.omron.com/en_US/ecb/products/pdf/en-g5v_2.pdf" H 8200 3400 50  0001 C CNN
	1    8400 3400
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR?
U 1 1 611A5FB9
P 8000 2700
F 0 "#PWR?" H 8000 2550 50  0001 C CNN
F 1 "+BATT" H 8015 2873 50  0000 C CNN
F 2 "" H 8000 2700 50  0001 C CNN
F 3 "" H 8000 2700 50  0001 C CNN
	1    8000 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 2700 8000 3100
Wire Wire Line
	8000 4000 8000 3700
Wire Wire Line
	8800 3700 8800 3850
$Comp
L Connector:Conn_01x02_Male J?
U 1 1 611A7CDF
P 10300 2800
F 0 "J?" H 10273 2680 50  0000 R CNN
F 1 "Connect Door Open" H 10850 2550 50  0000 R CNN
F 2 "" H 10300 2800 50  0001 C CNN
F 3 "~" H 10300 2800 50  0001 C CNN
	1    10300 2800
	-1   0    0    1   
$EndComp
Wire Wire Line
	10100 2800 9900 2800
Wire Wire Line
	9900 2800 9900 3850
Wire Wire Line
	8800 3850 9900 3850
$Comp
L Relay:G5V-2 K?
U 1 1 611AAE03
P 2850 3450
F 0 "K?" H 2220 3496 50  0000 R CNN
F 1 "HK19F-DC 5V-HSG" H 2220 3405 50  0000 R CNN
F 2 "" H 3500 3400 50  0001 L CNN
F 3 "http://omronfs.omron.com/en_US/ecb/products/pdf/en-g5v_2.pdf" H 2650 3450 50  0001 C CNN
	1    2850 3450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3250 4000 3250 3750
$Comp
L power:+BATT #PWR?
U 1 1 611AB857
P 3250 2650
F 0 "#PWR?" H 3250 2500 50  0001 C CNN
F 1 "+BATT" H 3265 2823 50  0000 C CNN
F 2 "" H 3250 2650 50  0001 C CNN
F 3 "" H 3250 2650 50  0001 C CNN
	1    3250 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 3150 3250 2650
$Comp
L Connector:Conn_01x02_Male J?
U 1 1 611AC33D
P 900 2750
F 0 "J?" H 873 2630 50  0000 R CNN
F 1 "Connect to Lamp" H 1450 2500 50  0000 R CNN
F 2 "" H 900 2750 50  0001 C CNN
F 3 "~" H 900 2750 50  0001 C CNN
	1    900  2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 3100 8900 2700
Wire Wire Line
	8900 2700 10100 2700
Wire Wire Line
	2350 3150 2350 2750
Wire Wire Line
	2350 2750 1100 2750
Wire Wire Line
	2450 3750 2450 4100
Wire Wire Line
	2450 4100 1600 4100
Wire Wire Line
	1600 4100 1600 2850
Wire Wire Line
	1600 2850 1100 2850
Text Notes 800  1350 0    50   ~ 0
Notes:\n1. Pinouts for relay are not correct. Use example connections\nfor your situation. The HK19F is a 5V relay coil.\n2. Some key pads may ues a series resistor to multiplex the lamp and the door opener.\n3.Project Testend on Gene: GXL9550CL\nDoor series resistor 100ohms\nLamp Series reistor 50ohms
$EndSCHEMATC
