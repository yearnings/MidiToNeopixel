#include <Adafruit_NeoPixel.h>
#define STRIP_LENGTH 12 // Number of pixels on LED strip
#define LEDPIN 12 // the pin we're using 

// Processing data in
char serialData;

// Neopixel setup
Adafruit_NeoPixel strip(STRIP_LENGTH, LEDPIN, NEO_GRB + NEO_KHZ800);

// midi note codes for drums – feel free to change or delete these.
int kick = 39;
int snare = 40;
int hat = 44;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Start listening to serial data
  Serial.begin(9600);
  
  // Start Neopixels
  strip.begin();
}

// the loop function runs over and over again forever
void loop() {
  // Get serial data (from processing) when available
  if(Serial.available()){
    serialData = Serial.read();
  }

  for(int px = 0; px < STRIP_LENGTH; px++) {
    if(px < 3){
      if(serialData == kick) {
        strip.setPixelColor(px, strip.Color(255,0,00));
      } else {
        strip.setPixelColor(px, strip.Color(5,0,3*(px+1)));
      }
    }
    if(px >= 3 && px < 10){
      if(serialData == snare) {
        strip.setPixelColor(px, strip.Color(255,255,255));
      } else {
        strip.setPixelColor(px, strip.Color(5,0,3*(px+1)));
      }
    }   
    if(px >=10){
      if(serialData == hat) {
        strip.setPixelColor(px, strip.Color(30,30,30));
      } else {
        strip.setPixelColor(px, strip.Color(5,0,3*(px+1)));
      }
    }    
  }
  // update the entire strip at once
  strip.show();

}
