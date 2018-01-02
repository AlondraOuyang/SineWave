#include "usart.h"

//#ifdef EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[64];     //���ջ���,���64���ֽ�//��Ӧ
//����״̬
//bit7��������ɱ�־
//bit6�����յ�0x0d
//bit5~0�����յ�����Ч�ֽ���Ŀ
u8 USART_RX_STA=0;       //����״̬���	  
  
void USART1_IRQHandler(void)
{
	u8 res;	    
	if(USART1->SR&(1<<5))//���յ����� //�����жϽ��յ�����
	{	 
		res=USART1->DR; 
		if((USART_RX_STA&0x80)==0)//����δ���  //��һ�ν����ʱ��USART_RX_STA=0&��Ϊ0 ��������if
		{
			if(USART_RX_STA&0x40)//���յ���0x0d //��һ��Ϊ0���� ����else
			{
				if(res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
				else USART_RX_STA|=0x80;	//���������	//���յ���0X0A ��־������� ����������if(USART_RX_STA&0x80)���ٰ�if(USART_RX_STA&0x80)���� 
			}else //��û�յ�0X0D
			{	
				if(res==0x0d)USART_RX_STA|=0x40;//���յ��س��ĵ�һ��0X0D ʹ��USART_RX_STA�Ľ���λbit6
				else//��һ�λ�û�յ��س�Ǯ  ֻ����˽��յ����ݰ����ݷ���USART_RX_STA��bit5~0
				{
					USART_RX_BUF[USART_RX_STA&0X3F]=res;
					USART_RX_STA++;
					if(USART_RX_STA>63)USART_RX_STA=0;//�������ݴ���,���¿�ʼ����//���ڽ������ݵ�USART_RX_STA���Χ	  
				}		 
			}
		}
		//USART1->SR &= ~(1<<5); 		 									     
	}  											 
} 
//#endif

//��ʼ��IO ����1
//pclk2:PCLK2ʱ��Ƶ��(Mhz)
//bound:������
//CHECK OK
//091209
void uart_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
	RCC->APB2ENR|=1<<14;  //ʹ�ܴ���ʱ�� 
	GPIOA->CRH&=0XFFFFF00F; 
	GPIOA->CRH|=0X000008B0;//IO״̬����    ����TXD��������������GPIO���ù̶�������
	
	RCC->APB2RSTR|=1<<14;   //��λ����1
	RCC->APB2RSTR&=~(1<<14);//ֹͣ��λ	   	   
	//����������
 	USART1->BRR=mantissa; // ����������	 
	USART1->CR1|=0X200C;  //1λֹͣ,��У��λ.
//#ifdef EN_USART1_RX		  //���ʹ���˽���
	//ʹ�ܽ����ж�
	USART1->CR1|=1<<8;    //PE�ж�ʹ��
	USART1->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
	MY_NVIC_Init(3,3,USART1_IRQChannel,2);//��2��������ȼ� 
//#endif
}

//�������ַ�
void send(u8 data)
{
	while((USART1->SR &(1<<6)==0));
	USART1->DR =data;
}
//�����ַ���
void sendstring(u8 *str)
{
	while(*str != '\0')
	{
		send(*str++);
	}
}
