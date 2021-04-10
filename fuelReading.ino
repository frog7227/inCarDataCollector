#include <driver/adc.h>
//#include <driver/adc_common.h>
#define adc_max (double) 4096
#define zeroAirSpeed (double) 1.3096// V
#define crossSectionAreaIntake 1.005 // cm^2
fuelReading::fuelReading() {
  // adc_power_on();
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11); // vinMax = ~800mV, ADC_ATTEN_DB_2_5 is max of ~1.1V
}

fuelReading::~fuelReading() {
  //adc_power_off();
}

double fuelReading::getCurrentFuelFlow() {

  int adc_reading_air = adc1_get_raw(ADC1_CHANNEL_0);
  int adc_reading_temp = adc1_get_raw(ADC1_CHANNEL_3);
  double adcVoltage_air = ((double)adc_reading_air) / adc_max * VrefVoltage;
  double adcVoltage_temp = ((double)adc_reading_temp) / adc_max * VrefVoltage;
  double tempC = (adcVoltage_temp - 0.4) / 0.01953;
  //double windSPeed = (((Volts – ZeroWind_V) / (3.038517 * (Temp_C ^ 0.115157 ))) / 0.087288 ) ^ 3.009364;
  double windSpeed = pow((adcVoltage_air - zeroAirSpeed) / (3.038517 * pow(tempC, 0.115157)), 3.009364) * 44.704;


  return  windSpeed * stochiometricRatio * crossSectionAreaIntake;

  /*
     adc_reading/adc_max*VrefVoltage is the ADC voltage
     airFlowCalConstant is the
     44.704 is mph to cm/s
  */
}
