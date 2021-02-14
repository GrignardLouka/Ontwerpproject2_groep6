//############### STATE 1 (scan)
#include "Mode2_State1_Scanning.h"


void PinMode_Scanning(){
  //Sensor
  pinMode(SS1_TRIGPIN, OUTPUT);
  pinMode(SS2_TRIGPIN, OUTPUT);
  pinMode(SS3_TRIGPIN, OUTPUT);
  pinMode(SS4_TRIGPIN, OUTPUT);

  pinMode(SS1_ECHOPIN, INPUT);
  pinMode(SS2_ECHOPIN, INPUT);
  pinMode(SS3_ECHOPIN, INPUT);
  pinMode(SS4_ECHOPIN, INPUT);

  //Servo
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  Servo_Around_Y.setPeriodHertz(50);    // standard 50 hz servo
  Servo_Around_Y.attach(SERVO_AROUND_Y_PIN, 500, 2500);
  Servo_Around_X.setPeriodHertz(50);
  Servo_Around_X.attach(SERVO_AROUND_X_PIN, 500, 2500);
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