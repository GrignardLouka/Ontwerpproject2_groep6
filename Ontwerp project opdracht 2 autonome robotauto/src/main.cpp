/* 
autonome robotauto
Groep 6
El Madani 	Ilyas
Grignard	Louka
Sahan	Baris
*/
//######################################     	Change log    ##############################################
/* 
08/02/2021     HC-SRO4 sensor(Measure + print in cm)      

09/02/2021      Joystick
                Wheel translation and rotation functions
                Movement(translation)

10/02/2021      
                Movement(Rotation)
*/

//##########################################   Notes   ###################################################
/*
RunningMedian(list) is uneven so the median is a true measurement.




*/
//#######################################     Libraries    ################################################
#include <Arduino.h>
#include <RunningMedian.h>
#include <ESP32Servo.h>

//#######################################  Constant Values  ############################################### 
/*
JOYSTICK_Y_CENTER = 115;
JOYSTICK_X_CENTER = 109;
Lowest allowed battery voltage is 7V 

*/
//#####################################    Variables   ####################################################
String Mode;
/*
0 = Battery empty
1 = Joystick
2 = Automatic 

*/
String State = "Scanning";
/*
1 = Scan
2 = Caclculate
3 = Moving
4 = Collision 
*/

int Loop_Counter;

int Speed;      // Get calculated based on incline with bmo sensor
                // tijd is based on the distance to the driving direction
//##################### 2 HC-SR04 sensoren
const int SS1_TRIGPIN = 18;  
const int SS2_TRIGPIN = 19;
const int SS3_TRIGPIN;
const int SS4_TRIGPIN;  

const int SS1_ECHOPIN = 16; 
const int SS2_ECHOPIN = 2;
const int SS3_ECHOPIN;
const int SS4_ECHOPIN; 




long SS1_afstand1; long SS1_afstand2; long SS1_afstand3;

long SS1_afstand1_Down; long SS1_afstand2_Down; long SS1_afstand3_Down;

long SS2_afstand;

//5 spots(left, left-middle, middle, right-middle, right)
RunningMedian SS1_samples1 = RunningMedian(49); RunningMedian SS1_samples2 =RunningMedian(49);
RunningMedian SS1_samples3 = RunningMedian(49); RunningMedian SS1_samples4 = RunningMedian(49);
RunningMedian SS1_samples5 =RunningMedian(49);    

RunningMedian SS1_samples1_Down = RunningMedian(49); RunningMedian SS1_samples3_Down = RunningMedian(49); RunningMedian SS1_samples5_Down = RunningMedian(49);

RunningMedian SS2_samples = RunningMedian(49);

//####################### Joystick
//Pin
const int JOYSTICKPIN_X = 35;         
const int JOYSTICKPIN_Y =34;
const int JOYSTICKPIN_BUTTON = 32;
const int JOYSTICK_CONTROL = 5;
//Values
double Joystick_X;                    
double Joystick_Y;
int Joystick_Button; 
int Rotating = 0;
int Joystick_Control;
// List of last 20 values
RunningMedian Joystick_X_samples = RunningMedian(19);    
RunningMedian Joystick_Y_samples = RunningMedian(19);


//##################### Motor
//Pin
const int MOTORALWPIN1 = 27; 
const int MOTORALWPIN2 = 26; 
const int MOTORARWPIN1 = 21; 
const int MOTORARWPIN2 = 19; 
const int MOTORVRWPIN1 = 23; 
const int MOTORVRWPIN2 = 22;
const int MOTORVLWPIN1 = 25; 
const int MOTORVLWPIN2 = 33; 

//###################### Servo
const int SERVO_AROUND_Y_PIN = 14;
const int SERVO_AROUND_X_PIN = 12;

Servo Servo_Around_Y;
Servo Servo_Around_X;

//###################### Battery check
const int BATTERY_LEVEL_PIN = 13;     
RunningMedian Battery_Samples = RunningMedian(49);
int Battery_Charge;

