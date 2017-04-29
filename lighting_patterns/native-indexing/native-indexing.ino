#include "FastLED.h"
#include "Graph.hpp"
#include "math.h"

// setup variables
#define NUM_PINS 2
#define DATA_PIN0 2
#define DATA_PIN1 8
#define CLOCK_PIN 13
#define LED_TYPE WS2812

// pattern variables
#define BRIGHTNESS 255
#define GRADIENT_SPEED 50

#define MAX_CRYST_PER_PIN 10 // Total crystal designs
#define LEDS_PER_PIN 27 // Maximum number of leds in a crystal

CRGB C[LEDS_PER_PIN * NUM_PINS];
int NumLeds[NUM_PINS * MAX_CRYST_PER_PIN] =
{
//0  1  2  3  4  5  6  7  8  9 10 11 12 13 15 16 18
  0, 2, 7, 1, 3, 6, 5, 2, 1, 4, 1, 2, 2, 2, 9, 4, 4
};


int lookup[MAX_CRYSTALS_NUM] = 
{
  0,15,18,13,12,3,4,11,10,16,5,6,7,8,9,2,1
};

int crystals[2][NUM_PINS * MAX_CRYST_PER_PIN] = 
{
// N/A      1        2        3     *DO THE REST*
  {0,0}, {37,45}, {50,53}, {35,36}
}

// global variables
Graph * g;
int *dist;
double x = 0;

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN0, RGB> (C, 0, LEDS_PER_PIN); // sets up strip one
  FastLED.addLeds<LED_TYPE, DATA_PIN1, RGB> (C, LEDS_PER_PIN, 40); // sets up strip 2
  // FastLED.addLeds<LED_TYPE, DATA_PIN2, RGB> (C, 2*LEDS_PER_PIN, LEDS_PER_PIN);
  FastLED.setBrightness(BRIGHTNESS); // brightness
  // hardcode for setting up graph
  int edges[MAX_CRYSTALS_NUM][MAX_EDGE_PER_CRYSTAL + 1] = {{-1}, {7, 4, 2, 18, 15, 3, 16, 6, 5, -1}, {8, 9, 7, 6, 4, 3, 1, -1}, {11, 13, 12, 4, 2, 18, 16, 15, 1, -1}, {10, 12, 11, 9, 3, 2, 1, -1}, {14, 16, 6, 1, -1}, {7, 2, 16, 5, 1, -1}, {9, 8, 6, 2, 1, -1}, {9, 7, 2, -1}, {11, 10, 8, 7, 4, 2, -1}, {11, 9, 4, -1}, {10, 9, 12, 4, 3, -1}, {11, 4, 18, 13, 3, -1}, {17, 18, 12, 3, -1}, {16, 5, -1}, {18, 16, 3, 1, -1}, {14, 18, 15, 3, 6, 5, 1, -1}, {18, 13, -1}, {17, 13, 12, 16, 15, 3, 1, -1}};
  g = new Graph(edges,MAX_CRYSTALS_NUM); // sets up graphs
  dist = g->calcDist(lookup[1]); // distance array
}

void loop() {
  int i;
  double offSet = 0;
  
  for(i = 1; i < MAX_CRYSTALS_NUM; i++) {
    // algorithm for gradient pattern
    offSet = dist[lookup[i]]/2;
    CrystalColour(i, (sin(x / 10 + offSet * 3.14)        + 1) * 122,
                     (sin(x / 10 + offSet * 3.14 + 3.14) + 1) * 122,
                     0);
  }
  
  delay(GRADIENT_SPEED);
  x++;
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

