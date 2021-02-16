//##################################################################    Pin    ############################################################################
const int WIEL_AL1 = 27; 
const int WIEL_AL2 = 26; 

const int WIEL_AR1 = 32; 
const int WIEL_AR2 = 19; 

const int WIEL_VR1 = 23; 
const int WIEL_VR2 = 13;

const int WIEL_VL1 = 25; 
const int WIEL_VL2 = 33; 

const int ENABLE_PIN = 14;

//##################################################################    PinMode    ############################################################################
void pinMode_Basic_Movement(){
    
  pinMode(WIEL_AL1,OUTPUT);       // Set pin to output
  pinMode(WIEL_AL2,OUTPUT);

  pinMode(WIEL_AR1,OUTPUT);
  pinMode(WIEL_AR2,OUTPUT);

  pinMode(WIEL_VR1,OUTPUT);
  pinMode(WIEL_VR2,OUTPUT);

  pinMode(WIEL_VL1,OUTPUT);
  pinMode(WIEL_VL2,OUTPUT);

  pinMode(ENABLE_PIN, OUTPUT);
  

}

//##################################################################    Functions    ############################################################################
void stop(){
  Movement_State = 0;

  digitalWrite(WIEL_AL1, LOW);
  digitalWrite(WIEL_AL2, LOW);

  digitalWrite(WIEL_AR1, LOW);
  digitalWrite(WIEL_AR2, LOW);

  digitalWrite(WIEL_VR1, LOW);
  digitalWrite(WIEL_VR2, LOW);

  digitalWrite(WIEL_VL1, LOW);
  digitalWrite(WIEL_VL2, LOW);

  Serial.println("Stop");
}
void forward(int snelheid, int tijd = 0){

  digitalWrite(WIEL_AL1, HIGH);
  digitalWrite(WIEL_AL2, LOW);

  digitalWrite(WIEL_AR1, HIGH);
  digitalWrite(WIEL_AR2, LOW);

  digitalWrite(WIEL_VR1, HIGH);
  digitalWrite(WIEL_VR2, LOW);

  digitalWrite(WIEL_VL1, HIGH);
  digitalWrite(WIEL_VL2, LOW);

  if(tijd != 0){
    delay(tijd);
    stop();
  }

  Serial.println("Forward");
}
void backward(int snelheid, int tijd = 0){

  digitalWrite(WIEL_AL1,LOW);
  digitalWrite(WIEL_AL2,HIGH);

  digitalWrite(WIEL_AR1,LOW);
  digitalWrite(WIEL_AR2,HIGH);

  digitalWrite(WIEL_VR1,LOW);
  digitalWrite(WIEL_VR2,HIGH);

  digitalWrite(WIEL_VL1,LOW);
  digitalWrite(WIEL_VL2,HIGH);

  if(tijd != 0){
    delay(tijd);
    stop();
  }
  Serial.println("Backwards");
  
}
void right(int snelheid, int tijd = 0){

  digitalWrite(WIEL_AL1,LOW);
  digitalWrite(WIEL_AL2,HIGH);

  digitalWrite(WIEL_AR1,HIGH);
  digitalWrite(WIEL_AR2,LOW);

  digitalWrite(WIEL_VR1,LOW);
  digitalWrite(WIEL_VR2,HIGH);

  digitalWrite(WIEL_VL1,HIGH);
  digitalWrite(WIEL_VL2,LOW);

  if(tijd != 0){
    delay(tijd);
    stop();
  }

  Serial.println("Right");
}
void left(int snelheid, int tijd = 0){
  digitalWrite(WIEL_AL1,HIGH);
  digitalWrite(WIEL_AL2,LOW);

  digitalWrite(WIEL_AR1,LOW);
  digitalWrite(WIEL_AR2,HIGH);

  digitalWrite(WIEL_VR1,HIGH);
  digitalWrite(WIEL_VR2,LOW);

  digitalWrite(WIEL_VL1,LOW);
  digitalWrite(WIEL_VL2,HIGH);

  if(tijd != 0){
    delay(tijd);
    stop();
  }

  Serial.println("Left");
}
void rotate_Left(int snelheid, int tijd = 0){

  digitalWrite(WIEL_AL1,LOW);
  digitalWrite(WIEL_AL2,HIGH);

  digitalWrite(WIEL_AR1,HIGH);
  digitalWrite(WIEL_AR2,LOW);

  digitalWrite(WIEL_VR1,HIGH);
  digitalWrite(WIEL_VR2,LOW);

  digitalWrite(WIEL_VL1,LOW);
  digitalWrite(WIEL_VL2,HIGH);

  if(tijd != 0){
    delay(tijd);
    stop();
  }

  Serial.println("Rotate Left");
}
void rotate_Right(int snelheid, int tijd = 0){

  digitalWrite(WIEL_AL1,HIGH);
  digitalWrite(WIEL_AL2,LOW);

  digitalWrite(WIEL_AR1,LOW);
  digitalWrite(WIEL_AR2,HIGH);

  digitalWrite(WIEL_VR1,LOW);
  digitalWrite(WIEL_VR2,HIGH);

  digitalWrite(WIEL_VL1,HIGH);
  digitalWrite(WIEL_VL2,LOW);

  if(tijd != 0){
    delay(tijd);
    stop();
  }

  Serial.println("Rotate Right");
}
