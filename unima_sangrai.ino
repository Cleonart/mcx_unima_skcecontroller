#include "max6675.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

/* Pin Mapping
MAX6675 so   = 4
MAX6676 cs   = 5
MAX6675 sck  = 6
LCD SDA      = A4
LCD SCL      = A5
RELAY        = 11
*/

// MAX6675 Settings
int soPin = 4;   // SO  = Serial Out
int csPin = 5;   // CS  = chip select CS pin
int sckPin = 6;  // SCK = Serial Clock pin
MAX6675 mx(sckPin, csPin, soPin);

// LCD Settings
LiquidCrystal_I2C lcd(0x27, 16, 2);

// PARAMETER
#define UPPER_BOUND 19.0  // Relay will go off, when desired temperature is reached
#define LOWER_BOUND 10.0  // Relay will go on, when desired temperature is reached

#define RELAY 11
#define RELAY_ON HIGH
#define RELAY_OFF LOW

void setup() {
  Serial.begin(9600);
  
  // Initialize LCD
  lcd.begin();
  lcd.backlight();
  showLCD("Halo..","");
  delay(5000);

  // Initialize Relay
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, RELAY_OFF);
}

void loop() {
  float temperature = mx.readCelsius();
  if(temperature > UPPER_BOUND){
    showLCD("Cooling..", String(temperature) + " C");
    digitalWrite(RELAY, RELAY_OFF);
  }
  else if(temperature < LOWER_BOUND){
    showLCD("Heating..", String(temperature) + " C");
    digitalWrite(RELAY, RELAY_ON);
  }
  delay(500);
}

void showLCD(String text_row_1, String text_row_2){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(text_row_1);
  lcd.setCursor(0,1);
  lcd.print(text_row_2);
}
