#pragma once
#include <driver/gpio.h>
#include <driver/pcnt.h>
#define counterMax 65535
/**
 * Header for the Speed code
 * Internal speed is in kph
 */
class Speed{

private:
  float pastSpeeds[11];// stores the past speeds for averaging, the 11th value is the average 
  unsigned short currPos;// gets set to 0 on initialization
  long double accumulatedDistance;
  double distancePerPulse;
  int16_t x;
  void attachSpeedSensor();
  pcnt_config_t speedSensorConfig; // this is to set the actual thing to configure the speed sensor interrupts
  pcnt_unit_t unit; // there are 8 independent counters called units, so we need to set which one is being used
  void setFilter(uint16_t value); // sets the filtering time in 
public:
  Speed();
  ~Speed();
  float getCurrSpeed();
  float getAvgSpeed();
  void resetSpeed();// clears the array
  void recSpeed(float currSpeed);
  double getTravelledDistance();
  
};
