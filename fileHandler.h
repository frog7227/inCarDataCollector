#pragma once
/**
 * Header for the file handler code
 * 
 */

 class fileHandler{

private:
  String fileName;
  
public:
  fileHandler();
  ~fileHandler();
  void appendSpeed();
  void appendFuelConsumed();
  void newFile();
  void closeFile();
};
