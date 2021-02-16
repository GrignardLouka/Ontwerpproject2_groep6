//##################################################################    Variable    ############################################################################
//################## Basic Movement
int Movement_State = 0;

//################## Joystick
double Joystick_X;                    
double Joystick_Y;
int Joystick_Button; 
int Rotating = 0;
int Joystick_Control;
RunningMedian Joystick_X_samples = RunningMedian(19);    
RunningMedian Joystick_Y_samples = RunningMedian(19);

//################## Scanning
// Sensor op servo
RunningMedian SS_Front_samples1 = RunningMedian(49); long SS_Front_afstand1;
RunningMedian SS_Front_samples2 = RunningMedian(49); long SS_Front_afstand2;
RunningMedian SS_Front_samples3 = RunningMedian(49); long SS_Front_afstand3;   

RunningMedian SS_Front_samples1_Down = RunningMedian(49); long SS_Front_afstand1_Down;
RunningMedian SS_Front_samples2_Down = RunningMedian(49); long SS_Front_afstand2_Down;
RunningMedian SS_Front_samples3_Down = RunningMedian(49); long SS_Front_afstand3_Down;

Servo Servo_Around_Y;
Servo Servo_Around_X;

//Sensor links
RunningMedian SS_Left_samples = RunningMedian(49); long SS_Left_afstand;
//Sensor right
RunningMedian SS_Right_samples = RunningMedian(49); long SS_Right_afstand;
//Sensor back
RunningMedian SS_Back_samples = RunningMedian(49); long SS_Back_afstand;

//BNO055
const int BNO055_SAMPLERATE_DELAY_MS =100;
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);
RunningMedian lijstx = RunningMedian(10); RunningMedian lijsty = RunningMedian(10); RunningMedian lijstz = RunningMedian(10);

bool Climbing = false;

//################## Expander
Adafruit_MCP23008 mcp;
