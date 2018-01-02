#include "TFT.h"
#include "delay.h"
#include "font.h"
//MY LCD ID:9325

//д��ַ //д���ݵĺ������ں궨����LCD_WR_DATA IO�ڵ�д���ٶȱ��
void LCD_WR_COM(u8 data)
{
	LCD_RS_CLR;
	LCD_CS_CLR;
	GPIOC->ODR = data;
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CS_SET;
}

//д�Ĵ���
void LCD_WR_REG(u8 com, u16 data)
{
	LCD_WR_COM(com);
	LCD_WR_DATA(data);
}

//GRAMͼ��Ĵ���

//��ILI93xx����������ΪGBR��ʽ��������д���ʱ��ΪRGB��ʽ��
//ͨ���ú���ת��
//c:GBR��ʽ����ɫֵ
//����ֵ��RGB��ʽ����ɫֵ
u16 LCD_BGR2RGB(u16 c)
{
	u16  r,g,b,rgb;   
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);
}

//��ʼ��LCD MY LCD ID : 9325
void LCD_Init(void)
{
	RCC->APB2ENR|=1<<3;//��ʹ������PORTBʱ��
 	RCC->APB2ENR|=1<<4;//��ʹ������PORTCʱ��
	RCC->APB2ENR|=1<<0;    //��������ʱ��
	JTAG_Set(SWD_ENABLE);  //����SWD
	//PORTB5~9����������� 	
	GPIOB->CRH&=0XFFFFFF00;
	GPIOB->CRH|=0X00000033; 
	GPIOB->CRL&=0X000FFFFF;
	GPIOB->CRL|=0X33300000;  
	GPIOB->ODR|=0x03E0; 	 
	//PORTC ������� 	
	GPIOC->CRH=0X33333333;
	GPIOC->CRL=0X33333333; 	 
	GPIOC->ODR=0XFFFF;
	delay_ms(50); // delay 50 ms 
	LCD_WR_REG(0x0000,0x0001);
	delay_ms(50); 
	
	//DeviceCode = 9325ʱ�ĳ�ʼ��
	LCD_WR_REG(0x00E5,0x78F0); 
	LCD_WR_REG(0x0001,0x0100); 
	LCD_WR_REG(0x0002,0x0700); 
	LCD_WR_REG(0x0003,0x1030); 
	LCD_WR_REG(0x0004,0x0000); 
	LCD_WR_REG(0x0008,0x0202);  
	LCD_WR_REG(0x0009,0x0000);
	LCD_WR_REG(0x000A,0x0000); 
	LCD_WR_REG(0x000C,0x0000); 
	LCD_WR_REG(0x000D,0x0000);
	LCD_WR_REG(0x000F,0x0000);
	//power on sequence VGHVGL
	LCD_WR_REG(0x0010,0x0000);   
	LCD_WR_REG(0x0011,0x0007);  
	LCD_WR_REG(0x0012,0x0000);  
	LCD_WR_REG(0x0013,0x0000); 
	LCD_WR_REG(0x0007,0x0000); 
	//vgh 
	LCD_WR_REG(0x0010,0x1690);   
	LCD_WR_REG(0x0011,0x0227);
	//delayms(100);
	//vregiout 
	LCD_WR_REG(0x0012,0x009D); //0x001b
	//delayms(100); 
	//vom amplitude
	LCD_WR_REG(0x0013,0x1900);
	//delayms(100); 
	//vom H
	LCD_WR_REG(0x0029,0x0025); 
	LCD_WR_REG(0x002B,0x000D); 
	//gamma
	LCD_WR_REG(0x0030,0x0007);
	LCD_WR_REG(0x0031,0x0303);
	LCD_WR_REG(0x0032,0x0003);// 0006
	LCD_WR_REG(0x0035,0x0206);
	LCD_WR_REG(0x0036,0x0008);
	LCD_WR_REG(0x0037,0x0406); 
	LCD_WR_REG(0x0038,0x0304);//0200
	LCD_WR_REG(0x0039,0x0007); 
	LCD_WR_REG(0x003C,0x0602);// 0504
	LCD_WR_REG(0x003D,0x0008); 
	//ram
	LCD_WR_REG(0x0050,0x0000); 
	LCD_WR_REG(0x0051,0x00EF);
	LCD_WR_REG(0x0052,0x0000); 
	LCD_WR_REG(0x0053,0x013F);  
	LCD_WR_REG(0x0060,0xA700); 
	LCD_WR_REG(0x0061,0x0001); 
	LCD_WR_REG(0x006A,0x0000); 
	//
	LCD_WR_REG(0x0080,0x0000); 
	LCD_WR_REG(0x0081,0x0000); 
	LCD_WR_REG(0x0082,0x0000); 
	LCD_WR_REG(0x0083,0x0000); 
	LCD_WR_REG(0x0084,0x0000); 
	LCD_WR_REG(0x0085,0x0000); 
	//
	LCD_WR_REG(0x0090,0x0010); 
	LCD_WR_REG(0x0092,0x0600); 
	
	LCD_WR_REG(0x0007,0x0133);
	LCD_WR_REG(0x00,0x0022);//	
			 
	PBout(9)=1;//��������	 
	clear(WHITE);	
}



