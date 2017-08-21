#include"time.h"
#include"usart.h"
#include"calculate.h"
#include"steper.h"

unsigned int timer1_counter = 0;   //定时器1的重装值
unsigned int left_counter = 10000; 
unsigned int right_counter = 10000; 

char remoterFlag = 0;     //遥控器连接标志  如果遥控断开，remoterFlag持续增长，停止运转

extern int valueX;
extern int valueY;
extern int valueC;

void time2_iqr() 
{           
     if(remoterFlag>=200)
     {
      valueX = ZORETurn;
      valueY = ZOREForward;
     }
     else
     {
        driveData();
        steper_control(valueY,valueX,&left_counter,&right_counter);
     }     
     remoterFlag++;
     if(remoterFlag>200)remoterFlag = 200;     
}

void time2_init(int interval)
{
  MsTimer2::set(interval, time2_iqr);
  MsTimer2::start();
}

ISR(TIMER1_OVF_vect)        //常规中断服务
{
  static unsigned int steperTimeFlagL=0;
  static unsigned int steperTimeFlagR=0;
  TCNT1 = timer1_counter;   //预加载 timer
  if(steperTimeFlagL >= left_counter)
  {
    LPulTurn;
    steperTimeFlagL = 0;
  }
  if(steperTimeFlagR >= right_counter)
  {
    RPulTurn;
    steperTimeFlagR = 0;
  }
  if(steperTimeFlagL>=1251) steperTimeFlagL = 0;
  if(steperTimeFlagR>=1251) steperTimeFlagR = 0;
  steperTimeFlagL++;
  steperTimeFlagR++;
}


//**********************使用time1，就无法使用sevor库了*********************//

void time1_init(int interval)    //计算公式:
{

  //初始化定时器1
  noInterrupts();           //禁止所有中断
  TCCR1A = 0;
  TCCR1B = 0;

  //为我们的中断设置timer1_counter为正确的时间间隔
  // timer1_counter = 64911; //预加载timer1为 65536-16MHz/256/100Hz
  // timer1_counter = 64286; //预加载timer1为 65536-16MHz/256/50HZ
  // timer1_counter = 34286;    //预加载timer1为 65536-16MHz/256/2Hz
  timer1_counter = interval;
  
  TCNT1 = timer1_counter;   //预加载 timer
  TCCR1B |= (1 << CS12);    //256 分频器(256 prescaler?) 
  TIMSK1 |= (1 << TOIE1);   //启用定时器溢出中断
  interrupts();             //允许所有中断
}

