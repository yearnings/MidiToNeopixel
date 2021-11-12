import themidibus.*;
import javax.sound.midi.MidiMessage;
import processing.serial.*;

MidiBus midi;
IntList activeNotes = new IntList();
Serial arduino;
String valToSend;

// run when your sketch runs
void setup(){
  midi = new MidiBus(this, "VBUS_A", -1);
  
  String port = Serial.list()[2];
  arduino = new Serial(this, port, 9600);
}


// run repeatedly every frame
void draw(){
  if(activeNotes.size() > 0){
    for(int n = 0; n < activeNotes.size(); n++){
      arduino.write(activeNotes.get(n));
    }
  } else {
    arduino.write(0);
  }
}

// called whenever we receive a midi message
void midiMessage(MidiMessage m){
  
  // the message type (eg note on/off)
  int status = m.getStatus();
  // data like which note (c# vs c etc)
  int msgData = m.getMessage()[1];
  
  if(status == 144) noteOn(msgData);
  if(status == 128) noteOff(msgData);
}

void noteOn(int noteNumber){
  if(!activeNotes.hasValue(noteNumber)){
    activeNotes.push(noteNumber);
  }
}

void noteOff(int noteNumber){
  if(activeNotes.hasValue(noteNumber)){
    int noteIndex = indexOf(noteNumber, activeNotes);
    activeNotes.remove(noteIndex);
  } else {
    println("Turning off note that isnt on" + noteNumber);
  }
}

// Return int representing the index of target data in a list
// or -1 if not found
int indexOf(int target, IntList source){
  for(int i = 0; i < source.size(); i++){
    if(source.get(i) == target) return i;
  }
  return -1;
}
