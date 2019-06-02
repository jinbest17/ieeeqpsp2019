#include<Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define Password_Lenght 7 // Give enough room for six chars + NULL char

// variables used for keypad
char Data[Password_Lenght]; // 6 is the number of chars it can hold + the null char = 7
char Master[Password_Lenght] = "123456"; 
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {
  10,11,12,13}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6,7,8,9}; //connect to the column pinouts of the keypad
Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); //initialize an instance of class NewKeypad 
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


// variables for 
int calibrationTime = 30;

long unsigned int lowIn;

long unsigned int pause = 500;

boolean lockLow = true;
boolean takeLowTime;

byte customBackslash[8] = {
  0b00000,
  0b10000,
  0b01000,
  0b00100,
  0b00010,
  0b00001,
  0b00000,
  0b00000
};

int pirPin = 3;
int ledPin = 13;

void setup() {
  // setup lcd display
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Setting up");
  lcd.createChar(7, customBackslash);

  
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);

  Serial.print("Calibrating sensor ");
  boolean greaterThanFive = false;
  for(int i = 0; i< calibrationTime*2; i++) {
    lcd.setCursor(10,0);
    switch(i % 4) {
      case 0: 
        lcd.print("|");
        break;
      case 1:
        lcd.write(byte(7));
        break;
      case 2:
        lcd.print("-");
        break;
      case 3: 
        lcd.print("/");
        break;
    }
    Serial.print(".");
    
    delay(500);
  }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  lcd.clear();
  lcd.print("Sensor Online");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Password");
}

void loop(){

  getPassword();

  if(digitalRead(pirPin) == HIGH) {
    if(lockLow) {
      lockLow = false;
      lcd.setCursor(0,1);
      lcd.print("Motion detected at");
      Serial.println("---");
      Serial.print("motion detected at ");
      lcd.print(millis()/1000);
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
      clearLine(1);
      lcd.print("Ready to detect");
      Serial.print("motion ended at ");
      Serial.print((millis() - pause) / 1000);
      Serial.println(" sec");
      delay(50);
    }
  }
}



void lockDoor() {
  
}

void unlockDoor() {
  
}

void getPassword() {
  customKey = customKeypad.getKey();
  if (customKey) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)
  {
    Data[data_count] = customKey; // store char into data array
    lcd.setCursor(data_count,0); // move cursor to show each new char
    lcd.print(Data[data_count]); // print char at said cursor
    data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
  }

  if(data_count == Password_Lenght-1) // if the array index is equal to the number of expected chars, compare data to master
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Password is ");

    if(!strcmp(Data, Master)) // equal to (strcmp(Data, Master) == 0)
      lcd.print("Good");
    else
      lcd.print("Bad");

    delay(1000);// added 1 second delay to make sure the password is completely shown on screen before it gets cleared.
    lcd.clear();
    lcd.print("Welcome, John");
    delay(2000);
    clearData();   
  }
}

void clearLine(int a) {
  lcd.setCursor(0,a);
  for (int i = 0; i < 16; i++)
    lcd.print(" ");
}

void clearData()
{
  while(data_count !=0)
  {   // This can be used for any array size, 
    Data[data_count--] = 0; //clear array for new data
  }
  return;
}
