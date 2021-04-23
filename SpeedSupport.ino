#include <driver/gpio.h>
#include "driver/pcnt.h"                                  // this is the hardware interface library we need to set it up
/*
   These functions should be encapsulated in the speed function, but like the display,
   the hardware components cannot be encapsulated, so they are in their own files, NOT to be used
   by other classes or methods outside of their respective parts.


*/
#define PCNT_FREQ_UNIT      PCNT_UNIT_0                   // set the pulse counter unit to 0 (the io mux needs this)
#define PCNT_H_LIM_VAL      10000                        // limit to 10k pulses
#define PCNT_INPUT_SIG_IO   4                             // Pulse Input on GPIO 4 

int counterOverflow;                                     // overflow counter

pcnt_isr_handle_t user_isr_handle = NULL;                 // interrupt handler
hw_timer_t * timer = NULL;                                // make the timer

//------------------------------------------------------------------------------------
void IRAM_ATTR overflowcounter(void *arg)                // Counter overflow interrupt function,the value is ignored but is required to exist.
{
  counterOverflow = counterOverflow + 1;                // add to the overflow counter, indicating an overflow occured
  PCNT.int_clr.val = BIT(PCNT_FREQ_UNIT);                 // clear the overflow flag
  pcnt_counter_clear(PCNT_FREQ_UNIT);                     // reset the pulse counter
}

//------------------------------------------------------------
void initializePulseCounter() {                              // initialize everything so that we can use the pulse counter

  pcnt_config_t pcntFreqConfig = { };                        // create an instance of the pulse counter
  pcntFreqConfig.pulse_gpio_num = PCNT_INPUT_SIG_IO;         // connect it to the pin
  pcntFreqConfig.neg_mode = PCNT_COUNT_INC;                  // increase on falling edge
  pcntFreqConfig.counter_h_lim = PCNT_H_LIM_VAL;             // limit the max count to PCNT_H_LIM_VAL (currently 10000)
  pcntFreqConfig.unit = PCNT_FREQ_UNIT;                      // set it to pulse counter 0
  pcntFreqConfig.channel = PCNT_CHANNEL_0;                   // Channel 0 of unit 0 of the hardware pulse counter
  pcnt_unit_config(&pcntFreqConfig);                         // put the pcntFreqConfig into the appropriate registers

  pcnt_counter_pause(PCNT_FREQ_UNIT);                        // pause the counter
  pcnt_counter_clear(PCNT_FREQ_UNIT);                        // clear the counter

  pcnt_event_enable(PCNT_FREQ_UNIT, PCNT_EVT_H_LIM);         // Interrupt the cpu when it his the max
  pcnt_isr_register(overflowcounter, NULL, 0, &user_isr_handle);  // configure the interrupt recorder
  pcnt_intr_enable(PCNT_FREQ_UNIT);                          // enable the inturrupt for the pulse counter
  //pcnt_counter_resume(PCNT_FREQ_UNIT);                       // resume the pulse counter, as we paused it to clear it
}

void startCounting() { // start the counter
  pcnt_counter_resume(PCNT_FREQ_UNIT);
}

void stopCounting() { // pause the counter
  pcnt_counter_pause(PCNT_FREQ_UNIT);
}

int16_t getCounterValue() { // get the value of the counter
  int16_t localCounter = 0;                               // make a local counter value
  pcnt_get_counter_value(PCNT_FREQ_UNIT, &localCounter);
  counterOverflow = 0;                                     // reset the overflow counter
  pcnt_counter_clear(PCNT_FREQ_UNIT);                      // clear the actual counter
  return localCounter;                                     // return the counter value
}

void setFilter(uint16_t value) {
  if (value == 0) {
    pcnt_filter_disable(PCNT_FREQ_UNIT);
  } else if (value < 1024) {
    pcnt_set_filter_value(PCNT_FREQ_UNIT, value);
    pcnt_filter_enable(PCNT_FREQ_UNIT);
  }
}
