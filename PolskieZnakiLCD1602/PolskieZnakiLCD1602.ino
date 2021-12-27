#include "Arduino.h"
#include "ZnakiPL.h"
#include <Wire.h>;

void setup() {
  Serial.begin(115200);
  Wire1.begin(22, 21); 
  lcd.init();                    
  lcd.backlight();
  String pamiec_lcd = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F";
  String tekst = "Wolność to jest to...";
  String tekstLCD ="";
  tekstLCD = create(tekst);

    lcd.setCursor(0, 0);
    lcd.print(tekstLCD);
    lcd.setCursor(0, 1);
    lcd.print(pamiec_lcd);
  
}

void loop() {
  

}
