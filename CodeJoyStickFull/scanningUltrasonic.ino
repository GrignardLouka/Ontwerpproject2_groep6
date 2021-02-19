void scanUltrasonic180(){
  //for (int i = 0; i < 50; i++) {
  myservo.attach(14);  
  digitalWrite(SensorV_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(SensorV_trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(SensorV_trigPin, LOW);
  float duration = pulseIn(SensorV_echoPin, HIGH);    // Mesure time needed for signal to return(in microseconds)
  duration=duration/58;
  
  dv = duration;

  myservo.write(0);
  delay(1000);
  
  digitalWrite(SensorV_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(SensorV_trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(SensorV_trigPin, LOW);
  float durationr = pulseIn(SensorV_echoPin, HIGH);    // Mesure time needed for signal to return(in microseconds)
  durationr=durationr/58;
  
  dr=durationr;

  myservo.write(180);
  delay(1000);

  digitalWrite(SensorV_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(SensorV_trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(SensorV_trigPin, LOW);
  float durationl = pulseIn(SensorV_echoPin, HIGH);    // Mesure time needed for signal to return(in microseconds)
  durationl=durationl/58;
  dl=durationl;
  myservo.write(90);
  delay(1000);
  myservo.detach();
  //}
}
void scanUltrasonicV(){ 

  digitalWrite(SensorV_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(SensorV_trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(SensorV_trigPin, LOW);
  float duration = pulseIn(SensorV_echoPin, HIGH);    // Mesure time needed for signal to return(in microseconds)
  duration=duration/58;
  
  dv = duration; 
  
}
void scanUltrasonicRA(){
  //for (int i = 0; i < 50; i++) {
  digitalWrite(SensorRA_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(SensorRA_trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(SensorRA_trigPin, LOW);
  float duration = pulseIn(SensorRA_echoPin, HIGH);    // Mesure time needed for signal to return(in microseconds)
  duration=duration/58;
  dra = duration;
  //}
}
void scanUltrasonicLA(){
  //for (int i = 0; i < 50; i++) {
  digitalWrite(SensorLA_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(SensorLA_trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(SensorLA_trigPin, LOW);
  float duration = pulseIn(SensorLA_echoPin, HIGH);    // Mesure time needed for signal to return(in microseconds)
  duration=duration/58;
  dla = duration;
  //}
}
