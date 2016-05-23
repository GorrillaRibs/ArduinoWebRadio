/*
  Robert Raffaele "GorrillaRIBS" Miller
  Arduino ICEcast streamer
  Code finalized Sun, 22 May, 2016
  Using own modified libraries that "work" with cleap 3rd party shields I'm using - should work properly
  with the actual shields/libraries as well

  Recieves data over I2C to from first arduino, which has an Ethernet connection for g
  rabbing the sound data, then processes the data

  Wake me up
  (Wake me up inside)
  Can't wake up
  (Wake me up inside)
  SAAAVVVEE MEEEE
*/

// Essentials
#include <SPI.h>
#include <Wire.h>

// Add normal SD library
//#include <SD.h>

// Add the SdFat Libraries
#include <SdFat.h>
#include <SdFatUtil.h>

// and the (modified) MP3 Shield Library
#include <SFEMP3Shield.h>

// No hardware interrups, so...
#if defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_Timer1
#include <TimerOne.h>
#elif defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer
#include <SimpleTimer.h>
#endif

SdFat sd; // create sdcard object w/ sdfat
SdFile stream; // create file w/ normal SD library
const uint8_t chipSelect = 9;

SFEMP3Shield player; // player object


void setup() {

  Serial.begin(115200);               // Start serial for debug




  Wire.begin(8);                             // Join i2c bus with address #8
  Wire.onReceive(receiveEvent);   // Register event
//  Serial.print("Init SD card...");
//  if (!sd.begin(chipSelect, SPI_HALF_SPEED)) sd.initErrorHalt();
//  // depending upon your SdCard environment, SPI_HALF_SPEED may work better.
//  //if (!sd.chdir("/")) sd.errorHalt("sd.chdir");
//  Serial.println("Init done.");

//  player.begin();

}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {

  char x = Wire.read();    // receive byte as a char
  // open the file for write
  player.pauseDataStream();
//  if (!stream.open("track002.mp3", O_RDWR | O_CREAT | O_AT_END)) {
//    sd.errorHalt("opening file for write failed");
//  }
//
//  //   if the file opened okay, write to it:
//
//  Serial.println("OPENED!");
//  stream.print(x);
//  stream.close();
  Serial.print(x);         // print the char



  player.resumeDataStream();
//
//  player.playTrack(2); // play track with filename "track002.mp3" on sdcard

}




