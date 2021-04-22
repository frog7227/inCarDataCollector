#pragma once
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#define TFT_DC 17
#define TFT_CS 16
extern Adafruit_ILI9341 disp; // this is used to allow for starting the disp object in other files
