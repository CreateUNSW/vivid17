#include "FastLED.h"
#include "math.h"

#define NUM_PINS 2
#define DATA_PIN0 2
#define DATA_PIN1 8
#define CLOCK_PIN 13
#define LED_TYPE WS2812
#define LED_TYPE1 UCS1903

#define BRIGHTNESS 255
#define GRADIENT_SPEED 50

#define LEDS_PER_PIN 24 // Maximum number of leds in a crystal
#define MAX_CRYSTAL_NUM 16
CRGB C[51];

int NumLeds[51] =
{
  8,1,2,3,2,3,1,4,1,2,5,5,3,2,7,1,4
};

uint8_t t = 0;

void setup() {
  FastLED.addLeds<LED_TYPE1, DATA_PIN1, RGB> (C, 0, LEDS_PER_PIN); // sets up strip one
  FastLED.addLeds<LED_TYPE, DATA_PIN0, RGB> (C, LEDS_PER_PIN, 26); // sets up strip 2
  FastLED.setBrightness(BRIGHTNESS); // brightness
  srand(10);
  for(int i = 0; i < MAX_CRYSTAL_NUM; i++) {
    CrystalHSV(i, rand(), 255, 255);
  }
  FastLED.show();
}

void loop() {  
  for(int i = 0; i < 51; i++) {
    C[i] = CRGB(0,0,0).setHSV(t+i*10, 255, 255);
  }
  t++;
  delay(10);
  FastLED.show();
}

// colours a specific crystal
void CrystalColour(int crystId, int r, int g, int b) {
  int offset = 0;
  // choose leds in a given crystal id
  for(int i =0;i< crystId; i++) offset += NumLeds[i];

  // lights up led in the crystal
  for (int k = 0; k < NumLeds[crystId]; k++) C[offset + k] = CRGB(r, b, g);
}

void CrystalHSV(int crystId, int r, int g, int b) {
  int offset = 0;
  // choose leds in a given crystal id
  for(int i =0;i< crystId; i++) offset += NumLeds[i];

  // lights up led in the crystal
  for (int k = 0; k < NumLeds[crystId]; k++) C[offset + k] = CRGB(0,0,0).setHSV(r, b, g);
}

