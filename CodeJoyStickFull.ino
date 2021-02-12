#include <Arduino.h>
#include <RunningMedian.h>
#include "NewPing.h" 

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
int snelheid = 25;

int pressed = 1;
int button = 39;
int JoyStickSwitch = 0;
//##################### 2 HC-SR04 sensoren
const int SensorR_trigPin =16;     
const int SensorR_echoPin =17;    
long SensorR_cm;

const int SensorL_trigPin = 2;    
const int SensorL_echoPin = 4;    
long SensorL_cm;

const int SensorV_trigPin = 15;    
const int SensorV_echoPin = 18;    
long SensorV_cm;

long duration;
int dr;
int dl;
int dv;
RunningMedian SensorR_samples = RunningMedian(100);
RunningMedian SensorL_samples = RunningMedian(100);
RunningMedian SensorV_samples = RunningMedian(100);
//////////////////////SETUP////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin (115200);
  
  pinMode(motorALWPin1, OUTPUT);
  pinMode(motorALWPin2, OUTPUT);

  pinMode(motorARWPin1, OUTPUT);
  pinMode(motorARWPin2, OUTPUT);

  pinMode(motorVRWPin1, OUTPUT);
  pinMode(motorVRWPin2, OUTPUT);

  pinMode(motorVLWPin1, OUTPUT);
  pinMode(motorVLWPin2, OUTPUT);
  pinMode(button, INPUT);

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
  //Start

  //2 HC-SRO4 sensoren
  pinMode(SensorR_trigPin, OUTPUT);
  pinMode(SensorR_echoPin, INPUT);

  pinMode(SensorL_trigPin, OUTPUT);
  pinMode(SensorL_echoPin, INPUT);
  
  pinMode(SensorV_trigPin, OUTPUT);
  pinMode(SensorV_echoPin, INPUT);
}
/////////////////////////////LOOP///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  //////////////////////////////////JoyStick On//////////////////////////////////
  if(JoyStickSwitch == 1){   
    //////////////////////////////////Joystick not Pressed //////////////////////////////////
    if(digitalRead(button)== 0){
      int xAxis = analogRead(34);
      int yAxis = analogRead(35); 
      //////////////////////////////////stop//////////////////////////////////
      if (xAxis < 2015 && xAxis > 1815) {
        if (yAxis < 1910 && yAxis > 1710) {
  
          Stop(0);
        }
      }
      //////////////////////////////////Forward//////////////////////////////////
      if (xAxis > 2100) {
        snelheid = (3830 - xAxis) / 16;
        Forward(snelheid);
  
      }
      //////////////////////////////////Backward//////////////////////////////////
      if (xAxis < 1725) {
        snelheid = (1915 - xAxis) / 16;
        Backward(snelheid);
      }
      //////////////////////////////////Right//////////////////////////////////
      if (yAxis > 2000) {
        snelheid = (3620 - yAxis) / 16;
        Right(200);
      }
      //////////////////////////////////Left//////////////////////////////////
      if (yAxis < 1650) {
        snelheid = (1810 - yAxis) / 16;
        Left(200);
      }
    }
    //////////////////////////////////Joystick Pressed//////////////////////////////////
    while( digitalRead(button) == 1){
      //Rotate Right
      int xAxis = analogRead(34);
      int yAxis = analogRead(35);
      if(yAxis>1910){
        RotateRight(200);
  
      }
      //Rotate Left
      if(yAxis < 1710){
          RotateLeft(200);
      }    
    }
  }
