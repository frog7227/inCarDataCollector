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
  
public:
  fileHandler();
  ~fileHandler();
  void appendSpeed();
  void appendFuelConsumed();
  void appendDistance();
  void newFile();
  void closeFile();
};
