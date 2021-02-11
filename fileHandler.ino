  #include "FS.h"
  #include "SD_MMC.h"
  
  
  fileHandler::fileHandler(){
    filePath="/DATA/";// seperated for easier management of the filename and path
    fileName = "LOGGED_DATA";
    fileExt = ".csv";
    SD_MMC.begin();// start the sd card interface
    int i = 1;
    while(file){// find the first available file, not done with a for loop as the i value must be retained to create the file
      ++i;
    file = SD_MMC.open((filePath +fileName + String(i) + fileExt).c_str(),FILE_READ);
    }
    file = SD_MMC.open((filePath +fileName + String(i) + fileExt).c_str(),FILE_WRITE);
    return;
  }
  
  fileHandler::~fileHandler(){
    SD_MMC.end();
    return;
  }
  
  void fileHandler::appendSpeed(){
    return;
  }
  
  void fileHandler::appendFuelConsumed(){
    return;
  }

  void fileHandler::appendDistance(){
  
  }

  void fileHandler::newFile(){
    return;
  }
    
  void fileHandler::closeFile(){
    return;
  }
