#ifndef __SINE_H
#define __SINE_H
#include "sys.h"

extern u32 Sine10[10];
extern u32 Sine20[20];
extern u32 Sine31[31];
extern u32 Sine40[40];
extern u32 Sine50[50];
extern u32 Sine61[61];
extern u32 Sine70[70];
extern u32 Sine80[80];
extern u32 Sine90[90];
extern u32 Sine100[100];



u32 Get_Sin_Table_Address(u8 num);
u16 Get_Sin_Table_Set_Fre(u8 num);
u8 Get_Sin_Table_Num(u8 num);
void Set_Fre(u32 fre);
#endif


