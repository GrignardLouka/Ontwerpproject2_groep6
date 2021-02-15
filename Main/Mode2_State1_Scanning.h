//Pin
const int SS1_TRIGPIN = 0;  
const int SS2_TRIGPIN = 1;
const int SS3_TRIGPIN = 2;
const int SS4_TRIGPIN = 3;  

const int SS1_ECHOPIN = 17; 
const int SS2_ECHOPIN = 2;
const int SS3_ECHOPIN = 18;
const int SS4_ECHOPIN = 15; 

const int SERVO_AROUND_Y_PIN = 14;
const int SERVO_AROUND_X_PIN = 12;

//PinMode
void pinMode_Scanning(){
  //Sensor
  mcp.pinMode(SS1_TRIGPIN, OUTPUT);
  mcp.pinMode(SS2_TRIGPIN, OUTPUT);
  mcp.pinMode(SS3_TRIGPIN, OUTPUT);
  mcp.pinMode(SS4_TRIGPIN, OUTPUT);

  pinMode(SS1_ECHOPIN, INPUT);
  pinMode(SS2_ECHOPIN, INPUT);
  pinMode(SS3_ECHOPIN, INPUT);
  pinMode(SS4_ECHOPIN, INPUT);

  //Servo
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  Servo_Around_Y.setPeriodHertz(50);    // standard 50 hz servo
  Servo_Around_Y.attach(SERVO_AROUND_Y_PIN, 500, 2500);
  Servo_Around_X.setPeriodHertz(50);
  Servo_Around_X.attach(SERVO_AROUND_X_PIN, 500, 2500);
}

//Variable
extern RunningMedian SS1_samples1;extern long SS1_afstand1;
extern RunningMedian SS1_samples2; extern long SS1_afstand2;
extern RunningMedian SS1_samples3; extern long SS1_afstand3;   

extern RunningMedian SS1_samples1_Down; extern long SS1_afstand1_Down;
extern RunningMedian SS1_samples2_Down; extern long SS1_afstand2_Down;
extern RunningMedian SS1_samples3_Down; extern long SS1_afstand3_Down;

extern RunningMedian SS2_samples; extern long SS2_afstand;

extern Servo Servo_Around_Y;
extern Servo Servo_Around_X;

//Functions
long ss_Meting(const int TRIGGER, const int ECHO, RunningMedian Lijst){
  long afstand;
  long duration;

  mcp.digitalWrite(TRIGGER, LOW);              //set to LOW first to ensure a clean signal
  delayMicroseconds(5);
  mcp.digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  mcp.digitalWrite(TRIGGER, LOW);

  duration = pulseIn(ECHO, HIGH) / 2;    // Measure time needed for signal to return(in microseconds)(/2 signal travels  back and forth)
  Lijst. add(duration / 29.1);            // Convert to cm and add to list
  afstand = Lijst.getMedian();              // Get median of the list(for a more accurate measurement)
  
  return(afstand);
  
}
void attach_Servos(){
  Servo_Around_Y.setPeriodHertz(50);    // standard 50 hz servo
  Servo_Around_Y.attach(SERVO_AROUND_Y_PIN, 500, 2500);
  Servo_Around_X.setPeriodHertz(50);    // standard 50 hz servo
  Servo_Around_X.attach(SERVO_AROUND_X_PIN, 500, 2500);
}
void detach_Servos(){
  Servo_Around_Y.detach();
  Servo_Around_X.detach();
}
void scan(){
  attach_Servos();

  // Pos 1  (rechts)
  Servo_Around_Y.write(0);
  Servo_Around_X.write(100);
  Serial.println("Turning to first position");
  delay(200);
  SS1_afstand1 = ss_Meting(SS1_TRIGPIN, SS1_ECHOPIN,SS1_samples1);

  // Pos 2
  Servo_Around_Y.write(70);
  Serial.println("Turning to third position");
  delay(200);
  SS1_afstand2 = ss_Meting(SS1_TRIGPIN, SS1_ECHOPIN,SS1_samples2);

  // Pos 3
  Servo_Around_Y.write(160);
  Serial.println("Turning to fifth position");
  delay(200);
  SS1_afstand3 = ss_Meting(SS1_TRIGPIN, SS1_ECHOPIN,SS1_samples3);
  //pos 7
  Servo_Around_X.write(15);
  Serial.println("Turning to the seventh position");
  delay(200);
  SS1_afstand3_Down = ss_Meting(SS1_TRIGPIN, SS1_ECHOPIN,SS1_samples3_Down);

  //pos 8
  Servo_Around_Y.write(70);
  Serial.println("Turning to the eight position");
  delay(200);
  SS1_afstand2_Down = ss_Meting(SS1_TRIGPIN, SS1_ECHOPIN,SS1_samples2_Down);
  //pos 9
  Servo_Around_Y.write(0);
  Serial.println("Turning to the ninth position");
  delay(200);
  SS1_afstand1_Down = ss_Meting(SS1_TRIGPIN, SS1_ECHOPIN,SS1_samples1_Down);
  Servo_Around_X.write(0);
  Serial.println("Turning to the first position");
  delay(200);

  detach_Servos();
}

