#ifndef METINGEN_H
#define METINGEN_H

#include <RunningMedian.h>

const int SS1_TRIGPIN = 18;  
const int SS2_TRIGPIN = 19;
const int SS3_TRIGPIN = 1;
const int SS4_TRIGPIN = 1;  

const int SS1_ECHOPIN = 16; 
const int SS2_ECHOPIN = 2;
const int SS3_ECHOPIN = 1;
const int SS4_ECHOPIN = 1; 

void PinMode_Metingen();
long SS_Meting(const int TRIGGER, const int ECHO, RunningMedian Lijst);

#endif