#include "DMA.h"
#include "delay.h"

u16 DAM1_LEN;//DMA每次数据传送的长度(0~65535)
//DMA1的各通道配置
//这里的传输形式是固定的,这点要根据不同的情况来修改
//从存储器->外设模式/8位数据宽度/存储器增量模式
//DMA_CHx:DMA通道CHx       DMA1_Channel1~7都有
//cpar:外设地址
//cmar:存储器地址
//cndtr:数据传输量  
void DMA1_config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{
 	RCC->AHBENR|=1<<0;		//开启DMA1时钟
 	delay_ms(1);			//等待DMA时钟稳定
 	DMA_CHx->CPAR=cpar;  	//DMA1 外设地址 
	DMA_CHx->CMAR=(u32)cmar;//DMA1,存储器地址
	DAM1_LEN=cndtr;     //保存DMA传输数据量
	DMA_CHx->CNDTR=cndtr;   //DMA1,传输数据量
	DMA_CHx->CCR=0X00000000;//复位
	DMA_CHx->CCR|=1<<4;  //从存储器读
	DMA_CHx->CCR|=1<<5;  //循环模式
	DMA_CHx->CCR|=0<<6;  //外设地址非增量模式
	DMA_CHx->CCR|=1<<7;  //存储器增量模式
	DMA_CHx->CCR|=2<<8;  //外设数据宽度为32位
	DMA_CHx->CCR|=2<<10; //存储器数据宽度32位
	DMA_CHx->CCR|=2<<12; //中等优先级
	
	DMA_CHx->CCR|=0<<14; //非存储器到存储器模式
	
	DMA_CHx->CCR|=1<<0;          //开启DMA传输


}

void DMA1_enable(DMA_Channel_TypeDef*DMA_CHx)
{
	DMA_CHx->CCR&=~(1<<0);       //关闭DMA传输 
	DMA_CHx->CNDTR=DAM1_LEN; //DMA1,传输数据量 
	DMA_CHx->CCR|=1<<0;          //开启DMA传输	
}



