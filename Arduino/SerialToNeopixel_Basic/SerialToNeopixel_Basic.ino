#include <Adafruit_NeoPixel.h>
#define LED_COUNT 12 // how many pixels are in the strip.
#define LED_PIN 12 // the pin we're using

// processing data in
char serialData;

// Neopixel init
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  strip.begin();
}

// the loop function runs over and over again forever
void loop() {
  if(Serial.available()){
    serialData = Serial.read();
  }

  // write a color to all of the pixels
  for(int p = 0; p < LED_COUNT; p++){
    if(serialData > 0){
      strip.setPixelColor(p, strip.Color(255,255,255));
    } else {
      strip.setPixelColor(p, strip.Color(0,0,50));
    }
    
  }
  
  strip.show();
}
