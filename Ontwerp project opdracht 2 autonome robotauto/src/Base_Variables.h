#ifndef VARIABLES_H
#define VARIABLES_H

#include <RunningMedian.h>

//Scanning
RunningMedian SS1_samples1 = RunningMedian(49); long SS1_afstand1;
RunningMedian SS1_samples2 = RunningMedian(49); long SS1_afstand2;
RunningMedian SS1_samples3 = RunningMedian(49); long SS1_afstand3;   

RunningMedian SS1_samples1_Down = RunningMedian(49); long SS1_afstand1_Down;
RunningMedian SS1_samples2_Down = RunningMedian(49); long SS1_afstand2_Down;
RunningMedian SS1_samples3_Down = RunningMedian(49); long SS1_afstand3_Down;

RunningMedian SS2_samples = RunningMedian(49); long SS2_afstand;

Servo Servo_Around_Y;
Servo Servo_Around_X;

//Joystick
double Joystick_X;                    
double Joystick_Y;
int Joystick_Button; 
int Rotating = 0;
int Joystick_Control;
RunningMedian Joystick_X_samples = RunningMedian(19);    
RunningMedian Joystick_Y_samples = RunningMedian(19);

 #endif