#include "AD.h"

void AD_init(void)
{
	RCC->APB2ENR |= 1<<2;//使能PORTA口时钟 
	GPIOA->CRL &=0XFFFF0000;//PA0 1 2 3输入
	RCC->APB2ENR |=1<<9;//ADC1时钟使能
	RCC->APB2RSTR |=1<<9;//ADC1复位
	RCC->APB2RSTR &=~(1<<9);
	RCC->CFGR &=~(3<<14);//分频因子清零
	RCC->CFGR |= 1<<14 | 1<<15;//SYSCLK/DIV2=12M ADC时钟设置为12M,最大不能超过14M准确度下降
	
	ADC1->CR1=0;//独立工作模式 非扫描模式
	ADC1->CR2 |= 0<<1;//单次转换模式
	ADC1->CR2 |= 1<<19 | 1<<18 | 1<<17;//ADC触发配置SWSTART(软件控制)为启动转换外部事件 
	ADC1->CR2 |= 1<<20;//使用用外部触发(SWSTART)!!!	必须使用一个事件来触发
	ADC1->CR2 |= 0<<11;//右对齐
	
	ADC1->SQR1&=~(0XF<<20);//清除
	ADC1->SQR1&=0<<20;//1个转换在规则序列中 也就是只转换规则序列1 
	
	//设置通道0~3的采样时间
	ADC1->SMPR2&=0XFFFFF000;//通道0,1,2,3采样时间清空	  
	ADC1->SMPR2|=7<<9;      //通道3  239.5周期,提高采样时间可以提高精确度	 
	ADC1->SMPR2|=7<<6;      //通道2  239.5周期,提高采样时间可以提高精确度	 
	ADC1->SMPR2|=7<<3;      //通道1  239.5周期,提高采样时间可以提高精确度	 
	ADC1->SMPR2|=7<<0;      //通道0  239.5周期,提高采样时间可以提高精确度
	
	ADC1->CR2 |= 1<<0;//开启AD转换
	ADC1->CR2 |= 1<<3;//使能复位校准 
	while(ADC1->CR2&1<<3);//等待校准结束
	ADC1->CR2 |= 1<<2;//开启AD校准
	while(ADC1->CR2&1<<2);  //等待校准结束	
}

//获得ADC值
//ch:通道值 0~3
u16 AD_get(u8 ch)
{
	//设置转换序列
	ADC1->SQR3&=0XFFFFFFE0;//把规则序列1 SQ1[0:4]清零 
	ADC1->SQR3|=ch;//把要转换的通道ch给SQ1
	ADC1->CR2|=1<<22;//开始转换
	while(!(ADC1->SR&1<<1));//等待转换结束
	return ADC1->DR;//返回adc值		
}





















