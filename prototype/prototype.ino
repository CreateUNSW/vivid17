#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS0 4
#define NUM_LEDS1 7
#define NUM_LEDS2 2
#define NUM_LEDS3 4
#define NUM_LEDS4 7
#define NUM_LEDS5 7
// daniel fucking with the library
#define AUTO_OFFSET 1

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
#define CLOCK_PIN 13

// Define the array of leds
CRGB crystal0[NUM_LEDS1];
CRGB crystal1[NUM_LEDS1];
CRGB crystal2[NUM_LEDS2];
CRGB crystal3[NUM_LEDS3];
CRGB crystal4[NUM_LEDS4];
CRGB crystal5[NUM_LEDS5];

void setup() {
      FastLED.addLeds<UCS1903, DATA_PIN, RGB> (crystal0, AUTO_OFFSET, NUM_LEDS1);
      FastLED.addLeds<UCS1903, DATA_PIN, RGB> (crystal1, AUTO_OFFSET, NUM_LEDS2);
      FastLED.addLeds<UCS1903, DATA_PIN, RGB> (crystal2, AUTO_OFFSET, NUM_LEDS3);
      FastLED.addLeds<UCS1903, DATA_PIN, RGB> (crystal3, AUTO_OFFSET, NUM_LEDS4);
      FastLED.addLeds<UCS1903, DATA_PIN, RGB> (crystal4, AUTO_OFFSET, NUM_LEDS5);
}

void loop() { 
   for(int i = 0; i < NUM_LEDS0; i++) {
    crystal0[i] = CRGB::Red;
   }
   for(int i = 0; i < NUM_LEDS1; i++) {
    crystal1[i] = CRGB::Red;
   }
   for(int i = 0; i < NUM_LEDS2; i++) {
    crystal2[i] = CRGB::Red;
   }
   for(int i = 0; i < NUM_LEDS3; i++) {
    crystal3[i] = CRGB::Red;
   }
   for(int i = 0; i < NUM_LEDS4; i++) {
    crystal4[i] = CRGB::Red;
   }
   for(int i = 0; i < NUM_LEDS5; i++) {
    crystal5[i] = CRGB::Red;
   }
   
}
