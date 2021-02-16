/**
 * This is the actual code file for the Speed stuff
 */
Speed::Speed(){
  currPos=0;
  accumulatedDistance = 0;// km
  distancePerPulse = 0.4;//m
  
  return;
}

Speed::~Speed(){
  resetSpeed();
return;
}

void Speed::updateSpeed(){
  unsigned int pulses = 0;
//pcnt_unit_config(PCNT_EVT_H_LIM);

  accumulatedDistance += pulses*distancePerPulse/1000;// /1000 for meters to km  conversion
}

float Speed::getCurrSpeed(){
return pastSpeeds[currPos];    
}

float Speed::getAvgSpeed(){
  return pastSpeeds[11];
}

void Speed::resetSpeed(){
  currPos=0;
  memset(pastSpeeds, 0, sizeof pastSpeeds); // zero out the array of speeds and the average speed
  return;
}

void Speed::averageSpeeds(){
  float sum = 0;
  for(int i = 0; i<=10;++i){
    sum += pastSpeeds[i];  
  }
  sum/=10;
  pastSpeeds[11]=sum;
  return;
}
void Speed::recSpeed(float currSpeed){
pastSpeeds[currPos]=currSpeed;
return;
}


double Speed::getTravelledDistance(){// returns the total travelled distance in km
  return accumulatedDistance;
}
