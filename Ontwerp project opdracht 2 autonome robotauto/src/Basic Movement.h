#ifndef TEST_H
#define TEST_H

const int MOTORALWPIN1 = 27; 
const int MOTORALWPIN2 = 26; 
const int MOTORARWPIN1 = 21; 
const int MOTORARWPIN2 = 19; 
const int MOTORVRWPIN1 = 23; 
const int MOTORVRWPIN2 = 22;
const int MOTORVLWPIN1 = 25; 
const int MOTORVLWPIN2 = 33; 

void PinMode_Basic_Movement();

void Stop();
void Forward(int snelheid, int tijd);
void Backward(int snelheid, int tijd);
void Right(int snelheid, int tijd);
void Left(int snelheid, int tijd);
void Rotate_Left(int snelheid, int tijd);
void Rotate_Right(int snelheid, int tijd);

#endif