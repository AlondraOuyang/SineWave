#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"		
#include "delay.h"		 	 
#include "TFT.h"
#include "AD.h"
#include "DA.h"
#include "timer.h"
#include "DMA.h"
#include "math.h"
#include "Sine.h"
#include "touch.h"

#define DAC_DHR12R1_Address		0x40007408//0x40007400+0x08
//void change_vol(void);

u8 idex;
u8 i;

int main(void)
{			
	u16 sin_arr,sin_psc;
	u32 fre;
	
	u8 sin_num;	
	Stm32_Clock_Init(9); 	//系统时钟设置
	delay_Init(72);	     	//延时初始化
	//uart_init(72,9600);		//串口初始化
	DA_init();
	LCD_Init();
	touch_Init();

	sin_psc = 9;
	
	fre = 2100;
	//sin_num=100;
	//num = fre / 100;
	//num = 100 - num;
	Set_Fre(fre);
	
	//sin_arr=72000000/(100*fre*(sin_psc+1));
	//Timerx_Init(sin_arr,sin_psc);
	//Timerx_Init(sin_arr,9);	//10us
	//DMA1_config(DMA1_Channel7,(u32)&DAC->DHR12R1,(u32)Sine40,40);//(u32)&DAC->DHR12R1	



	//fre = Get_Sin_Table_Set_Fre(num);
	//fre=sin_table[num].Set_Fre;
	
	//	sin_num = Get_Sin_Table_Num(num);

	//*sin_address = Get_Sin_Table_Address(num);


	
	
	
	
	
	draw_rectangle(0,0,30,30,RED);//+1
	showstring(1,1,"+1",RED,YELLOW);

	draw_rectangle(50,0,80,30,RED);//+10
	showstring(51,1,"+10",RED,YELLOW);

	draw_rectangle(100,0,130,30,RED);//+100
	showstring(101,1,"+100",RED,YELLOW);

	draw_rectangle(150,0,180,30,RED);//+1000
	showstring(151,1,"+1000",RED,YELLOW);


	draw_rectangle(0,50,30,80,RED);//-1
	showstring(1,51,"-1",RED,YELLOW);

	draw_rectangle(50,50,80,80,RED);//-10
	showstring(51,51,"-10",RED,YELLOW);

	draw_rectangle(100,50,130,80,RED);//-100
	showstring(101,51,"-100",RED,YELLOW);

	draw_rectangle(150,50,180,80,RED);//-1000
	showstring(151,51,"-1000",RED,YELLOW);

	draw_rectangle(0,150,20,180,RED);//100 biao
	showstring(1,151,"1",RED,YELLOW);
	
	draw_rectangle(20,150,40,180,RED);//90 biao
	showstring(21,151,"2",RED,YELLOW);
	
	draw_rectangle(40,150,60,180,RED);//80 biao
	showstring(41,151,"3",RED,YELLOW);
	
	draw_rectangle(60,150,80,180,RED);//70 biao
	showstring(61,151,"4",RED,YELLOW);
	
	draw_rectangle(80,150,100,180,RED);//60 biao
	showstring(81,151,"5",RED,YELLOW);
	
	draw_rectangle(120,150,140,180,RED);//50 biao
	showstring(121,151,"6",RED,YELLOW);
	
	draw_rectangle(140,150,160,180,RED);//40 biao
	showstring(141,151,"7",RED,YELLOW);
	
	draw_rectangle(160,150,180,180,RED);//30 biao
	showstring(161,151,"8",RED,YELLOW);
	
	draw_rectangle(180,150,200,180,RED);//20 biao
	showstring(181,151,"9",RED,YELLOW);
	
	draw_rectangle(200,150,220,180,RED);//10 biao
	showstring(201,151,"10",RED,YELLOW);


	
	while(1)
	{
		if(Pen_Point.Key_Sta==1)
			{
				Pen_Int_set(0);//关闭中断
				//showstring(10,10,"HELLO",BLACK,WHITE);
				do
				{
					touch_get_xy();
					Pen_Point.Key_Sta=0;
					shownum(100,100,Pen_Point.X0,4,16,BLACK,LBBLUE);//显示数值
					shownum(100,120,Pen_Point.Y0,4,16,BLACK,LBBLUE);//显示数值
					if(Pen_Point.X0>0&&Pen_Point.X0<30&&Pen_Point.Y0>0&&Pen_Point.Y0<30)
					{
						while(PEN==0);
						fre=fre+1;
						sin_arr=(72000000/sin_num)/fre/(sin_psc+1);
						Timerx_Init(sin_arr,sin_psc);
						//fill(50,50,80,80,BLACK);						
					}
					if(Pen_Point.X0>50&&Pen_Point.X0<80&&Pen_Point.Y0>0&&Pen_Point.Y0<30)
					{
						while(PEN==0);
						fre=fre+10;
						sin_arr=(72000000/sin_num)/fre/(sin_psc+1);
						Timerx_Init(sin_arr,sin_psc);
						//fill(50,50,80,80,RED);						
					}
					if(Pen_Point.X0>100&&Pen_Point.X0<130&&Pen_Point.Y0>0&&Pen_Point.Y0<30)
					{
						while(PEN==0);
						fre=fre+100;
						//num = fre / 100;
						//num = 100 - num;
						//Set_Fre(num);
						Set_Fre(fre);
						//fill(50,50,80,80,RED);						
					}
					if(Pen_Point.X0>150&&Pen_Point.X0<180&&Pen_Point.Y0>0&&Pen_Point.Y0<30)
					{
						while(PEN==0);
						fre=fre+1000;
						sin_arr=(72000000/sin_num)/fre/(sin_psc+1);
						Timerx_Init(sin_arr,sin_psc);
						//fill(50,50,80,80,RED);						
					}


					if(Pen_Point.X0>0&&Pen_Point.X0<30&&Pen_Point.Y0>50&&Pen_Point.Y0<80)
					{
						while(PEN==0);
						fre=fre-1;
						sin_arr=(72000000/sin_num)/fre/(sin_psc+1);
						Timerx_Init(sin_arr,sin_psc);
						//fill(50,50,80,80,BLACK);						
					}
					if(Pen_Point.X0>50&&Pen_Point.X0<80&&Pen_Point.Y0>50&&Pen_Point.Y0<80)
					{
						while(PEN==0);
						fre=fre-10;
						sin_arr=(72000000/sin_num)/fre/(sin_psc+1);
						Timerx_Init(sin_arr,sin_psc);
						//fill(50,50,80,80,RED);						
					}
					if(Pen_Point.X0>100&&Pen_Point.X0<130&&Pen_Point.Y0>50&&Pen_Point.Y0<80)
					{
						while(PEN==0);
						fre=fre-100;
						//num = fre / 100;
						//num = 100 - num;
						Set_Fre(fre);
						//fill(50,50,80,80,RED);						
					}
					if(Pen_Point.X0>150&&Pen_Point.X0<180&&Pen_Point.Y0>50&&Pen_Point.Y0<80)
					{
						while(PEN==0);
						fre=fre-1000;
						sin_arr=(72000000/sin_num)/fre/(sin_psc+1);
						Timerx_Init(sin_arr,sin_psc);
						//fill(50,50,80,80,RED);						
					}
//					if(Pen_Point.X0>0&&Pen_Point.X0<20&&Pen_Point.Y0>150&&Pen_Point.Y0<180)//1
//					{
//						while(PEN==0);
//						//fre=fre-1000;
//						//sin_arr=(72000000/sin_num)/fre/(sin_psc+1);
//						DMA1_Channel7->CCR&=~(1<<0);       //关闭DMA传输
//						DMA1_config(DMA1_Channel7,(u32)&DAC->DHR12R1,(u32)Sine10,10);//(u32)&DAC->DHR12R1	
//						Timerx_Init(sin_arr,sin_psc);shownum(100,200,1,4,16,RED,YELLOW);	
//						//fill(50,50,80,80,RED);											
//					}
//					if(Pen_Point.X0>20&&Pen_Point.X0<40&&Pen_Point.Y0>150&&Pen_Point.Y0<180)//2
//					{
//						while(PEN==0);
//						//fre=fre-1000;
//						//sin_arr=(72000000/sin_num)/fre/(sin_psc+1)
//						DMA1_Channel7->CCR&=~(1<<0);       //关闭DMA传输;
//						DMA1_config(DMA1_Channel7,(u32)&DAC->DHR12R1,(u32)Sine20,20);//(u32)&DAC->DHR12R1	
//						Timerx_Init(sin_arr,sin_psc);shownum(100,200,2,4,16,RED,YELLOW);
//						//fill(50,50,80,80,RED);						
//					}
//					if(Pen_Point.X0>40&&Pen_Point.X0<60&&Pen_Point.Y0>150&&Pen_Point.Y0<180)//3
//					{
//						while(PEN==0);
//						//fre=fre-1000;
//						//sin_arr=(72000000/sin_num)/fre/(sin_psc+1);
//						DMA1_Channel7->CCR&=~(1<<0);       //关闭DMA传输
//						DMA1_config(DMA1_Channel7,(u32)&DAC->DHR12R1,(u32)Sine30,30);//(u32)&DAC->DHR12R1	
//						Timerx_Init(sin_arr,sin_psc);shownum(100,200,3,4,16,RED,YELLOW);
//						//fill(50,50,80,80,RED);						
//					}
//					if(Pen_Point.X0>60&&Pen_Point.X0<80&&Pen_Point.Y0>150&&Pen_Point.Y0<180)//4
//					{
//						while(PEN==0);
//						//fre=fre-1000;
//						//sin_arr=(72000000/sin_num)/fre/(sin_psc+1);
//						DMA1_Channel7->CCR&=~(1<<0);       //关闭DMA传输
//						DMA1_config(DMA1_Channel7,(u32)&DAC->DHR12R1,(u32)Sine40,40);//(u32)&DAC->DHR12R1	
//						Timerx_Init(sin_arr,sin_psc);shownum(100,200,4,4,16,RED,YELLOW);
//						//fill(50,50,80,80,RED);						
//					}
//					if(Pen_Point.X0>80&&Pen_Point.X0<100&&Pen_Point.Y0>150&&Pen_Point.Y0<180)//5
//					{
//						while(PEN==0);
//						//fre=fre-1000;
//						//sin_arr=(72000000/sin_num)/fre/(sin_psc+1);
//						DMA1_Channel7->CCR&=~(1<<0);       //关闭DMA传输
//						DMA1_config(DMA1_Channel7,(u32)&DAC->DHR12R1,(u32)Sine50,50);//(u32)&DAC->DHR12R1	
//						Timerx_Init(sin_arr,sin_psc);shownum(100,200,5,4,16,RED,YELLOW);
//						//fill(50,50,80,80,RED);						
//					}
//					if(Pen_Point.X0>120&&Pen_Point.X0<140&&Pen_Point.Y0>150&&Pen_Point.Y0<180)//6
//					{
//						while(PEN==0);
//						//fre=fre-1000;
//						//sin_arr=(72000000/sin_num)/fre/(sin_psc+1);
//						DMA1_Channel7->CCR&=~(1<<0);       //关闭DMA传输
//						DMA1_config(DMA1_Channel7,(u32)&DAC->DHR12R1,(u32)Sine61,61);//(u32)&DAC->DHR12R1	
//						Timerx_Init(sin_arr,sin_psc);shownum(100,200,6,4,16,RED,YELLOW);
//						//fill(50,50,80,80,RED);						
//					}
//					if(Pen_Point.X0>140&&Pen_Point.X0<160&&Pen_Point.Y0>150&&Pen_Point.Y0<180)//7
//					{
//						while(PEN==0);
//						//fre=fre-1000;
//						//sin_arr=(72000000/sin_num)/fre/(sin_psc+1);
//						DMA1_Channel7->CCR&=~(1<<0);       //关闭DMA传输
//						DMA1_config(DMA1_Channel7,(u32)&DAC->DHR12R1,(u32)Sine70,70);//(u32)&DAC->DHR12R1	
//						Timerx_Init(sin_arr,sin_psc);shownum(100,200,7,4,16,RED,YELLOW);
//						//fill(50,50,80,80,RED);						
//					}
//					if(Pen_Point.X0>160&&Pen_Point.X0<180&&Pen_Point.Y0>150&&Pen_Point.Y0<180)//8
//					{
//						while(PEN==0);
//						//fre=fre-1000;
//						//sin_arr=(72000000/sin_num)/fre/(sin_psc+1);
//						DMA1_Channel7->CCR&=~(1<<0);       //关闭DMA传输
//						DMA1_config(DMA1_Channel7,(u32)&DAC->DHR12R1,(u32)Sine80,80);//(u32)&DAC->DHR12R1	
//						Timerx_Init(sin_arr,sin_psc);shownum(100,200,8,4,16,RED,YELLOW);
//						//fill(50,50,80,80,RED);						
//					}
//					if(Pen_Point.X0>180&&Pen_Point.X0<200&&Pen_Point.Y0>150&&Pen_Point.Y0<180)//9
//					{
//						while(PEN==0);
//						//fre=fre-1000;
//						//sin_arr=(72000000/sin_num)/fre/(sin_psc+1);
//						DMA1_Channel7->CCR&=~(1<<0);       //关闭DMA传输
//						DMA1_config(DMA1_Channel7,(u32)&DAC->DHR12R1,(u32)Sine90,90);//(u32)&DAC->DHR12R1	
//						Timerx_Init(sin_arr,sin_psc);shownum(100,200,9,4,16,RED,YELLOW);
//						//fill(50,50,80,80,RED);						
//					}
//					if(Pen_Point.X0>200&&Pen_Point.X0<220&&Pen_Point.Y0>150&&Pen_Point.Y0<180)//10
//					{
//						while(PEN==0);
//						//fre=fre-1000;
//						//sin_arr=(72000000/sin_num)/fre/(sin_psc+1);
//						DMA1_Channel7->CCR&=~(1<<0);       //关闭DMA传输
//						DMA1_config(DMA1_Channel7,(u32)&DAC->DHR12R1,(u32)Sine100,100);//(u32)&DAC->DHR12R1	
//						Timerx_Init(sin_arr,sin_psc);shownum(100,200,10,4,16,RED,YELLOW);
//						//fill(50,50,80,80,RED);						
//					}
					shownum(5,200,fre,5,16,RED,YELLOW);
				}while(PEN==0);
				Pen_Int_set(1);//开启中断
			}
			else delay_ms(1);
		}	

}


//void change_vol(void)
//{
//	for(idex=0;idex<128;idex++)
//	{
////		Sine12bit[idex]	= Sine12bit[idex]*(2*pow(2,0.5)/3.3);
//	}
//}
























