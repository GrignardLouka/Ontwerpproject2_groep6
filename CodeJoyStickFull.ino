
#include <ESP32Servo.h>
Servo myservo;

// Motor ALW
int motorALWPin1 = 27;
int motorALWPin2 = 26;


// Motor ARW
int motorARWPin1 = 32;//was 21;
int motorARWPin2 = 19;


// Motor VRW
int motorVRWPin1 = 23;
int motorVRWPin2 = 13;//was 22 ori;


// Motor VLW
int motorVLWPin1 = 25;
int motorVLWPin2 = 33;


/*int pressed = 1;
int button = 39;
int JoyStickSwitch = 0;*/
bool b = true;
//##################### 2 HC-SR04 sensoren
/*const int SensorR_trigPin =15;     
const int SensorR_echoPin =18;    
long SensorR_cm;*/

const int SensorLA_trigPin = 2;    
const int SensorLA_echoPin = 4;    
long SensorL_cm;

const int SensorV_trigPin = 15;    
const int SensorV_echoPin = 18;    
long SensorV_cm;

const int SensorRA_trigPin = 16;    
const int SensorRA_echoPin = 17;    
long SensorRA_cm;

float duration;

int dr;
int dl;
int dv;
int dra;
int dla;

//////////////////////SETUP////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin (115200);
  myservo.attach(14);

  pinMode(motorALWPin1, OUTPUT);
  pinMode(motorALWPin2, OUTPUT);

  pinMode(motorARWPin1, OUTPUT);
  pinMode(motorARWPin2, OUTPUT);

  pinMode(motorVRWPin1, OUTPUT);
  pinMode(motorVRWPin2, OUTPUT);

  pinMode(motorVLWPin1, OUTPUT);
  pinMode(motorVLWPin2, OUTPUT);
  //pinMode(button, INPUT);

////////////PWM Channel/////////////
  ledcSetup(0, 5000, 8);
  ledcAttachPin(motorALWPin1, 0);
  ledcSetup(1, 5000, 8);
  ledcAttachPin(motorALWPin2, 1);
  ledcSetup(2, 5000, 8);
  ledcAttachPin(motorARWPin1, 2);
  ledcSetup(3, 5000, 8);
  ledcAttachPin(motorARWPin2, 3);
  ledcSetup(4, 5000, 8);
  ledcAttachPin(motorVRWPin1, 4);
  ledcSetup(5, 5000, 8);
  ledcAttachPin(motorVRWPin2, 5);
  ledcSetup(6, 5000, 8);
  ledcAttachPin(motorVLWPin1, 6);
  ledcSetup(7, 5000, 8);
  ledcAttachPin(motorVLWPin2, 7);
  

  ////////////////////////////// 2 HC-SRO4 sensoren///////////////////
/*  pinMode(SensorR_trigPin, OUTPUT);
  pinMode(SensorR_echoPin, INPUT);*/

  pinMode(SensorLA_trigPin, OUTPUT);
  pinMode(SensorLA_echoPin, INPUT);
  
  pinMode(SensorV_trigPin, OUTPUT);
  pinMode(SensorV_echoPin, INPUT);

  pinMode(SensorRA_trigPin, OUTPUT);
  pinMode(SensorRA_echoPin, INPUT); 
  ////////////////////////////////Servo/////////////////

}
/////////////////////////////LOOP///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {


 //EvenwijdigMetZij();
 /*if(b==true){
  myservo.write(90);
  b = false;
 }  */
  //CalculateLongestDistance();
  Forward(200);
  delay(500);
  Stop(0);
  delay(1000);
  myservo.write(90);
  delay(1000);
  myservo.write(180);
  delay(1000);
  myservo.write(0);
  delay(1000);

}/////////////////////////////////////////END LOOP///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
