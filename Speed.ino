/**
   This is the actual code file for the Speed stuff
*/

Speed::Speed() {
  accumulatedDistance = 0;// km
  distancePerPulse = 0.4;//m
}


float Speed::getCurrSpeed() { // gets the current speed over the last recording time
  int currTime = millis();
  //becuase each pulse is distancePerPulse, we can replace the distance with pulses*distancePerPulse
  int16_t Pulses = getCounterValue();
  accumulatedDistance += Pulses * distancePerPulse;
  return (float) Pulses / ((currTime - previousRecordTime)) / 1000.0 / 3600.0;
}

float Speed::getAvgSpeed() { // returns the average speed since the start of the recording
  return (float) accumulatedDistance / ((millis() - initialRecordTime)) / 1000.0 / 3600.0; // km /ms/1000(ms/s)/3600(s/hr) to get km/hr
}
void Speed::startRecording() { // starts recording
  startCounting();
  previousRecordTime = initialRecordTime = millis();
}
void Speed::resetSpeed() { // stops recording and initializes everything again
  stopCounting();
  previousRecordTime = initialRecordTime = 0;
}


double Speed::getTravelledDistance() { // returns the total travelled distance in km
  return accumulatedDistance;
}
