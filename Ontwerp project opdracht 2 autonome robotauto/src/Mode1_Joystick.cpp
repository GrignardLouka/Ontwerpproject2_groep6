#include "Mode1_Joystick.h"

void PinMode_Joystick(){
  pinMode(JOYSTICKPIN_X, INPUT);
  pinMode(Joystick_Y, INPUT);
  pinMode(JOYSTICKPIN_BUTTON, INPUT_PULLUP);
  pinMode(JOYSTICK_CONTROL, INPUT_PULLDOWN);
}

void Joystick_Position(){
    Joystick_X_samples.add(map(analogRead(JOYSTICKPIN_X),0,4095,0,255));
    Joystick_X = Joystick_X_samples.getMedian();
    Joystick_Y_samples.add(map(analogRead(JOYSTICKPIN_Y),0,4095,0,255));
    Joystick_Y = Joystick_Y_samples.getMedian();

    Joystick_Button = !digitalRead(JOYSTICKPIN_BUTTON);
    if(Rotating == 1){    //If you stop rotating STOP and wait 750 ms to prevent weird behavior
      if(Joystick_Button == 0){
        Stop();
        delay(500);
        Rotating = 0;
      }
    }
}
void Move_Joystick(){

  if(Joystick_Button == 0){
    Serial.println(Joystick_Button);
    if(Joystick_X < 185 && Joystick_X > 70){
      if(Joystick_Y > 182){
        Forward((Joystick_Y - 182) * 2, 0); //* 3.45
      }
      else if(Joystick_Y < 73){
        Backward((73 - Joystick_Y) * 2, 0); // 3.45
      }
      else{
        Stop();
      }
    }
    else if(Joystick_X < 70){
      Left((70 - Joystick_X) * 2, 0); // 3.6
    }
    else if(Joystick_X > 185){
      Right((Joystick_X - 185) * 2, 0); // 3.6
    }
    
  }
  else{ // if button = 1 = HIGH
      if(Joystick_X > 185){
          Rotate_Right((Joystick_X - 185) * 2, 0); // * 3.6
          Rotating = 1;
        }
        else if(Joystick_X < 70){
          Rotate_Left((70 - Joystick_X) * 2, 0); // *3.6
          Rotating = 1;
        }
        else{
          Stop();
        }
    }
  
}
