//############### STATE 1 (scan)

#include <ESP32Servo.h>
#include <RunningMedian.h>

#include "Scanning.h"
#include "Metingen.h"

// Functions
void PinMode_Scanning(){
  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

  Servo_Around_Y.setPeriodHertz(50);    // standard 50 hz servo
  Servo_Around_Y.attach(SERVO_AROUND_Y_PIN, 500, 2500);
  Servo_Around_X.setPeriodHertz(50);
  Servo_Around_X.attach(SERVO_AROUND_X_PIN, 500, 2500);
}

void Attach_Servos(){
  Servo_Around_Y.setPeriodHertz(50);    // standard 50 hz servo
	Servo_Around_Y.attach(SERVO_AROUND_Y_PIN, 500, 2500);
  Servo_Around_X.setPeriodHertz(50);    // standard 50 hz servo
	Servo_Around_X.attach(SERVO_AROUND_X_PIN, 500, 2500);
}
void Detach_Servos(){
  Servo_Around_Y.detach();
  Servo_Around_X.detach();
}
void Scan(){
  Attach_Servos();

  // Pos 1  (rechts)
  Servo_Around_Y.write(0);
  Servo_Around_X.write(100);
  Serial.println("Turning to first position");
  delay(200);
  SS1_afstand1 = SS_Meting(SS1_TRIGPIN, SS1_ECHOPIN,SS1_samples1);

  // Pos 2
  Servo_Around_Y.write(70);
  Serial.println("Turning to third position");
  delay(200);
  SS1_afstand2 = SS_Meting(SS1_TRIGPIN, SS1_ECHOPIN,SS1_samples2);

  // Pos 3
  Servo_Around_Y.write(160);
  Serial.println("Turning to fifth position");
  delay(200);
  SS1_afstand3 = SS_Meting(SS1_TRIGPIN, SS1_ECHOPIN,SS1_samples3);
  //pos 7
  Servo_Around_X.write(15);
  Serial.println("Turning to the seventh position");
  delay(200);
  SS1_afstand3_Down = SS_Meting(SS1_TRIGPIN, SS1_ECHOPIN,SS1_samples3_Down);

  //pos 8
  Servo_Around_Y.write(70);
  Serial.println("Turning to the eight position");
  delay(200);
  SS1_afstand2_Down = SS_Meting(SS1_TRIGPIN, SS1_ECHOPIN,SS1_samples2_Down);
  //pos 9
  Servo_Around_Y.write(0);
  Serial.println("Turning to the ninth position");
  delay(200);
  SS1_afstand1_Down = SS_Meting(SS1_TRIGPIN, SS1_ECHOPIN,SS1_samples1_Down);
  Servo_Around_X.write(0);
  Serial.println("Turning to the first position");
  delay(200);

  Detach_Servos();
}