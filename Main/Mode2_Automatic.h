#include <Wire.h>
#include <Adafruit_MCP23008.h>
#include <RunningMedian.h>
#include <ESP32Servo.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
//#####################################################################    Pin    ############################################################################
//################################# Scanning
const int SS_FRONT_TRIGPIN = 1;  
const int SS_LEFT_TRIGPIN = 2;
const int SS_RIGHT_TRIGPIN = 0;
const int SS_BACK_TRIGPIN = 3;  

const int SS_FRONT_ECHOPIN = 39; 
const int SS_LEFT_ECHOPIN = 36;
const int SS_RIGHT_ECHOPIN = 16;
const int SS_BACK_ECHOPIN = 17; 

const int SERVO_AROUND_Y_PIN = 2;
const int SERVO_AROUND_X_PIN = 15;

//##################################################################    Variable    ############################################################################
Adafruit_MCP23008 mcp;
int Movement_State;
extern const int DISABLE_PIN;

//Sensor op servo
RunningMedian SS_Front_samples1 = RunningMedian(80); long SS_Front_afstand1;
RunningMedian SS_Front_samples2 = RunningMedian(80); long SS_Front_afstand2;
RunningMedian SS_Front_samples3 = RunningMedian(80); long SS_Front_afstand3;   

RunningMedian SS_Front_samples1_Down = RunningMedian(80); long SS_Front_afstand1_Down;
RunningMedian SS_Front_samples2_Down = RunningMedian(80); long SS_Front_afstand2_Down;
RunningMedian SS_Front_samples3_Down = RunningMedian(80); long SS_Front_afstand3_Down;

Servo Servo_Around_Y;
Servo Servo_Around_X;
//Sensor left
RunningMedian SS_Left_samples = RunningMedian(80); long SS_Left_afstand;
//Sensor right
RunningMedian SS_Right_samples = RunningMedian(1); long SS_Right_afstand;
//Sensor back
RunningMedian SS_Back_samples = RunningMedian(80);  long SS_Back_afstand;

//BNO055 
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);

RunningMedian lijstx = RunningMedian(10); RunningMedian lijsty = RunningMedian(10); RunningMedian lijstz = RunningMedian(10);

bool Climbing = false;
bool Descending = false;

RunningMedian Memory = RunningMedian(20);

//###################################################################    PinMode    ############################################################################
void pinMode_Scanning(){
  //Sensor
  mcp.pinMode(SS_FRONT_TRIGPIN, OUTPUT);
  mcp.pinMode(SS_LEFT_TRIGPIN, OUTPUT);
  mcp.pinMode(SS_RIGHT_TRIGPIN, OUTPUT);
  mcp.pinMode(SS_BACK_TRIGPIN, OUTPUT);

  pinMode(SS_FRONT_ECHOPIN, INPUT);
  pinMode(SS_LEFT_ECHOPIN, INPUT);
  pinMode(SS_RIGHT_ECHOPIN, INPUT);
  pinMode(SS_BACK_ECHOPIN, INPUT);

  //Servo
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  Servo_Around_Y.setPeriodHertz(50);    
  Servo_Around_Y.attach(SERVO_AROUND_Y_PIN, 500, 2500);
  Servo_Around_X.setPeriodHertz(50);
  Servo_Around_X.attach(SERVO_AROUND_X_PIN, 500, 2500);
}

//#################################################################    Functions    ############################################################################
//################################# Scanning


long ss_Meting(const int TRIGGER, const int ECHO){
	long afstand;
	long duration;
	Serial.println("Measuring");
	mcp.digitalWrite(TRIGGER, LOW);              //set to LOW first to ensure a clean signal
	delayMicroseconds(5);
	mcp.digitalWrite(TRIGGER, HIGH);
	delayMicroseconds(10);
	mcp.digitalWrite(TRIGGER, LOW);

	//Measure time needed for the pulse to return
	duration = pulseIn(ECHO, HIGH) / 2;    
	//Return in cm
	return((duration / 29.1)); 
	
}

void attach_Servos(){
	Servo_Around_Y.setPeriodHertz(50);   
	Servo_Around_Y.attach(SERVO_AROUND_Y_PIN, 500, 2500);
	Servo_Around_X.setPeriodHertz(50);  
	Servo_Around_X.attach(SERVO_AROUND_X_PIN, 500, 2500);
}
void detach_Servos(){
	Servo_Around_Y.detach();
	Servo_Around_X.detach();
}

