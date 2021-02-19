//#####################################################################    Pin    ############################################################################
//################################# Scanning
const int SS_FRONT_TRIGPIN = 3;  
const int SS_LEFT_TRIGPIN = 2;
const int SS_RIGHT_TRIGPIN = 0;
const int SS_BACK_TRIGPIN = 1;  

const int SS_FRONT_ECHOPIN = 39; 
const int SS_LEFT_ECHOPIN = 36;
const int SS_RIGHT_ECHOPIN = 16;
const int SS_BACK_ECHOPIN = 17; 

const int SERVO_AROUND_Y_PIN = 2;
const int SERVO_AROUND_X_PIN = 15;

//##################################################################    Variable    ############################################################################
Adafruit_MCP23008 mcp;
extern const int DISABLE_PIN;

//Sensor op servo
RunningMedian SS_FrontRight_samples = RunningMedian(80);	float SS_FrontRight_afstand; 	//int dr = SS_Front_afstand1;
RunningMedian SS_Front_samples = RunningMedian(80); 		float SS_Front_afstand;		//	int dv = SS_Front_afstand2;
RunningMedian SS_FrontLeft_samples = RunningMedian(80); 	float SS_FrontLeft_afstand;   	//int dl = SS_Front_afstand3;

RunningMedian SS_FrontRight_samples_Down = RunningMedian(80); 	float SS_FrontRight_afstand_Down;//	int drn = SS_Front_afstand1_Down;
RunningMedian SS_Front_samples_Down = RunningMedian(80); 		float SS_Front_afstand_Down;//	int dvn = SS_Front_afstand2_Down;
RunningMedian SS_FrontLeft_samples_Down = RunningMedian(80); 	float SS_FrontLeft_afstand_Down;//	int dln = SS_Front_afstand3_Down;

Servo Servo_Around_Y;
Servo Servo_Around_X;
//Sensor left
RunningMedian SS_Left_samples = RunningMedian(80); float SS_Left_afstand;
//Sensor right
RunningMedian SS_Right_samples = RunningMedian(1); float SS_Right_afstand;
//Sensor back
RunningMedian SS_Back_samples = RunningMedian(80);  float SS_Back_afstand;

//BNO055 
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);

RunningMedian lijstx = RunningMedian(10); RunningMedian lijsty = RunningMedian(10); RunningMedian lijstz = RunningMedian(10);

bool Climbing = false;
bool Descending = false;


//Automatic
RunningMedian Memory = RunningMedian(20);

extern String Mode;
            /*
            0 = Battery empty
            1 = Joystick
            2 = Automatic 
            */

const int speed = 200;

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

void servo_move(Servo servo, const int PIN, int angle){	//AYA = Around Y Axis
	servo.attach(PIN, 500, 2500);
	delay(200);
	servo.write(angle);
	delay(500);
	servo.detach();
	delay(200);
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
		Serial.println((float)event.orientation.z);

		delay(BNO055_SAMPLERATE_DELAY_MS);
	}
	
	//Take the median of the list and check if the car is climbing
	if(lijstz.getMedian() < 160 && lijstz.getMedian() > 90){
		Climbing = true;
	}
	else if(lijstz.getMedian() > -160 && lijstz.getMedian() < -90){
		Descending = true;
	}
	else{	Climbing = false; Descending = false;	}

	Serial.print(Climbing);
}

void scan_servo(){
	//Check if we are on a hill
	//bno_Meting();

	//Make sure the servo is oriëntated right
	servo_move(Servo_Around_X, SERVO_AROUND_X_PIN, 55);
	servo_move(Servo_Around_Y, SERVO_AROUND_Y_PIN, 70);

	//Front
	for(int i = 0; i < 1; i++){SS_Front_samples.add(ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN));}
	SS_Front_afstand = SS_Front_samples.getMedian();
	Serial.print("Front: ");Serial.println(SS_Front_afstand);

	//Front Right
	servo_move(Servo_Around_Y, SERVO_AROUND_Y_PIN, 0);
	for(int i = 0; i < 1; i++){SS_FrontRight_samples.add(ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN));}
	SS_FrontRight_afstand = SS_FrontRight_samples.getMedian();
	Serial.print("Front right: ");Serial.println(SS_FrontRight_afstand);

	//Front Left
	servo_move(Servo_Around_Y, SERVO_AROUND_Y_PIN, 160);
	for(int i = 0; i < 1; i++){SS_FrontLeft_samples.add(ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN));}
	SS_FrontLeft_afstand = SS_FrontLeft_samples.getMedian();
	Serial.print("Front left: "); Serial.println(SS_FrontLeft_afstand);

	if(Climbing || Descending){
		//Front Left Down
		servo_move(Servo_Around_X, SERVO_AROUND_X_PIN, 0);
		for(int i = 0; i < 1; i++){SS_FrontLeft_samples_Down.add(ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN));}
		SS_FrontLeft_afstand_Down = SS_FrontLeft_samples_Down.getMedian();

		//Front Down
		servo_move(Servo_Around_Y, SERVO_AROUND_Y_PIN, 70);
		for(int i = 0; i < 1; i++){SS_Front_samples_Down.add(ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN));}
		SS_Front_afstand_Down = SS_Front_samples_Down.getMedian();

		//Front Right Down
		servo_move(Servo_Around_Y, SERVO_AROUND_Y_PIN, 0);
		for(int i = 0; i < 1; i++){SS_FrontRight_samples_Down.add(ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN));}
		SS_FrontRight_afstand_Down = SS_FrontRight_samples_Down.getMedian();

	}
	//Look to the  frontside
	servo_move(Servo_Around_X, SERVO_AROUND_X_PIN, 55);
	servo_move(Servo_Around_Y, SERVO_AROUND_Y_PIN, 70);
}
void scan_front(){
	for(int i = 0; i < 1; i++){SS_Front_samples.add(ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN));}
	SS_Front_afstand = SS_Front_samples.getMedian();
	Serial.print("Front: ");Serial.println(SS_Front_afstand);
}
void scan_left(){
	//Sensor left
	for(int i = 0; i < 1; i++){SS_Left_samples.add(ss_Meting(SS_LEFT_TRIGPIN, SS_LEFT_ECHOPIN));}
	SS_Left_afstand = SS_Left_samples.getMedian();
	Serial.print("left: ");	Serial.println(SS_Left_afstand);
}
void scan_right(){
	//Sensor right
	for(int i = 0; i < 1; i++){SS_Right_samples.add(ss_Meting(SS_RIGHT_TRIGPIN, SS_RIGHT_ECHOPIN));}
	SS_Right_afstand = SS_Right_samples.getMedian();
	Serial.print("right: ");	Serial.println(SS_Right_afstand);
}
void scan_back(){
	//Sensor back
	for(int i = 0; i < 1; i++){SS_Back_samples.add(ss_Meting(SS_BACK_TRIGPIN, SS_BACK_ECHOPIN));}
	SS_Back_afstand = SS_Back_samples.getMedian();
	Serial.print("Back: ");	Serial.println(SS_Back_afstand);
}
void scan(){
	scan_servo;
	scan_left;
	scan_right;
	scan_back;
}

