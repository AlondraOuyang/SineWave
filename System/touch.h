#ifndef __TOUCH_H__
#define __TOUCH_H__
#include"sys.h"
#include "delay.h"

//�봥����оƬ��������	   
#define PEN  PBin(10)   //PB10  INT
#define DOUT PBin(11)   //PB11  MISO
#define TDIN PBout(14)  //PB14  MOSI
#define TCLK PBout(13)  //PB13  SCLK
#define TCS  PBout(12) //PB12 CS    

//ADS7843����ϵͳ��Ҫָ��
#define CMD_RDX     0XD0  //0B10010000   ���ò�ַ�ʽ��X����
#define CMD_RDY     0X90  //0B11010000  ���ò�ַ�ʽ��Y����
//����һ������Ľṹ��
typedef struct 
{
	u16 X0;//ԭʼ����
	u16 Y0;
	u16 X; //����/�ݴ�����
	u16 Y;						   	    
	u8  Key_Sta;//�ʵ�״̬			  
	//������У׼����
	float xfac;
	float yfac;
	short xoff;
	short yoff;
//�����Ĳ���,��������������������ȫ�ߵ�ʱ��Ҫ�õ�.
//touchtype=0��ʱ��,�ʺ�����ΪX����,����ΪY�����TP.
//touchtype=1��ʱ��,�ʺ�����ΪY����,����ΪX�����TP.
	u8 touchtype;
}Pen_typedef;

extern Pen_typedef Pen_Point;

void touch_wr_byte(u8 com);
u16 touch_re_byte(u8 com);
u16 touch_re_xy1(u8 com);
u8 touch_re_xy2(u16 *x, u16 *y);
u8 touch_re_xy(u16 *x, u16 *y);
void touch_get_xy(void);
void touch_Init(void);
void Pen_Int_set(u8 en);
void touch_adj(void);
#endif











