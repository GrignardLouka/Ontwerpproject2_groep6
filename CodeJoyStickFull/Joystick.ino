 /* //////////////////////////////////JoyStick On//////////////////////////////////
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
  }*/
