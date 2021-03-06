#include "FastLED.h"
#include "Graph.hpp"
#include "math.h"

#define NUM_PINS 2
#define DATA_PIN0 2
#define DATA_PIN1 8
#define CLOCK_PIN 13

#define LED_TYPE WS2812
#define BRIGHTNESS 255

#define MAX_CRYST_PER_PIN 10 // Total crystal designs
#define LEDS_PER_PIN 27 // Maximum number of leds in a crystal

CRGB C[LEDS_PER_PIN * NUM_PINS];
int NumLeds[NUM_PINS * MAX_CRYST_PER_PIN] =
{
  0,2,7,1,3,6,5,2,1,4,1,2,2,2,9,4,4
};

int lookup[MAX_CRYSTALS_NUM] = 
{
  0,15,18,13,12,3,4,11,10,16,5,6,7,8,9,2,1
};

Graph * g;
int *dist;
double x = 0;

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN0, RGB> (C, 0, LEDS_PER_PIN);
  FastLED.addLeds<LED_TYPE, DATA_PIN1, RGB> (C, LEDS_PER_PIN, 40);
  // FastLED.addLeds<LED_TYPE, DATA_PIN2, RGB> (C, 2*LEDS_PER_PIN, LEDS_PER_PIN);
  FastLED.setBrightness(BRIGHTNESS);
  
  int edges[MAX_CRYSTALS_NUM][MAX_EDGE_PER_CRYSTAL + 1] = {{-1}, {7, 4, 2, 18, 15, 3, 16, 6, 5, -1}, {8, 9, 7, 6, 4, 3, 1, -1}, {11, 13, 12, 4, 2, 18, 16, 15, 1, -1}, {10, 12, 11, 9, 3, 2, 1, -1}, {14, 16, 6, 1, -1}, {7, 2, 16, 5, 1, -1}, {9, 8, 6, 2, 1, -1}, {9, 7, 2, -1}, {11, 10, 8, 7, 4, 2, -1}, {11, 9, 4, -1}, {10, 9, 12, 4, 3, -1}, {11, 4, 18, 13, 3, -1}, {17, 18, 12, 3, -1}, {16, 5, -1}, {18, 16, 3, 1, -1}, {14, 18, 15, 3, 6, 5, 1, -1}, {18, 13, -1}, {17, 13, 12, 16, 15, 3, 1, -1}};
  g = new Graph(edges,MAX_CRYSTALS_NUM);
}

void loop() {

  dist = g->calcLine(lookup[8], lookup[2]);
  int i;
  for(i = 0; i < 7; i++) {
    if(dist[i] > 0) {
      CrystalColour(ltn(dist[i]), 255,255,255);
    }
  }
  dist = g->calcLine(lookup[2], lookup[9]);
  for(i = 0; i < 7; i++) {
    if(dist[i] > 0) {
      CrystalColour(ltn(dist[i]), 255,255,255);
    }
  }
  dist = g->calcLine(lookup[9], lookup[13]);
  for(i = 0; i < 7; i++) {
    if(dist[i] > 0) {
      CrystalColour(ltn(dist[i]), 255,255,255);
    }
  }
  delay(50);
  x++;
  
  
  FastLED.show();
}

void CrystalColour(int index, int r, int g, int b) {
  int offset = 0;
  for(int i =0;i< index; i++) {
    offset += NumLeds[i];
  }
  for (int k = 0; k < NumLeds[index]; k++) C[offset + k] = CRGB(r, b, g);
}


int ltn(int lookup_index) {
  int index = 0;
  while(lookup_index != lookup[index]) index++;
  return index;
}

