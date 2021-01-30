#pragma once
/**
 * Header for the Speed code
 */
class Speed{

private:
  float pastSpeeds[11];// stores the past speeds for averaging, the 11th value is the 
  int currPos;// gets set to 0 on initialization
  void averageSpeeds();

public:
  Speed();
  ~Speed();
  float getCurrSpeed();
  float getAvgSpeed();
  void resetSpeed();// clears the array
};
