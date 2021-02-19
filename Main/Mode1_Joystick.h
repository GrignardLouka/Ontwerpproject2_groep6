//####################################################################    Pin    ############################################################################
const int JOYSTICKPIN_X = 35;         
const int JOYSTICKPIN_Y =34;
const int JOYSTICKPIN_BUTTON = 4;
const int JOYSTICK_CONTROL = 5;
const int Y_CENTER = 115;
const int Y_DISTANCE = ((255 - Y_CENTER) / 2); // 70
const int X_CENTER = 109;
const int X_DISTANCE = ((255 - X_CENTER) / 2); // 73

//##################################################################    Variable    ############################################################################

int Rotating = 0;
int Joystick_Control;


extern Adafruit_MCP23008 mcp;
extern int Movement_State;

//##################################################################    PinMode    ############################################################################
void pinMode_Joystick(){
  pinMode(JOYSTICKPIN_X, INPUT);
  pinMode(JOYSTICKPIN_Y, INPUT);
  mcp.pinMode(JOYSTICKPIN_BUTTON, INPUT);
  mcp.pinMode(JOYSTICK_CONTROL, INPUT);

}
//##################################################################    Functions    ############################################################################

void move_Joystick(int X, int Y, int Button){


  if(Button == 0){
    if(X < (255 - Y_DISTANCE)       &&       X > Y_DISTANCE){
      if(Y > (255 - X_DISTANCE)){
        forward((Y - (255 - X_DISTANCE)) * 2); //* 3.45
      }
      else if(Y < X_DISTANCE){
        backward((73 - Y) * 2); // 3.45
      }
      else{
        stop();
      }
    }
    else if(X < Y_DISTANCE){
      left((70 - X) * 2); // 3.6
    }
    else if(X > (255 - Y_DISTANCE)){
      right((X - (255 - Y_DISTANCE)) * 2); // 3.6
    }
    
  }
  else{ // if button = 1 = HIGH
      if(X > (255 - Y_DISTANCE)){
          rotate_right((X - (255 - Y_DISTANCE)) * 2); // * 3.6
          Rotating = 1;
        }
        else if(X < Y_DISTANCE){
          rotate_left((Y_DISTANCE - X) * 2); // *3.6
          Rotating = 1;
        }
        else{
          stop();
        }
    }
  
}
void joystick_Position(){
	int X;                    
    int Y;
    int Button; 
    RunningMedian X_samples = RunningMedian(19);    
    RunningMedian Y_samples = RunningMedian(19);

    X_samples.add(map(analogRead(JOYSTICKPIN_X),0,4095,0,255));
    X = X_samples.getMedian();
    Y_samples.add(map(analogRead(JOYSTICKPIN_Y),0,4095,0,255));
    Y = Y_samples.getMedian();

    Button = !mcp.digitalRead(JOYSTICKPIN_BUTTON);
    Serial.println(Button);
    if(Rotating == 1){    //If you stop rotating STOP and wait 500 ms to prevent weird behavior
      if(Button == 0){
        stop();
        delay(500);
        Rotating = 0;
      }
    }

	move_Joystick(X , Y , Button);
}










