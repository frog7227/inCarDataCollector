#include "Display.h" // includes for all other objects
#include "Speed.h"
#include "fileHandler.h"
#include "fuelReading.h"
#include "FS.h"
#include "SD_MMC.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
extern boolean record = false;
extern boolean running = false;
unsigned long prevTime = 0;
int delayTime = 1000;
/**
   This code is to handle all of the functions of the data collection, displaying and processing.
   @author: Andrew Ostrosky and the inCarDataCollection senior project gang

*/

Speed SpeedReader = Speed();
fileHandler FileHandler = fileHandler();
fuelReading FuelReader = fuelReading();

void setup() {
  // put your setup code here, to run once:
  disp.begin();
  SD_MMC.begin();

  initializePulseCounter();
  setFilter(90);// wait 90 clock cycles before counting another pulse, the is to prevent ringing from being counted

  warmUpMessage();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currTime = millis();
  if (!record) { // if not recording anymore
    running = false;// we're not running the recorder
    FileHandler.end();// close the file
  }

  if (record && !running) { // if we're recording, but not running yet, i.e. haven't initialized anything, initialize the fileHandler so a new document can be saved
    running = true;
    FileHandler.begin();
    SpeedReader.startRecording();
  }

  if ((currTime - prevTime > delayTime) && record && running) { // if it's time to record a new measurement, and are wanting to record and are running, i.e. ready to record, record the data.
    float currSpeed = SpeedReader.getCurrSpeed();// Take all measurements
    double distTravelled = SpeedReader.getTravelledDistance();
    double fuelFlow = FuelReader.getCurrentFuelFlow();
    float avgSpeed = SpeedReader.getAvgSpeed();
    updateScreen(avgSpeed, currSpeed); // update the screen
    FileHandler.writeLine(currSpeed, fuelFlow, distTravelled); // save the measurements to the SD card
  }







}
