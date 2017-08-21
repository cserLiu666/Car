#include <stdlib.h>
#include"usart.h"
#include"calculate.h"
#include"led.h"
#include"steper.h"

extern char data[17];

int valueX = ZORETurn;
int valueY = ZOREForward;
int valueC = 0;

void driveData()
{
  char index = 0;
  String valueTemp = "";
  for(index = 0;data[index]!='\n';index++)
  {
    if (data[index] == 'x')
    {
        valueTemp = "";
      }
     else if( data[index] == 'y')
      {
        valueX = valueTemp.toInt();
        valueTemp = "";
      }
     else if(data[index] == 'c')
      {
        valueY = valueTemp.toInt();
        valueTemp = "";
      }
     else
      {
        valueTemp += data[index];
      }
  }
  valueC = valueTemp.toInt();
  valueTemp = "";
}
