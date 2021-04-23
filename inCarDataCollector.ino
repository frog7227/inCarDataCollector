#include "Display.h" // includes for all other objects
#include "Speed.h"
#include "fileHandler.h"
#include "fuelReading.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#define buttonPin 0
extern bool buttonPressed = false;
extern boolean record = false;
extern boolean running = false;
unsigned long prevTime = 0;
const int delayTime = 1000;
volatile uint32_t prevBounce = 0;
volatile uint32_t debounceTimeout = 200;
/**
   This code is to handle all of the functions of the data collection, displaying and processing.
   @author: Andrew Ostrosky and the inCarDataCollection senior project gang

*/


Speed SpeedReader = Speed();
fileHandler FileHandler = fileHandler();
fuelReading FuelReader = fuelReading();

void IRAM_ATTR buttonInterrupt() {
  if(xTaskGetTickCount() > prevBounce + debounceTimeout){
    Serial.println("Button was Pressed!");
    buttonPressed = true;  
    prevBounce = xTaskGetTickCount();
}
}

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  disp.begin();
  if(!SD.begin()){
        Serial.println("Card Mount Failed");
        return;
    }else{
      Serial.println("SD Card Mounted Successfully");
    }

  initializePulseCounter();
  setFilter(90);// wait 90 clock cycles before counting another pulse, the is to prevent ringing from being counted
  attachInterrupt(buttonPin, buttonInterrupt, FALLING);
  warmUpMessage();
  updateScreen(0, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currTime = millis();
  
  if(buttonPressed){// if the button was pressed
    buttonPressed = false; // say it was not pressed anymore
    record = !record;// toggle record
  }
  
  if (!record && running) { // if not recording anymore
    stop(); // stop the display timer
    SpeedReader.resetSpeed(); // stop the speed recording
   // Serial.println("record stop!");
    updateScreen(0, 0);
    running = false;// we're not running the recorder
    FileHandler.end();// close the file
  }

  if (record && !running) { // if we're recording, but not running yet, i.e. haven't initialized anything, initialize the fileHandler so a new document can be saved
    start();// start the display timer
    SpeedReader.startRecording(); // start recording the speed
    //Serial.println("record start!");
    running = true;
    FileHandler.begin();
    SpeedReader.startRecording();
  }

  if ((currTime - prevTime >= delayTime) && record && running) { // if it's time to record a new measurement, and are wanting to record and are running, i.e. ready to record, record the data.
  //  Serial.println("recording!");
    float currSpeed = SpeedReader.getCurrSpeed();// Take all measurements
   // Serial.println("Current Speed(in main)" +String(currSpeed,4));
    double distTravelled = SpeedReader.getTravelledDistance();
    //Serial.println("Distance Travelled(in main)" +String(distTravelled,3));
    double fuelFlow = FuelReader.getCurrentFuelFlow();
    float avgSpeed = SpeedReader.getAvgSpeed();
    updateScreen(avgSpeed, currSpeed); // update the screen
    FileHandler.writeLine(currSpeed, fuelFlow, distTravelled); // save the measurements to the SD card
    prevTime = currTime;
  }
  
}
