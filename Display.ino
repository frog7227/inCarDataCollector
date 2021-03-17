#include <SparkFunSerialGraphicLCD.h>//inculde the Serial Graphic LCD library

#define maxX 59 // used for the display coordinates
#define maxY 127


/**
 * This is the actual code file for the display stuff
 */
Display::Display(){

  Serial.begin(9600);
  return;
}
Display::~Display(){
  return;
}

void Display::updateScreen(){
  return;
}
void Display::updateSpeed(float currSpeed){
  return;
}
void Display::updateAvgSpeed(float AvgSpeed){
  
  return;
}
void Display::dispWarning(String warning){
  return;
}
void Display::clearWarning(){
  
  return;
}
