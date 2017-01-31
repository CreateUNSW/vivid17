#include <SPI.h>
#include <SD.h>
#include <Time.h>
#include <DS1302RTC.h>
#include <Wire.h>
#include <VL53L0X.h>
#include <NewPing.h>

VL53L0X sensor;
File myFile;
tmElements_t tm;
int i = 0;

// Set pins:  CE, IO,CLK
DS1302RTC RTC(5, 6, 7);

#define TRIGGER_PIN  3  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(9600);  
  while (!Serial);
  
  Serial.println("RTC module activated");
  delay(500);
  if (RTC.haltRTC()) {
    Serial.println("The DS1302 is stopped.  Please run the SetTime");
    Serial.println("example to initialize the time and begin running.");
  }
  if (!RTC.writeEN()) {
    Serial.println("The DS1302 is write protected. This normal.");
  }
  delay(3000);
  
  Serial.print("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  // open the file
  myFile = SD.open("test.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("file normal.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  myFile.close();
  
  Wire.begin();
  sensor.init();
  sensor.setTimeout(500);
  // Start continuous back-to-back mode
  sensor.startContinuous();
  Serial.println("TOF activated");
  Serial.flush();
}

void loop() {
  while (tm.Day <40) {
    Serial.print(RTC.get());
    myFile = SD.open("test.txt", FILE_WRITE);
    if (! RTC.read(tm)) {
      myFile.print("Time = ");
      print2digits(tm.Hour);
      myFile.print(':');
      print2digits(tm.Minute);
      myFile.print(", Date (D/M/Y) = ");
      myFile.print(tm.Day);
      myFile.print('/');
      myFile.print(tm.Month);
      myFile.print('/');
      myFile.print(tmYearToCalendar(tm.Year));
      myFile.println();
    } else {
      Serial.println("DS1302 read error!  Please check the circuitry.");
      delay(5000);
    } 
    // Send ping, get ping time in microseconds (uS).
    unsigned int uS = sonar.ping(); 
    myFile.print("Ping: ");
    // Convert ping time to distance in cm and print result (0 = outside set distance range)
    myFile.print(uS / US_ROUNDTRIP_CM); 
    myFile.println("cm");
    // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    delay(100);                      
    myFile.print("TOF reading: ");
    myFile.println(sensor.readRangeContinuousMillimeters());
    if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
    delay(100); 
    myFile.print("IR reading :");
    myFile.println(analogRead(A0));
    myFile.close();
    delay(30000);
    Serial.flush();
  }
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    myFile.print('0');
  }
  myFile.print(number);
}
