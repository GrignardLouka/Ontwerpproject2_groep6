// Motor ALW
int motorALWPin1 = 27; 
int motorALWPin2 = 26; 


// Motor ARW
int motorARWPin1 = 0; 
int motorARWPin2 = 2; 


// Motor VRW
int motorVRWPin1 = 12; 
int motorVRWPin2 = 4; 


// Motor VLW
int motorVLWPin1 = 25; 
int motorVLWPin2 = 33; 
int snelheid = 25;

void setup() {
  pinMode(motorALWPin1,OUTPUT);
  pinMode(motorALWPin2,OUTPUT);

  pinMode(motorARWPin1,OUTPUT);
  pinMode(motorARWPin2,OUTPUT);

  pinMode(motorVRWPin1,OUTPUT);
  pinMode(motorVRWPin2,OUTPUT);

  pinMode(motorVLWPin1,OUTPUT);
  pinMode(motorVLWPin2,OUTPUT);

  
  ledcSetup(0,5000,8);
  ledcAttachPin(motorALWPin1,0);
  ledcSetup(1,5000,8);
  ledcAttachPin(motorALWPin2,1);
  ledcSetup(2,5000,8);
  ledcAttachPin(motorARWPin1,2);
  ledcSetup(3,5000,8);
  ledcAttachPin(motorARWPin2,3);
  ledcSetup(4,5000,8);
  ledcAttachPin(motorVRWPin1,4);
  ledcSetup(5,5000,8);
  ledcAttachPin(motorVRWPin2,5);
  ledcSetup(6,5000,8);
  ledcAttachPin(motorVLWPin1,6); 
  ledcSetup(7,5000,8);
  ledcAttachPin(motorVLWPin2,7);    
  
  Serial.begin(115200);
  


}

void loop() {
  /*Forward(125);
  delay(5000);
  Stop(0);
  delay(5000);
  Left(225);
  delay(5000);
  Right(125);
  delay(5000);*/
  Serial.println(analogRead(35));
  Serial.println(analogRead(34));
  Serial.println("-------------");

  int xAxis = analogRead(34);
  int yAxis = analogRead(35);
  if(xAxis<2015 && xAxis>1815){
    if(yAxis<1910 && yAxis>1710){
      Stop(0);
    }
  }
  //Forward
  if(xAxis>2015){
    //snelheid = (4095-xAxis)/16;
    Forward(125);
  }
  //Backward
  if(xAxis < 1815){
    //snelheid = (2045-xAxis)/16;
    Backward(125);
  }
  //Right
  if(yAxis>1910){
    //snelheid = (4095-yAxis)/16;
    Right(125);
  }
  //Left
  if(yAxis < 1710){
    //snelheid = (2045-yAxis)/16;
    Left(125);}

}
void Forward(int snelheid)
{
  ledcWrite(0,snelheid);
  ledcWrite(1,0);
  ledcWrite(2,snelheid);
  ledcWrite(3,0);
  ledcWrite(4,snelheid);
  ledcWrite(5,0);
  ledcWrite(6,snelheid);
  ledcWrite(7,0);
}
void Backward(int snelheid)
{
  ledcWrite(0,0);
  ledcWrite(1,snelheid);
  ledcWrite(2,0);
  ledcWrite(3,snelheid);
  ledcWrite(4,0);
  ledcWrite(5,snelheid);
  ledcWrite(6,0);
  ledcWrite(7,snelheid);
 
  
}
void Stop(int snelheid)
{
  ledcWrite(0,0);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,0);
  ledcWrite(4,0);
  ledcWrite(5,0);
  ledcWrite(6,0);
  ledcWrite(7,0);
}
void Right(int snelheid)
{
  ledcWrite(0,0);
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
  ledcWrite(0,snelheid);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,snelheid);
  ledcWrite(4,snelheid);
  ledcWrite(5,0);
  ledcWrite(6,0);
  ledcWrite(7,snelheid);
}