void bno_Meting(){
	//Take 10 measurements
	Serial.println("Measurering hill");
	for(int i = 0; i < 10; i++){
		// Get data from sensor
		sensors_event_t event;
		bno.getEvent(&event);
		// Read the wanted data and add it to a list
		lijstz.add((float)event.orientation.z);

		delay(BNO055_SAMPLERATE_DELAY_MS);
	}
	
	//Take the median of the list and check if the car is climbing
	if(lijstz.getMedian() > -160 || lijstz.getMedian() < -90){
		Climbing = true;
	}
	else if(lijstz.getMedian() < 160 || lijstz.getMedian() > 90){
		Descending = true;
	}
	else{	Climbing = false; Descending = false;	}
}

void scan(){

	//Check if we are on a hill
	bno_Meting();

	//Front
	Servo_Around_X.write(55);
	Servo_Around_Y.write(70);
	delay(500);
	for(int i = 0; i < 1; i++){SS_Front_samples2.add(ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN));}
	SS_Front_afstand2 = SS_Front_samples2.getMedian();

	//Right
	attach_Servos();
	Servo_Around_Y.write(0);
	Servo_Around_X.write(65);
	delay(500);
	for(int i = 0; i < 1; i++){SS_Front_samples1.add(ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN));}
	SS_Front_afstand1 = SS_Front_samples1.getMedian();

	//Left
	Servo_Around_Y.write(160);
	delay(500);
	for(int i = 0; i < 1; i++){SS_Front_samples3.add(ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN));}
	SS_Front_afstand3 = SS_Front_samples3.getMedian();

	if(Climbing || Descending){
		//Left Down
		Servo_Around_X.write(0);
		delay(500);
		for(int i = 0; i < 1; i++){SS_Front_samples1_Down.add(ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN));}
		SS_Front_afstand3_Down = SS_Front_samples1_Down.getMedian();

		// Front Down
		Servo_Around_Y.write(70);
		delay(500);
		for(int i = 0; i < 1; i++){SS_Front_samples2_Down.add(ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN));}
		SS_Front_afstand2_Down = SS_Front_samples2_Down.getMedian();

		// Right Down
		Servo_Around_Y.write(0);
		delay(500);
		for(int i = 0; i < 1; i++){SS_Front_samples1_Down.add(ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN));}
		SS_Front_afstand1_Down = SS_Front_samples1_Down.getMedian();

	}
	//Look to the  frontside
	Servo_Around_X.write(55);
	Servo_Around_Y.write(70);
	delay(500);
	
  detach_Servos();

	//Sensor left
	for(int i = 0; i < 1; i++){SS_Left_samples.add(ss_Meting(SS_LEFT_TRIGPIN, SS_LEFT_ECHOPIN));}
	SS_Left_afstand = SS_Left_samples.getMedian();
	//Sensor right
	for(int i = 0; i < 1; i++){SS_Right_samples.add(ss_Meting(SS_RIGHT_TRIGPIN, SS_RIGHT_ECHOPIN));}
	SS_Right_afstand = SS_Right_samples.getMedian();
	//Sensor back
	for(int i = 0; i < 1; i++){SS_Back_samples.add(ss_Meting(SS_BACK_TRIGPIN, SS_BACK_ECHOPIN));}
	SS_Back_afstand = SS_Back_samples.getMedian();
	SS_Back_afstand = ss_Meting(SS_BACK_TRIGPIN, SS_BACK_ECHOPIN);
	
}

//################################# Calculate
void calculate(){
//Use Memory.getElement(x) to get the x'th element
	
	if(Memory.getElement(1) == 1){ // if last move was forward
		if(SS_Front_afstand2 < 5 && SS_Front_afstand1 < 5 && SS_Front_afstand2 < 5){
			backward();
		}
	}

	// rotate parralel to wall
}
// als 2 SS rechts < 2 SS links zorg dat evenwijdig is met rechts
// als 2 SS rechts > 2 SS links zorg dat evenwijdig is met links
// als 1 SS > en 1 SS < dan 


//################################# Move
void move(long period = 50){ //check what an good average speed is 
    long duration;
    if(Climbing){period *= 2;}
	else if(Descending){period *= 0.5;}

	if(Mode == "Automatic"){
		while(SS_Front_afstand2 > 8){
    
			// Give power to H-bridges
			digitalWrite(DISABLE_PIN, LOW);
			delay(period);
			digitalWrite(DISABLE_PIN, HIGH); 
			delay(period);

			SS_Front_afstand2 = ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN);
		}
	}
	else{

	}
    
}




