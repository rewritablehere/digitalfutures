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

  // Load a soundfile
  soundfile = new SoundFile(this, "sound.mp3");

  // Indication that soundfile was picked up
  println("SFSampleRate= " + soundfile.sampleRate() + " Hz");
  println("SFSamples= " + soundfile.frames() + " samples");
  println("SFDuration= " + soundfile.duration() + " seconds");

  // Play the file in a loop
  soundfile.loop();
}      

char instruction;

void draw() {
  
  if (myPort.available() > 0) {
    instruction = myPort.readChar();
  }
  if(instruction > 29 && instruction < 81)
  {
    if (soundfile.isPlaying()) {
    // Map distance from 0.25 to 4.0 for playback rate. 1 equals original playback speed,
    // 2 is twice the speed and will sound an octave higher, 0.5 is half the speed and
    // will make the file sound one octave lower.
    float playbackSpeed = map(instruction, -30, -80, 0.25, 4.0);
    soundfile.rate(playbackSpeed); 
    } else {
    soundfile.play();
    }
  

  } else if (instruction > -30 && soundfile.isPlaying())
  {
    soundfile.pause();
  } else if (instruction < -80 && soundfile.isPlaying())
  {
    soundfile.pause();
  }
}
