#ifdef __cplusplus
extern "C" {
#endif
int _isatty (){
  return 0;
}
int _fstat (){
  return 1;
}
#ifdef __cplusplus
}
#endif
#include "malloc.h"

#include <FastLED.h>
#include "Graph.hpp"
#include "RGBtoHSV.hpp"


// IO/Hardware config
//--------------------------------------------------
#define RIGHT_GREEN 2
#define RIGHT_YELLOW 7
#define RIGHT_PINK 8
#define RIGHT_BLUE 14
#define LEFT_GREEN 5
#define LEFT_YELLOW 6
#define LEFT_PINK 20
#define LEFT_BLUE 21

#define RG_INDEX 0
#define RY_INDEX 172
#define RP_INDEX 352
#define RB_INDEX 510
#define LB_INDEX 755
#define LP_INDEX 1029
#define LY_INDEX 1193
#define LG_INDEX 1372+2
#define MAX_LED_NUM 1548+2

#define CLOCK_PIN 13

#define NUM_SENSORS 5

#define LED_TYPE UCS1903
#define BRIGHTNESS 100
//--------------------------------------------------

// Crystals/LEDs config
//--------------------------------------------------
#define NUM_CRYSTALS 291
//--------------------------------------------------

CRGB leds[MAX_LED_NUM];
uint16_t firstLED[291] = {0,5,10,13,16,21,27,33,40,45,48,54,58,67,71,75,79,85,88,94,100,107,111,115,122,129,133,138,144,152,158,165,172,176,182,186,190,194,198,202,206,211,215,219,223,228,236,245,250,254,260,263,267,271,275,282,287,292,298,304,307,313,318,325,333,338,345,352,356,362,367,372,377,383,389,392,395,398,402,407,414,420,429,432,434,439,447,451,455,459,462,465,469,473,482,488,491,495,504,510,515,521,529,533,536,542,550,555,562,566,572,578,585,590,595,602,607,610,615,622,630,633,637,641,647,654,658,666,675,681,688,692,696,699,706,713,716,724,730,734,740,743,746,752,755,761,765,776,786,796,807,810,816,824,829,836,840,846,852,859,864,869,876,881,884,889,896,904,907,911,915,921,928,932,940,949,955,962,966,970,973,980,987,990,998,1004,1008,1014,1017,1020,1026,1029,1033,1038,1043,1048,1054,1060,1063,1069,1075,1078,1081,1085,1090,1097,1103,1112,1115,1117,1122,1130,1134,1138,1142,1145,1148,1152,1156,1165,1171,1174,1178,1187,1193,1197,1202,1206,1210,1215,1219,1223,1227,1231,1235,1239,1243,1248,1256,1265,1270,1274,1280,1283,1288,1292,1296,1303,1309,1314,1320,1326,1329,1335,1340,1347,1355,1360,1367,1374,1383,1388,1391,1394,1399,1405,1411,1418,1423,1426,1432,1436,1445,1449,1453,1457,1463,1466,1472,1478,1485,1489,1493,1500,1507,1511,1516,1522,1530,1536,1543};
uint16_t lastLED[291] = {4,9,12,15,20,26,32,39,44,47,53,57,66,70,74,78,84,87,93,99,106,110,114,121,128,132,137,143,151,157,164,171,175,181,185,189,193,197,201,205,210,214,218,222,227,235,244,249,253,259,262,266,270,274,281,286,291,297,303,306,312,317,324,332,337,344,351,355,361,366,371,376,382,388,391,394,397,401,406,413,419,428,431,433,438,446,450,454,458,461,464,468,472,481,487,490,494,503,509,514,520,528,532,535,541,549,554,561,565,571,577,584,589,594,601,606,609,614,621,629,632,636,640,646,653,657,665,674,680,687,691,695,698,705,712,715,723,729,733,739,742,745,751,754,760,764,775,785,795,806,809,815,823,828,835,839,845,851,858,863,868,875,880,883,888,895,903,906,910,914,920,927,931,939,948,954,961,965,969,972,979,986,989,997,1003,1007,1013,1016,1019,1025,1028,1032,1037,1042,1047,1053,1059,1062,1068,1074,1077,1080,1084,1089,1096,1102,1111,1114,1116,1121,1129,1133,1137,1141,1144,1147,1151,1155,1164,1170,1173,1177,1186,1192,1196,1201,1205,1209,1214,1218,1222,1226,1230,1234,1238,1242,1247,1255,1264,1269,1273,1279,1282,1287,1291,1295,1302,1308,1313,1319,1325,1328,1334,1339,1346,1354,1359,1366,1373,1382,1387,1390,1393,1398,1404,1410,1417,1422,1425,1431,1435,1444,1448,1452,1456,1462,1465,1471,1477,1484,1488,1492,1499,1506,1510,1515,1521,1529,1535,1542,1549};

