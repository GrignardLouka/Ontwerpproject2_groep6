//####################################################################    Pin    ############################################################################
const int JOYSTICKPIN_X = 35;         
const int JOYSTICKPIN_Y =34;
const int JOYSTICKPIN_BUTTON = 4;
const int JOYSTICK_CONTROL = 5;
const int JOYSTICK_Y_CENTER = 115;
const int JOYSTICK_Y_DISTANCE = ((255 - JOYSTICK_Y_CENTER) / 2); // 70
const int JOYSTICK_X_CENTER = 109;
const int JOYSTICK_X_DISTANCE = ((255 - JOYSTICK_X_CENTER) / 2); // 73

//##################################################################    Variable    ############################################################################
double Joystick_X;                    
double Joystick_Y;
int Joystick_Button; 
int Rotating = 0;
int Joystick_Control;
RunningMedian Joystick_X_samples = RunningMedian(19);    
RunningMedian Joystick_Y_samples = RunningMedian(19);

extern Adafruit_MCP23008 mcp;
extern int Movement_State;

extern String Mode;
void move(long period);

//##################################################################    PinMode    ############################################################################
void pinMode_Joystick(){
  pinMode(JOYSTICKPIN_X, INPUT);
  pinMode(JOYSTICKPIN_Y, INPUT);
  mcp.pinMode(JOYSTICKPIN_BUTTON, INPUT);
  mcp.pinMode(JOYSTICK_CONTROL, INPUT);

}
//##################################################################    Functions    ############################################################################


void joystick_Position(){
    Joystick_X_samples.add(map(analogRead(JOYSTICKPIN_X),0,4095,0,255));
    Joystick_X = Joystick_X_samples.getMedian();
    Joystick_Y_samples.add(map(analogRead(JOYSTICKPIN_Y),0,4095,0,255));
    Joystick_Y = Joystick_Y_samples.getMedian();

    Joystick_Button = !mcp.digitalRead(JOYSTICKPIN_BUTTON);
    Serial.println(Joystick_Button);
    if(Rotating == 1){    //If you stop rotating STOP and wait 500 ms to prevent weird behavior
      if(Joystick_Button == 0){
        stop();
        delay(500);
        Rotating = 0;
      }
    }
}
void move_Joystick(){


  if(Joystick_Button == 0){
    if(Joystick_X < (255 - JOYSTICK_Y_DISTANCE)       &&       Joystick_X > JOYSTICK_Y_DISTANCE){
      if(Joystick_Y > (255 - JOYSTICK_X_DISTANCE)){
        forward(); //* 3.45
        move(map(((Joystick_Y - (255 - JOYSTICK_X_DISTANCE)) * 2, 0), 0 ,70 , 250, 20) )
      }
      else if(Joystick_Y < JOYSTICK_X_DISTANCE){
        backward((73 - Joystick_Y) * 2, 0); // 3.45
      }
      else{
        stop();
      }
    }
    else if(Joystick_X < JOYSTICK_Y_DISTANCE){
      left((70 - Joystick_X) * 2, 0); // 3.6
    }
    else if(Joystick_X > (255 - JOYSTICK_Y_DISTANCE)){
      right((Joystick_X - (255 - JOYSTICK_Y_DISTANCE)) * 2, 0); // 3.6
    }
    
  }
  else{ // if button = 1 = HIGH
      if(Joystick_X > (255 - JOYSTICK_Y_DISTANCE)){
          rotate_Right((Joystick_X - (255 - JOYSTICK_Y_DISTANCE)) * 2, 0); // * 3.6
          Rotating = 1;
        }
        else if(Joystick_X < JOYSTICK_Y_DISTANCE){
          rotate_Left((JOYSTICK_Y_DISTANCE - Joystick_X) * 2, 0); // *3.6
          Rotating = 1;
        }
        else{
          stop();
        }
    }
  
}







