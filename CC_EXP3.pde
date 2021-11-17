import processing.serial.*;
import processing.video.*;
import processing.sound.*;

Serial myPort;

Movie myMovie1, myMovie2;
SoundFile myMusic;

int numFrames = 120;
int currentFrame = 0;
PImage[] images = new PImage[numFrames];
PImage md, fb, glaucoma;

int offset = 0;
Boolean playOnce = true;


void setup() {
  size(960, 540);
  myMovie1 = new Movie(this, "ch1.mp4");
  myMusic = new SoundFile(this, "sound.mp3");
  md = loadImage("md.png");
  fb = loadImage("fb.png");
  glaucoma = loadImage("glaucoma.png");
  for (int i = 0; i < numFrames; i++)
  {
    String imageName = "gif/gif-" + i + ".png";
    images[i] = loadImage(imageName);
  }
  String portName = Serial.list()[0]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
}
char instruction;
int toggle=0;
int videoStopped=0;

void draw() {
  image(myMovie1, 0, 0);
  myMovie1.play();
  if ( myPort.available() > 0) {
    instruction = myPort.readChar();
    toggle=1;
  }
  switch(instruction)
  {
  case 'N':

if (playOnce) {
playSoundOnce();
}

frameRate(18);

    print ("Chromesthesia");
    //Chromesthesia -----------------------------------------------------
    if (videoStopped==1)
      myMovie1.play();
    videoStopped=0;
    if (toggle==1)
      myMovie1.jump(0);
    toggle=0;
    currentFrame = (currentFrame+1) % numFrames; // Use % to cycle through frames
    offset = 0;
    image(images[(currentFrame+offset) % numFrames], 0, 0);
    offset+=1;
    break;
  case 'J':
    print ("Fullblindness");
    //Fullblindness -----------------------------------------------------
    if (videoStopped==1)
      myMovie1.play();
    videoStopped=0;
    if (toggle==1)
      myMovie1.jump(0);
    toggle=0;
    image(fb, 0, 0);
    break;
  case 'B':
    print ("MD");
    //Macular Degeneration -----------------------------------------------------
    if (videoStopped==1)
      myMovie1.play();
    videoStopped=0;
    if (toggle==1)
      myMovie1.jump(0);
    toggle=0;
    image(md, 0, 0);
    break;
  case 'G':
    print ("Glaucoma");
    //Glaucoma -----------------------------------------------------
    if (videoStopped==1)
      myMovie1.play();
    videoStopped=0;
    if (toggle==1)
      myMovie1.jump(0);
    toggle=0;
    image(glaucoma, 0, 0);
    break;
  case 'H':
    print (5);
    myMovie1.stop();
    videoStopped = 1;
    break;
  //case 'Y' :
  //  myMovie1.pause();
  //  break;
  }
}
void movieEvent(Movie m) {
  m.read();
}

void playSoundOnce()
{
myMusic.play();
playOnce = false;
}
