#include"usart.h"

char data[17];

extern char remoterFlag;

//****带有接收中断的串口初始化******//
void usart_init(int baud)
{
//  bitSet(DDRB,5);                 //适合UNO         输出    板载led控制
  bitSet(UCSR0B,RXCIE0);                    //允许接收完成中断// 
  bitSet(UCSR0B,RXEN0);                     //开启接收功能// 
  bitSet(UCSR0B,TXEN0);                     //开启发送功能// 
  bitSet(UCSR0C,UCSZ01);
  bitSet(UCSR0C,UCSZ00);                    // 
  UBRR0=(F_CPU/16/baud-1);                  //波特率小于38400
}


/*
函数功能：通过uart0发送一个字符
*/  
void PutChar(char c)
{
  loop_until_bit_is_set(UCSR0A,UDRE0);
  UDR0=c;
} 

/*
函数功能：通过uart0发送字符串 
*/
void PutString(char *str)
{
  while(*str)
  {
    PutChar(*str);
    str++;
  }
}

/*
函数功能：通过uart0发送字符串 ,并在结尾加上回车换行 
*/
void PutStringEnter(char *str)
{
  while(*str)
  {
    PutChar(*str);
    str++;
  }
  PutChar(0x0d);
  PutChar(0x0a);  
}

/*
USART0--接收中断// 
*/
ISR(USART_RX_vect)                    //适合UNO
{
  static char beginFlag = 0;
  static char number = 0;
  static char datatemp[17];
  unsigned char temp;
  temp = UDR0;
//  bitSet(PINB,5);                 //适合UNO         翻转 
  


//数据格式：f开头，g结尾,小于17个字符
  if(temp == 'g' && beginFlag == 1)
  {
     remoterFlag = 0;
     beginFlag = 0;
     datatemp[number] = '\n';
     number = 0;
     data_copy(datatemp,data);
   }
  
  if(temp != 'f' && beginFlag == 1)
    datatemp[number++] = temp;
  
  if(temp == 'f'&&beginFlag == 0)
  {
    beginFlag = 1;
    number = 0;
  }
}

void data_copy(char *datatemp,char *datacontiner)
{
  int index=0;
  while(datatemp[index]!='\n')
  {
    datacontiner[index] = datatemp[index];
    index++;
  }
  datacontiner[index]='\n';
}

//****************遇到'\n'停止输出*************//
void printstr(char *str)
{
  int index=0;
  while(str[index]!='\n')
  {
    PutChar(str[index++]);
  }
  PutChar(0x0d);
  PutChar(0x0a);  
}
