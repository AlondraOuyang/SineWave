#include "timer.h"

u16 flag=0;
//****ͨ�ö�ʱ����ʼ���ж�ģ��***************//
//��ʱT=(arr*(psc+1))/Tclk    TclkΪ��ʱ��������ʱ��Ƶ��(Hz)  TΪ���ʱ��
//ͨ�ö�ʱ��2�жϳ�ʼ��  APB1��0~2λ��TIME2~4
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��

//�ɸĶ�ʱ��
void Timerx_Init(u16 arr,u16 psc)
{

	RCC->APB1ENR|=1<<2;	//TIM4ʱ��ʹ��   APB1��0~2λ��TIME2~4 //STM32F103RBT6��û�ж�ʱ��5
 	TIM4->ARR=arr;  	//�Զ���װ��ֵ 
	TIM4->PSC=psc;  	//�ֳ�Ƶ��F=(72M/(PSC+1))//72MΪ��ʱ������ʱ��	  
	TIM4->CR1|=1<<0;    //ʹ�ܶ�ʱ��2
	
	TIM4->DIER|=1<<0;   //��������ж�	  
	TIM4->DIER|=1<<8;	//�������DMA����

	TIM4->CR2|=2<<4;	//�����¼�ѡ��ΪTRGO

	flag++;

  	//MY_NVIC_Init(1,3,TIM4_IRQChannel,2);//��ռ1�������ȼ�3����2									 
}
/*//��ʱ��2�жϷ������	 
void TIM4_IRQHandler(void)
{
	if(TIM4->SR&(1<<0))
	{
		;//PAout(8)=!PAout(8);
	}
	TIM4->SR&=~(1<<0);
} */
















