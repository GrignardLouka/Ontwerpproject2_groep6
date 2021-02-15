//Pin
const int WIEL_AL1 = 27; 
const int WIEL_AL2 = 26; 

const int WIEL_AR1 = 32; 
const int WIEL_AR2 = 19; 

const int WIEL_VR1 = 23; 
const int WIEL_VR2 = 13;

const int WIEL_VL1 = 25; 
const int WIEL_VL2 = 33; 

//PinMode
void pinMode_Basic_Movement(){
    
  pinMode(WIEL_AL1,OUTPUT);       // Set pin to output
  pinMode(WIEL_AL2,OUTPUT);

  pinMode(WIEL_AR1,OUTPUT);
  pinMode(WIEL_AR2,OUTPUT);

  pinMode(WIEL_VR1,OUTPUT);
  pinMode(WIEL_VR2,OUTPUT);

  pinMode(WIEL_VL1,OUTPUT);
  pinMode(WIEL_VL2,OUTPUT);

}

//Basic Movement
void stop(){
  analogWrite(WIEL_AL1,0);
  analogWrite(WIEL_AL2,0);

  analogWrite(WIEL_AR1,0);
  analogWrite(WIEL_AR2,0);

  analogWrite(WIEL_VR1,0);
  analogWrite(WIEL_VR2,0);

  analogWrite(WIEL_VL1,0);
  analogWrite(WIEL_VL2,0);

  Serial.println("Stop");
}
void forward(int snelheid, int tijd){
  analogWrite(WIEL_AL1,snelheid);
  analogWrite(WIEL_AL2,0);

  analogWrite(WIEL_AR1,snelheid);
  analogWrite(WIEL_AR2,0);

  analogWrite(WIEL_VR1,snelheid);
  analogWrite(WIEL_VR2,0);

  analogWrite(WIEL_VL1,snelheid);
  analogWrite(WIEL_VL2,0);

  if(tijd != 0){
    delay(tijd);
    stop();
  }

  Serial.println("Forward");
}
void backward(int snelheid, int tijd){
  analogWrite(WIEL_AL1,0);
  analogWrite(WIEL_AL2,snelheid);

  analogWrite(WIEL_AR1,0);
  analogWrite(WIEL_AR2,snelheid);

  analogWrite(WIEL_VR1,0);
  analogWrite(WIEL_VR2,snelheid);

  analogWrite(WIEL_VL1,0);
  analogWrite(WIEL_VL2,snelheid);

  if(tijd != 0){
    delay(tijd);
    stop();
  }
  Serial.println("Backwards");

 
  
}
void right(int snelheid, int tijd){
  analogWrite(WIEL_AL1,0);
  analogWrite(WIEL_AL2,snelheid);

  analogWrite(WIEL_AR1,snelheid);
  analogWrite(WIEL_AR2,0);

  analogWrite(WIEL_VR1,0);
  analogWrite(WIEL_VR2,snelheid);

  analogWrite(WIEL_VL1,snelheid);
  analogWrite(WIEL_VL2,0);

  if(tijd != 0){
    delay(tijd);
    stop();
  }

  Serial.println("Right");
}
void left(int snelheid, int tijd){
  analogWrite(WIEL_AL1,snelheid);
  analogWrite(WIEL_AL2,0);

  analogWrite(WIEL_AR1,0);
  analogWrite(WIEL_AR2,snelheid);

  analogWrite(WIEL_VR1,snelheid);
  analogWrite(WIEL_VR2,0);

  analogWrite(WIEL_VL1,0);
  analogWrite(WIEL_VL2,snelheid);


  if(tijd != 0){
    delay(tijd);
    stop();
  }

  Serial.println("Left");
}
void rotate_Left(int snelheid, int tijd){
  analogWrite(WIEL_AL1,0);
  analogWrite(WIEL_AL2,snelheid);

  analogWrite(WIEL_AR1,snelheid);
  analogWrite(WIEL_AR2,0);

  analogWrite(WIEL_VR1,snelheid);
  analogWrite(WIEL_VR2,0);

  analogWrite(WIEL_VL1,0);
  analogWrite(WIEL_VL2,snelheid);

  if(tijd != 0){
    delay(tijd);
    stop();
  }

  Serial.println("Rotate Left");
}
void rotate_Right(int snelheid, int tijd){
  analogWrite(WIEL_AL1,snelheid);
  analogWrite(WIEL_AL2,0);

  analogWrite(WIEL_AR1,0);
  analogWrite(WIEL_AR2,snelheid);

  analogWrite(WIEL_VR1,0);
  analogWrite(WIEL_VR2,snelheid);

  analogWrite(WIEL_VL1,snelheid);
  analogWrite(WIEL_VL2,0);

  if(tijd != 0){
    delay(tijd);
    stop();
  }

  Serial.println("Rotate Right");
}
