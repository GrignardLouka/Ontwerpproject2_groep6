#include <Arduino.h>
#include <RunningMedian.h>

#include <Metingen.h>


//##################### 2 HC-SR04 sensoren




//HC-SOR4 sensor



void PinMode_Metingen(){
  pinMode(SS1_TRIGPIN, OUTPUT);
  pinMode(SS2_TRIGPIN, OUTPUT);
  pinMode(SS3_TRIGPIN, OUTPUT);
  pinMode(SS4_TRIGPIN, OUTPUT);
  
  pinMode(SS1_ECHOPIN, INPUT);
  pinMode(SS2_ECHOPIN, INPUT);
  pinMode(SS3_ECHOPIN, INPUT);
  pinMode(SS4_ECHOPIN, INPUT);

}

long SS_Meting(const int TRIGGER, const int ECHO, RunningMedian Lijst){
  long afstand;
  long duration;

  digitalWrite(TRIGGER, LOW);              //set to LOW first to ensure a clean signal
  delayMicroseconds(5);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);

  duration = pulseIn(ECHO, HIGH) / 2;    // Measure time needed for signal to return(in microseconds)(/2 signal travels  back and forth)
  Lijst. add(duration / 29.1);            // Convert to cm and add to list
  afstand = Lijst.getMedian();              // Get median of the list(for a more accurate measurement)
  
  return(afstand);
  
}