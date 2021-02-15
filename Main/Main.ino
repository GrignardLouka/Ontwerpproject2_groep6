/* 
autonome robotauto
Groep 6
El Madani   Ilyas
Grignard  Louka
Sahan Baris
*/

//#########################################################    Change log   ###########################################################
/* 
08/02/2021     HC-SRO4 sensor(Measure + print in cm)      

09/02/2021      Joystick
                Wheel translation and rotation functions
                Movement(translation)

10/02/2021      Movement(Rotation)

11/02/2021      Servo + sensoren

12/02/2021      MCP23008
                Battery charge check
*/

//#########################################################    Libraries    ###########################################################
#include <Wire.h>
#include <Adafruit_MCP23008.h>
#include <RunningMedian.h>
#include <ESP32Servo.h>

#include "Variables.h"
#include "Basic_Movemment.h"
#include "Mode2_State1_Scanning.h"
#include "Mode1_Joystick.h"

//######################################################    Constant Values    #######################################################
/*


Lowest allowed battery voltage is 7V 
*/

//###########################################################    Pins    ##############################################################
//Battery
const int BATTERY_LEVEL_PIN = 2; 
const int BUZZER_BATTERY_LEVEL = 6;

//#########################################################    Variables    ###########################################################
//Mode
String Mode;
/*
0 = Battery empty
1 = Joystick
2 = Automatic 
*/

//State
String State = "Scanning";
/*
1 = Scan
2 = Caclculate
3 = Moving
4 = Collision 
*/

//Battery
RunningMedian Battery_Samples = RunningMedian(49); 
int Battery_Charge;
int Lowest_Battery_Charge = 2900;

//Create new I/O Expander


int Loop_Counter;
int Speed;      // Get calculated based on incline with bmo sensor
                // tijd is based on the distance to the driving direction

//#########################################################    Functions    ###########################################################
void initialize(){
  // Check Battery
  Battery_Samples.add(analogRead(BATTERY_LEVEL_PIN)); // Read battery charge and add to list
  Battery_Charge = Battery_Samples.getMedian();       // Get median of battery charge list
  if(Loop_Counter % 100 == 0){Serial.println(Battery_Charge);} //Print battery charge every 100 loops so it doesn't overrun the console

  //Check which of the 4 modes the robot is in
  if(Battery_Charge == 0){
    Mode = "Battery not connected";
  }
  else if(Battery_Charge < Lowest_Battery_Charge){
    Mode = "Battery low";
  }
  else if(!mcp.digitalRead(JOYSTICK_CONTROL) == 1){
    Mode = "Joystick mode";
  }
  else{
    Mode = "Automatic mode";
  }
  Serial.println(!mcp.digitalRead(JOYSTICK_CONTROL));
}

void calculate_Movement(){
  //Put the logic here

  State = "Moving";
}

void move_autmatic(){
  //Put the movement logic in here
  Serial.println("Not yet implemented");


  State = "Scanning";
}


//###########################################################    Setup    #############################################################
void setup() {
  //Start serial
  Serial.begin (115200);

  //Start MCP23008
  mcp.begin();

  //Battery check
  pinMode(BATTERY_LEVEL_PIN, INPUT);
  mcp.pinMode(BUZZER_BATTERY_LEVEL, OUTPUT);

  //Basic Movement
  pinMode_Basic_Movement();

  //Joystick
  pinMode_Joystick();

  //Scanning
  pinMode_Scanning();
  
}

//############################################################    Loop    #############################################################
void loop(){

  Initialize();

  //Check mode
  
  if(Mode == "Battery not connected")   { Serial.println("Battery not connected");}

  else if(Mode == "Battery low")        { 
                                          Serial.println("Battery low, please recharge.");
                                          mcp.digitalWrite(BUZZER_BATTERY_LEVEL, HIGH);
                                        }

  else if(Mode == "Joystick mode")      {
                                          Serial.println("Joystick mode");
                                          joystick_Position();
                                          move_Joystick();
                                        }

  else if(Mode == "Automatic mode")     {
                                          if(State == "Scanning")        { 
                                                                            //Serial.println("Scanning");
                                                                            //scan();                                                                           
                                                                            State = "Calculate";                                                                   
                                                                         }
                                          else if(State == "Calculate")  {
                                                                            //...
                                                                            State = "Moving";
                                                                          }
                                          else if(State == "Moving")      { 
                                                                            //...
                                                                            State = "Scanning";
                                                                          }
                                          else if(State == "Collision")   {      
                                                                              //...
                                                                              State = "Scanning";
                                                                            }
  }
  
  delay(10);
  Loop_Counter++;

}
