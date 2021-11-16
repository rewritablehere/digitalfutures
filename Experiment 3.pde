import processing.serial.*;
import processing.video.*;
import processing.sound.*;



Serial myPort;



SoundFile synesthesiaMusic;



int numFrames = 120; // The number of frames in the animation
int currentFrame = 0;
PImage[] images = new PImage[numFrames];
PImage md, fb, glaucoma, begin;



Movie movieForward, movieReverse;



void setup()
{
size(960, 540, P3D);
fullScreen();
frameRate(17);



String portName = Serial.list()[1];
myPort = new Serial(this, portName, 9600);



for (int i = 0; i < numFrames; i++)
{
String imageName = "/Users/admin/Desktop/assets/gif/gif-" + i + ".png";
images[i] = loadImage(imageName);
}



/*begin = loadImage("/Users/admin/Desktop/assets/begin.png");
image(begin, 0, 0, displayWidth, displayHeight);
delay(5000);*/



md = loadImage("/Users/admin/Desktop/assets/md.png");
fb = loadImage("/Users/admin/Desktop/assets/fb.png");
glaucoma = loadImage("/Users/admin/Desktop/assets/glaucoma.png");



movieForward = new Movie(this, "/Users/admin/Desktop/assets/VideoForward.mp4");
movieForward.loop();



movieReverse = new Movie(this, "/Users/admin/Desktop/assets/VideoReverse.mp4");
movieReverse.loop();



synesthesiaMusic = new SoundFile(this, "/Users/admin/Desktop/assets/sound.mp3");
synesthesiaMusic.loop();
}



char instruction;
int receivingData = 0;
int choice = 0;



void draw()
{
if ( myPort.available() > 0) {
 instruction = myPort.readChar();
 receivingData = 1;
}
if (receivingData == 1)
{
 receivingData = 0;
switch(instruction)
{
case 'F':
choice=1;
break;
case 'A':
choice=2;
break;
case 'S':
choice=3;
break;
case 'D':
choice=4;
break;
case 'G':
choice=0;
synesthesiaMusic.stop();
movieForward.stop();
movieReverse.stop();
break;
case 'Y':
switch (choice)
{
case 1 :
if (movieForward.available())
{
movieForward.read();
chromesthesiaForwardDisplay();
}
break;
case 2 :
if (movieForward.available())
{
movieForward.read();
synesthesiaMusic.stop();
mdForwardDisplay();
}
break;
case 3 :
if (movieForward.available())
{
movieForward.read();
synesthesiaMusic.stop();
fullBlindnessForwardDisplay();
}
break;
case 4 :
if (movieForward.available())
{
movieForward.read();
synesthesiaMusic.stop();
glaucomaForwardDisplay();
}
break;
default :
synesthesiaMusic.pause();
movieForward.pause();
movieReverse.pause();
break;
}
break;
case 'H':
synesthesiaMusic.pause();
movieForward.pause();
movieReverse.pause();
break;
case 'N':
switch (choice)
{
case 1 :
if (movieReverse.available())
{
movieReverse.read();
chromesthesiaReverseDisplay();
}
break;
case 2 :
if (movieReverse.available())
{
movieReverse.read();
synesthesiaMusic.stop();
mdReverseDisplay();
}
break;
case 3 :
if (movieReverse.available())
{
movieReverse.read();
synesthesiaMusic.stop();
fullBlindnessReverseDisplay();
}
break;
case 4 :
if (movieReverse.available())
{
movieReverse.read();
synesthesiaMusic.stop();
glaucomaReverseDisplay();
}
break;
default :
synesthesiaMusic.pause();
movieForward.pause();
movieReverse.pause();
break;
}
break;
}
}
}



void chromesthesiaForwardDisplay() {
image(movieForward, 0, 0, displayWidth, displayHeight);
currentFrame = (currentFrame+1) % numFrames; // Use % to cycle through frames
int offset = 0;
image(images[(currentFrame+offset) % numFrames], 0, 0, displayWidth, displayHeight);
offset+=1;
}



void chromesthesiaReverseDisplay() {
image(movieReverse, 0, 0, displayWidth, displayHeight);
currentFrame = (currentFrame+1) % numFrames; // Use % to cycle through frames
int offset = 0;
image(images[(currentFrame+offset) % numFrames], 0, 0, displayWidth, displayHeight);
offset+=1;
}



void fullBlindnessForwardDisplay() {
image(movieForward, 0, 0, displayWidth, displayHeight);
image(fb, 0, 0, displayWidth, displayHeight);
}



void fullBlindnessReverseDisplay() {
image(movieReverse, 0, 0, displayWidth, displayHeight);
image(fb, 0, 0, displayWidth, displayHeight);
}



void mdForwardDisplay() {
image(movieForward, 0, 0, displayWidth, displayHeight);
image(md, 0, 0, displayWidth, displayHeight);
}



void mdReverseDisplay() {
image(movieReverse, 0, 0, displayWidth, displayHeight);
image(md, 0, 0, displayWidth, displayHeight);
}



void glaucomaForwardDisplay() {
image(movieForward, 0, 0, displayWidth, displayHeight);
image(glaucoma, 0, 0, displayWidth, displayHeight);
}



void glaucomaReverseDisplay() {
image(movieReverse, 0, 0, displayWidth, displayHeight);
image(glaucoma, 0, 0, displayWidth, displayHeight);
}



void astigForwardDisplay() {
image(movieForward, 0, 0, displayWidth, displayHeight);
}



void astigReverseDisplay() {
image(movieReverse, 0, 0, displayWidth, displayHeight);
}
