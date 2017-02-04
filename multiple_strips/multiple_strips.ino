#include "FastLED.h"

#define NUM_PINS 2
#define DATA_PIN0 6
#define DATA_PIN1 7
#define CLOCK_PIN 13

#define LED_TYPE WS2812
#define BRIGHTNESS 64

#define MAX_CRYST_PER_PIN 10 // Total crystal designs
#define LEDS_PER_PIN 50 // Maximum number of leds in a crystal

CRGB C[LEDS_PER_PIN * NUM_PINS];
int NumLeds[NUM_PINS * MAX_CRYST_PER_PIN] =
{
  10,6,2,3,6,
  1,7,7,1,6,
  //next pin
  5,5,5,5,5,
  5,5,5,5,5
};

void setup() {
      FastLED.addLeds<LED_TYPE, DATA_PIN0, RGB> (C, 0, LEDS_PER_PIN);
      FastLED.addLeds<LED_TYPE, DATA_PIN1, RGB> (C, LEDS_PER_PIN, LEDS_PER_PIN);
      // https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples
      // FastLED.addLeds<LED_TYPE, DATA_PIN2, RGB> (C, 2*LEDS_PER_PIN, LEDS_PER_PIN);
}

void loop() {
  CrystalColour(0,200,0,0);
  CrystalColour(1,0,200,0);
  CrystalColour(2,200,200,0);
  CrystalColour(3,0,0,200);
  CrystalColour(4,200,0,200);
  CrystalColour(5,0,200,200);
  CrystalColour(6,200,200,200);
  CrystalColour(7,200,0,0);
  CrystalColour(8,0,200,0);
  CrystalColour(9,200,200,0);
  CrystalColour(10,200,200,200);
  CrystalColour(11,200,0,0);
  CrystalColour(12,0,200,0);
  CrystalColour(13,200,200,0);
  CrystalColour(14,0,0,200);
  CrystalColour(15,200,0,200);
  CrystalColour(16,0,200,200);
  CrystalColour(17,200,200,200);
  CrystalColour(18,200,0,0);
  CrystalColour(19,0,200,0);
  FastLED.show();
}

void CrystalColour(int index, int r, int g, int b) {
  int offset = 0;
  for(int i =0;i< index; i++) {
    offset += NumLeds[i];
  }
  for (int k = 0; k < NumLeds[index]; k++) C[offset + k] = CRGB(r, g, b);
}
