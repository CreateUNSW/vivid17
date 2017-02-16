/*
 * Multi-sensor test set up for Arduino Mega 2560
 * Wiring for SD card module SPI:
 * MOSI: 51
 * MISO: 50
 * SCK:  52
 * SS:   53
 */

#include <SPI.h>
#include <SD.h>
#include <TimeLib.h> //important: use TimeLib.h not Time.h
#include <DS1302RTC.h>
#include <Wire.h>
#include <VL53L0X.h>
#include <NewPing.h>

VL53L0X sensor; // Time of flight sensor
File myFile;

// Set pins for RTC module: CE/RST, IO/DAT, CLK
DS1302RTC RTC(5, 6, 7);

// Set pins for ultrasonic module
#define TRIGGER_PIN  14  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     15  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

tmElements_t tm; // class variable for storing the time

void setup() {
  analogWrite(A1, 255); // turns on an indicating LED on A1
  Serial.begin(9600);  
  while (!Serial);
  
  Serial.println("RTC module activated");
  delay(500);
  if (RTC.haltRTC()) {
    Serial.println("The DS1302 is stopped.  Please run the SetTime");
    Serial.println("example to initialize the time and begin running.");
    analogWrite(A1, 0); // switches off LED if this test isn't passed.
  }
  if (!RTC.writeEN()) {
    Serial.println("The DS1302 is write protected. This normal.");
  }
  delay(3000);

  // Initialises SD card reader module
  Serial.print("Initializing SD card...");
  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    analogWrite(A1, 0); // switches off LED if this test isn't passed.
    return;
  }
  Serial.println("initialization done.");
  // open the file
  myFile = SD.open("test1.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("file normal.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
    analogWrite(A1, 0); // switches off LED if this test isn't passed.
  }
  myFile.close();

  // set up for Time of Flight sensor
  Wire.begin();
  sensor.init();
  sensor.setTimeout(500);
  sensor.startContinuous();
  Serial.println("TOF activated");
  Serial.flush();
}

void loop() {
  // sets which date to stop at
  while (tm.Day < 15) {
    Serial.print(RTC.get()); // gets UNIX time
    myFile = SD.open("test.txt", FILE_WRITE); // open file
    // if read successful, prints time to file on SD card.
    if ((myFile)&&(! RTC.read(tm))) {
        myFile.print("Time = ");
        //Serial.print("Time = ");
        print2digits(tm.Hour);
        myFile.print(':');
        //Serial.print(':');    
        print2digits(tm.Minute);
        myFile.print(", Date (D/M/Y) = ");
        //Serial.print(", Date (D/M/Y) = ");
        myFile.print(tm.Day);
        //Serial.print(tm.Day);
        myFile.print('/');
        //Serial.print('/');
        myFile.print(tm.Month);
        //Serial.print(tm.Month);
        myFile.print('/');
        //Serial.print('/');
        myFile.print(tmYearToCalendar(tm.Year));
        //Serial.print(tmYearToCalendar(tm.Year));
        myFile.println();
        //Serial.println();    
    } else {
        Serial.println("Error! Please check the circuitry.");
        myFile.close();
        analogWrite(A1, 0); // turns off LED
        return;
    } 
    // prints ultrasonic
    unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
    myFile.print("Ping: ");
    myFile.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
    myFile.println("cm");
    delay(100);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    // prints time of flight
    myFile.print("TOF reading: ");
    myFile.println(sensor.readRangeContinuousMillimeters());
    if (sensor.timeoutOccurred()) {
        myFile.print(" TOF TIMEOUT");
        //Serial.print(" TOF TIMEOUT");
        myFile.close();
        analogWrite(A1, 0); // turns off LED
        return;
    }
    delay(100); 
    // prints IR sensor
    myFile.print("IR reading :");
    myFile.println(analogRead(A0));
    myFile.close();
    delay(30000); // wait 30 seconds before next reading
    Serial.flush(); // clean up serial 
  }
  analogWrite(A1, 0); // turns off LED
}

// prints minutes/hours to two digits
void print2digits(int number) {
  if (number >= 0 && number < 10) {
    myFile.print('0');
    //Serial.print('0');
  }
  myFile.print(number);
  //Serial.print(number);
}
