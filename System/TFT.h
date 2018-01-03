#ifndef _TFT_H
#define _TFT_H
#include "sys.h"
#include "delay.h"


//快速IO
#define	LCD_CS_SET  GPIOB->BSRR=1<<7    //片选端口  	     PB7
#define	LCD_RS_SET	GPIOB->BSRR=1<<5    //数据/命令          PB5	   
#define	LCD_WR_SET	GPIOB->BSRR=1<<8    //写数据			 PB8
#define	LCD_RD_SET	GPIOB->BSRR=1<<6    //读数据			 PB6
								    
#define	LCD_CS_CLR  GPIOB->BRR=1<<7     //片选端口  	     PB7
#define	LCD_RS_CLR	GPIOB->BRR=1<<5     //数据/命令          PB5	   
#define	LCD_WR_CLR	GPIOB->BRR=1<<8     //写数据			 PB8
#define	LCD_RD_CLR	GPIOB->BRR=1<<6     //读数据
//写8位数据函数
//用宏定义,提高速度.
//快速IO
#define LCD_WR_DATA(data){\
LCD_RS_SET;\
LCD_CS_CLR;\
GPIOC->ODR = data;\
LCD_WR_CLR;\
LCD_WR_SET;\
LCD_CS_SET;\
} 



//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

void LCD_WR_COM(u8 data);
void LCD_WR_REG(u8 com, u16 data);
u16 LCD_BGR2RGB(u16 c);
void LCD_Init(void);
void showchar(u16 x,u16 y,u8 num,u8 size, u16 color, u16 BACK_COLOR);
u32 mypow(u8 m,u8 n);
void shownum(u16 x,u16 y,u32 num,u8 len,u8 size, u16 color, u16 BACK_COLOR);
void showstring(u16 x,u16 y,const u8 *p,u16 color, u16 BACK_COLOR);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void clear(u16 color);
void fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
void draw_point(u16 x, u16 y, u16 color);
void draw_line(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
void draw_rectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
void draw_circle(u16 x0, u16 y0, u8 r, u16 color);
void showch16(u16 x,u16 y,u8 index,u16 color, u16 BACK_COLOR);
void showch24(u16 x,u16 y,u8 index,u16 color, u16 BACK_COLOR);
void showch32(u16 x,u16 y,u8 index,u16 color,u16 BACK_COLOR);
void showch56(u16 x,u16 y,u8 index,u16 color,u16 BACK_COLOR);
void show24num(u16 x,u16 y,u32 num,u16 color, u16 BACK_COLOR);
#endif

