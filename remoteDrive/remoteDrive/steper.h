#ifndef STEPER_H_
#define STEPER_H_
#include<Arduino.h>

#define ZOREForward 515
#define ZORETurn 530

#define leftPul 4 //左电机PUL  pin4
#define leftDir 5 //左电机DIR  pin5
#define rightPul 6 //右电机PUL  pin6
#define rightDir 7 //右电机DIR  pin7

#define LFoward digitalWrite(leftDir, 0)
#define LBack digitalWrite(leftDir, 1)
#define LTurn digitalWrite(leftDir, digitalRead(leftDir) ^ 1)
#define RFoward digitalWrite(rightDir, 0)
#define RBack digitalWrite(rightDir, 1)
#define RTurn digitalWrite(rightDir, digitalRead(rightDir) ^ 1)

#define LPulHigh digitalWrite(leftPul, 1)
#define LPulLow digitalWrite(leftPul, 0)
#define LPulTurn digitalWrite(leftPul, digitalRead(leftPul) ^ 1)
#define RPulHigh digitalWrite(rightPul, 1)
#define RPulLow digitalWrite(rightPul, 0)
#define RPulTurn digitalWrite(rightPul, digitalRead(rightPul) ^ 1)

void steper_init();
void steper_control(int foward,int turn, unsigned *timesLeft, unsigned *timesRight);

#endif
