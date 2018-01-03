#include "touch.h"
Pen_typedef Pen_Point;
//SPIд����
void touch_wr_byte(u8 com)
{
	u8 count=0;
	for(count=0;count<8;count++)
	{
		if(com&0x80)TDIN=1; //PC3 MOSI
		else TDIN=0;
		com<<=1;
		TCLK=0;TCLK=1;//��������Ч  ��ȡ��������
	}
}

//SPI������ 
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
		TCLK=1;TCLK=0;//�½�����Ч 
		if(DOUT)num++;	
	}
	num>>=3;
	TCS=1;//�ͷ�ADS7843	
	return(num);
}
//Ϊ��ȡ����׼��1
//����һ�ζ�X��Y����Ĳ���
//��ȡһ������ֵ ����ȡֵ15������������
//ȥ����ͺ����ȡƽ��ֵ
//com���ƶ�X����Y
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
//Ϊ��ȡ����׼��2
//�˲������ȡ ��Сֵ��������100
u8 touch_re_xy2(u16 *x, u16 *y)
{
	u16 xtemp,ytemp;			 	 		  
	xtemp=touch_re_xy1(CMD_RDY);//0B10010000���ò�ַ�ʽ��X����
	ytemp=touch_re_xy1(CMD_RDX);//0B11010000���ò�ַ�ʽ��Y����	  												   
	if(xtemp<100||ytemp<100)return 0;//����ʧ��
	*x=xtemp;
	*y=ytemp;
	return 1;//�����ɹ�
}

//��ȡ���� 2�ζ�ȡ��Чֵ ƫ���С��50
u8 touch_re_xy(u16 *x, u16 *y)
{
	u16 x1,y1;
 	u16 x2,y2;
 	u8 flag;    
    flag=touch_re_xy2(&x1,&y1);   
    if(flag == 0) return(0);
    flag=touch_re_xy2(&x2,&y2);	   
    if(flag==0)return(0);   
    if(((x2<=x1&&x1<x2+50)||(x1<=x2&&x2<x1+50))//ǰ�����β�����+-50��
    &&((y2<=y1&&y1<y2+50)||(y1<=y2&&y2<y1+50)))
    {
        *x=(x1+x2)/2;
        *y=(y1+y2)/2;
        return 1;
    }
	else return 0;	 
}
//�õ�һ������ֵ 
void touch_get_xy(void)
{
	if(touch_re_xy(&Pen_Point.X, &Pen_Point.Y))//�����ȡ��ȷ����Ϊ1
	{
		Pen_Point.X0=Pen_Point.xfac*Pen_Point.X+Pen_Point.xoff;	
		Pen_Point.Y0=Pen_Point.yfac*Pen_Point.Y+Pen_Point.yoff;
	}
}

//������ʼ��
void touch_Init(void)
{
	//ע��,ʱ��ʹ��֮��,��GPIO�Ĳ�������Ч
	//��������֮ǰ,����ʹ��ʱ��.����ʵ���������������
	RCC->APB2ENR|=1<<3;    //PBʱ��ʹ��	   
	RCC->APB2ENR|=1<<0;    //��������ʱ��							  
	GPIOB->CRH&=0XF00F00FF;//PB10 11 13 14
	GPIOB->CRH|=0X03308800;
	 
	GPIOB->CRH&=0XFFF0FFFF;//PB12
	GPIOB->CRH|=0X00030000;//PB12������� 
	GPIOB->ODR|=0X7C00;    //PB10~14 ȫ������	   
 	touch_re_xy(&Pen_Point.X,&Pen_Point.Y);//��һ�ζ�ȡ��ʼ��			 
	MY_NVIC_Init(2,0,EXTI15_10_IRQChannel,2);	 
	RCC->APB2ENR|=0x01;    //ʹ��io����ʱ��	    
    AFIO->EXTICR[2]|=0X0100; //EXTI10ӳ�䵽PB10   
	EXTI->IMR|=1<<10;        //����line10�ϵ��ж�
	EXTI->EMR|=1<<10;        //������line10�ϵ��¼�
	EXTI->FTSR|=1<<10;       //line10���¼��½��ش���
//	NVIC->ISER[0] = (u32)(1 << 7);//���ж�
	touch_adj();	
} 

//����Ļ������ʱ�ñ�־λ
void EXTI15_10_IRQHandler(void)
{
	Pen_Point.Key_Sta=0x01;
	EXTI->PR=1<<10;
}
//�յ�һ�ΰ��¹ص���ȴ������� �ڿ������յڶ���
void Pen_Int_set(u8 en)
{
	if(en)EXTI->IMR|=1<<10;   //����line1�ϵ��ж�	  	
	else EXTI->IMR&=~(1<<10); //�ر�line1�ϵ��ж�	
}

//����Ĭ��У׼ֵ
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

	Pen_Point.xfac = (float)280/(pos_temp[0][1] - pos_temp[2][1]);//�õ�xfac		 
	Pen_Point.xoff = (320 - Pen_Point.xfac*(pos_temp[2][1] + pos_temp[0][1]))/2;//�õ�xoff
		  
	Pen_Point.yfac = (float)200/(pos_temp[3][0] - pos_temp[2][0]);//�õ�yfac
	Pen_Point.yoff = (240 - Pen_Point.yfac*(pos_temp[3][0] + pos_temp[2][0]))/2;//�õ�yoff
}

