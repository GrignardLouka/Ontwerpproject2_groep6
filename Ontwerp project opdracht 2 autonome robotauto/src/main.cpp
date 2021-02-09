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

09/02/2021     Joystick
               Wheel translation and rotation functions
               Movement(translation)

10/02/2021      
*/

//#######################################     Libraries    ################################################
#include <Arduino.h>
#include <RunningMedian.h>

//#####################################    Variables   ###################################################
//##################### 2 HC-SR04 sensoren
const int SS1_TRIGPIN = 17;  
const int SS2_TRIGPIN = 4;  

const int SS1_ECHOPIN = 16; 
const int SS2_ECHOPIN = 2; 

long SS1_afstand;
long SS2_afstand;

RunningMedian SS1_samples = RunningMedian(50);
RunningMedian SS2_samples = RunningMedian(50);

long duration;

//####################### Joystick
//Pin
const int JOYSTICKPIN_X = 35;         
const int JOYSTICKPIN_Y =34;
const int JOYSTICKPIN_BUTTON = 32;
//Values
double Joystick_X;                    
double Joystick_Y;
int Joystick_Button; 
// List of last 20 values
RunningMedian Joystick_X_samples = RunningMedian(20);    
RunningMedian Joystick_Y_samples = RunningMedian(20);
// Cte values
// const int JOYSTICK_Y_CENTER = 115;
// const int JOYSTICK_X_CENTER = 109;

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

//######################################     Functies     ##########################################################
//############################### HC-SOR4 sensor
void Median_SS(){
  digitalWrite(SS1_TRIGPIN, LOW);              //set to LOW first to ensure a clean signal
  delayMicroseconds(5);
  digitalWrite(SS1_TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SS1_TRIGPIN, LOW);
  duration = pulseIn(SS1_ECHOPIN, HIGH) / 2;    // Mesure time needed for signal to return(in microseconds)(/2 heen en terug)
  SS1_samples.add((duration) / 29.1);           //Convert to cm and add to array(/29,1 om naar cm om te zetten)
  SS1_afstand = SS1_samples.getMedian();        // Get Median distance

  delay(5);                                     // wait 5 ms to prevent to much noise from other sensor

  digitalWrite(SS2_TRIGPIN, LOW);
  delayMicroseconds(5);
  digitalWrite(SS2_TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SS2_TRIGPIN, LOW);
  duration = pulseIn(SS2_ECHOPIN, HIGH) / 2;    
  SS2_samples.add((duration) / 29.1);
  SS2_afstand = SS2_samples.getMedian();

  delay(5);
}

//############################### Joystick
void Joystick_Position(){
  
  Joystick_X_samples.add(map(analogRead(JOYSTICKPIN_X),0,4095,0,255));
  Joystick_X = Joystick_X_samples.getMedian();
  Joystick_Y_samples.add(map(analogRead(JOYSTICKPIN_Y),0,4095,0,255));
  Joystick_Y = Joystick_Y_samples.getMedian();

  Joystick_Button = !digitalRead(JOYSTICKPIN_BUTTON);
}

//############################### Movement
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
void Forward(int snelheid)
{
  ledcWrite(0,snelheid);
  ledcWrite(1,0);
  ledcWrite(2,snelheid);
  ledcWrite(3,0);
  ledcWrite(4,snelheid);
  ledcWrite(5,0);
  ledcWrite(6,snelheid);
  ledcWrite(7,0);
  Serial.println("Forward");
}
void Backward(int snelheid)
{
  ledcWrite(0,0);
  ledcWrite(1,snelheid);
  ledcWrite(2,0);
  ledcWrite(3,snelheid);
  ledcWrite(4,0);
  ledcWrite(5,snelheid);
  ledcWrite(6,0);
  ledcWrite(7,snelheid);
  Serial.println("Backwards");
 
  
}
void Right(int snelheid)
{
  ledcWrite(0,0);
  ledcWrite(1,snelheid);
  ledcWrite(2,snelheid);
  ledcWrite(3,0);
  ledcWrite(4,0);
  ledcWrite(5,snelheid);
  ledcWrite(6,snelheid);
  ledcWrite(7,0);
  Serial.println("Right");
}
void Left(int snelheid)
{
  ledcWrite(0,snelheid);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,snelheid);
  ledcWrite(4,snelheid);
  ledcWrite(5,0);
  ledcWrite(6,0);
  ledcWrite(7,snelheid);
  Serial.println("Left");
}
void Rotate_Left(int snelheid){
  ledcWrite(0,0);
  ledcWrite(1,snelheid);
  ledcWrite(2,snelheid);
  ledcWrite(3,0);
  ledcWrite(4,snelheid);
  ledcWrite(5,0);
  ledcWrite(6,0);
  ledcWrite(7,snelheid);
  Serial.println("Rotate Left");
}
void Rotate_Right(int snelheid){
  ledcWrite(0,snelheid);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,snelheid);
  ledcWrite(4,0);
  ledcWrite(5,snelheid);
  ledcWrite(6,snelheid);
  ledcWrite(7,0);
  Serial.println("Rotate Right");
}

void Move(){

  if(Joystick_Button == 0){
    if(Joystick_X < 185 && Joystick_X > 70){
      if(Joystick_Y > 182){
        Forward((Joystick_Y - 182) * 3.45);
      }
      else if(Joystick_Y < 73){
        Backward((73 - Joystick_Y) * 3.45);
      }
      else{
        Stop();
      }
    }
    else if(Joystick_X < 70){
      Left((70 - Joystick_X)  * 3.6);
    }
    else if(Joystick_X > 185){
      Right((Joystick_X - 185) * 3.6);
    }
  }
  else{ // if button = 1 = HIGH
    if(Joystick_X > 185){
        Rotate_Right((Joystick_X - 185) * 3.6);
      }
      else if(Joystick_X < 70){
        Rotate_Left((70 - Joystick_X) * 3.6);
      }
      else{
        Stop();
      }
  }
}

 //####################################    SETUP    ##################################################
void setup() {
  //Start
  Serial.begin (115200);

  // 2 HC-SRO4 sensoren
  pinMode(SS1_TRIGPIN, OUTPUT);
  pinMode(SS1_ECHOPIN, INPUT);
  pinMode(SS2_TRIGPIN, OUTPUT);
  pinMode(SS2_ECHOPIN, INPUT);

  // Joystick
  pinMode(JOYSTICKPIN_X, INPUT);
  pinMode(Joystick_Y, INPUT);
  pinMode(JOYSTICKPIN_BUTTON, INPUT_PULLUP);

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
}

//#########################################     LOOP     ###############################################
void loop(){

//########################## Joystick
Joystick_Position();
//########################## Movement
Move();

/*
//######################### HC_SRO4 sensor
  Median_SS();

  Serial.print("De eerste sensor meet: ");
  Serial.print(SS1_afstand);
  Serial.println(" cm");

 Serial.print("De tweede sensor meet: ");
 Serial.print(SS2_afstand);
 Serial.println(" cm");
*/
}
