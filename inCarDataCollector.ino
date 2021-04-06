#include "Display.h" // includes for all other objects
#include "Speed.h"
#include "fileHandler.h"
#include "fuelReading.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

/**
 * This code is to handle all of the functions of the data collection, displaying and processing.
 * @author: Andrew Ostrosky and the inCarDataCollection senior project gang
 * 
 */


void setup() {
  // put your setup code here, to run once:
  disp.begin();
  Speed SpeedReader = Speed();
  fileHandler FileHandler = fileHandler();
  fuelReading FuelReader = fuelReading();
}

void loop() {
  // put your main code here, to run repeatedly:


// Take all measurements

//wait some amount of time

//update screen, and save everything else to the sd card


}
