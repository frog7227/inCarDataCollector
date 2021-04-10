#include "Display.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
//Adafruit_ILI9341 disp = Adafruit_ILI9341(TFT_CS, TFT_DC);
#define warmUpTime 5 // number of seconds to wait for the warmup
Adafruit_ILI9341 disp = Adafruit_ILI9341(TFT_CS, TFT_DC);// the pins are defined in the header for this file
unsigned long startTime = 0;

void warmUpMessage() {
  disp.fillScreen(ILI9341_BLACK);
  disp.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  for (int i = warmUpTime; i > 0; --i) {
    disp.setCursor(0, 0);
    disp.setTextSize(3);// print "PLEASE WAIT"
    disp.println("Please Wait");
    disp.println("The Mass Air");
    disp.println("Flow Sensor");
    disp.println("is warming up");

    disp.println("TimeRemaining: ");
    disp.setTextSize(11);// print "PLEASE WAIT"
    if (i < 10) disp.print("0"); // print 0 for the countdown if the number is single digit so 09, 08, etc.
    disp.println(i);
    delay(1000);

  }

  disp.fillScreen(ILI9341_GREEN); // display READY on the screen for 2 seconds
  disp.setCursor(15 , 150);
  disp.setTextColor(ILI9341_BLACK, ILI9341_GREEN);
  disp.setTextSize(7);
  disp.println("READY");
  delay(2000);
  disp.fillScreen(ILI9341_BLACK);
}
/*
   updateScreen CANNOT be called before start(), or after stop(), otherwise strange behavior will occur
   i.e. HUGE times which are invalid
*/
void updateScreen(float avgSpeed, float currSpeed) {
  disp.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  if (avgSpeed > 99.9) avgSpeed = 99.9; // if the speed is higher than the max of the display, lock it at the max
  if (currSpeed > 99) currSpeed = 99;
  disp.setCursor(0, 0);
  disp.setTextSize(10);// print the average speed with 1 decimal place
  if (avgSpeed < 10) disp.print("0");
  disp.println(avgSpeed, 1);

  disp.setCursor(150, 75); // print the "Average" text
  disp.setTextSize(2);
  disp.println("Average");


  disp.setTextSize(10);// print the current speed
  disp.setCursor(0, 80);
  if (currSpeed < 10) disp.print("0");
  disp.println(floor(currSpeed), 0);

  disp.setCursor(150, 130); // print the "Current" text
  disp.setTextSize(2);
  disp.println("Current");

  disp.setTextSize(6);// print MPH
  disp.setCursor(130, 150);
  disp.println("MPH");
  unsigned int Time = 0;
  if ( startTime != 0) { // if it is recording, i.e. startTime is not zero, then it is set, if not it is left as zero so the time is 0:00:00
    Time =  floor((millis() - startTime) / 1000); // find the time amounts
  }

  unsigned int Hours = (unsigned int) floor(Time / 3600); // find hr, min and seconds to print to the screen
  unsigned int Minutes = (Time % 3600) / 60;
  unsigned int Seconds  = Time % 60;



  disp.setTextSize(4);// print  recording time
  disp.setCursor(20, 250);

  disp.print(String(Hours) + ":");// hours is always 1 digit, so no correction is needed

  if (Minutes < 10) disp.print("0"); // make minutes 2 digit if not already
  disp.print(String(Minutes) + ":");

  if (Seconds < 10) disp.print("0"); // make minutes 2 digit if not already
  disp.print(String(Seconds));
}


void start() {
  startTime = millis();// start of the recording

}
void stop() {
  startTime = 0;// reset the timer
}
