#pragma once
#include "FS.h"
#include "SD.h"
/**
   Header for the file handler code

*/

class fileHandler {

  private:
    String fileName;
    String filePath;
    String fileExt;
    String currFile;
    File file;
    double currSpeed;
    unsigned long startTime;

  public:
    fileHandler();
    void begin();
    void end();
    ~fileHandler();
    void writeLine(double currSpeed, double currFuelFlow, double currDistanceTravelled);
};