///////////////��ͼ�β���////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
//LCD������ʾ
void LCD_DisplayOn(void)
{					   
	LCD_WR_REG(0x07, 0x0173); //26��ɫ��ʾ����
}	 
//LCD�ر���ʾ
void LCD_DisplayOff(void)
{	   
	LCD_WR_REG(0x07, 0x0);//�ر���ʾ 
} 
//����  //Color:Ҫ���������ɫ
void clear(u16 color)
{
	u32 index=0;
	LCD_WR_REG(0X20,0);//���ù��λ��
	LCD_WR_REG(0X21,0);
	LCD_WR_COM(0X22);//��ʼд��GRAM
	for(index=0;index<76800;index++)
	{
		LCD_WR_DATA(color);    
	}
}
//���  //�����С:(xend-xsta)*(yend-ysta)
void fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{
	u16 i,j;
	u16 xlen=0;
	xlen=yend-ysta+1;	   
	for(i=xsta;i<=xend;i++)
	{
		LCD_WR_REG(0X20,ysta);//���ù��λ��
		LCD_WR_REG(0X21,319-i);

		LCD_WR_COM(0X22);//��ʼд��GRAM 
		for(j=0;j<xlen;j++)
			LCD_WR_DATA(color);//���ù��λ�� 	    
	}
}
//����
void draw_point(u16 x, u16 y, u16 color)
{
	LCD_WR_REG(0X20,y);//���ù��λ��
	LCD_WR_REG(0X21,319-x);
	LCD_WR_COM(0X22);//��ʼд��GRAM
	LCD_WR_DATA(color);
}
//����
void draw_line(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		draw_point(uRow,uCol,color);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	} 
}
//������
void draw_rectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
	draw_line(x1,y1,x2,y1,color);
	draw_line(x1,y1,x1,y2,color);
	draw_line(x1,y2,x2,y2,color);
	draw_line(x2,y1,x2,y2,color);
}
//��Բ r�뾶 (x,y)���ĵ�
void draw_circle(u16 x0, u16 y0, u8 r, u16 color)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		draw_point(x0-b,y0-a,color);             //3           
		draw_point(x0+b,y0-a,color);             //0           
		draw_point(x0-a,y0+b,color);             //1       
		draw_point(x0-b,y0-a,color);             //7           
		draw_point(x0-a,y0-b,color);             //2             
		draw_point(x0+b,y0+a,color);             //4               
		draw_point(x0+a,y0-b,color);             //5
		draw_point(x0+a,y0+b,color);             //6 
		draw_point(x0-b,y0+a,color);             
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 
		draw_point(x0+a,y0+b,color);
	}	
}


/////////////��ʾ�ַ����ֲ���//////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

//��ָ��λ����ʾһ���ַ�
//x:0~234
//y:0~308
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16
//color ������ɫ
void showchar(u16 x,u16 y,u8 num,u8 size, u16 color, u16 BACK_COLOR)
{     
	#define MAX_CHAR_POSX 312
	#define MAX_CHAR_POSY 232
    u8 temp;
    u8 pos,t;
	u16 x0=x;
	u16 colortemp=color;      
    if(x>MAX_CHAR_POSX||y>MAX_CHAR_POSY)return;	    
	//���ô���		   
	num=num-' ';//�õ�ƫ�ƺ��ֵ
	//�ǵ��ӷ�ʽ
	for(pos=0;pos<size;pos++)
	{
		if(size==12)temp=asc2_1206[num][pos];//����1206����
		else temp=asc2_1608[num][pos];		 //����1608����
		for(t=0;t<size/2;t++)
	    {                 
	        if(temp&0x01)color=colortemp;
			else color=BACK_COLOR;
			draw_point(x,y,color);	
			temp>>=1; 
			x++;
	    }
		x=x0;
		y++;		
	}
	color=colortemp;	    	   	 	  
}   
//m^n����
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ
//num:��ֵ(0~4294967295);	 
void shownum(u16 x,u16 y,u32 num,u8 len,u8 size, u16 color, u16 BACK_COLOR)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				showchar(x+(size/2)*t,y,' ',size,color,BACK_COLOR);
				continue;
			}else enshow=1; 
		 	 
		}
	 	showchar(x+(size/2)*t,y,temp+'0',size,color,BACK_COLOR); 
	}
} 
 
//��ʾ�ַ���
//x,y:�������  
//*p:�ַ�����ʼ��ַ
//��16����
void showstring(u16 x,u16 y,const u8 *p,u16 color, u16 BACK_COLOR)
{         
    while(*p!='\0')
    {       
        if(x>MAX_CHAR_POSX){x=0;y+=16;}
        if(y>MAX_CHAR_POSY){y=x=0;clear(WHITE);}
        showchar(x,y,*p,16,color,BACK_COLOR);
        x+=8;
        p++;
    }  
}

