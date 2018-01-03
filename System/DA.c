#include"DA.h"
#include "math.h"


//DA初始化
void DA_init(void)
{
	RCC->APB2ENR |= 1<<2;//使能PA时钟   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );
	RCC->APB1ENR |= 1<<29;//使能DAC时钟 RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );
	
	GPIOA->CRL &= 0XFFF0FFFF;//PA4  PA5
	GPIOA->CRL |= 0X00000000;//模拟输入 但是STM32内部会连接在DAC模拟输出上 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	
	DAC->CR |= 1<<0;//DAC1使能  
	DAC->CR |= 0<<1;//DAC1输出缓存
	
	DAC->CR |= 1<<2;//使能DAC1触发 即3个APB1时钟周期DAC_DHRx传入DAC_DOR1
	
	DAC->CR |= 5<<3;//触发选择TIM4 TRGO 		使能DAC1触发后才有效
	
	DAC->CR |= 0<<6;//关闭波形发生
	DAC->CR |= 0<<8;//9<<8;//DAC1屏蔽幅值
	
	DAC->CR |= 1<<12;//DAC1 DMA使能


	
	DAC->DHR12R1 |= 0;//DAC1 12位 右对齐  DAC_SetChannel1Data(DAC_Align_12b_R, 0);


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


/*库函数版本





    //DAC通道1输出初始化
    void Dac1_Init(void)
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        DAC_InitTypeDef DAC_InitType;
        
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );     //使能PORTA通道时钟
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );     //使能DAC通道时钟
        
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;                 // 端口配置
         GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;          //模拟输入
         GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
         GPIO_Init(GPIOA, &GPIO_InitStructure);
        GPIO_SetBits(GPIOA,GPIO_Pin_4)    ;//PA.4 输出高
        
        DAC_InitType.DAC_Trigger=DAC_Trigger_None;    //不使用出发功能 TEN1=0
        DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生器
        DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//屏蔽、幅值设置
        DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;    //DAC1输出缓存关闭 BOFF1=1
        DAC_Init(DAC_Channel_1,&DAC_InitType);     //初始化DAC通道1
        
        DAC_Cmd(DAC_Channel_1, ENABLE); //使能DAC1
        DAC_SetChannel1Data(DAC_Align_12b_R, 0); //12位左右对齐数据格式DAC值
    }


    //设置通道1输出电压
    //vol:0~3300,代表0~3.3V
    void Dac1_Set_Vol(u16 vol)
    {
        float temp=vol;
        temp/=1000;
        temp=temp*4096/3.3;
        DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12位右对齐数据格式设置DAC值
    }

*/
