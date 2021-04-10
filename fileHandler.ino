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
  do { // find the first available file, not done with a for loop as the i value must be retained to create the file
    file = SD_MMC.open((this->filePath + this->fileName + String(i) + this->fileExt).c_str(), FILE_READ);
    ++i;
  } while (file);
  file.close();
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
