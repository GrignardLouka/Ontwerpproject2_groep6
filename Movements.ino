void Forward(int snelheid)
{
  ledcWrite(0, 125);
  ledcWrite(1, 0);
  ledcWrite(2, snelheid);
  ledcWrite(3, 0);
  ledcWrite(4, snelheid);
  ledcWrite(5, 0);
  ledcWrite(6, snelheid);
  ledcWrite(7, 0);
  /*analogWrite(motorALWPin1,snelheid);
  analogWrite(motorALWPin2,0);
  analogWrite(motorARWPin1,snelheid);
  analogWrite(motorARWPin2,0);
  analogWrite(motorVRWPin1,snelheid);
  analogWrite(motorVRWPin2,0);
  analogWrite(motorVLWPin1,185);
  analogWrite(motorVLWPin2,0);*/
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
  /*analogWrite(motorALWPin1,0);
  analogWrite(motorALWPin2,snelheid);
  analogWrite(motorARWPin1,0);
  analogWrite(motorARWPin2,snelheid);
  analogWrite(motorVRWPin1,0);
  analogWrite(motorVRWPin2,snelheid);
  analogWrite(motorVLWPin1,0);
  analogWrite(motorVLWPin2,snelheid);*/
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

  /*analogWrite(motorALWPin1,0);
  analogWrite(motorALWPin2,0);
  analogWrite(motorARWPin1,0);
  analogWrite(motorARWPin2,0);
  analogWrite(motorVRWPin1,0);
  analogWrite(motorVRWPin2,0);
  analogWrite(motorVLWPin1,0);
  analogWrite(motorVLWPin2,0);*/
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

  /*analogWrite(motorALWPin1,0);
  analogWrite(motorALWPin2,snelheid);
  analogWrite(motorARWPin1,snelheid);
  analogWrite(motorARWPin2,0);
  analogWrite(motorVRWPin1,0);
  analogWrite(motorVRWPin2,snelheid);
  analogWrite(motorVLWPin1,snelheid);
  analogWrite(motorVLWPin2,0);*/
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

  /*analogWrite(motorALWPin1,snelheid);
  analogWrite(motorALWPin2,0);
  analogWrite(motorARWPin1,0);
  analogWrite(motorARWPin2,snelheid);
  analogWrite(motorVRWPin1,snelheid);
  analogWrite(motorVRWPin2,0);
  analogWrite(motorVLWPin1,0);
  analogWrite(motorVLWPin2,snelheid);*/
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

  /*analogWrite(motorALWPin1,snelheid);
  analogWrite(motorALWPin2,0);
  analogWrite(motorARWPin1,0);
  analogWrite(motorARWPin2,snelheid);
  analogWrite(motorVRWPin1,0);
  analogWrite(motorVRWPin2,snelheid);
  analogWrite(motorVLWPin1,snelheid);
  analogWrite(motorVLWPin2,0);*/
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

  /*analogWrite(motorALWPin1,0);
  analogWrite(motorALWPin2,snelheid);
  analogWrite(motorARWPin1,snelheid);
  analogWrite(motorARWPin2,0);
  analogWrite(motorVRWPin1,snelheid);
  analogWrite(motorVRWPin2,0);
  analogWrite(motorVLWPin1,0);
  analogWrite(motorVLWPin2,snelheid);*/
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

  /*analogWrite(motorALWPin1,0);
  analogWrite(motorALWPin2,0);
  analogWrite(motorARWPin1,snelheid);
  analogWrite(motorARWPin2,0);
  analogWrite(motorVRWPin1,0);
  analogWrite(motorVRWPin2,0);
  analogWrite(motorVLWPin1,snelheid);
  analogWrite(motorVLWPin2,0);*/
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

  /*analogWrite(motorALWPin1,snelheid);
  analogWrite(motorALWPin2,0);
  analogWrite(motorARWPin1,0);
  analogWrite(motorARWPin2,0);
  analogWrite(motorVRWPin1,snelheid);
  analogWrite(motorVRWPin2,0);
  analogWrite(motorVLWPin1,0);
  analogWrite(motorVLWPin2,0);*/
}
