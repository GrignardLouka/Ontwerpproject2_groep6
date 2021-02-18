void CalculateLongestDistance()
{
  scanUltrasonicV();
  if(dv<=10 || dv>800)
  {
    Stop(0);
    delay(500);
    scanUltrasonic180();
    if(dr>dl && dr<100){
      RotateRight(150);
      delay(500);
    }
    else if(dr<dl && dl<100)
    {
      RotateLeft(150);
      delay(500);
    }
   
  }
  else{
    Forward(115);
    delay(500);    
    Stop(0);
    //scanUltrasonicV();
  }
 

}
