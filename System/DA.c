#include"DA.h"
#include "math.h"


//DA��ʼ��
void DA_init(void)
{
	RCC->APB2ENR |= 1<<2;//ʹ��PAʱ��
	RCC->APB1ENR |= 1<<29;//ʹ��DACʱ��
	
	GPIOA->CRL &= 0XFFF0FFFF;//PA4  PA5
	GPIOA->CRL |= 0X00000000;//ģ������ ����STM32�ڲ���������DACģ�������
	
	DAC->CR |= 1<<0;//DAC1ʹ��
	DAC->CR |= 0<<1;//DAC1�������
	
	DAC->CR |= 1<<2;//ʹ��DAC1���� ��3��APB1ʱ������DAC_DHRx����DAC_DOR1
	
	DAC->CR |= 5<<3;//����ѡ��TIM4 TRGO 		ʹ��DAC1���������Ч
	
	DAC->CR |= 0<<6;//�رղ��η���
	DAC->CR |= 0<<8;//9<<8;//DAC1���η�ֵ
	
	DAC->CR |= 1<<12;//DAC1 DMAʹ��


	
	DAC->DHR12R1 |= 0;//DAC1 12λ �Ҷ���


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


//�����ѹֵ
//vol:0~3000 ���� 0~3.3V
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

