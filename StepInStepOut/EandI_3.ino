#include <CircularBuffer.h>
CircularBuffer<int, 60> keyPresses;

#define pauseBetweenSounds 2000

#include <Keypad.h>
const int ROW_NUM = 3; //three rows
const int COLUMN_NUM = 3; //three columns
boolean recordingEnabled  = false;

char keys[ROW_NUM][COLUMN_NUM] = {
  {'0', '1', '2'},
  {'3', '4', '5'},
  {'6', '7', '8'}
};

byte pin_rows[ROW_NUM] = {8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

unsigned long previousMillis = 0;
const long interval = 20000;

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
  if(keypad.getKey() && !recordingEnabled){
      recordingEnabled = true;
      currentMillis = millis();
      
    }
  if (currentMillis - previousMillis < interval && recordingEnabled) {
    char key = keypad.getKey();
    int convertedKey = (int)key;
    if (key) {
      if(key-'0'>0){
        convertedKey = key - '0';
        }
       Serial.println(convertedKey);
      keyPresses.push(convertedKey); // to store the value to the end of queue
    }
  }
  else if(currentMillis - previousMillis >= interval) {
    Serial.println(keyPresses.shift()); // to send the first value in queue
    delay(pauseBetweenSounds);
    if (keyPresses.isEmpty())
      previousMillis = currentMillis;
      recordingEnabled = false;
  }
}

//KEYPAD TESTER CODE BELOW
/*
#include <Keypad.h>
const int ROW_NUM = 3; //three rows
const int COLUMN_NUM = 3; //three columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'}
};

byte pin_rows[ROW_NUM] = {8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void setup() {
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
  }
}
*/
