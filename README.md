# serial-controlled-lcd
Serial Controlled 1602 LCD Display on Arduino


Use an Arduino to drive a 1602 LCD display, sending text to it from another device (such as a Raspberry Pi or C.H.I.P) over Serial.

Usage:
* By default, Serial interface runs as 115200 baud
* On initialisation, the Arduino will send "WUT_SAY"
* Send text of up to 32 characters
* Optionally, break between line 1 and 2 of the display with ~ (eg. "This is line 1~This is line 2")
* End text with a line break / EOL ("\n")
* The arduino will reply with "K_DONE~(Your text)"

Text automatically wraps across both lines of the display, unless, line 2 is explicitly set as above using ~ as a break.


The circuit:
* LCD RS pin to digital pin 12
* LCD Enable pin to digital pin 11
* LCD D4 pin to digital pin 5
* LCD D5 pin to digital pin 4
* LCD D6 pin to digital pin 3
* LCD D7 pin to digital pin 2
* LCD R/W pin to ground
* LCD VSS pin to ground
* LCD VCC pin to 5V
* 10K resistor:
* ends to +5V and ground
* wiper to LCD VO pin (pin 3)