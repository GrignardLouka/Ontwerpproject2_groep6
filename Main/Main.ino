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
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#include "Variables.h"
#include "Basic_Movemment.h"
#include "Mode2_State1_Scanning.h"
#include "Mode1_Joystick.h"


//###########################################################    Pins    ##############################################################
//Battery
const int BATTERY_LEVEL_PIN = 2; 
const int BUZZER_BATTERY_LEVEL = 15;

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
  if(Battery_Charge < 2000){
    Mode = "Battery not connected";
  }
  else if(Battery_Charge < Lowest_Battery_Charge){
    Mode = "Battery low";
  }
  else if(mcp.digitalRead(JOYSTICK_CONTROL) == 1){
    Mode = "Joystick mode";
  }
  else{
    Mode = "Automatic mode";
  }
}

void buzzer_Switchmode(){
  while(Battery_Charge < 2000){
    tone(BUZZER_BATTERY_LEVEL, 2000);
    delay(1000);
    noTone(BUZZER_BATTERY_LEVEL);
    delay(1000);

  Battery_Charge = analogRead(BATTERY_LEVEL_PIN);

  }
  
}

//###########################################################    Setup    #############################################################
void setup() {
  //Start serial
  Serial.begin (115200);

  //Start MCP23008
  mcp.begin();
  bno.begin();
  delay(1000);
  bno.setExtCrystalUse(true);

  //Battery check
  pinMode(BATTERY_LEVEL_PIN, INPUT);
  pinMode(BUZZER_BATTERY_LEVEL, OUTPUT);

  //Basic Movement
  pinMode_Basic_Movement();

  //Joystick
  pinMode_Joystick();

  //Scanning
  pinMode_Scanning();
  
}

//############################################################    Loop    #############################################################
void loop(){


  //initialize();

  if(Mode == "Battery not connected")   { Serial.println("Battery not connected");
                                          //noTone(BUZZER_BATTERY_LEVEL);
                                          //buzzer_Switchmode();
                                        }
  else if(Mode == "Battery low")        { 
                                          Serial.println("Battery low, please recharge.");
                                          //tone(BUZZER_BATTERY_LEVEL, 2000);
                                          stop();
                                        }

  else if(Mode == "Joystick mode")      {
                                          noTone(BUZZER_BATTERY_LEVEL);
                                          Serial.println("Joystick mode");
                                          joystick_Position();
                                          move_Joystick();
                                        }

  else if(Mode == "Automatic mode")     {
                                          noTone(BUZZER_BATTERY_LEVEL);
                                          if(State == "Scanning")        { 
                                                                            Serial.println("Scanning");
                                                                            scan();                                                                           
                                                                            State = "Calculate";                                                                   
                                                                         }
                                          else if(State == "Calculate")  {
                                                                            
                                                                            State = "Moving";
                                                                          }
                                          else if(State == "Moving")      { 
                                                                            move();
                                                                            State = "Scanning";
                                                                          }
                                          else if(State == "Collision")   {      
                                                                              //...
                                                                              State = "Scanning";
                                                                            }
  }

  Loop_Counter++;

}
