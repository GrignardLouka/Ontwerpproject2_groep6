//Basic Movement
int Frequency;
bool Movement_State = false;

//Joystick
double Joystick_X;                    
double Joystick_Y;
int Joystick_Button; 
int Rotating = 0;
int Joystick_Control;
RunningMedian Joystick_X_samples = RunningMedian(19);    
RunningMedian Joystick_Y_samples = RunningMedian(19);

//Scanning
RunningMedian SS1_samples1 = RunningMedian(49); long SS1_afstand1;
RunningMedian SS1_samples2 = RunningMedian(49); long SS1_afstand2;
RunningMedian SS1_samples3 = RunningMedian(49); long SS1_afstand3;   

RunningMedian SS1_samples1_Down = RunningMedian(49); long SS1_afstand1_Down;
RunningMedian SS1_samples2_Down = RunningMedian(49); long SS1_afstand2_Down;
RunningMedian SS1_samples3_Down = RunningMedian(49); long SS1_afstand3_Down;

RunningMedian SS2_samples = RunningMedian(49); long SS2_afstand;

Servo Servo_Around_Y;
Servo Servo_Around_X;

//BNO055
const int BNO055_SAMPLERATE_DELAY_MS =100;
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);
RunningMedian lijstx = RunningMedian(10); RunningMedian lijsty = RunningMedian(10); RunningMedian lijstz = RunningMedian(10);

bool Climbing = false;

//Expander
Adafruit_MCP23008 mcp;
