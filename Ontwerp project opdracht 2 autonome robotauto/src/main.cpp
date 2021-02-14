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

10/02/2021      Movement(Rotation)

11/02/2021      
*/

//#######################################     Libraries    ################################################
/*
    Arduino.h
    RunningMedian.h
    ESP32Servo.h
    Wire.h
    BluetoothSerial.h
*/
#include <Wire.h>
#include <BluetoothSerial.h>

//######################################     Header files    #############################################
#include "Mode1_Joystick.h"
#include "Mode2_State1_Scanning.h"
#include <Base_Variables.h>

//#######################################  Constant Values  ############################################### 
/*
JOYSTICK_Y_CENTER = 115;
JOYSTICK_X_CENTER = 109;
Lowest allowed battery voltage is 7V 

*/
//#######################################   Variables   ####################################################
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



//Bluetooth
BluetoothSerial SerialBT;


//###################### Battery check
const int BATTERY_LEVEL_PIN = 13;     
RunningMedian Battery_Samples = RunningMedian(49);
int Battery_Charge;

//######################################     Functies     ##########################################################
//############################### Base functions

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
  else if(Joystick_Control == 1){
    Mode = "Joystick mode";
  }
  else{
    Mode = "Automatic mode";
  }
}

//############################### MODE 2 (Joystick)

//############################### MODE 3 (Automatic)



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

  //Bluetooth
  SerialBT.begin("ESP32test");   

  //Battery check
  pinMode(BATTERY_LEVEL_PIN, INPUT);

  PinMode_Scanning();
  PinMode_Basic_Movement();
  PinMode_Joystick();

  

}

//#########################################     LOOP     ###############################################
void loop(){

  Initialize();

  SerialBT.println("Test u mama bluetooth");
  //Check mode
  
  if(Mode == "Battery not connected")   {SerialBT.println("Battery not connected");}
  else if(Mode == "Battery low")        {SerialBT.println("Battery low, please recharge.");}
  else if(Mode == "Joystick mode")      {
                                          Joystick_Position();
                                          Move_Joystick();
                                        }
  else if(Mode == "Automatic mode")     {
                                          if(State == "Scanning")        { 
                                                                            Scan();
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
