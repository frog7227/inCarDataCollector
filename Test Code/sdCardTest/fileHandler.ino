#include "FS.h"
#include "SD_MMC.h"


fileHandler::fileHandler() {
  filePath = "/DATA/"; // seperated for easier management of the filename and path
  fileName = "LOGGED_DATA";
  fileExt = ".csv";


}
void fileHandler::begin() {
  startTime = millis();
  int i = 0;
  while(SD_MMC.exists((filePath + fileName + String(i) + fileExt).c_str())){
    Serial.println("i=" + String(++i));
  }
  file = SD_MMC.open((filePath + fileName + String(i) + fileExt).c_str(), FILE_WRITE); // opening the latest number for writing
  file.println("Time (seconds),Speed (MPH), fuel Flow (ml/min),Distance Travelled (mi)");


  return;
}
void fileHandler::end() {
  file.close();
  startTime = 0;
}
fileHandler::~fileHandler() {

  return;
}


void fileHandler::writeLine(double currSpeed, double currFuelFlow, double currDistanceTravelled) {
  file.println(String((int) (millis() - startTime) / 1000) + ',' + String(currSpeed / 1.609) + ',' + String(currFuelFlow) + ',' + String(currDistanceTravelled / 1.609));
}
