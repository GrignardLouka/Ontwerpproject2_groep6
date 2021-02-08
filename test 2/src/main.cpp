#include <Arduino.h>
#include <RunningMedian.h>


/* 
autonome robotauto

Groep 6

El Madani 	Ilyas
Grignard	Louka
Sahan	Baris

*/

///////////////////////////	Change log //////////////////////////////////////////
/* 
08/02/2021 13:48: Begin                                                                                     L
           14:57: 2 HC-SRO4 sensoren meten en printen afstand                                               L


*/


//#####################################    Variables   ##############################################
//2 HC-SR04 sensoren
const int SS1_trigPin = 18;    
const int SS1_echoPin = 19;    
long SS1_cm;

const int SS2_trigPin = 33;    
const int SS2_echoPin = 32;    
long SS2_cm;

long duration;

RunningMedian SS1_samples = RunningMedian(50);
RunningMedian SS2_samples = RunningMedian(50);


//######################################     Functies     ##########################################################
void Median_SS(){
  digitalWrite(SS1_trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(SS1_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(SS1_trigPin, LOW);
  duration = pulseIn(SS1_echoPin, HIGH);    // Mesure time needed for signal to return(in microseconds)
  SS1_samples.add((duration/2) / 29.1);
  SS1_cm = SS1_samples.getMedian();

  digitalWrite(SS2_trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(SS2_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(SS2_trigPin, LOW);
  duration = pulseIn(SS2_echoPin, HIGH);    // Mesure time needed for signal to return(in microseconds)
  SS2_samples.add((duration/2) / 29.1);
  SS2_cm = SS2_samples.getMedian();
}

 //####################################    SETUP    ##################################################
void setup() {
  //Start
  Serial.begin (115200);
  
  //2 HC-SRO4 sensoren
  pinMode(SS1_trigPin, OUTPUT);
  pinMode(SS1_echoPin, INPUT);

  pinMode(SS2_trigPin, OUTPUT);
  pinMode(SS2_echoPin, INPUT);

}
 
//#########################################     LOOP     ###############################################
void loop() {

  Serial.println("Starting scan");
  Median_SS();
  Serial.println("Done scanning");

  Serial.print("De eerste sensor meet: ");
  Serial.print(SS1_cm);
  Serial.println(" cm");



 Serial.println("De tweede sensor meet: ");
 Serial.print(SS2_cm);
 Serial.print(" cm");

  Serial.println("Delay");
  delay(10);



}



