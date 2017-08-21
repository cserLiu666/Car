#ifndef USART_H_
#define USART_H_
#include<Arduino.h>

void usart_init(int baud);
void PutChar(char c);
void PutString(char *str);
void PutStringEnter(char *str);

void data_copy(char *datatemp,char *datacontiner);
void printstr(char *str);     //输出字符数组，遇到'\n'停止输出

#endif
