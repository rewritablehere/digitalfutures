#define delay50 100
//-------------------------------------------
//reading distance

const int TriggerPin = 12; 
const int EchoPin = 13;
long Duration = 0;
//-------------------------------------------
//initializing LEDs

int myled[] = {2, 3, 4, 5, 6, 7, 8, 9,10,11};
int num_of_leds;
//-------------------------------------------
//Initialize

void setup() {

    num_of_leds = sizeof(myled) / sizeof(int);
  for (int i = 0; i < num_of_leds; i++) {
    pinMode(myled[i], OUTPUT);
  }
  // put your setup code here, to run once:
pinMode(TriggerPin, OUTPUT);
pinMode(EchoPin, INPUT);
Serial.begin(9600);
  
}
//-------------------------------------------
//Main program steps to run repeatedly

void loop() {
  
  //Distance detection
  digitalWrite(TriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);

  Duration = pulseIn(EchoPin, HIGH);

  long Distance_cm = Distance(Duration);

  Serial.println(Distance_cm);

  if(Distance_cm > 250 && Distance_cm < 300)
    {
      for(int i = 0; i < 5; i++)
        { 
          //Draw LED pattern
          pattern(); 
        }
    }
}

  long Distance (long time)
  {
    long DistanceCalc;
    DistanceCalc = ((time * 0.034) /2);
    return DistanceCalc;
  }

//-------------------------------------------
//Run LEDs from LEFT TO RIGHT FILL
void pattern() {
  for (int i = 0; i < num_of_leds; i++) {
    digitalWrite(myled[i], HIGH);
    delay(delay50);
  }
  for (int i = num_of_leds; i > 0; i--) {
    digitalWrite(myled[i - 1], LOW);
    delay(delay50);
  }
}
