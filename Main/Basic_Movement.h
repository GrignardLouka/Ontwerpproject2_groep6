//##################################################################    Pin    ############################################################################
const int WIEL_AL1 = 26; //27
const int WIEL_AL2 = 27; //26

const int WIEL_AR1 = 23; //32
const int WIEL_AR2 = 19; //19

const int WIEL_VR1 = 13; //13
const int WIEL_VR2 = 32	; //23

const int WIEL_VL1 = 25; //33
const int WIEL_VL2 = 33; //25

const int DISABLE_PIN = 14;

extern RunningMedian Memory;

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

  pinMode(DISABLE_PIN, OUTPUT);
  

}

//##################################################################    Functions    ############################################################################
void stop(){
  digitalWrite(DISABLE_PIN, LOW);

  digitalWrite(WIEL_AL1, LOW);
  digitalWrite(WIEL_AL2, LOW);

  digitalWrite(WIEL_AR1, LOW);
  digitalWrite(WIEL_AR2, LOW);

  digitalWrite(WIEL_VR1, LOW);
  digitalWrite(WIEL_VR2, LOW);

  digitalWrite(WIEL_VL1, LOW);
  digitalWrite(WIEL_VL2, LOW);

  digitalWrite(DISABLE_PIN, HIGH);

  Serial.println("Stop");
}
void forward(){
  digitalWrite(DISABLE_PIN, LOW);

  digitalWrite(WIEL_AL1, HIGH);
  digitalWrite(WIEL_AL2, LOW);

  digitalWrite(WIEL_AR1, HIGH);
  digitalWrite(WIEL_AR2, LOW);

  digitalWrite(WIEL_VR1, HIGH);
  digitalWrite(WIEL_VR2, LOW);

  digitalWrite(WIEL_VL1, HIGH);
  digitalWrite(WIEL_VL2, LOW);

  digitalWrite(DISABLE_PIN, HIGH);

  Memory.add(1);
  Serial.println("Forward");
}
void backward(){
  digitalWrite(DISABLE_PIN, LOW);

  digitalWrite(WIEL_AL1,LOW);
  digitalWrite(WIEL_AL2,HIGH);

  digitalWrite(WIEL_AR1,LOW);
  digitalWrite(WIEL_AR2,HIGH);

  digitalWrite(WIEL_VR1,LOW);
  digitalWrite(WIEL_VR2,HIGH);

  digitalWrite(WIEL_VL1,LOW);
  digitalWrite(WIEL_VL2,HIGH);

  digitalWrite(DISABLE_PIN, HIGH);
  Memory.add(2);
  Serial.println("Backwards");
  
}
void right(){
  digitalWrite(DISABLE_PIN, LOW);

  digitalWrite(WIEL_AL1,LOW);
  digitalWrite(WIEL_AL2,HIGH);

  digitalWrite(WIEL_AR1,HIGH);
  digitalWrite(WIEL_AR2,LOW);

  digitalWrite(WIEL_VR1,LOW);
  digitalWrite(WIEL_VR2,HIGH);

  digitalWrite(WIEL_VL1,HIGH);
  digitalWrite(WIEL_VL2,LOW);

  digitalWrite(DISABLE_PIN, HIGH);

  Memory.add(3);
  Serial.println("Right");
}
void left(){
  digitalWrite(DISABLE_PIN, LOW);

  digitalWrite(WIEL_AL1,HIGH);
  digitalWrite(WIEL_AL2,LOW);

  digitalWrite(WIEL_AR1,LOW);
  digitalWrite(WIEL_AR2,HIGH);

  digitalWrite(WIEL_VR1,HIGH);
  digitalWrite(WIEL_VR2,LOW);

  digitalWrite(WIEL_VL1,LOW);
  digitalWrite(WIEL_VL2,HIGH);

  digitalWrite(DISABLE_PIN, HIGH);

  Memory.add(4);
  Serial.println("Left");
}
void rotate_Left(){
  digitalWrite(DISABLE_PIN, LOW);

  digitalWrite(WIEL_AL1,LOW);
  digitalWrite(WIEL_AL2,HIGH);

  digitalWrite(WIEL_AR1,HIGH);
  digitalWrite(WIEL_AR2,LOW);

  digitalWrite(WIEL_VR1,HIGH);
  digitalWrite(WIEL_VR2,LOW);

  digitalWrite(WIEL_VL1,LOW);
  digitalWrite(WIEL_VL2,HIGH);

  digitalWrite(DISABLE_PIN, HIGH);

  Memory.add(5);
  Serial.println("Rotate Left");
}
void rotate_Right(){
  digitalWrite(DISABLE_PIN, LOW);

  digitalWrite(WIEL_AL1,HIGH);
  digitalWrite(WIEL_AL2,LOW);

  digitalWrite(WIEL_AR1,LOW);
  digitalWrite(WIEL_AR2,HIGH);

  digitalWrite(WIEL_VR1,LOW);
  digitalWrite(WIEL_VR2,HIGH);

  digitalWrite(WIEL_VL1,HIGH);
  digitalWrite(WIEL_VL2,LOW);

  digitalWrite(DISABLE_PIN, HIGH);

  Memory.add(6);
  Serial.println("Rotate Right");
}
