#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <RunningMedian.h>

#include "Basic Movement.h"

//Pin
const int JOYSTICKPIN_X = 35;         
const int JOYSTICKPIN_Y =34;
const int JOYSTICKPIN_BUTTON = 32;
const int JOYSTICK_CONTROL = 5;

//PinMode
void PinMode_Joystick();

//Variable
extern double Joystick_X;                    
extern double Joystick_Y;
extern int Joystick_Button; 
extern int Rotating;
extern int Joystick_Control;
extern RunningMedian Joystick_X_samples;    
extern RunningMedian Joystick_Y_samples;

//Functions
void Joystick_Position();
void Move_Joystick();

#endif