#include "LiquidCrystal_I2C.h"

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

#define ENCODER1 A2
#define ENCODER2 A3

#define POTENTIOMETER A0

LiquidCrystal_I2C lcd(0x27, 16, 2);
volatile bool redPressed = false;

void initRGB()
{
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

void initSensor(){
  pinMode(POTENTIOMETER, INPUT);
}

void initButtons()
{
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

void initEncoder()
{
  pinMode(ENCODER1, INPUT_PULLUP);
  pinMode(ENCODER2, INPUT_PULLUP);
}

void initLcd() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Voltage");
}

String readVoltage() {
  float read = 5.0 * analogRead(POTENTIOMETER)/1023.0;
  read = round(100.0*read)/100.0;
  return String(read);
}

void updateScreen() {
  const unsigned long perioid = 250;
  static unsigned long lastRun = 0;
  static String previousVoltage = "";
  if (millis() - lastRun > perioid) {
    lastRun = millis();
    String currentVoltage = readVoltage();
    if (previousVoltage != currentVoltage) {
      lcd.setCursor(8, 0);
      lcd.print("        ");  
      lcd.setCursor(8, 0);
      lcd.print(currentVoltage);
      previousVoltage = currentVoltage;
    }
  }
}

void setup()
{
  initLcd();
  initSensor();
}

void loop() {
  updateScreen();
}