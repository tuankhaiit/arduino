#include <Wire.h>
#include "LiquidCrystal_I2C.h"
#include "Keypad.h"
#include <string.h>


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'0', 'F', 'E', 'D'}
};
byte rowPins[ROWS] = {28, 26, 24, 22}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {30, 32, 34, 36}; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x3F, 16, 4);

void setup()
{
  //Ket noi voi dong co
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("$ 100.000VND");

}

void loop()
{
      char customKey = customKeypad.getKey();
       if (customKey){
        lcd.setCursor(2, 1);
        lcd.print(customKey);
         Serial.println(customKey);
      }
      lcd.setCursor(2, 1);
      lcd.print("AAA");
  

}













