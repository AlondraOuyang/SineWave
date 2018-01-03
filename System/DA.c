#include"DA.h"
#include "math.h"


//DA��ʼ��
void DA_init(void)
{
	RCC->APB2ENR |= 1<<2;//ʹ��PAʱ��   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );
	RCC->APB1ENR |= 1<<29;//ʹ��DACʱ�� RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );
	
	GPIOA->CRL &= 0XFFF0FFFF;//PA4  PA5
	GPIOA->CRL |= 0X00000000;//ģ������ ����STM32�ڲ���������DACģ������� GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	
	DAC->CR |= 1<<0;//DAC1ʹ��  
	DAC->CR |= 0<<1;//DAC1�������
	
	DAC->CR |= 1<<2;//ʹ��DAC1���� ��3��APB1ʱ������DAC_DHRx����DAC_DOR1
	
	DAC->CR |= 5<<3;//����ѡ��TIM4 TRGO 		ʹ��DAC1���������Ч
	
	DAC->CR |= 0<<6;//�رղ��η���
	DAC->CR |= 0<<8;//9<<8;//DAC1���η�ֵ
	
	DAC->CR |= 1<<12;//DAC1 DMAʹ��


	
	DAC->DHR12R1 |= 0;//DAC1 12λ �Ҷ���  DAC_SetChannel1Data(DAC_Align_12b_R, 0);


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


/*�⺯���汾





    //DACͨ��1�����ʼ��
    void Dac1_Init(void)
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        DAC_InitTypeDef DAC_InitType;
        
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );     //ʹ��PORTAͨ��ʱ��
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );     //ʹ��DACͨ��ʱ��
        
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;                 // �˿�����
         GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;          //ģ������
         GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
         GPIO_Init(GPIOA, &GPIO_InitStructure);
        GPIO_SetBits(GPIOA,GPIO_Pin_4)    ;//PA.4 �����
        
        DAC_InitType.DAC_Trigger=DAC_Trigger_None;    //��ʹ�ó������� TEN1=0
        DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//��ʹ�ò��η�����
        DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//���Ρ���ֵ����
        DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;    //DAC1�������ر� BOFF1=1
        DAC_Init(DAC_Channel_1,&DAC_InitType);     //��ʼ��DACͨ��1
        
        DAC_Cmd(DAC_Channel_1, ENABLE); //ʹ��DAC1
        DAC_SetChannel1Data(DAC_Align_12b_R, 0); //12λ���Ҷ������ݸ�ʽDACֵ
    }


    //����ͨ��1�����ѹ
    //vol:0~3300,����0~3.3V
    void Dac1_Set_Vol(u16 vol)
    {
        float temp=vol;
        temp/=1000;
        temp=temp*4096/3.3;
        DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12λ�Ҷ������ݸ�ʽ����DACֵ
    }

*/