//######################################     Functies     ##########################################################
//############################### Base functions
void Stop()
{
  ledcWrite(0,0);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,0);
  ledcWrite(4,0);
  ledcWrite(5,0);
  ledcWrite(6,0);
  ledcWrite(7,0);
  Serial.println("Stop");
}
void Forward(int snelheid, int tijd)
{
  ledcWrite(0,snelheid);
  ledcWrite(1,0);
  ledcWrite(2,snelheid);
  ledcWrite(3,0);
  ledcWrite(4,snelheid);
  ledcWrite(5,0);
  ledcWrite(6,snelheid);
  ledcWrite(7,0);

  if(tijd != 0){
    delay(tijd);
    Stop();
  }

  Serial.println("Forward");
}
void Backward(int snelheid, int tijd)
{
  ledcWrite(0,0);
  ledcWrite(1,snelheid);
  ledcWrite(2,0);
  ledcWrite(3,snelheid);
  ledcWrite(4,0);
  ledcWrite(5,snelheid);
  ledcWrite(6,0);
  ledcWrite(7,snelheid);

  if(tijd != 0){
    delay(tijd);
    Stop();
  }
  Serial.println("Backwards");

 
  
}
void Right(int snelheid, int tijd)
{
  ledcWrite(0,0);
  ledcWrite(1,snelheid);
  ledcWrite(2,snelheid);
  ledcWrite(3,0);
  ledcWrite(4,0);
  ledcWrite(5,snelheid);
  ledcWrite(6,snelheid);
  ledcWrite(7,0);

  if(tijd != 0){
    delay(tijd);
    Stop();
  }

  Serial.println("Right");
}
void Left(int snelheid, int tijd)
{
  ledcWrite(0,snelheid);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,snelheid);
  ledcWrite(4,snelheid);
  ledcWrite(5,0);
  ledcWrite(6,0);
  ledcWrite(7,snelheid);

  if(tijd != 0){
    delay(tijd);
    Stop();
  }

  Serial.println("Left");
}
void Rotate_Left(int snelheid, int tijd){
  ledcWrite(0,0);
  ledcWrite(1,snelheid);
  ledcWrite(2,snelheid);
  ledcWrite(3,0);
  ledcWrite(4,snelheid);
  ledcWrite(5,0);
  ledcWrite(6,0);
  ledcWrite(7,snelheid);

  if(tijd != 0){
    delay(tijd);
    Stop();
  }

  Serial.println("Rotate Left");
}
void Rotate_Right(int snelheid, int tijd){
  ledcWrite(0,snelheid);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,snelheid);
  ledcWrite(4,0);
  ledcWrite(5,snelheid);
  ledcWrite(6,snelheid);
  ledcWrite(7,0);

  if(tijd != 0){
    delay(tijd);
    Stop();
  }

  Serial.println("Rotate Right");
}

//############################## Initialize
void Initialize(){
  // Check Battery
  Battery_Samples.add(analogRead(BATTERY_LEVEL_PIN));
  Battery_Charge = Battery_Samples.getMedian();
  if(Loop_Counter % 100 == 0){Serial.println(Battery_Charge);}
  
  if(Battery_Charge == 0){
    Mode = "Battery not connected";
  }
  if(Battery_Charge < 1450){
    Mode = "Battery low";
  }
  else if(Battery_Charge == 1){
    Mode = "Joystick mode";
  }
  else{
    Mode = "Automatic mode";
  }
}

//############################### MODE 2 (Joystick)
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
        Forward((Joystick_Y - 182) * 2); //* 3.45
      }
      else if(Joystick_Y < 73){
        Backward((73 - Joystick_Y) * 2); // 3.45
      }
      else{
        Stop();
      }
    }
    else if(Joystick_X < 70){
      Left((70 - Joystick_X) * 2); // 3.6
    }
    else if(Joystick_X > 185){
      Right((Joystick_X - 185) * 2); // 3.6
    }
    
  }
  else{ // if button = 1 = HIGH
      if(Joystick_X > 185){
          Rotate_Right((Joystick_X - 185) * 2); // * 3.6
          Rotating = 1;
        }
        else if(Joystick_X < 70){
          Rotate_Left((70 - Joystick_X) * 2); // *3.6
          Rotating = 1;
        }
        else{
          Stop();
        }
    }
  
}

//############################### MODE 3 (Automatic)
//############### STATE 1 (scan)
//HC-SOR4 sensor
long SS_Meting(const int TRIGGER, const int ECHO, RunningMedian Lijst){
  long afstand;
  long duration;

  digitalWrite(TRIGGER, LOW);              //set to LOW first to ensure a clean signal
  delayMicroseconds(5);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);

  duration = pulseIn(ECHO, HIGH) / 2;    // Measure time needed for signal to return(in microseconds)(/2 signal travels  back and forth)
  lijst. add(duration / 29.1);            // Convert to cm and add to list
  afstand = SS.getMedian();              // Get median of the list(for a more accurate measurement)
  
  return(afstand);
  
}
// Servo
void Attach_Servos(){
  Servo_Around_Y.setPeriodHertz(50);    // standard 50 hz servo
	Servo_Around_Y.attach(SERVO_AROUND_Y_PIN, 500, 2500);
  Servo_Around_X.setPeriodHertz(50);    // standard 50 hz servo
	Servo_Around_X.attach(SERVO_AROUND_X_PIN, 500, 2500);
}
void Detach_Servos(){
  Servo_Around_Y.detach();
  Servo_Around_X.detach();
}
void Scan(){

  //Attach timers to servo
  Attach_Servos();

  //Bring servo to start position
  Servo_Around_Y.write(0);
  Servo_Around_X.write(100);
  Serial.println("Turning to first position");

  //Measure front
  // Pos 1  (rechts)
  SS1_afstand1 = SS_Meting(SS1_TRIGPIN, SS1_ECHOPIN,SS1_samples1);

  // Pos 2
  Servo_Around_Y.write(70);
  Serial.println("Turning to third position");
  delay(200);
  SS1_afstand2 = SS_Meting(SS1_TRIGPIN, SS1_ECHOPIN,SS1_samples2);

  // Pos 3
  Servo_Around_Y.write(160);
  Serial.println("Turning to fifth position");
  delay(200);
  SS1_afstand3 = SS_Meting(SS1_TRIGPIN, SS1_ECHOPIN,SS1_samples3);
  //pos 7
  Servo_Around_X.write(15);
  Serial.println("Turning to the seventh position");
  delay(200);
  SS1_afstand3_Down = SS_Meting(SS1_TRIGPIN, SS1_ECHOPIN,SS1_samples3_Down);

  //pos 8
  Servo_Around_Y.write(70);
  Serial.println("Turning to the eight position");
  delay(200);
  SS1_afstand2_Down = SS_Meting(SS1_TRIGPIN, SS1_ECHOPIN,SS1_samples2_Down);
  //pos 9
  Servo_Around_Y.write(0);
  Serial.println("Turning to the ninth position");
  delay(200);
  SS1_afstand1_Down = SS_Meting(SS1_TRIGPIN, SS1_ECHOPIN,SS1_samples1_Down);
  Servo_Around_X.write(0);
  Serial.println("Turning to the first position");
  delay(200);

  Detach_Servos();
}

