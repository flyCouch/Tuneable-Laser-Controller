//Copyright 2024 Ron Lyttle.
//No charge for use or distribution though.

#include <LiquidCrystal_I2C.h>

const int redPin = 4;
const int greenPin = 3;
const int bluePin = 2;

const int sensor1Pin = A7;
const int sensor2Pin = A6;
const int sensor3Pin = A3;
const int pausePin = A2;

int pauseRead = 0;
int pauseUse = 0;

const int lcdAddress = 0x27;

LiquidCrystal_I2C lcd(lcdAddress, A4, A5);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Lyttle ReSearch ");
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  int sensor1Value = analogRead(sensor1Pin);
  int sensor2Value = analogRead(sensor2Pin);
  int sensor3Value = analogRead(sensor3Pin);
  int pauseRead = analogRead(pausePin);

  int redBrightness = map(sensor1Value, 0, 1023, 0, 255);
  int greenBrightness = map(sensor2Value, 0, 1023, 0, 255);
  int blueBrightness = map(sensor3Value, 0, 1023, 0, 255);
  int pauseUse = map(pauseRead, 0, 1023, 0, 255);

  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("R");
  lcd.print(redBrightness);
  lcd.setCursor(4, 1);
  lcd.print("G");
  lcd.print(greenBrightness);
  lcd.setCursor(8, 1);
  lcd.print("B");
  lcd.print(blueBrightness);
  lcd.setCursor(12, 1);
  lcd.print("P");
  lcd.print(pauseUse);

  for (int i = 1; i <= 4000; i++) {
    analogWrite(redPin, redBrightness);
    analogWrite(greenPin, greenBrightness);
    analogWrite(bluePin, blueBrightness);

    delayMicroseconds(1);

    if (pauseUse != 0) {
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      delayMicroseconds(pauseUse);
    }
  }
}
