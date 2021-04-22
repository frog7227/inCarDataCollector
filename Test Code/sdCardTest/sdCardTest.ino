#include "fileHandler.h"
#include "FS.h"
#include "SD_MMC.h"

fileHandler FileHandler = fileHandler();
void setup() {
  // put your setup code here, to run once:
SD_MMC.begin();
Serial.begin(115200);
FileHandler.begin();
/*
for(int i = 0; i <10;++i){
  int currSpeed = i*2, fuelFlow = i*3,distTravelled = i*4;
  FileHandler.writeLine(currSpeed, fuelFlow, distTravelled); // save the measurements to the SD card 
}
*/
FileHandler.end();
Serial.println("Done");
}

void loop() {
  // put your main code here, to run repeatedly:

}
