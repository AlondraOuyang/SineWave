#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"		
#include "delay.h"		 	 
#include "AD.h"
#include "DA.h"
#include "timer.h"
#include "DMA.h"
#include "math.h"
#include "Sine.h"

#define DAC_DHR12R1_Address		0x40007408//0x40007400+0x08

u8 idex;
u8 i;

int main(void)
{			
	u16 sin_arr,sin_psc;
	u32 fre;
	
	u8 sin_num;	
	Stm32_Clock_Init(9); 	//系统时钟设置
	delay_Init(72);	     	//延时初始化
	DA_init();


	sin_psc = 9;
	
	fre = 2100;
	Set_Fre(fre);
	
	while(1)
	{
						fre=fre+1;
						sin_arr=(72000000/sin_num)/fre/(sin_psc+1);
						Timerx_Init(sin_arr,sin_psc);
						
						fre=fre+10;
						sin_arr=(72000000/sin_num)/fre/(sin_psc+1);
						Timerx_Init(sin_arr,sin_psc);
						
						fre=fre+100;
						Set_Fre(fre);
						fre=fre+1000;
						sin_arr=(72000000/sin_num)/fre/(sin_psc+1);
						Timerx_Init(sin_arr,sin_psc);
						fre=fre-1;
						sin_arr=(72000000/sin_num)/fre/(sin_psc+1);
						Timerx_Init(sin_arr,sin_psc);
						fre=fre-10;
						sin_arr=(72000000/sin_num)/fre/(sin_psc+1);
						Timerx_Init(sin_arr,sin_psc);
						fre=fre-100;
						Set_Fre(fre);
						fre=fre-1000;
						sin_arr=(72000000/sin_num)/fre/(sin_psc+1);
						Timerx_Init(sin_arr,sin_psc);
}
}