//################ STATE 2 (Calculate)
// Movement
void Calculate_Movement(){
  //Put the logic here

  State = "Moving";
}





void Move_autmatic(){
  //Put the movement logic in here
  Serial.println("Not yet implemented");


  State = "Scanning";
}





 //####################################    SETUP    ##################################################
void setup() {

  //Start
  Serial.begin (115200);

  //Battery check
  pinMode(BATTERY_LEVEL_PIN, INPUT);

  // 2 HC-SRO4 sensoren
  pinMode(SS1_TRIGPIN, OUTPUT);
  pinMode(SS2_TRIGPIN, OUTPUT);
  pinMode(SS3_TRIGPIN, OUTPUT);
  pinMode(SS4_TRIGPIN, OUTPUT);
  
  pinMode(SS1_ECHOPIN, INPUT);
  pinMode(SS2_ECHOPIN, INPUT);
  pinMode(SS3_ECHOPIN, INPUT);
  pinMode(SS4_ECHOPIN, INPUT);

  // Joystick
  pinMode(JOYSTICKPIN_X, INPUT);
  pinMode(Joystick_Y, INPUT);
  pinMode(JOYSTICKPIN_BUTTON, INPUT_PULLUP);
  pinMode(JOYSTICK_CONTROL, INPUT_PULLDOWN);

  // Motor
  pinMode(MOTORALWPIN1,OUTPUT);       // Set pin to output
  ledcSetup(0,5000,8);                // Create ledc 
  ledcAttachPin(MOTORALWPIN1,0);      // Asign pin to ledc

  pinMode(MOTORALWPIN2,OUTPUT);
  ledcSetup(1,5000,8);
  ledcAttachPin(MOTORALWPIN2,1);

  pinMode(MOTORARWPIN1,OUTPUT);
  ledcSetup(2,5000,8);
  ledcAttachPin(MOTORARWPIN1,2);

  pinMode(MOTORARWPIN2,OUTPUT);
  ledcSetup(3,5000,8);
  ledcAttachPin(MOTORARWPIN2,3);

  pinMode(MOTORVRWPIN1,OUTPUT);
  ledcSetup(4,5000,8);
  ledcAttachPin(MOTORVRWPIN1,4);

  pinMode(MOTORVRWPIN2,OUTPUT);
  ledcSetup(5,5000,8);
  ledcAttachPin(MOTORVRWPIN2,5);

  pinMode(MOTORVLWPIN1,OUTPUT);
  ledcSetup(6,5000,8);
  ledcAttachPin(MOTORVLWPIN1,6);

  pinMode(MOTORVLWPIN2,OUTPUT);
  ledcSetup(7,5000,8);
  ledcAttachPin(MOTORVLWPIN2,7); 

  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

  Servo_Around_Y.setPeriodHertz(50);    // standard 50 hz servo
	Servo_Around_Y.attach(SERVO_AROUND_Y_PIN, 500, 2500);
  Servo_Around_X.setPeriodHertz(50);
  Servo_Around_X.attach(SERVO_AROUND_X_PIN, 500, 2500);

}

//#########################################     LOOP     ###############################################
void loop(){

  //Initialize();





  //Check mode
  if(Mode == "Battery not connected"){Serial.println("Battery not connected");}
  else if(Mode == "Battery low"){Serial.println("Battery low, please recharge.");}
  else if(Mode == "Joystick mode"){
    Joystick_Position();
    Move_Joystick();
  }
  else if(Mode == "Automatic mode"){
    if(State == "Scanning"){ 
      Scan();
      State = "Calculate";
      
    }
    else if(State == "Calculate"){
      //...
      State = "Moving";
    }
    else if(State == "Moving"){ 
      //...
      State = "Scanning";
    }
    else if(State == "Collision"){      
      //...
      State = "Scanning";
    }
  }
  


  
  delay(10);
  
  Loop_Counter++;     //Currently not in use

}
