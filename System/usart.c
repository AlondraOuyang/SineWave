#include "usart.h"

//#ifdef EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[64];     //接收缓冲,最大64个字节//对应
//接收状态
//bit7，接收完成标志
//bit6，接收到0x0d
//bit5~0，接收到的有效字节数目
u8 USART_RX_STA=0;       //接收状态标记	  
  
void USART1_IRQHandler(void)
{
	u8 res;	    
	if(USART1->SR&(1<<5))//接收到数据 //串口中断接收到数据
	{	 
		res=USART1->DR; 
		if((USART_RX_STA&0x80)==0)//接收未完成  //第一次进入的时候USART_RX_STA=0&后还为0 进入下面if
		{
			if(USART_RX_STA&0x40)//接收到了0x0d //第一次为0跳过 进入else
			{
				if(res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
				else USART_RX_STA|=0x80;	//接收完成了	//接收到了0X0A 标志接收完成 在主函数里if(USART_RX_STA&0x80)后再把if(USART_RX_STA&0x80)清零 
			}else //还没收到0X0D
			{	
				if(res==0x0d)USART_RX_STA|=0x40;//接收到回车的第一个0X0D 使能USART_RX_STA的接收位bit6
				else//第一次还没收到回车钱  只进入此接收到数据把数据放在USART_RX_STA的bit5~0
				{
					USART_RX_BUF[USART_RX_STA&0X3F]=res;
					USART_RX_STA++;
					if(USART_RX_STA>63)USART_RX_STA=0;//接收数据错误,重新开始接收//大于接收数据的USART_RX_STA最大范围	  
				}		 
			}
		}
		//USART1->SR &= ~(1<<5); 		 									     
	}  											 
} 
//#endif

//初始化IO 串口1
//pclk2:PCLK2时钟频率(Mhz)
//bound:波特率
//CHECK OK
//091209
void uart_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //使能PORTA口时钟  
	RCC->APB2ENR|=1<<14;  //使能串口时钟 
	GPIOA->CRH&=0XFFFFF00F; 
	GPIOA->CRH|=0X000008B0;//IO状态设置    其中TXD复用是由于外设GPIO配置固定决定的
	
	RCC->APB2RSTR|=1<<14;   //复位串口1
	RCC->APB2RSTR&=~(1<<14);//停止复位	   	   
	//波特率设置
 	USART1->BRR=mantissa; // 波特率设置	 
	USART1->CR1|=0X200C;  //1位停止,无校验位.
//#ifdef EN_USART1_RX		  //如果使能了接收
	//使能接收中断
	USART1->CR1|=1<<8;    //PE中断使能
	USART1->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
	MY_NVIC_Init(3,3,USART1_IRQChannel,2);//组2，最低优先级 
//#endif
}

//发发送字符
void send(u8 data)
{
	while((USART1->SR &(1<<6)==0));
	USART1->DR =data;
}
//发送字符串
void sendstring(u8 *str)
{
	while(*str != '\0')
	{
		send(*str++);
	}
}
