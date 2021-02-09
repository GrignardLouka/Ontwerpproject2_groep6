/* 
autonome robotauto
Groep 6
El Madani 	Ilyas
Grignard	Louka
Sahan	Baris
*/
//######################################     	Change log    ##############################################
/* 
08/02/2021     HC-SRO4 sensoren(meten + afstand printen)                                              
09/02/2021     Joystick
               Banden
*/

//#######################################     Libraries    ################################################
#include <Arduino.h>
#include <RunningMedian.h>

//#####################################    Variables   ###################################################
//2 HC-SR04 sensoren
const int SS1_trigPin = 18;    
const int SS1_echoPin = 19;    
long SS1_afstand;
RunningMedian SS1_samples = RunningMedian(50);

const int SS2_trigPin = 33;    
const int SS2_echoPin = 32;    
long SS2_afstand;
RunningMedian SS2_samples = RunningMedian(50);

long duration;

//Joystick
const int JoystickPin_X = 34;
double Joystick_X;
const int JoystickPin_Y =35;
double Joystick_Y;
const int JoystickPin_Button = 27;
int Joystick_Button;

//######################################     Functies     ##########################################################
void Median_SS(){
  digitalWrite(SS1_trigPin, LOW);           //set to LOW first to ensure a clean signal
  delayMicroseconds(5);
  digitalWrite(SS1_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(SS1_trigPin, LOW);
  duration = pulseIn(SS1_echoPin, HIGH);    // Mesure time needed for signal to return(in microseconds)
  SS1_samples.add((duration/2) / 29.1);     //Convert to cm and add to array
  SS1_afstand = SS1_samples.getMedian();    // Get Median distance

  delay(5);                                 // wait 5 ms to prevent to much noise from other sensor

  digitalWrite(SS2_trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(SS2_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(SS2_trigPin, LOW);
  duration = pulseIn(SS2_echoPin, HIGH);    
  SS2_samples.add((duration/2) / 29.1);
  SS2_afstand = SS2_samples.getMedian();

  delay(5);
}

void Joystick_Position(){
  Joystick_X = map(analogRead(JoystickPin_X),0,4095,0,255);
  Joystick_Y = map(analogRead(JoystickPin_Y),0,4095,0,255);
  Joystick_Button = !digitalRead(JoystickPin_Button);
  

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

  pinMode(Joystick_X, INPUT);
  pinMode(Joystick_Y, INPUT);
  pinMode(Joystick_Button, PULLUP);

}

//#########################################     LOOP     ###############################################
void loop(){


//########################## Joystick
/*
Joystick_Position();

Serial.print("X value: ");
Serial.println(Joystick_X);
Serial.print("Y value: ");
Serial.println(Joystick_Y);
Serial.print("Button value: ");
Serial.println(Joystick_Button);
*/

//######################### HC_SRO4 sensor
/*
  Median_SS();

  Serial.print("De eerste sensor meet: ");
  Serial.print(SS1_afstand);
  Serial.println(" cm");

 Serial.print("De tweede sensor meet: ");
 Serial.print(SS2_afstand);
 Serial.println(" cm");
*/
}
