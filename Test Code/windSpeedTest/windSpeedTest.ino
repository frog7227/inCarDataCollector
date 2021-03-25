#include <driver/adc.h>
//#include <driver/adc_common.h>
#define adc_max (double) 4096
#define zeroAirSpeed (double) 1.3096// V
#define crossSectionAreaIntake 1.005 // cm^2

const double stochiometricRatio = 18.75; //:1
const double diameterOfIntake = 2.54; //CM
const double VrefVoltage = 1.1;
/*
 * This is used to test the ADC and the code for the fuel flow readout
 */
void setup() {

 Serial.begin(9600);
 adc1_config_width(ADC_WIDTH_BIT_12);
 adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_11);// vinMax = ~800mV, ADC_ATTEN_DB_2_5 is max of ~1.1V
}

void loop() {

int adc_reading_air = adc1_get_raw(ADC1_CHANNEL_0);
int adc_reading_temp = adc1_get_raw(ADC1_CHANNEL_3);
double adcVoltage_air = ((double)adc_reading_air)/adc_max*VrefVoltage; 
double adcVoltage_temp = ((double)adc_reading_temp)/adc_max*VrefVoltage; 
double tempC = (adcVoltage_temp-0.4)/0.01953;
//double windSPeed = (((Volts – ZeroWind_V) / (3.038517 * (Temp_C ^ 0.115157 ))) / 0.087288 ) ^ 3.009364;
double windSpeed = pow((adcVoltage_air - zeroAirSpeed)/(3.038517 * pow(tempC,0.115157)),3.009364);
Serial.print("Current Wind Speed in mph: " );
Serial.println(windSpeed);
Serial.println("Current Temperature in Degress Celcius: ");
Serial.println(tempC);
delay(1000);
}
