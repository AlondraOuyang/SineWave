#include "timer.h"

u16 flag=0;
//****通用定时器初始化中断模块***************//
//定时T=(arr*(psc+1))/Tclk    Tclk为定时器的输入时钟频率(Hz)  T为溢出时间
//通用定时器2中断初始化  APB1的0~2位是TIME2~4
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数

//可改定时器
void Timerx_Init(u16 arr,u16 psc)
{

	RCC->APB1ENR|=1<<2;	//TIM4时钟使能   APB1的0~2位是TIME2~4 //STM32F103RBT6上没有定时器5
 	TIM4->ARR=arr;  	//自动重装的值 
	TIM4->PSC=psc;  	//分出频率F=(72M/(PSC+1))//72M为定时器输入时钟	  
	TIM4->CR1|=1<<0;    //使能定时器2
	
	TIM4->DIER|=1<<0;   //允许更新中断	  
	TIM4->DIER|=1<<8;	//允许更新DMA请求

	TIM4->CR2|=2<<4;	//更新事件选择为TRGO

	flag++;

  	//MY_NVIC_Init(1,3,TIM4_IRQChannel,2);//抢占1，子优先级3，组2									 
}
/*//定时器2中断服务程序	 
void TIM4_IRQHandler(void)
{
	if(TIM4->SR&(1<<0))
	{
		;//PAout(8)=!PAout(8);
	}
	TIM4->SR&=~(1<<0);
} */
