#define WING_1_SIZE 109
#define WING_2_SIZE 82
#define WING_3_SIZE 83
#define WING_4_SIZE 89
#define WING_5_SIZE 88

bool wing1[291] = {0,0,0,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool wing2[291] = {0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool wing3[291] = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool wing4[291] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool wing5[291] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

Graph * g;
int *dist = NULL;

// Time variables
uint8_t t = 0;

// HSV variables 
// NOTE: uint8_t allows you to have a range 0-255 without having to mod any values (via 8-bit overflow)
uint8_t hue = 0;
uint8_t hueDelta = 1;

// sensor variables
uint8_t sensorPins[NUM_SENSORS] = {17, 18, 19, 22, 23};

// Pattern global variables
int oldCentre = -1;
std::vector <int> dynRndArray;
int dynRndTime = 7;


void setup() {
  srand(0);
  Serial.begin(9600);
  FastLED.addLeds<LED_TYPE, RIGHT_GREEN, RGB>(leds, RG_INDEX, 172);
  FastLED.addLeds<LED_TYPE, RIGHT_YELLOW, RGB>(leds, RY_INDEX, 180);
  FastLED.addLeds<LED_TYPE, RIGHT_PINK, RGB> (leds, RP_INDEX, 158);
  FastLED.addLeds<LED_TYPE, RIGHT_BLUE, RGB> (leds, RB_INDEX, 245);
  FastLED.addLeds<LED_TYPE, LEFT_BLUE, RGB> (leds, LB_INDEX, 274);
  FastLED.addLeds<LED_TYPE, LEFT_PINK, RGB> (leds, LP_INDEX, 164);
  FastLED.addLeds<LED_TYPE, LEFT_YELLOW, RGB> (leds, LY_INDEX, 179+2);
  FastLED.addLeds<LED_TYPE, LEFT_GREEN, RGB> (leds, LG_INDEX, 176);
  g = new Graph();
  
  for(int i = 0; i < NUM_CRYSTALS; i++) {
    crystalHSV(i, rand() % 255,  rand() % 100 + 155, 255); 
  }
  FastLED.show();

  for (int i = 0; i < NUM_SENSORS; i++) {
    pinMode(sensorPins[i], INPUT);
  }
}

void loop() {
  
// Measures execution time
//--------------------------------
  unsigned long duration = micros();
  float total = 0;
//--------------------------------
//=================================================
// PATTERN CODE GOES HERE

  //chrisWings();
  //randomDynamic();

  bool *currWing = NULL;
  bool wingOn = true;

  // Note sensors are active low
  if(!digitalRead(sensorPins[0])) {
    if(!digitalRead(sensorPins[4]) && !digitalRead(sensorPins[3]) && !digitalRead(sensorPins[2]) && !digitalRead(sensorPins[1]) && !digitalRead(sensorPins[0])) {
      currWing = wing5;
    } else if(!digitalRead(sensorPins[3]) && !digitalRead(sensorPins[2]) && !digitalRead(sensorPins[1]) && !digitalRead(sensorPins[0])) {
      currWing = wing4;
    } else if(!digitalRead(sensorPins[2]) && !digitalRead(sensorPins[1]) && !digitalRead(sensorPins[0])) {
      currWing = wing3;
    } else if(!digitalRead(sensorPins[1]) && !digitalRead(sensorPins[0])) {
      currWing = wing2;
    } else if(!digitalRead(sensorPins[0])) {
      currWing = wing1;
    } else {
      currWing = NULL;
      wingOn = false;
    }
    shimmerCenter(currWing, 259);
  }
  
//=================================================
  // t is global timer of range 0-255, don't change at all only use, create your own timer if needed
  t++;
  FastLED.show();
// Measures execution time
//--------------------------------
  duration = micros() - duration;
  total += duration;
  Serial.print("\nTime per loop: ");
  Serial.print(total);
  Serial.println(" microseconds");
  Serial.print("FPS: ");
  Serial.println(1000000/(float)total);
//--------------------------------

// Measures RAM usage
//--------------------------------
  int ramUsage = 196608 - freeRAM() + mallinfo().uordblks;
  Serial.print("Ram usage: ");
  Serial.print((float)ramUsage/196608 * 100);
  Serial.print("% | ");
  Serial.print(ramUsage);
  Serial.println("/196608 bytes");
//--------------------------------
  
// Reads and prints sensor output 
//--------------------------------
  Serial.print("Sensor values: ");
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print(digitalRead(sensorPins[i]));
  }
  Serial.println();
//--------------------------------
  
}

//FADE TO FUNCTION
//takes in current state of led and target state and transitions to it
//fadeTo() {
  
//}

void chrisWings() {
  int chris[291*3] = {110,65,0,0,67,171,0,0,0,0,0,0,0,149,211,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,110,65,0,86,0,163,1,2,144,0,39,157,0,0,0,0,10,146,20,0,145,116,0,173,69,0,157,50,0,151,0,14,148,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,174,250,0,198,168,0,190,242,0,198,0,0,149,0,0,118,0,0,23,0,30,0,0,77,0,0,35,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,110,65,0,110,65,0,0,0,198,0,0,43,110,65,0,0,0,0,0,0,0,110,65,0,110,65,0,0,76,0,0,167,0,0,232,0,193,251,9,0,250,0,164,241,13,68,202,29,1,180,57,0,0,0,0,0,0,0,246,0,0,170,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,110,65,0,110,65,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,110,65,0,0,0,0,110,65,0,110,65,0,0,189,94,0,219,166,0,0,240,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,110,65,0,110,65,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,110,65,0,0,0,0,110,65,0,110,65,0,0,184,80,0,211,148,0,251,230,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,110,65,0,110,65,0,110,65,0,248,0,198,0,0,58,110,65,0,0,0,0,0,0,0,110,65,0,110,65,0,0,62,0,0,151,0,0,223,0,211,252,6,0,243,0,186,249,10,89,210,25,12,181,49,0,0,0,0,0,0,0,237,0,0,152,0,0,0,0,0,0,0,0,0,0,0,0,0,110,65,0,0,4,144,79,0,160,104,0,168,12,0,144,0,47,162,0,0,0,0,18,149,55,0,153,36,0,148,0,26,152,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,188,233,0,198,144,0,181,228,0,198,0,0,164,0,0,139,0,0,37,0,19,0,0,59,0,0,21,0,0,0,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,110,65,0,0,71,172,0,0,0,0,0,0,0,165,220,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  for(int i = 0; i < 291*3; i++) {
      crystalRGB(i/3, chris[i++], chris[i++], chris[i]);
  }
}


// Shimmer pattern
// @arg wing: pass in wing array to light up that wing, or pass in NULL to light up whole wall
// @arg centre: crystal ID for gradient centre
void shimmerCenter(bool *wing, int centre) {
  // remove next line when sensors are implemented, timer is used to fading pattern
  // if sensor detected, timer ++(cap at 255), else timer --(cap at 0)
  int timer = 255;

  // recalculate distance array if center changes
  if(centre != oldCentre) {
    oldCentre = centre;
    if(dist != NULL) delete[] dist;
    dist = g->calcDist(centre);
  }

  // Constants
  double minSaturation = 0.8;
  int maxDist = 15; // Acts as stretching factor to rainbow
  double globalBrightness = 0.5;

  // Pattern algorithm
  for(int i = 0; i < NUM_CRYSTALS; i++) {
    if(wing == NULL || wing[i]) {
      double hue = ((float)dist[i]/50)*255 + t*5;
      if(hue >= 255) hue = hue - 255;
      crystalHSV(i, hue, ((float)(rand()%21)/100+minSaturation)*255, 255);//255-((float)dist[i]/maxDist)*((float)timer))*globalBrightness);
    } else {
      // Turns off other crystals
      crystalHSV(i, 0, 0, 0);
    }
  }
}

void randomDynamic() {
  //every random period of time between 3-10 seconds
  //add a crystal to the array
  if(t % 100 / 10 == dynRndTime) {
    dynRndTime = rand() % 7 + 3;
    for(int i = rand() % 10; i > 0; i--) {
      dynRndArray.insert(dynRndArray.begin(), rand() % 291);
    }
    for(int i = dynRndArray.size()/3; i > 0; i--) {
      dynRndArray.erase(dynRndArray.begin() + (rand() % dynRndArray.size()));
    }
  }
  // all the crystal in the arryalist increment hue by random ammount between 1-20
  for (unsigned i = 0; i < dynRndArray.size(); i++) {
    int red = leds[firstLED[dynRndArray.at(i)]+1].red;
    int green = leds[firstLED[dynRndArray.at(i)]+1].green;
    int blue = leds[firstLED[dynRndArray.at(i)]+1].blue;
    int hue = rgb2hsv(red, green, blue) + 1;
    crystalHSV(dynRndArray.at(i),  hue, 255, 255);
    Serial.println(hue);
  }
}

void crystalRGB(int index, int r, int g, int b) {
  for (int i = firstLED[index]; i <= lastLED[index]; i++) leds[i] = CRGB(r, b, g);
}

void crystalHSV(int index, int h, int s, int v) {
  for (int i = firstLED[index]; i <= lastLED[index]; i++) leds[i].setHSV(h, s, v);
}

uint32_t freeRAM(){ // for Teensy 3.5
    uint32_t stackTop;
    uint32_t heapTop;

    // current position of the stack.
    stackTop = (uint32_t) &stackTop;

    // current position of heap.
    void* hTop = malloc(1);
    heapTop = (uint32_t) hTop;
    free(hTop);

    // The difference is the free, available ram.
    return stackTop - heapTop;
}
