#define forward_MacDegen A0
#define reverse_MacDegen A1
#define forward_Blind A2
#define reverse_Blind A3
#define forward_Astig A4
#define reverse_Astig A5
#define forward_synest A6
#define reverse_synest A7
#define toggle_PlayPause 3



int state = 0; // toggle between changing effect (if 0) and speed (if 1)
int effect = 0; // choose 4 effects



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
state = 0;
Serial.print("G");
delay(250);
}
if (!state) {
if (digitalRead(forward_MacDegen) || digitalRead(reverse_MacDegen)) {
state = 1;
effect = 0;
Serial.print("A");
}
if (digitalRead(forward_Blind) || digitalRead(reverse_Blind)) {
state = 1;
effect = 1;
Serial.print("S");
}
if (digitalRead(forward_Astig) || digitalRead(reverse_Astig)) {
state = 1;
effect = 2;
Serial.print("D");
}
if (digitalRead(forward_synest) || digitalRead(reverse_synest)) {
state = 1;
effect = 3;
Serial.print("F");
}
}
if (state) {
if (effect == 0) {
if (digitalRead(forward_MacDegen)) {
Serial.print("Y");
delay(250);
}
else if (digitalRead(reverse_MacDegen)) {
Serial.print("N");
delay(250);
}
else {
Serial.print("H");
delay(250);
}
}
if (effect == 1) {
if (digitalRead(forward_Blind)) {
Serial.print("Y");
delay(250);
}
else if (digitalRead(reverse_Blind)) {
Serial.print("N");
delay(250);
}
else {
Serial.print("H");
delay(250);
}
}
if (effect == 2) {
if (digitalRead(forward_Astig)) {
Serial.print("Y");
delay(250);
}
else if (digitalRead(reverse_Astig)) {
Serial.print("N");
delay(250);
}
else {
Serial.print("H");
delay(250);
}
}
if (effect == 3) {
if (digitalRead(forward_synest)) {
Serial.print("Y");
delay(250);
}
else if (digitalRead(reverse_synest)) {
Serial.print("N");
delay(250);
}
else {
Serial.print("H");
delay(250);
}
}
}
}
