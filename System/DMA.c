#include "DMA.h"
#include "delay.h"

u16 DAM1_LEN;//DMAÿ�����ݴ��͵ĳ���(0~65535)
//DMA1�ĸ�ͨ������
//����Ĵ�����ʽ�ǹ̶���,���Ҫ���ݲ�ͬ��������޸�
//�Ӵ洢��->����ģʽ/8λ���ݿ��/�洢������ģʽ
//DMA_CHx:DMAͨ��CHx       DMA1_Channel1~7����
//cpar:�����ַ
//cmar:�洢����ַ
//cndtr:���ݴ�����  
void DMA1_config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{
 	RCC->AHBENR|=1<<0;		//����DMA1ʱ��
 	delay_ms(1);			//�ȴ�DMAʱ���ȶ�
 	DMA_CHx->CPAR=cpar;  	//DMA1 �����ַ 
	DMA_CHx->CMAR=(u32)cmar;//DMA1,�洢����ַ
	DAM1_LEN=cndtr;     //����DMA����������
	DMA_CHx->CNDTR=cndtr;   //DMA1,����������
	DMA_CHx->CCR=0X00000000;//��λ
	DMA_CHx->CCR|=1<<4;  //�Ӵ洢����
	DMA_CHx->CCR|=1<<5;  //ѭ��ģʽ
	DMA_CHx->CCR|=0<<6;  //�����ַ������ģʽ
	DMA_CHx->CCR|=1<<7;  //�洢������ģʽ
	DMA_CHx->CCR|=2<<8;  //�������ݿ��Ϊ32λ
	DMA_CHx->CCR|=2<<10; //�洢�����ݿ��32λ
	DMA_CHx->CCR|=2<<12; //�е����ȼ�
	
	DMA_CHx->CCR|=0<<14; //�Ǵ洢�����洢��ģʽ
	
	DMA_CHx->CCR|=1<<0;          //����DMA����


}

void DMA1_enable(DMA_Channel_TypeDef*DMA_CHx)
{
	DMA_CHx->CCR&=~(1<<0);       //�ر�DMA���� 
	DMA_CHx->CNDTR=DAM1_LEN; //DMA1,���������� 
	DMA_CHx->CCR|=1<<0;          //����DMA����	
}



