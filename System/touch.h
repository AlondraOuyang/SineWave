#ifndef __TOUCH_H__
#define __TOUCH_H__
#include"sys.h"
#include "delay.h"

//与触摸屏芯片连接引脚	   
#define PEN  PBin(10)   //PB10  INT
#define DOUT PBin(11)   //PB11  MISO
#define TDIN PBout(14)  //PB14  MOSI
#define TCLK PBout(13)  //PB13  SCLK
#define TCS  PBout(12) //PB12 CS    

//ADS7843命令系统重要指令
#define CMD_RDX     0XD0  //0B10010000   即用差分方式读X坐标
#define CMD_RDY     0X90  //0B11010000  即用差分方式读Y坐标
//定义一个坐标的结构体
typedef struct 
{
	u16 X0;//原始坐标
	u16 Y0;
	u16 X; //最终/暂存坐标
	u16 Y;						   	    
	u8  Key_Sta;//笔的状态			  
	//触摸屏校准参数
	float xfac;
	float yfac;
	short xoff;
	short yoff;
//新增的参数,当触摸屏的左右上下完全颠倒时需要用到.
//touchtype=0的时候,适合左右为X坐标,上下为Y坐标的TP.
//touchtype=1的时候,适合左右为Y坐标,上下为X坐标的TP.
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











