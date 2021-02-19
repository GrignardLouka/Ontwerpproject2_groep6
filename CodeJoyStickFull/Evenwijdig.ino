void EvenwijdigMetZij()
{
  dr = dr -9;
  dl = dl-9;
  if(dr<dl){
    if(dr>dra)
    {
      while(dr-dra>5)
      {
        scanUltrasonic180();
        delay(350);
        scanUltrasonicRA();
        delay(350);
        RotateRight(150);
        delay(350);
        Stop(0);
        Serial.println("dr-dra>5,RotateRight ");
  
      }
      Stop(0);
  
    }
    if(dr<dra)
    {
      while(dra-dr>5)
      {
        scanUltrasonic180();
        delay(350);
        scanUltrasonicRA();
        delay(350);
        RotateLeft(150);
        delay(350);
        Stop(0);
        Serial.println("dra-dr>5,RotateLeft ");
        
  
      }
      Stop(0);
    }
  }
  if(dl<dr){
    if(dl>dla)
    {
      while(dl-dla>5)
      {
        scanUltrasonic180();
        delay(350);
        scanUltrasonicLA();
        delay(350);
        RotateLeft(150);
        delay(350);
        Stop(0);
        Serial.println("dl-dla>5,RotateLeft ");
        
  
      }
      Stop(0);
  
    }
    if(dl<dla)
    {
      while(dla-dl>5)
      {
        scanUltrasonic180();
        delay(350);
        scanUltrasonicLA();
        delay(350);
        RotateRight(150);
        delay(350);
        Stop(0);
        Serial.println("dla-dl>5,RotateRight ");
        
  
      }
      Stop(0);
    }
  }
}
