#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int calibrationTime = 30;

long unsigned int lowIn;

long unsigned int pause = 500;

boolean lockLow = true;
boolean takeLowTime;

int pirPin = 3;
int ledPin = 13;

void setup() {
  // setup lcd display
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("ready to detect");

  
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);

  Serial.print("Calibrating sensor ");
  for(int i = 0; i< calibrationTime; i++) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);
}

void loop(){

  if(digitalRead(pirPin) == HIGH) {
    if(lockLow) {
      lockLow = false;
      lcd.clear();
      lcd.print("Motion detected");
      Serial.println("---");
      Serial.print("motion detected at ");
      Serial.print(millis()/1000);
      Serial.println(" sec");
      delay(50);
    }
    takeLowTime = true;
  }

  if(digitalRead(pirPin) == LOW) {


    if(takeLowTime) {
      lowIn = millis();
      takeLowTime = false;
    }

    if(!lockLow && millis() - lowIn > pause) {
      lockLow = true;
      lcd.clear();
      lcd.print("Ready to detect");
      Serial.print("motion ended at ");
      Serial.print((millis() - pause) / 1000);
      Serial.println(" sec");
      delay(50);
    }
  }
}
