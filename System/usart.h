#ifndef __USART_H
#define __USART_H
#include <stm32f10x.h>
#include"sys.h"
 	  	
extern u8 USART_RX_BUF[64];     //���ջ���,���63���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8 USART_RX_STA;         //����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
//#define EN_USART1_RX //ʹ�ܴ���1����
void uart_init(u32 pclk2,u32 bound);
void send(u8 data);
void sendstring(u8 *str);
#endif	   
















