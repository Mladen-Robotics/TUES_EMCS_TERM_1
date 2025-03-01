// |———————————————————————————————————————————————————————| 
// |  made by Arduino_uno_guy 11/13/2019                   |
// |   https://create.arduino.cc/projecthub/arduino_uno_guy|
//  |———————————————————————————————————————————————————————|


#include <LiquidCrystal_I2C.h>

#define PIR_PIN 8

//initialize the liquid crystal library
//the first parameter is  the I2C address
//the second parameter is how many rows are on your screen
//the  third parameter is how many columns are on your screen
LiquidCrystal_I2C lcd(0x20,  16, 2);

int pirState = 0;
int prevState = 0;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(13, OUTPUT);
  //initialize lcd screen
  lcd.init();
  lcd.backlight();
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("No motion detected!");
  // turn on the backlight
  //lcd.backlight();
  Serial.begin(9600);
}
void loop() {
  //wait  for a second
  
  pirState = digitalRead(PIR_PIN);
  if(pirState == HIGH)
  {
    if(pirState != prevState)
    {
    	lcd.clear();
    lcd.setCursor(0,0);
    prevState = pirState;
       lcd.print("Motion!!");
    }
  	
    digitalWrite(13, millis() % 2000 < 1000);
  }
  else if(pirState == LOW && pirState != prevState)
  {
    digitalWrite(13, 0);
  	lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("No motion detected!");
    prevState = pirState;
  }
  
  
}

/*
While a movement is being detected:
	blink a led.
If it is not:
	just print a message once

*/
