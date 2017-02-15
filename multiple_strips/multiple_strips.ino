#include "FastLED.h"
#include "Graph.hpp"

#define NUM_PINS 2
#define DATA_PIN0 8
#define DATA_PIN1 2
#define CLOCK_PIN 13

#define LED_TYPE WS2812
#define BRIGHTNESS 64

#define MAX_CRYST_PER_PIN 10 // Total crystal designs
#define LEDS_PER_PIN 27 // Maximum number of leds in a crystal

CRGB C[LEDS_PER_PIN * NUM_PINS];
int NumLeds[NUM_PINS * MAX_CRYST_PER_PIN] =
{
  0,2,7,1,3,6,5,2,1,4,1,2,2,2,9,4,4
};
//,1,2,2,2,9,4,4
int lookup[MAX_CRYSTALS_NUM] = 
{0,15,18,13,12,3,4,11,10,16,5,6,7,8,9,2,1};
//,5,6,7,8,9,2,1
Graph * g;
int *dist;
int blue = 0;
int blueFlag = 0;

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN0, RGB> (C, 0, LEDS_PER_PIN);
  int edges[MAX_CRYSTALS_NUM][MAX_EDGE_PER_CRYSTAL + 1] = {{-1}, {7, 4, 2, 18, 15, 3, 16, 6, 5, -1}, {8, 9, 7, 6, 4, 3, 1, -1}, {11, 13, 12, 4, 2, 18, 16, 15, 1, -1}, {10, 12, 11, 9, 3, 2, 1, -1}, {14, 16, 6, 1, -1}, {7, 2, 16, 5, 1, -1}, {9, 8, 6, 2, 1, -1}, {9, 7, 2, -1}, {11, 10, 8, 7, 4, 2, -1}, {11, 9, 4, -1}, {10, 9, 12, 4, 3, -1}, {11, 4, 18, 13, 3, -1}, {17, 18, 12, 3, -1}, {16, 5, -1}, {18, 16, 3, 1, -1}, {14, 18, 15, 3, 6, 5, 1, -1}, {18, 13, -1}, {17, 13, 12, 16, 15, 3, 1, -1}};
  g = new Graph(edges,MAX_CRYSTALS_NUM);
  Serial.begin(9600);
  FastLED.addLeds<LED_TYPE, DATA_PIN1, RGB> (C, LEDS_PER_PIN, 40);
  // https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples
  // FastLED.addLeds<LED_TYPE, DATA_PIN2, RGB> (C, 2*LEDS_PER_PIN, LEDS_PER_PIN);
  dist = g->calcDist(lookup[1]);
}

void loop() {

  int i;
  int red=0, green=0; 
  for(i = 1; i < 17; i++) {
    red = dist[lookup[i]]*85;
    green =  255-(dist[lookup[i]]*85);
    CrystalColour(i, red, blue,green);
//    Serial.print(lookup[i]);
//    Serial.println(dist[lookup[i]]);
      Serial.println(blue);
  }
  delay(30);
//  delete dist;

  if(blue >= 40) {
    blueFlag = 1;
  } else if(blue == 0) {
    blueFlag = 0;
  }

  if(blueFlag == 0) {
    blue++;
  } else {
    blue--;
  }
  FastLED.show();
}

void CrystalColour(int index, int r, int g, int b) {
  int offset = 0;
  for(int i =0;i< index; i++) {
    offset += NumLeds[i];
  }
  for (int k = 0; k < NumLeds[index]; k++) C[offset + k] = CRGB(r, g, b);
}

