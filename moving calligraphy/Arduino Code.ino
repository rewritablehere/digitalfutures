
// ---------------------------------------------------------------- //
// Arduino Ultrasoninc Sensor HC-SR04 & MG996R Servo
// ---------------------------------------------------------------- //

#include <Servo.h>

Servo myservo1, myservo2, myservo3;  // create servo objects to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

#define echoPin1 12 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin1 13 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPin2 11 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin2 10 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration1; // variable for the duration of sound wave travel
int distance1; // variable for the distance measurement
long duration2; // variable for the duration of sound wave travel
int distance2; // variable for the distance measurement

void setup() {
  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(8);  // attaches the servo on pin 8 to the servo object
  myservo3.attach(7);  // attaches the servo on pin 8 to the servo object
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin1, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin2, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}

void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
  // Calculating the distance
  distance1 = duration1 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)


    // Clears the trigPin condition
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  // Displays the distance on the Serial Monitor
//printSerial();

  if (distance1 == 100 && distance2 == 100)
  {

  playServo(); // sweep Servo if distance of anyone standing in front of both the sensors is 1m
  printSerial();

  }
}

void printSerial() {
  //Serial.print("Distance: ");
  Serial.print(distance1);
  Serial.print("    ");
  Serial.println(distance2);
 // Serial.print(distance2);
 // Serial.println(" cm");

}
  
void playServo() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(pos); 
    myservo2.write(pos);
    myservo3.write(pos); // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);
    myservo2.write(pos);
    myservo3.write(pos); // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
