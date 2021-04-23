/**
   This is the actual code file for the Speed stuff
*/

Speed::Speed() {
  accumulatedDistance = 0;// mi
  distancePerPulse = 1;//ft
}


float Speed::getCurrSpeed() { // gets the current speed over the last recording time
  int currTime = millis();
  //becuase each pulse is distancePerPulse, we can replace the distance with pulses*distancePerPulse
  int16_t Pulses = getCounterValue();
  //Serial.println("Pulses: " + String(Pulses));
  this->accumulatedDistance += ((double) Pulses) * this->distancePerPulse / (double) 5280;// ft * pulses / ft/mi = pulse*mi (pulse is unitless) therefore mi is the unit 
  //Serial.println("currDistance" + String(accumulatedDistance));
  //Serial.println("Current Speed" + String((float) (Pulses * distancePerPulse/5280/(currTime - previousRecordTime)/ 1000.0 / 3600.00 ))));
 float currSpeed = ((double) Pulses) * this->distancePerPulse / (double) 5280 / ((double) (currTime -  previousRecordTime)/ (double) 1000 / (double) 3600);
  previousRecordTime = currTime;
  return currSpeed;
}

float Speed::getAvgSpeed() { // returns the average speed since the start of the recording
  return accumulatedDistance / ((double)(millis() - initialRecordTime) / (double) 1000 / (double) 3600);
}
void Speed::startRecording() { // starts recording
  startCounting();
  previousRecordTime = initialRecordTime = millis();
}
void Speed::resetSpeed() { // stops recording and initializes everything again
  stopCounting();
  previousRecordTime = initialRecordTime = 0;
  accumulatedDistance = 0;
}


double Speed::getTravelledDistance() { // returns the total travelled distance in km
  return accumulatedDistance;
}
