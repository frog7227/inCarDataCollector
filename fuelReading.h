#pragma once
/**
 * Header for the fuel flow approximation
 */
class fuelReading{
private:
// values used to aquire and compute the data
const int readPin = 5;
const double stochiometricRatio = 18.75; //:1

public:
fuelReading();//Constructor
~fuelReading();//Destructor
double getCurrentFuelFlow();

};
