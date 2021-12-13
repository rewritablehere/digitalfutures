/*
This plays the everyday sounds but is reactive to movement and the ditance between the brains
*/

import processing.serial.*;
import processing.sound.*;

Serial myPort;
SoundFile soundfile;

void setup() {
  size(640, 360);
  background(255);

  String portName = Serial.list()[1]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
  
  // Load a soundfile
  soundfile = new SoundFile(this, "sound.mp3");

  // Indication that soundfile was picked up
  println("SFSampleRate= " + soundfile.sampleRate() + " Hz");
  println("SFSamples= " + soundfile.frames() + " samples");
  println("SFDuration= " + soundfile.duration() + " seconds");

  // Play the file in a loop
  soundfile.loop();
}      

int instruction;

void draw() {
  
  if (myPort.available() > 0) {
    instruction = myPort.read(); // reading normalized value and modulating sound file with distance values
  }
  if(instruction > 0 && instruction < 50)
  {
    if (soundfile.isPlaying()) {
    // Map distance from 0.25 to 4.0 for playback rate. 1 equals original playback speed,
    // 2 is twice the speed and will sound an octave higher, 0.5 is half the speed and
    // will make the file sound one octave lower.
    float playbackSpeed = map(instruction, 0, 50, 0.25, 4.0);
    soundfile.rate(playbackSpeed); 
    } else {
    soundfile.play();
    }
  

  } else if (instruction > 50 && soundfile.isPlaying())
  {
    soundfile.pause();
  } else if (instruction < 0 && soundfile.isPlaying())
  {
    soundfile.pause();
  }
}
