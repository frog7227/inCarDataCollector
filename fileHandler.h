#pragma once
#include "FS.h"
#include "SD_MMC.h"
/**
 * Header for the file handler code
 * 
 */

 class fileHandler{

private:
  String fileName;
  String filePath;
  String fileExt;
  File file;
  double currSpeed;
  unsigned long startTime;
  
public:
  fileHandler();
  ~fileHandler();
  void writeLine(double currSpeed,double currFuelFlow,double currDistanceTravelled);
};
