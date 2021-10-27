/* Sweep */

#include <Arduino_APDS9960.h> 
#include <Servo.h>

Servo myservo;  // create servo object to control a servo


int pos = 80;   // variable to store the servo position
int servoState = 0; 

#define delay50 100

int myled[] = {2, 3, 4, 5, 6, 7, 8, 9,10,11,12};
int num_of_leds;

void setup() {
  Serial.begin(9600);
  
  myservo.attach(13);  // attaches the servo on pin 13 to the servo object

  num_of_leds = sizeof(myled) / sizeof(int);
  for (int i = 0; i < num_of_leds; i++) {
    pinMode(myled[i], OUTPUT);
  }

}

void loop() {
  // check if a proximity reading is available
  if (APDS.proximityAvailable()) {
    // read the proximity

    int proximity = APDS.readProximity();
    Serial.println(proximity);
    
  if(proximity < 245){
  if(pos=148 && servoState == 0)
  {
    moveServo();  //routine to move servo
  }
  
  ledPattern();   //routine to turn on LEDs
  }
}
}

void moveServo() {
  
     for (pos = 80; pos <= 148; pos += 1) 
      {                                // goes from 80 degrees to 148 degrees in steps of 1 degree
     
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(50);                       // waits 50 ms for the servo to reach the position
      }
     servoState = 1; 
}

//RIGHT TO LEFT
void ledPattern() {
  for (int i = num_of_leds; i > 0; i--) {
    digitalWrite(myled[i - 1], HIGH);
    delay(delay50);
    digitalWrite(myled[i - 1], LOW);
  }
}
  