/////////////////////////////////////// HC_SRO4 sensor reading //////////////////////////////////

  /*Serial.print("Sensor rechts meet: ");
  Serial.print(SensorR_cm);
  Serial.println("cm");
 
  Serial.println("Delay");


  Serial.println("Sensor links meet: ");
  Serial.print(SensorL_cm);
  Serial.print(" cm");*/




  ///////////////////////////////////////SelfDriving)//////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////Scan obstacles///////////////////////////////////////////////////////////////////////////
  scanUltrasonicV();
  scanUltrasonicL();
  scanUltrasonicR();

  Serial.print("Sensor rechts meet: ");
  Serial.print(SensorR_cm);
  Serial.println("cm");
 
  Serial.print("Sensor links meet: ");
  Serial.print(SensorL_cm);
  Serial.println(" cm");   
  
  Serial.print("Sensor voor meet: ");
  Serial.print(SensorV_cm);
  Serial.println(" cm");  
  ///////////////////////////////////////Calculating Driving state////////////////////////////////////////////////////////////////
  CalculateState3();



  /////////////////////////////////////
}/////////////////////////////////////////END LOOP///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////MOVEMENT/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Forward(int snelheid)
{
  ledcWrite(0, snelheid);
  ledcWrite(1, 0);
  ledcWrite(2, snelheid);
  ledcWrite(3, 0);
  ledcWrite(4, snelheid);
  ledcWrite(5, 0);
  ledcWrite(6, snelheid);
  ledcWrite(7, 0);
}
void Backward(int snelheid)
{
  ledcWrite(0, 0);
  ledcWrite(1, snelheid);
  ledcWrite(2, 0);
  ledcWrite(3, snelheid);
  ledcWrite(4, 0);
  ledcWrite(5, snelheid);
  ledcWrite(6, 0);
  ledcWrite(7, snelheid);
}
void Stop(int snelheid)
{
  ledcWrite(0, 0);
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, 0);
  ledcWrite(4, 0);
  ledcWrite(5, 0);
  ledcWrite(6, 0);
  ledcWrite(7, 0);
}
void Right(int snelheid)
{
  ledcWrite(0, 0);
  ledcWrite(1,snelheid);
  ledcWrite(2,snelheid);
  ledcWrite(3,0);
  ledcWrite(4,0);
  ledcWrite(5,snelheid);
  ledcWrite(6,snelheid);
  ledcWrite(7,0);
}
void Left(int snelheid)
{
  ledcWrite(0, snelheid);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,snelheid);
  ledcWrite(4,snelheid);
  ledcWrite(5,0);
  ledcWrite(6,0);
  ledcWrite(7,snelheid);
}
void RotateRight(int snelheid)
{
  ledcWrite(0,snelheid);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,snelheid);
  ledcWrite(4,0);
  ledcWrite(5,snelheid);
  ledcWrite(6,snelheid);
  ledcWrite(7,0); 
}
void RotateLeft(int snelheid)
{
  ledcWrite(0, 0);
  ledcWrite(1, snelheid);
  ledcWrite(2, snelheid);
  ledcWrite(3, 0);
  ledcWrite(4, snelheid);
  ledcWrite(5, 0);
  ledcWrite(6, 0);
  ledcWrite(7, snelheid);
}
void ForwardRight(int snelheid)
{
  ledcWrite(0, 0);
  ledcWrite(1, 0);
  ledcWrite(2, snelheid);
  ledcWrite(3, 0);
  ledcWrite(4, 0);
  ledcWrite(5, 0);
  ledcWrite(6, snelheid);
  ledcWrite(7, 0);  
}
void ForwardLeft(int snelheid)
{
  ledcWrite(0, snelheid);
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, 0);
  ledcWrite(4, snelheid);
  ledcWrite(5, 0);
  ledcWrite(6, 0);
  ledcWrite(7, 0);  
}
//////////////////////////////////Ultrasonic Sensor//////////////////////////////////
void scanUltrasonicR(){
  for (int i = 0; i < 100; i++) {
  digitalWrite(SensorR_trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(SensorR_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(SensorR_trigPin, LOW);
  duration = pulseIn(SensorR_echoPin, HIGH);    // Mesure time needed for signal to return(in microseconds)
  SensorR_samples.add((duration/2) / 29.1);
  SensorR_cm = SensorR_samples.getMedian();
  dr = SensorR_cm;
  }
}
void scanUltrasonicL(){
  for (int i = 0; i < 100; i++) {
  digitalWrite(SensorL_trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(SensorL_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(SensorL_trigPin, LOW);
  duration = pulseIn(SensorL_echoPin, HIGH);    // Mesure time needed for signal to return(in microseconds)
  SensorL_samples.add((duration/2) / 29.1);
  SensorL_cm = SensorL_samples.getMedian();
  dl = SensorL_cm;
  }
}
void scanUltrasonicV(){
  for (int i = 0; i < 100; i++) {
  digitalWrite(SensorV_trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(SensorV_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(SensorV_trigPin, LOW);
  duration = pulseIn(SensorV_echoPin, HIGH);    // Mesure time needed for signal to return(in microseconds)
  SensorV_samples.add((duration/2) / 29.1);
  SensorV_cm = SensorV_samples.getMedian();
  dv = SensorV_cm;
  }
}
/////////////////////////////////Driving State///////////////////////////////////////
void calculateState(){
  if(dr>dl){
    if(dr-dl<8){
    Forward(200);
    Serial.println("dr-dl<5,forward");
    delay(250);
    Stop(0);    
    }    
  }
  if(dl>dr){
    if(dl-dr<8){
    Forward(200);
    Serial.println("dl-dr<5,forward");    
    delay(250);
    Stop(0);
       
    }
  }
  if(dr-dl>8){
    ForwardRight(200);
    Serial.println("dr-dl>5,go right");
    delay(250);
    Stop(0);

    /*RotateRight(100);   
    Forward(200);*/
    
  }
  if(dl-dr>8){
    ForwardLeft(200);
    Serial.println("dl-dr>5,go left");
    delay(250);
    Stop(0);

    /*RotateLeft(100);
    Forward(200);*/
    
  }
  if(dr<8 && dl<8){
    if(dr>dl){
      RotateRight(200);
      Serial.println("dr>dl,Rotateright");
      delay(500);//45graden
      Stop(0);

      
    }
    if(dl>dr){
      RotateLeft(200);
      Serial.println("dl>dr,rotateleft");
      delay(500);//45graden
      Stop(0);

      
    }
  }
}
void CalculateState2()//Hug Right wall
{
  if(dr>7&& dv >5)
  {
    Right(200);
    delay(250);
    Stop(0);
  }
  if(dr<7 && dv>5)
  {
    Forward(200);
    delay(250);
    Stop(0);
  }
  if(dr<7 && dv<5)
  {
    Left(200);
    delay(250);
    Stop(0);
    
  }
  int xdl = dl;
  if(dr>7 && dv<5)
  {
    while((dl-xdl)<5)
    {
      Backward(200);
      delay(250);
      Stop(0);
      scanUltrasonicL();

    }
    while(dl>5)
    {
      Left(200);
      delay(200);
      Stop(0);
      scanUltrasonicL();
    }
  }
  
}
void CalculateState3()
{
  if(dv>dr && dv>dl)
  {

      Forward(200);
      delay(200);
      Stop(0);
  
  }
  if(dr>dv && dr>dl)
  {
    
      RotateRight(200);
      delay(500);
      Stop(0);
    
  }
  if(dl>dv && dl>dr)
  {

    RotateLeft(200);
    delay(500);
    Stop(0);
    
  }
}
