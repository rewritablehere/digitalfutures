/* Sweep */

#include <Servo.h>

Servo myservo;           // create servo object to control a servo


int pos = 80;            // variable to store the servo position
int servoState = 0;      // variable to check running more than once

void setup() {
  myservo.attach(13);    // attaches the servo on pin 13 to the servo object
}

void loop() {
  if(pos=148 && servoState == 0)         // exit if motor has not reached sweep position and hasn't already run once
  {
  
  for (pos = 80; pos <= 148; pos += 1) { // goes from 80 degrees to 143 degrees in steps of 1 degree
    
    myservo.write(pos);                  // tell servo to go to position in variable 'pos'
    delay(50);                           // waits 50 ms for the servo to reach the position
  }
    servoState = 1;                      // lets routine know motor has run once
  }


  }
