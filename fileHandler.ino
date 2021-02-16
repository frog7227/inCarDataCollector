  #include "FS.h"
  #include "SD_MMC.h"
  
  
  fileHandler::fileHandler(){
    filePath="/DATA/";// seperated for easier management of the filename and path
    fileName = "LOGGED_DATA";
    fileExt = ".csv";
    startTime = millis();
    SD_MMC.begin();// start the sd card interface
    int i = 1;
    while(file){// find the first available file, not done with a for loop as the i value must be retained to create the file
      ++i;
    file = SD_MMC.open((filePath +fileName + String(i) + fileExt).c_str(),FILE_READ);
    }
    file = SD_MMC.open((filePath +fileName + String(i) + fileExt).c_str(),FILE_WRITE);// opening the latest number and
    file.print("Time (seconds),Speed (MPH), fuel Flow (ml/min),Distance Travelled (mi)");
    return;
  }
  
  fileHandler::~fileHandler(){
    SD_MMC.end();
    startTime = 0;
    return;
  }
  
  
  void fileHandler::writeLine(double currSpeed,double currFuelFlow,double currDistanceTravelled){
  file.println(String((int) (millis() - startTime)/1000) + ',' + String(currSpeed/1.609) + ',' + String(currFuelFlow) + ',' + String(currDistanceTravelled/1.609));
  }

  
