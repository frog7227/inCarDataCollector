/**
 * This is the actual code file for the Speed stuff
 */
 #define speedSensorPin (gpio_num_t) 5 // the pin for the speed sensing
 
Speed::Speed(){
  currPos=0;
  accumulatedDistance = 0;// km
  distancePerPulse = 0.4;//m
  this->attachSpeedSensor();
  
  return;
}

Speed::~Speed(){
  resetSpeed();
return;
}
void Speed::attachSpeedSensor(){
 unit = (pcnt_unit_t) speedSensorPin;// not sure if this is right
gpio_pad_select_gpio(speedSensorPin);
gpio_set_direction(speedSensorPin, GPIO_MODE_INPUT);// set the counter pin to input
speedSensorConfig.pulse_gpio_num = speedSensorPin;
speedSensorConfig.unit = unit;
speedSensorConfig.channel = PCNT_CHANNEL_0;
speedSensorConfig.channel = PCNT_CHANNEL_0;
speedSensorConfig.pos_mode = PCNT_COUNT_DIS;// "discard" rising edge
speedSensorConfig.neg_mode = PCNT_COUNT_INC; // count the falling edge
speedSensorConfig.counter_l_lim = 0;
speedSensorConfig.counter_h_lim = counterMax;
 this->setFilter(100); // prevent pusle counting within 100 clock cycles, aka debounce and ringing

pcnt_counter_pause(unit); // pause the counter
pcnt_counter_clear(unit); // clear it
pcnt_counter_resume(unit); // start it back up
}

float Speed::getCurrSpeed(){
// get the new current speed
//pcnt_counter_pause(unit); // pause the counter
int16_t counterValue;
pcnt_get_counter_value(unit,&counterValue);
float currSpeed = distancePerPulse*(float)(uint16_t)counterValue*3.6; // distance per pulse * pulses * (m/s -> kph)
pastSpeeds[currPos] = currSpeed;
if(currSpeed <10){// move back to the beginning if needed
  currPos++;
}else currPos = 0;

accumulatedDistance += currSpeed;// currSpeed was over 1s and is in m/s, so make it 
pcnt_counter_clear(unit); // clear it
//pcnt_counter_resume(unit); // start it back up
return pastSpeeds[currPos];    
}

float Speed::getAvgSpeed(){
  float sum = 0;
  for(int i = 0; i<=10;++i){
    sum += pastSpeeds[i];  
  }
  sum/=10;
  pastSpeeds[11]=sum;
  return sum;// returns the 11th value which is the speed
}

void Speed::resetSpeed(){
  currPos=0;
  memset(pastSpeeds, 0, sizeof pastSpeeds); // zero out the array of speeds and the average speed
  return;
}

void Speed::recSpeed(float currSpeed){
pastSpeeds[currPos]=currSpeed;
return;
}


double Speed::getTravelledDistance(){// returns the total travelled distance in km
  return accumulatedDistance;
}

void Speed::setFilter(uint16_t value) {
  if(value==0) {
    pcnt_filter_disable(unit);  
  } else {
    pcnt_set_filter_value(unit, value);
    pcnt_filter_enable(unit); 
  }
}
