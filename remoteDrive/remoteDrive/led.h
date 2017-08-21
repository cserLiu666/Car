#ifndef LED_H_
#define LED_H_
#include<Arduino.h>

#define ledPin 13 //设置输出口为13口
#define LEDTURN digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
#define LEDON digitalWrite(ledPin, 1);
#define LEDOFF digitalWrite(ledPin, 0);
#define LEDINIT pinMode(ledPin, OUTPUT);LEDON

void led_init();

#endif
