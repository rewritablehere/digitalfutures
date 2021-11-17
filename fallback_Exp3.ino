#define forward_MacDegen A3
#define reverse_MacDegen A4
#define forward_Blind A1
#define reverse_Blind A0
#define forward_Astig A6
#define reverse_Astig A5
#define forward_synest A7
#define reverse_synest 3
#define toggle_PlayPause A2

char prev;
void setup() {
  Serial.begin(9600);
  pinMode(forward_MacDegen, INPUT);
  pinMode(reverse_MacDegen, INPUT);
  pinMode(forward_Blind, INPUT);
  pinMode(reverse_Blind, INPUT);
  pinMode(forward_Astig, INPUT);
  pinMode(reverse_Astig, INPUT);
  pinMode(forward_synest, INPUT);
  pinMode(reverse_synest, INPUT);
  pinMode(toggle_PlayPause, INPUT);
}
void loop() {
  if (digitalRead(toggle_PlayPause)) {
    if (prev != 'H')
    {
      Serial.print("H");
      prev = 'H';
    }
  }
  if (digitalRead(forward_MacDegen) || digitalRead(reverse_MacDegen)) {
    if (prev != 'G')
    {
      Serial.print("G");
      prev = 'G';
    }
  }
  if (digitalRead(forward_Blind) || digitalRead(reverse_Blind)) {
    if (prev != 'J')
    {
      Serial.print("J");
      prev = 'J';
    }
  }
  if (digitalRead(forward_Astig) || digitalRead(reverse_Astig)) {
    if (prev != 'B')
    {
      Serial.print("B");
      prev = 'B';
    }
  }
  if (digitalRead(forward_synest) || digitalRead(reverse_synest)) {
    if (prev != 'N')
    {
      Serial.print("N");
      prev = 'N';
    }
  }
  else
  {
    if (prev != 'Y')
    {
      Serial.print("Y");
      prev = 'Y';
    }

  }
}
