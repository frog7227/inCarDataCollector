#pragma once

/**
   Header for the fuel flow approximation
*/
class fuelReading {
  private:
    // values used to aquire and compute the data
    const double stochiometricRatio = 18.75; //:1
    const double diameterOfIntake = 2.54; //CM
    const double VrefVoltage = 1.1;



  public:
    fuelReading();//Constructor
    ~fuelReading();//Destructor
    double getCurrentFuelFlow();

};
