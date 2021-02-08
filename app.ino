/* 
autonome robotauto

Groep 6

El Madani 	Ilyas
Grignard	Louka
Sahan	Baris

*/

///////////////////////////	Change log //////////////////////////////////////////
/* 
08/02/2021 13:48: Begin


*/





const int SS1_trigPin = 18;    // Trigger
const int SS1_echoPin = 19;    // Echo
const int SS2_trigPin = 33;    // Trigger
const int SS2_echoPin = 32;    // Echo
long SS1_duration, SS2_duration, cm1, cm2;
 
void setup() {
  Serial.begin (115200);
  
  pinMode(SS1_trigPin, OUTPUT);
  pinMode(SS1_echoPin, INPUT);
  pinMode(SS2_trigPin, OUTPUT);
  pinMode(SS2_echoPin, INPUT);

}
 
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(SS1_trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(SS1_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(SS1_trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(SS1_echoPin, INPUT);
  SS1_duration = pulseIn(SS1_echoPin, HIGH);
 
  // Convert the time into a distance
  cm1 = (SS1_duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343

  Serial.print(cm1);
  Serial.print("cm SS1");
  Serial.println("");

  delay(250);

  digitalWrite(SS2_trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(SS2_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(SS2_trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(SS2_echoPin, INPUT);
  SS2_duration = pulseIn(SS2_echoPin, HIGH);


  cm2 = (SS2_duration/2) / 29.1;

  Serial.print(cm2);
  Serial.print("cm SS2");
  Serial.println("");
  Serial.println("einde data");
  Serial.println("");

  delay(1500); // standaard 250
}
