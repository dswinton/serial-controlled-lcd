/*

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

*/

#include <LiquidCrystal.h>

String serialString;


// Initialise the LCD
//LiquidCrystal lcd(52, 53, 50, 51, 48, 49); //Mega 2560
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Mini

void setup() {

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  // Print an initial message to the LCD.
  lcd.print("Just a sec...");

  //Open the serial port
  Serial.begin(115200);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  
  Serial.println("WUT_SAY"); 
}

void loop() {
  
  //Listen to serial until we receive an EOL
  serialString = Serial.readStringUntil('\n');

  if(serialString.length() > 0){

    String line1 = getValue(serialString, '~', 0);
    String line2 = getValue(serialString, '~', 1);

    //If line2 is empty, check if line1 needs to wrap
    if((line2.length() == 0) && (line1.length() > 16)){
      line2 = line1.substring(16);
    }

    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print(line1);

    lcd.setCursor(0, 1);
    lcd.print(line2);

    Serial.println("K_DONE~"+serialString); 
    
  };

  //Add an optional delay before we will display another message
  //delay(100);
}



//Substitute for explode() type function
String getValue(String data, char separator, int index){
	int found = 0;
	int strIndex[] = {0, -1};
	int maxIndex = data.length()-1;
	
	for(int i=0; i<=maxIndex && found<=index; i++){
		if(data.charAt(i)==separator || i==maxIndex){
			found++;
			strIndex[0] = strIndex[1]+1;
			strIndex[1] = (i == maxIndex) ? i+1 : i;
		}
	}
	
	return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}


