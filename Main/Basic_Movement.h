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
extern bool Climbing;
extern bool Descending;
extern String Mode;

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

	analogWrite(WIEL_AL1, 0);
	analogWrite(WIEL_AL2, 0);

	analogWrite(WIEL_AR1, 0);
	analogWrite(WIEL_AR2, 0);

	analogWrite(WIEL_VR1, 0);
	analogWrite(WIEL_VR2, 0);

	analogWrite(WIEL_VL1, 0);
	analogWrite(WIEL_VL2, 0);

/*
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
*/
  Serial.println("Stop");
}
void forward(int snelheid){
/*
  analogWrite(WIEL_AL1, snelheid);
  analogWrite(WIEL_AL2, 0);

  analogWrite(WIEL_AR1, snelheid);
  analogWrite(WIEL_AR2, 0);

  analogWrite(WIEL_VR1, snelheid);
  analogWrite(WIEL_VR2, 0);

  analogWrite(WIEL_VL1, snelheid);
  analogWrite(WIEL_VL2, 0);
*/
  
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
void backward(int snelheid){
/*
	analogWrite(WIEL_AL1,0);
	analogWrite(WIEL_AL2,snelheid);

	analogWrite(WIEL_AR1,0);
	analogWrite(WIEL_AR2,snelheid);

	analogWrite(WIEL_VR1,0);
	analogWrite(WIEL_VR2,snelheid);

	analogWrite(WIEL_VL1,0);
	analogWrite(WIEL_VL2,snelheid);
*/
	
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
void right(int snelheid){
  
	analogWrite(WIEL_AL1,0);
	analogWrite(WIEL_AL2,snelheid);

	analogWrite(WIEL_AR1,snelheid);
	analogWrite(WIEL_AR2,0);

	analogWrite(WIEL_VR1,0);
	analogWrite(WIEL_VR2,snelheid);

	analogWrite(WIEL_VL1,snelheid);
	analogWrite(WIEL_VL2,0);

  /*
  digitalWrite(DISABLE_PIN, LOW);

  digitalWrite(WIEL_AL1,LOW);
  digitalWrite(WIEL_AL2,HIGH);

  digitalWrite(WIEL_AR1,HIGH);
  digitalWrite(WIEL_AR2,LOW);

  digitalWrite(WIEL_VR1,LOW);
  digitalWrite(WIEL_VR2,HIGH);

  digitalWrite(WIEL_VL1,HIGH);
  digitalWrite(WIEL_VL2,LOW);

  //digitalWrite(DISABLE_PIN, HIGH);

  Memory.add(3);
	*/

  Serial.println("Right");
}
void left(int snelheid){

	analogWrite(WIEL_AL1,snelheid);
	analogWrite(WIEL_AL2,0);

	analogWrite(WIEL_AR1,0);
	analogWrite(WIEL_AR2,snelheid);

	analogWrite(WIEL_VR1,snelheid);
	analogWrite(WIEL_VR2,0);

	analogWrite(WIEL_VL1,0);
	analogWrite(WIEL_VL2,snelheid);
  /*
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

  */
  Serial.println("Left");
}
void rotate_left(int snelheid){

	analogWrite(WIEL_AL1,0);
	analogWrite(WIEL_AL2,snelheid);

	analogWrite(WIEL_AR1,snelheid);
	analogWrite(WIEL_AR2,0);

	analogWrite(WIEL_VR1,snelheid);
	analogWrite(WIEL_VR2,0);

	analogWrite(WIEL_VL1,0);
	analogWrite(WIEL_VL2,snelheid);


	/*
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
	*/

	Serial.println("Rotate Left");
}
void rotate_right(int snelheid){

	analogWrite(WIEL_AL1,snelheid);
	analogWrite(WIEL_AL2,0);

	analogWrite(WIEL_AR1,0);
	analogWrite(WIEL_AR2,snelheid);

	analogWrite(WIEL_VR1,0);
	analogWrite(WIEL_VR2,snelheid);

	analogWrite(WIEL_VL1,snelheid);
	analogWrite(WIEL_VL2,0);

	/*
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
	*/
	Serial.println("Rotate Right");
}
void forward_right(int snelheid){
	analogWrite(WIEL_AL1, 0);
	analogWrite(WIEL_AL2, 0);
	analogWrite(WIEL_AR1, snelheid);
	analogWrite(WIEL_AR2, 0);
	analogWrite(WIEL_VR1, 0);
	analogWrite(WIEL_VR2, 0);
	analogWrite(WIEL_VL1, snelheid);
	analogWrite(WIEL_VL2, 0); 

	Serial.println("Moving forward right");
}
void forward_left(int snelheid){
	analogWrite(WIEL_AL1, snelheid);
	analogWrite(WIEL_AL2, 0);
	analogWrite(WIEL_AR1, 0);
	analogWrite(WIEL_AR2, 0);
	analogWrite(WIEL_VR1, snelheid);
	analogWrite(WIEL_VR2, 0);
	analogWrite(WIEL_VL1, 0);
	analogWrite(WIEL_VL2, 0); 

	Serial.println("Moving forward left");
}