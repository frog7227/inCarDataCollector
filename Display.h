#pragma once
/**
 * Header for the Display code
 */
class Display{
private:
public:
Display();//Constructor
~Display();//Destructor
void updateScreen();
void updateSpeed(float currSpeed);
void updateAvgSpeed(float AvgSpeed);
void dispWarning(String warning);
void clearWarning();
};
