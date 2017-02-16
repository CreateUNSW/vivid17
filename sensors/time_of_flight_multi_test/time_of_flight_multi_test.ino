/*
 * Please read following link to get an idea of how to operate multiple sensors
 * tl;dr: use pinMode(pinNum, INPUT) to pull the XSHUT pin high and activate sensor
 *        and use digitalWrite(pinNum,LOW) to pull the XSHUT to GND for shutdown. 
 * https://github.com/pololu/vl53l0x-arduino/issues/1
 * 
 * This code requires the use of the following library:
 * https://github.com/pololu/vl53l0x-arduino
*/
#include <Wire.h>
#include <VL53L0X.h>

// XSHUT pin defines
#define SEN 52
#define SEN_2 53

// sensor classes
VL53L0X sensor;
VL53L0X sensor2; 

void setup() {

  pinMode(SEN, OUTPUT);
  pinMode(SEN_2, OUTPUT);
  digitalWrite(SEN_2, LOW);
  digitalWrite(SEN, LOW);

  delay(500);
  Wire.begin();

  Serial.begin (9600);

  pinMode(SEN_2, INPUT);
  delay(150);
  Serial.println("00");
  sensor.init(true);

  Serial.println("01");
  delay(100);
  sensor.setAddress((uint8_t)22);
  Serial.println("02");

  pinMode(SEN, INPUT);
  delay(150);
  sensor2.init(true);
  Serial.println("03");
  delay(100);
  sensor2.setAddress((uint8_t)25);
  Serial.println("04");

  Serial.println("addresses set");

  I2Cscan();
  sensor.startContinuous();
  sensor2.startContinuous();
}

void loop() {
    pinMode(SEN, INPUT);
    digitalWrite(SEN_2, LOW);
    Serial.println(sensor2.readRangeContinuousMillimeters());
    delay(10);
    digitalWrite(SEN, LOW);
    pinMode(SEN_2,INPUT);
    Serial.println(sensor.readRangeContinuousMillimeters());
    delay(1000);
}

// determine I2C address of each sensor
void I2Cscan() {
  Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;

  for (byte i = 1; i < 120; i++){
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0) {
      Serial.print ("Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      delay (1);
    } // end of good response
  } // end of for loop
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");

  delay(3000);
}
