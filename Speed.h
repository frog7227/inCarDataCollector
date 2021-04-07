#pragma once
#include <driver/gpio.h>
#include <driver/pcnt.h>
/**
 * Header for the Speed code
 * Internal speed is in kph
 */
class Speed{

private:
  long double accumulatedDistance;
  double distancePerPulse;
  unsigned long previousRecordTime;
  unsigned long initialRecordTime;
public:
  Speed();
  void startRecording();
  float getCurrSpeed();
  float getAvgSpeed();
  double getTravelledDistance();
  void resetSpeed();// clears the array
  
  
};