//��ʾ����16*16
//(x,y):������ʾ��λ��
//index:tfont��������ĵڼ�������
//color:������ֵ���ɫ
void showch16(u16 x,u16 y,u8 index,u16 color, u16 BACK_COLOR)
{   			    
	u8 temp,t,t1;
	u16 y0=y;				   
    for(t=0;t<32;t++)//ÿ��16*16�ĺ��ֵ��� ��32���ֽ�
    {   
		if(t<16)temp=tfont16[index*2][t];      //ǰ16���ֽ�
		else temp=tfont16[index*2+1][t-16];    //��16���ֽ�	                          
        for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)draw_point(x,y,color);//��ʵ�ĵ�
			else draw_point(x,y,BACK_COLOR);   //���հ׵㣨ʹ�ñ���ɫ��
			temp<<=1;
			y++;
			if((y-y0)==16)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}
//��ʾ1��24*24�ĺ���
//(x,y):������ʾ��λ��
//index:tfont��������ĵڼ�������
//color:������ֵ���ɫ
void showch24(u16 x,u16 y,u8 index,u16 color, u16 BACK_COLOR)
{   			    
	u8 temp,t,t1;
	u16 y0=y;				   
    for(t=0;t<72;t++)//ÿ��24*24�ĺ��ֵ��� ��72���ֽ�
    {   
		if(t<24)temp=tfont24[index*3][t];           //ǰ24���ֽ�
		else if(t<48)temp=tfont24[index*3+1][t-24]; //��24���ֽ�	                          
        else temp=tfont24[index*3+2][t-48];         //��24���ֽ�
	    for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)draw_point(x,y,color);//��ʵ�ĵ�
			else draw_point(x,y,BACK_COLOR);   //���հ׵㣨ʹ�ñ���ɫ��
			temp<<=1;
			y++;
			if((y-y0)==24)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}


//��ʾ24�Ĵ�����0~9 �����ʾ5λ�� �ɸ�
void show24num(u16 x,u16 y,u32 num,u16 color, u16 BACK_COLOR)
{   			    
	u8 temp,t,t1,lenth,index,t0;
	u16 y0=y;		
	if(num>0&&num<100) lenth=2;
	else if(num>=100&&num<1000) lenth=3;
	else if(num>=1000&&num<10000) lenth=4;
	else if(num>=10000&&num<100000) lenth=5;
	for(t0=0;t0<lenth;t0++)
	{
		index=(num/mypow(10,lenth-t0-1))%10;
		for(t=0;t<48;t++)//ÿ��24*24�ĺ��ֵ��� ��72���ֽ�
		{   
			if(t<24)temp=tfont24num[index*2][t];           //ǰ24���ֽ�
			else temp=tfont24num[index*2+1][t-24]; //��24���ֽ�(t<48)	                          
			for(t1=0;t1<8;t1++)
			{
				if(temp&0x80)draw_point(x,y,color);//��ʵ�ĵ�
				else draw_point(x,y,BACK_COLOR);   //���հ׵㣨ʹ�ñ���ɫ��
				temp<<=1;
				y++;
				if((y-y0)==24)
				{
					y=y0;
					x++;
					break;
				}
			}
		}
		x-=4;
	}
}




void showch32(u16 x,u16 y,u8 index,u16 color,u16 BACK_COLOR)
{          
	u8 temp,t,t1;
	u16 y0=y;       
    for(t=0;t<128;t++)//ÿ��32*32�ĺ��ֵ��� ��128���ֽ�
    {   
          if(t<32)temp=tfont32[index*4][t];           //ǰ32���ֽ�
         else if(t<64)temp=tfont32[index*4+1][t-32]; //��32���ֽ�
         else if(t<96)temp=tfont32[index*4+2][t-64];                  
         else temp=tfont32[index*4+3][t-96];         //��32���ֽ�
         for(t1=0;t1<8;t1++)
        {
            if(temp&0x80)draw_point(x,y,color);//��ʵ�ĵ�
            else draw_point(x,y,BACK_COLOR);   //���հ׵㣨ʹ�ñ���ɫ��
            temp<<=1;
            y++;
           if((y-y0)==32)
          {
             y=y0;
             x++;
            break;
          }
       }    
    }          
}

void showch56(u16 x,u16 y,u8 index,u16 color,u16 BACK_COLOR)
{          
	u16 temp,t,t1;
	u16 y0=y;       
    for(t=0;t<392;t++)//ÿ��56*56�ĺ��ֵ��� ��392���ֽ�
    {   
         if(t<56)temp=tfont56[index*7][t];          
         else if(t<112)temp=tfont56[index*7+1][t-56]; 
         else if(t<168)temp=tfont56[index*7+2][t-112]; 
		 else if(t<224)temp=tfont56[index*7+3][t-168];
		 else if(t<280)temp=tfont56[index*7+4][t-224];
		 else if(t<336)temp=tfont56[index*7+5][t-280];                 
         else temp=tfont56[index*7+6][t-336];      
         for(t1=0;t1<8;t1++)
        {
            if(temp&0x80)draw_point(x,y,color);//��ʵ�ĵ�
            else draw_point(x,y,BACK_COLOR);   //���հ׵㣨ʹ�ñ���ɫ��
            temp<<=1;
            y++;
           if((y-y0)==56)
          {
             y=y0;
             x++;
            break;
          }
       }    
    }          
}














