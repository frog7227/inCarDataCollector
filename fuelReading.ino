#include <driver/adc.h>
//#include <driver/adc_common.h>
#define adc_max (double) 4096
#define refVoltage 3.3
#define zeroAirSpeed (double) 1.3096// V
#define crossSectionAreaIntake 1.005 // cm^2
fuelReading::fuelReading() {
  analogReadResolution(12);
  // adc_power_on();
}

fuelReading::~fuelReading() {
  //adc_power_off();
}

double fuelReading::getCurrentFuelFlow() {

  int adc_reading_air = analogRead(33);
  int adc_reading_temp = analogRead(35);
  double adcVoltage_air = ((double)adc_reading_air) / adc_max * refVoltage;
  double adcVoltage_temp = ((double)adc_reading_temp) / adc_max * refVoltage;
  double tempC = (adcVoltage_temp - 0.4) / 0.01953;
  //double windSPeed = (((Volts – ZeroWind_V) / (3.038517 * (Temp_C ^ 0.115157 ))) / 0.087288 ) ^ 3.009364;
  double windSpeed = pow(((adcVoltage_air-zeroAirSpeed)/(3.038517*pow(tempC,0.115157))/0.087288),3.009364);


  return  windSpeed * stochiometricRatio * crossSectionAreaIntake;

  /*
     adc_reading/adc_max*refVoltage is the ADC voltage
     airFlowCalConstant is the
     44.704 is mph to cm/s
  */
}
