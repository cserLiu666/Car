#include"steper.h"
#include"time.h"

void steper_init()
{
  pinMode(leftPul, OUTPUT);
  pinMode(leftDir, OUTPUT);
  pinMode(rightPul, OUTPUT);
  pinMode(rightDir, OUTPUT);

  digitalWrite(leftPul, 1);
  digitalWrite(leftDir, 0);
  digitalWrite(rightPul, 1);
  digitalWrite(rightDir, 0);  

  time1_init(65511); // 65536-16MHz/256/2500Hz  相当于脉冲频率 1250Hz
}

void steper_control(int foward,int turn, unsigned *timesLeft, unsigned *timesRight)
{
  //取得左右轮速度
  int left = ZOREForward - foward + turn - ZORETurn;
  int right = ZOREForward - foward - turn + ZORETurn;
  //判断左右轮正反转
  if(left<0)
  {
    LBack;
    left = -left;
  }
  else
    LFoward;
  if(right<0)
  {
    RBack;
    right = -right;
  }
  else
    RFoward;
  //计算左右轮定时器计数值
  if(left <= 5) *timesLeft = 10000;     //转速为0，即计数器永远达不到的值
  else *timesLeft  =  1250/map(left, 1, 512,  1, 1250);   //计数值为：   2500/2/需要的频率值
  if(right <= 5) *timesRight = 10000;
  else *timesRight =  1250/map(right, 1, 512, 1, 1250);
}