//################################# Calculate
/*
void calculate(){
//Use Memory.getElement(x) to get the x'th element
	
	if(Memory.getElement(1) == 1){ // if last move was forward
		if(SS_Front_afstand < 5 && SS_FrontLeft_afstand < 5 && SS_FrontRight_afstand < 5){
			backward(speed);
		}
	}

	// rotate parralel to wall
}
// als 2 SS rechts < 2 SS links zorg dat evenwijdig is met rechts
// als 2 SS rechts > 2 SS links zorg dat evenwijdig is met links
// als 1 SS > en 1 SS < dan 

*/
//################################# Move
//#################################################### NOT USED ( wegens geen disable pin)
/*
void move(long period = 50){ //check what an good average speed is 
    if(Climbing){period *= 0.5;}
	else if(Descending){period *= 2;}

	if(Mode == "Automatic"){
		while(SS_Front_afstand > 8){
    
			// Give power to H-bridges
			digitalWrite(DISABLE_PIN, LOW);
			delay(period);
			digitalWrite(DISABLE_PIN, HIGH); 
			delay(period);

			SS_Front_afstand = ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN);
		}
	}
	else{
		digitalWrite(DISABLE_PIN, LOW);
		delay(period);
		digitalWrite(DISABLE_PIN, HIGH); 
		delay(period);
	}
    
}

*/

void EvenwijdigMetZij()
{
  SS_FrontRight_afstand = SS_FrontRight_afstand - 9;
  SS_FrontLeft_afstand = SS_FrontLeft_afstand - 9; 
  if(SS_FrontRight_afstand < SS_FrontLeft_afstand){
    if(SS_FrontRight_afstand > SS_Right_afstand)
    {
      while(SS_FrontRight_afstand - SS_Right_afstand > 5)
      {
        scan_servo();
		scan_right();
        rotate_right(150);
        delay(350);
        stop();
        Serial.println("dr-dra>5,rotate_right ");
  
      }
      stop();
  
    }
    if(SS_FrontRight_afstand<SS_Right_afstand)
    {
      while(SS_Right_afstand-SS_FrontRight_afstand>5)
      {
        scan_servo();
        scan_right();
        rotate_left(150);
        delay(350);
        stop();
        Serial.println("dra-dr>5,rotate_left ");
        
  
      }
      stop();
    }
  }
  if(SS_FrontLeft_afstand < SS_FrontRight_afstand){
    if(SS_FrontLeft_afstand > SS_Left_afstand)
    {
      while(SS_FrontLeft_afstand-SS_Left_afstand>5)
      {
        scan_servo();
        scan_left();
        rotate_left(150);
        delay(350);
        stop();
        Serial.println("dl-dla>5,rotate_left ");
        
      }
      stop();
  
    }
    if(SS_FrontLeft_afstand<SS_Left_afstand)
    {
      while(SS_Left_afstand-SS_FrontLeft_afstand>5)
      {
        scan_servo();
        scan_left();
        rotate_right(150);
        delay(350);
        stop();
        Serial.println("dla-dl>5,rotate_right ");
        
  
      }
      stop();
    }
  }
}

void CalculateLongestDistance()
{	EvenwijdigMetZij();
	SS_Front_afstand = ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN);
	if(SS_Front_afstand <= 10 || SS_Front_afstand > 800)
	{
		stop();
		delay(500);
		scan_servo();
		if(SS_Right_afstand > SS_Left_afstand && SS_Right_afstand < 100){
		rotate_right(speed);
		delay(500);
		}
		else if(SS_Right_afstand < SS_Left_afstand && SS_Left_afstand < 100)
		{
		rotate_left(speed);
		delay(500);
		}
	}
	else{
		forward(speed);
		delay(500);    
		stop();
	}
 

}

