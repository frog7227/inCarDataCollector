#pragma once


/**
 * Header for the Speed code
 */
class Speed{

private:
  float pastSpeeds[11];// stores the past speeds for averaging, the 11th value is the 
  unsigned short currPos;// gets set to 0 on initialization
  void averageSpeeds();
  double accumulatedDistance;
  double distancePerPulse;
  int16_t x;

public:
  Speed();
  ~Speed();
  float getCurrSpeed();
  float getAvgSpeed();
  void updateSpeed();
  void resetSpeed();// clears the array
  void recSpeed(float currSpeed);
  double getTravelledDistance();
  
};
