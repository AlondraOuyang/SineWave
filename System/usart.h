#ifndef __USART_H
#define __USART_H
#include <stm32f10x.h>
#include"sys.h"
 	  	
extern u8 USART_RX_BUF[64];     //接收缓冲,最大63个字节.末字节为换行符 
extern u8 USART_RX_STA;         //接收状态标记	
//如果想串口中断接收，请不要注释以下宏定义
//#define EN_USART1_RX //使能串口1接收
void uart_init(u32 pclk2,u32 bound);
void send(u8 data);
void sendstring(u8 *str);
#endif	   
















