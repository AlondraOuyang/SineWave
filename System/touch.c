#include "touch.h"
Pen_typedef Pen_Point;
//SPI写数据
void touch_wr_byte(u8 com)
{
	u8 count=0;
	for(count=0;count<8;count++)
	{
		if(com&0x80)TDIN=1; //PC3 MOSI
		else TDIN=0;
		com<<=1;
		TCLK=0;TCLK=1;//上升沿有效  读取总线数据
	}
}

//SPI读数据 
u16 touch_re_byte(u8 com)
{
	u8 count=0;
	u16 num=0;
	TCLK=0;TCS=0;
	touch_wr_byte(com);
	delay_us(6);
	TCLK=1;
	TCLK=0;
	for(count=0;count<15;count++)
	{
		num<<=1;
		TCLK=1;TCLK=0;//下降沿有效 
		if(DOUT)num++;	
	}
	num>>=3;
	TCS=1;//释放ADS7843	
	return(num);
}
//为读取坐标准备1
//进行一次读X或Y坐标的操作
//读取一个坐标值 连续取值15次再升序排列
//去掉最低和最高取平均值
//com控制读X或者Y
u16 touch_re_xy1(u8 com)
{
	u16 i, j;
	u16 buf[15];
	u16 sum=0;
	u16 temp;
	for(i=0;i<15;i++)
	{
		buf[i]=touch_re_byte(com);
	}
	for(i=0;i<14;i++)
	{
		for(j=i+1;j<15;j++)
		{
			if(buf[i] > buf[j])
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}
	sum=0;
	for(i=5;i<10;i++) sum+=buf[i];
	temp = sum / 5;
	return temp;	
}
//为读取坐标准备2
//滤波坐标读取 最小值不能少于100
u8 touch_re_xy2(u16 *x, u16 *y)
{
	u16 xtemp,ytemp;			 	 		  
	xtemp=touch_re_xy1(CMD_RDY);//0B10010000即用差分方式读X坐标
	ytemp=touch_re_xy1(CMD_RDX);//0B11010000即用差分方式读Y坐标	  												   
	if(xtemp<100||ytemp<100)return 0;//读数失败
	*x=xtemp;
	*y=ytemp;
	return 1;//读数成功
}

//读取坐标 2次读取有效值 偏差不能小于50
u8 touch_re_xy(u16 *x, u16 *y)
{
	u16 x1,y1;
 	u16 x2,y2;
 	u8 flag;    
    flag=touch_re_xy2(&x1,&y1);   
    if(flag == 0) return(0);
    flag=touch_re_xy2(&x2,&y2);	   
    if(flag==0)return(0);   
    if(((x2<=x1&&x1<x2+50)||(x1<=x2&&x2<x1+50))//前后两次采样在+-50内
    &&((y2<=y1&&y1<y2+50)||(y1<=y2&&y2<y1+50)))
    {
        *x=(x1+x2)/2;
        *y=(y1+y2)/2;
        return 1;
    }
	else return 0;	 
}
//得到一次坐标值 
void touch_get_xy(void)
{
	if(touch_re_xy(&Pen_Point.X, &Pen_Point.Y))//如果读取正确返回为1
	{
		Pen_Point.X0=Pen_Point.xfac*Pen_Point.X+Pen_Point.xoff;	
		Pen_Point.Y0=Pen_Point.yfac*Pen_Point.Y+Pen_Point.yoff;
	}
}

//触屏初始化
void touch_Init(void)
{
	//注意,时钟使能之后,对GPIO的操作才有效
	//所以上拉之前,必须使能时钟.才能实现真正的上拉输出
	RCC->APB2ENR|=1<<3;    //PB时钟使能	   
	RCC->APB2ENR|=1<<0;    //开启辅助时钟							  
	GPIOB->CRH&=0XF00F00FF;//PB10 11 13 14
	GPIOB->CRH|=0X03308800;
	 
	GPIOB->CRH&=0XFFF0FFFF;//PB12
	GPIOB->CRH|=0X00030000;//PB12推挽输出 
	GPIOB->ODR|=0X7C00;    //PB10~14 全部上拉	   
 	touch_re_xy(&Pen_Point.X,&Pen_Point.Y);//第一次读取初始化			 
	MY_NVIC_Init(2,0,EXTI15_10_IRQChannel,2);	 
	RCC->APB2ENR|=0x01;    //使能io复用时钟	    
    AFIO->EXTICR[2]|=0X0100; //EXTI10映射到PB10   
	EXTI->IMR|=1<<10;        //开启line10上的中断
	EXTI->EMR|=1<<10;        //不屏蔽line10上的事件
	EXTI->FTSR|=1<<10;       //line10上事件下降沿触发
//	NVIC->ISER[0] = (u32)(1 << 7);//开中断
	touch_adj();	
} 

//当屏幕被按下时置标志位
void EXTI15_10_IRQHandler(void)
{
	Pen_Point.Key_Sta=0x01;
	EXTI->PR=1<<10;
}
//收到一次按下关掉后等处理完了 在开启接收第二次
void Pen_Int_set(u8 en)
{
	if(en)EXTI->IMR|=1<<10;   //开启line1上的中断	  	
	else EXTI->IMR&=~(1<<10); //关闭line1上的中断	
}

//采用默认校准值
void touch_adj(void)
{
	u16 pos_temp[4][2];

	pos_temp[0][0] = 537;
	pos_temp[0][1] = 414;
	pos_temp[1][0] = 3590;
	pos_temp[1][1] = 413;
	pos_temp[2][0] = 514;
	pos_temp[2][1] = 3541;
	pos_temp[3][0] = 3538;
	pos_temp[3][1] = 3497;

	Pen_Point.xfac = (float)280/(pos_temp[0][1] - pos_temp[2][1]);//得到xfac		 
	Pen_Point.xoff = (320 - Pen_Point.xfac*(pos_temp[2][1] + pos_temp[0][1]))/2;//得到xoff
		  
	Pen_Point.yfac = (float)200/(pos_temp[3][0] - pos_temp[2][0]);//得到yfac
	Pen_Point.yoff = (240 - Pen_Point.yfac*(pos_temp[3][0] + pos_temp[2][0]))/2;//得到yoff
}

