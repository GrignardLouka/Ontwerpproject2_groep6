#ifndef TEST_H
#define TEST_H

const int SERVO_AROUND_Y_PIN = 14;
const int SERVO_AROUND_X_PIN = 12;

//5 spots(lright, middle, left)
RunningMedian SS1_samples1 = RunningMedian(49); long SS1_afstand1;
RunningMedian SS1_samples2 = RunningMedian(49); long SS1_afstand2;
RunningMedian SS1_samples3 = RunningMedian(49); long SS1_afstand3;   

RunningMedian SS1_samples1_Down = RunningMedian(49); long SS1_afstand1_Down;
RunningMedian SS1_samples2_Down = RunningMedian(49); long SS1_afstand2_Down;
RunningMedian SS1_samples3_Down = RunningMedian(49); long SS1_afstand3_Down;

RunningMedian SS2_samples = RunningMedian(49); long SS2_afstand;

Servo Servo_Around_Y;
Servo Servo_Around_X;

void PinMode_Scanning();

void Attach_Servos();
void Scan();
void Detach_Servos();

#endif

