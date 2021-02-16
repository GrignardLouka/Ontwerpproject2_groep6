//#####################################################################    Pin    ############################################################################
//################################# Scanning
const int SS_FRONT_TRIGPIN = 0;  
const int SS_LEFT_TRIGPIN = 1;
const int SS_RIGHT_TRIGPIN = 2;
const int SS_BACK_TRIGPIN = 3;  

const int SS_FRONT_ECHOPIN = 17; 
const int SS_LEFT_ECHOPIN = 2;
const int SS_RIGHT_ECHOPIN = 18;
const int SS_BACK_ECHOPIN = 15; 

const int SERVO_AROUND_Y_PIN = 14;
const int SERVO_AROUND_X_PIN = 12;

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

//##################################################################    Variable    ############################################################################
extern Adafruit_MCP23008 mcp;

//Sensor op servo
extern RunningMedian SS_Front_samples1; extern long SS_Front_afstand1;
extern RunningMedian SS_Front_samples2; extern long SS_Front_afstand2;
extern RunningMedian SS_Front_samples3; extern long SS_Front_afstand3;   

extern RunningMedian SS_Front_samples1_Down; extern long SS_Front_afstand1_Down;
extern RunningMedian SS_Front_samples2_Down; extern long SS_Front_afstand2_Down;
extern RunningMedian SS_Front_samples3_Down; extern long SS_Front_afstand3_Down;

extern Servo Servo_Around_Y;
extern Servo Servo_Around_X;
//Sensor left
extern RunningMedian SS_Left_samples; extern long SS_Left_afstand;
//Sensor right
extern RunningMedian SS_Right_samples; extern long SS_Right_afstand;
//Sensor back
extern RunningMedian SS_Back_samples; extern long SS_Back_afstand;

//BNO055 
extern const int BNO055_SAMPLERATE_DELAY_MS;
extern Adafruit_BNO055 bno;

extern RunningMedian lijstx; extern RunningMedian lijsty; extern RunningMedian lijstz;

extern bool Climbing;


//#################################################################    Functions    ############################################################################
//################################# Scanning

long ss_Meting(const int TRIGGER, const int ECHO, RunningMedian Lijst){
  long afstand;
  long duration;

  //Take 100 measurements
  for(int i = 0; i < 100; i++){
    mcp.digitalWrite(TRIGGER, LOW);              //set to LOW first to ensure a clean signal
    delayMicroseconds(5);
    mcp.digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(10);
    mcp.digitalWrite(TRIGGER, LOW);

    //Measure time needed for the pulse to return
    duration = pulseIn(ECHO, HIGH) / 2;    

    //Convert to cm
    Lijst.add(duration / 29.1);          
  }

  //Return the median of the list  
  return(Lijst.getMedian()); 
  
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
  for(int i = 0; i < 10; i++){
    // Get data from sensor
    sensors_event_t event;
    bno.getEvent(&event);
    // Read the wanted data and add it to a list
    lijstz.add((float)event.orientation.z);

    delay(BNO055_SAMPLERATE_DELAY_MS);
  }
  
  //Take the median of the list and check if the car is climbing
  if(lijstz.getMedian() > -160 && lijstz.getMedian() < -90){
    Climbing = true;
  }
}

void scan(){
  

  //Sensor left
  SS_Left_afstand = ss_Meting(SS_LEFT_TRIGPIN, SS_LEFT_ECHOPIN, SS_Left_samples);
  //Sensor right
  SS_Right_afstand = ss_Meting(SS_RIGHT_TRIGPIN, SS_RIGHT_ECHOPIN, SS_Right_samples);
  //Sensor back
  SS_Back_afstand = ss_Meting(SS_BACK_TRIGPIN, SS_BACK_ECHOPIN, SS_Back_samples);
  //BNO055
  bno_Meting();
}

void sensor_servo(){
    //############################ Sensor on servo
    attach_Servos();
    
    //Front
    SS_Front_afstand2 = ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN, SS_Front_samples2);

    // Right
    Servo_Around_Y.write(0);
    Serial.println("Turning to second position");
    delay(200);
    SS_Front_afstand1 = ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN, SS_Front_samples1);

    // Left
    Servo_Around_Y.write(160);
    Serial.println("Turning to third position");
    delay(200);
    SS_Front_afstand3 = ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN, SS_Front_samples3);

    if(Climbing){
        // Down left
        Servo_Around_X.write(15);
        Serial.println("Turning to the fourth position");
        delay(200);
        SS_Front_afstand3_Down = ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN ,SS_Front_samples3_Down);

        // Down front
        Servo_Around_Y.write(70);
        Serial.println("Turning to the fifth position");
        delay(200);
        SS_Front_afstand2_Down = ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN, SS_Front_samples2_Down);

        // Down right
        Servo_Around_Y.write(0);
        Serial.println("Turning to the sixth position");
        delay(200);
        SS_Front_afstand1_Down = ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN, SS_Front_samples1_Down);
        
        //Return to start
        Servo_Around_X.write(100);
        Serial.println("Turning to the first position");

        Climbing = false;
    }

    // look at the front
    Servo_Around_Y.write(70);
    delay(200);
    
    
    detach_Servos();
}


void sensor_front(){
    attach_Servos();


    SS_Front_afstand2 = ss_Meting(SS_FRONT_TRIGPIN, SS_FRONT_ECHOPIN, SS_Front_samples2);

    detach_Servos();
}
    
void sensor_left(){

}

//################################# Move
void move(int frequency = 50){
    long duration;
    long period = (1 / frequency) / 2;  

     while(SS_Front_afstand2 > 5){
    
        // Give power to H-bridges
        digitalWrite(ENABLE_PIN, HIGH);
        delay(period);
        digitalWrite(ENABLE_PIN, LOW); 
        delay(period);

        // Measure the distance again
        mcp.digitalWrite(SS_FRONT_TRIGPIN, LOW);              
        delayMicroseconds(5);
        mcp.digitalWrite(SS_FRONT_TRIGPIN, HIGH);
        delayMicroseconds(10);
        mcp.digitalWrite(SS_FRONT_TRIGPIN, LOW);

        duration = pulseIn(SS_FRONT_ECHOPIN, HIGH) / 2;    

        SS_Front_afstand2 = duration / 29.1; 
    }
}




