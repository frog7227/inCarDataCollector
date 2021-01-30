/**
 * This is the actual code file for the Speed stuff
 */
Speed::Speed(){
  currPos=0;
  return;
}

Speed::~Speed(){
  resetSpeed();
return;
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
