#ifndef SCANNING_H
#define SCANNING_H

#include <ESP32Servo.h>
#include <RunningMedian.h>

//Pin
const int SS1_TRIGPIN = 16;  
const int SS2_TRIGPIN = 4;
const int SS3_TRIGPIN = 39;
const int SS4_TRIGPIN = 36;  

const int SS1_ECHOPIN = 17; 
const int SS2_ECHOPIN = 2;
const int SS3_ECHOPIN = 18;
const int SS4_ECHOPIN = 15; 

const int SERVO_AROUND_Y_PIN = 14;
const int SERVO_AROUND_X_PIN = 12;

//PinMode
void PinMode_Scanning();

//Variable
extern RunningMedian SS1_samples1; extern long SS1_afstand1;
extern RunningMedian SS1_samples2; extern long SS1_afstand2;
extern RunningMedian SS1_samples3; extern long SS1_afstand3;   

extern RunningMedian SS1_samples1_Down; extern long SS1_afstand1_Down;
extern RunningMedian SS1_samples2_Down; extern long SS1_afstand2_Down;
extern RunningMedian SS1_samples3_Down; extern long SS1_afstand3_Down;

extern RunningMedian SS2_samples; extern long SS2_afstand;

extern Servo Servo_Around_Y;
extern Servo Servo_Around_X;

//Functions
long SS_Meting(const int TRIGGER, const int ECHO, RunningMedian Lijst);
void Attach_Servos();
void Scan();
void Detach_Servos();
 

 #endif

