#include "FS.h"
#include "SD.h"


fileHandler::fileHandler() {
  filePath = "/"; // seperated for easier management of the filename and path
  fileName = "LOGGED_DATA";
  fileExt = ".csv";

}
void fileHandler::begin() {
  startTime = millis();
  String path = "";
  int i = 0;
  do{
    currFile = filePath + fileName + String(i) + fileExt;
    ++i;
  }while(SD.exists(currFile));
  appendFile(SD,path.c_str(),"Time(s),Speed (Mi),Fuel Flow (mL/Hr),Distance Travelled (Mi)\r\n");

}
void fileHandler::end() {
  startTime = 0;
}
fileHandler::~fileHandler() {
  return;
}


void fileHandler::writeLine(double currSpeed, double currFuelFlow, double currDistanceTravelled) {
  appendFile(SD,currFile.c_str(),(String((int) (millis() - startTime) / 1000) + ',' + String(currSpeed / 1.609) + ',' + String(currFuelFlow) + ',' + String(currDistanceTravelled / 1.609)+ "\r\n").c_str());
}
