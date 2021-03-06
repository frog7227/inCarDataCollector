#pragma once

/**
   Header for the fuel flow approximation
*/
class fuelReading {
  private:
    // values used to aquire and compute the data
    const double stochiometricRatio = 18.75; //:1
    const double diameterOfIntake = 1.27; //CM



  public:
    fuelReading();//Constructor
    ~fuelReading();//Destructor
    double getCurrentFuelFlow();

};
