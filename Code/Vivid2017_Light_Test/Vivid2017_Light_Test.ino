#include "FastLED.h"

#define DATA_PIN 3
#define CLOCK_PIN 13

#define LED_TYPE UCS1903
#define BRIGHTNESS 64

#define NUM_STRIPS 3  // Total individual strips

#define NUM_WINGS 5 //Total wing designs
#define MAX_CRYSTALS 15 // Maximum number of crystals in a wing

#define NUM_CRYSTALS 40 // Total crystal designs
#define MAX_LEDS 10 // Maximum number of leds in a crystal

//int DataPins[NUM_STRIPS] = {3, 4, 5}; // Data pins for each led strip

//CRGB* Crystals[NUM_CRYSTALS]; // If using dynamic memory allocaation
CRGB Crystals[NUM_CRYSTALS][MAX_LEDS]; 
int WingCrystals[NUM_WINGS][MAX_CRYSTALS] = {
                                              {7,   3,  2,  5,  10},        // Index of crystals that correspond to each wing design 
                                              {8,   4,  20, 6,  7},
                                              {9,   11, 16, 17, 18},
                                              {12,  1,  15, 19, 13},
                                              {0,  22, 23, 24, 21}
                                            }; 

int NumLeds[NUM_CRYSTALS] = {7,  3,  2,  5,  10, 9,  6,  4,  2,  3,     // Number of LEDs in each respective crystal
                             5,  7,  2,  1,  3,  8,  5,  8,  4,  7,
                             7,  3,  2,  5,  10, 9,  6,  4,  2,  3,
                             5,  7,  2,  1,  3,  8,  5,  8,  4,  7}; 

int NumCrystals[NUM_WINGS] = {5, 5, 5, 5, 5}; // Number of Crystals in each respective wing

void setup() {
      /*
      //Dynamics memory array allocation
      for(int i=0;i<NUM_CRYSTALS; i++) {
       Crystals[i] = new CRGB[NUM_LEDS[i]];
      }*/
  
      // Set up all Crystals
      for (int i = 0; i < NUM_STRIPS; i++) {
        for (int j = 0; j < NUM_CRYSTALS; j++) {
            FastLED.addLeds <LED_TYPE, DATA_PIN, RGB> (Crystals[j], NumLeds[j]);
        }
      }
      
      FastLED.setBrightness(BRIGHTNESS);
}

void loop() { 
  for(int i = 0; i < 16; i++) {
    CrystalColour(i, 16*i, 16*i, 16*i);
//    crystalHSV(i, 16*i, 16*i, 16*i);
  }
  FastLED.show();
}

void CrystalColour(int index, int r, int g, int b) {
  for (int k = 0; k < NumLeds[index]; k++) Crystals[index][k] = CRGB(r, g, b);
}

void crystalHSV(int index, int h, int s, int v) {
  for (int k = 0; k < NumLeds[index]; k++) Crystals[index][k] = CRGB(0, 0, 0).setHSV(h, s, v);
}
void WingColour(int index, int r, int g, int b) {
  for (int h= 0; h < NumCrystals[index]; h++) CrystalColour(WingCrystals[index][h], r, g, b);
}

