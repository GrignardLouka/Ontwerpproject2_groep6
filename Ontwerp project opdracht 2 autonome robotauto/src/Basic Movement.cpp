#include "Basic Movement.h"

void PinMode_Basic_Movement(){
  pinMode(MOTORALWPIN1,OUTPUT);       // Set pin to output
  ledcSetup(0,5000,8);                // Create ledc 
  ledcAttachPin(MOTORALWPIN1,0);      // Asign pin to ledc

  pinMode(MOTORALWPIN2,OUTPUT);
  ledcSetup(1,5000,8);
  ledcAttachPin(MOTORALWPIN2,1);

  pinMode(MOTORARWPIN1,OUTPUT);
  ledcSetup(2,5000,8);
  ledcAttachPin(MOTORARWPIN1,2);

  pinMode(MOTORARWPIN2,OUTPUT);
  ledcSetup(3,5000,8);
  ledcAttachPin(MOTORARWPIN2,3);

  pinMode(MOTORVRWPIN1,OUTPUT);
  ledcSetup(4,5000,8);
  ledcAttachPin(MOTORVRWPIN1,4);

  pinMode(MOTORVRWPIN2,OUTPUT);
  ledcSetup(5,5000,8);
  ledcAttachPin(MOTORVRWPIN2,5);

  pinMode(MOTORVLWPIN1,OUTPUT);
  ledcSetup(6,5000,8);
  ledcAttachPin(MOTORVLWPIN1,6);

  pinMode(MOTORVLWPIN2,OUTPUT);
  ledcSetup(7,5000,8);
  ledcAttachPin(MOTORVLWPIN2,7); 
}

void Stop()
{
  ledcWrite(0,0);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,0);
  ledcWrite(4,0);
  ledcWrite(5,0);
  ledcWrite(6,0);
  ledcWrite(7,0);
  Serial.println("Stop");
}
void Forward(int snelheid, int tijd)
{
  ledcWrite(0,snelheid);
  ledcWrite(1,0);
  ledcWrite(2,snelheid);
  ledcWrite(3,0);
  ledcWrite(4,snelheid);
  ledcWrite(5,0);
  ledcWrite(6,snelheid);
  ledcWrite(7,0);

  if(tijd != 0){
    delay(tijd);
    Stop();
  }

  Serial.println("Forward");
}
void Backward(int snelheid, int tijd)
{
  ledcWrite(0,0);
  ledcWrite(1,snelheid);
  ledcWrite(2,0);
  ledcWrite(3,snelheid);
  ledcWrite(4,0);
  ledcWrite(5,snelheid);
  ledcWrite(6,0);
  ledcWrite(7,snelheid);

  if(tijd != 0){
    delay(tijd);
    Stop();
  }
  Serial.println("Backwards");

 
  
}
void Right(int snelheid, int tijd)
{
  ledcWrite(0,0);
  ledcWrite(1,snelheid);
  ledcWrite(2,snelheid);
  ledcWrite(3,0);
  ledcWrite(4,0);
  ledcWrite(5,snelheid);
  ledcWrite(6,snelheid);
  ledcWrite(7,0);

  if(tijd != 0){
    delay(tijd);
    Stop();
  }

  Serial.println("Right");
}
void Left(int snelheid, int tijd)
{
  ledcWrite(0,snelheid);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,snelheid);
  ledcWrite(4,snelheid);
  ledcWrite(5,0);
  ledcWrite(6,0);
  ledcWrite(7,snelheid);

  if(tijd != 0){
    delay(tijd);
    Stop();
  }

  Serial.println("Left");
}
void Rotate_Left(int snelheid, int tijd){
  ledcWrite(0,0);
  ledcWrite(1,snelheid);
  ledcWrite(2,snelheid);
  ledcWrite(3,0);
  ledcWrite(4,snelheid);
  ledcWrite(5,0);
  ledcWrite(6,0);
  ledcWrite(7,snelheid);

  if(tijd != 0){
    delay(tijd);
    Stop();
  }

  Serial.println("Rotate Left");
}
void Rotate_Right(int snelheid, int tijd){
  ledcWrite(0,snelheid);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,snelheid);
  ledcWrite(4,0);
  ledcWrite(5,snelheid);
  ledcWrite(6,snelheid);
  ledcWrite(7,0);

  if(tijd != 0){
    delay(tijd);
    Stop();
  }

  Serial.println("Rotate Right");
}
