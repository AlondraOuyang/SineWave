#include"DA.h"
#include "math.h"


//DA初始化
void DA_init(void)
{
	RCC->APB2ENR |= 1<<2;//使能PA时钟
	RCC->APB1ENR |= 1<<29;//使能DAC时钟
	
	GPIOA->CRL &= 0XFFF0FFFF;//PA4  PA5
	GPIOA->CRL |= 0X00000000;//模拟输入 但是STM32内部会连接在DAC模拟输出上
	
	DAC->CR |= 1<<0;//DAC1使能
	DAC->CR |= 0<<1;//DAC1输出缓存
	
	DAC->CR |= 1<<2;//使能DAC1触发 即3个APB1时钟周期DAC_DHRx传入DAC_DOR1
	
	DAC->CR |= 5<<3;//触发选择TIM4 TRGO 		使能DAC1触发后才有效
	
	DAC->CR |= 0<<6;//关闭波形发生
	DAC->CR |= 0<<8;//9<<8;//DAC1屏蔽幅值
	
	DAC->CR |= 1<<12;//DAC1 DMA使能


	
	DAC->DHR12R1 |= 0;//DAC1 12位 右对齐


//	DAC->CR |= 1<<16;
//	DAC->CR |= 1<<17;
//	DAC->CR |= 0<<18;
//	DAC->CR |= 0<<19;
//	DAC->CR |= 0<<21;
//	DAC->CR |= 0<<23;
//	DAC->CR |= 0<<27;
//	DAC->CR |= 0<<28;
//
//	DAC->DHR12R2 |= 0;	
}


//输出电压值
//vol:0~3000 代表 0~3.3V
void DAC1_set_vol(u16 vol)
{
	float temp = vol;
	temp = temp*(2*pow(2,0.5)/3.3);

	//temp /= 1000;
	//temp = temp*4096/3.3;
	DAC->DHR12R1=temp;
}

void DAC2_set_vol(u16 vol)
{
	float temp = vol;
	temp /= 1000;
	temp = temp*4096/3.3;
	DAC->DHR12R2=temp;
}

