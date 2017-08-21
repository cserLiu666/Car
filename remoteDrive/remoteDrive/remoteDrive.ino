#include"time.h"
#include"usart.h"
#include"led.h"
#include"steper.h"

void setup()
{
//  LEDINIT;
// how to add code
  led_init();       //如果led.cpp文件改成了led.c文件，就会报错！！！！！
  usart_init(9600);
  time2_init(20);
  steper_init();
}



void loop()
{
}

