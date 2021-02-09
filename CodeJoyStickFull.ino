// Motor ALW
int motorALWPin1 = 27;
int motorALWPin2 = 26;


// Motor ARW
int motorARWPin1 = 21;
int motorARWPin2 = 19;


// Motor VRW
int motorVRWPin1 = 23;
int motorVRWPin2 = 22;


// Motor VLW
int motorVLWPin1 = 25;
int motorVLWPin2 = 33;
int snelheid = 25;

int pressed = 1;
int button = 39;
void setup() {
  pinMode(motorALWPin1, OUTPUT);
  pinMode(motorALWPin2, OUTPUT);

  pinMode(motorARWPin1, OUTPUT);
  pinMode(motorARWPin2, OUTPUT);

  pinMode(motorVRWPin1, OUTPUT);
  pinMode(motorVRWPin2, OUTPUT);

  pinMode(motorVLWPin1, OUTPUT);
  pinMode(motorVLWPin2, OUTPUT);
  pinMode(button, INPUT);


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

  Serial.begin(115200);



}

void loop() {

  int xAxis = analogRead(34);
  int yAxis = analogRead(35);
  Serial.println(digitalRead(39));
  Serial.println("-------------");
  //////////button pressing////////
  if(digitalRead(button)==1)
  {
    pressed = !pressed;
  }  
  ///////Button not Pressed /////////////////
  if(digitalRead(button)== 0){
  Serial.println("Translatie");
  Serial.println(xAxis); 
  Serial.println(yAxis); 
  //stop
  if (xAxis < 2015 && xAxis > 1815) {
    if (yAxis < 1910 && yAxis > 1710) {
      Serial.println("stop");
      Stop(0);
    }
  }
  //Forward
  if (xAxis > 2100) {
    snelheid = (3830 - xAxis) / 16;
    Forward(snelheid);
    Serial.println("forward");
  }
  //Backward
  if (xAxis < 1725) {
    snelheid = (1915 - xAxis) / 16;
    Backward(snelheid);
    Serial.println("backward");
  }
  //Right
  if (yAxis > 2000) {
    snelheid = (3620 - yAxis) / 16;
    Right(200);
    Serial.println("right");
  }
  //Left
  if (yAxis < 1650) {
    snelheid = (1810 - yAxis) / 16;
    Left(200);
    Serial.println("left");
  }
  }
  /////////Button Pressed//////////////
  while( digitalRead(button) == 1){
  Serial.println("Rotatie"); 
  Serial.println(xAxis); 
  Serial.println(yAxis); 
  //Rotate Right
  int xAxis = analogRead(34);
  int yAxis = analogRead(35);
  if(yAxis>1910){
  RotateRight(200);
  Serial.println("rotateleft");
  }
  //Rotate Left
  if(yAxis < 1710){
  RotateLeft(200);
  Serial.println("rotateleft");
  }
  
    
  }

}
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
  Serial.println("infunction");
  ledcWrite(0,snelheid);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,snelheid);
  ledcWrite(4,0);
  ledcWrite(5,snelheid);
  ledcWrite(6,snelheid);
  ledcWrite(7,0);
  Serial.println("zzzzzz");  
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
