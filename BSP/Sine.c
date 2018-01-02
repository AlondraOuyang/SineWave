#include "Sine.h"
#include "timer.h"
#include "DMA.h"

//table sin_table;

u32 Sine100[100] = { 0x7FF,0x880,0x900,0x97F,0x9FC,0xA78,0xAF1,0xB67,0xBD9,0xC48,0xCB2,0xD18,0xD79,0xDD4,0xE29,0xE77
,0xEC0,0xF01,0xF3C,0xF6F,0xF9A,0xFBE,0xFDA,0xFEE,0xFFA,0xFFE,0xFFA,0xFEE,0xFDA,0xFBE,0xF9A,0xF6F
,0xF3C,0xF01,0xEC0,0xE77,0xE29,0xDD4,0xD79,0xD18,0xCB2,0xC48,0xBD9,0xB67,0xAF1,0xA78,0x9FC,0x97F
,0x900,0x880,0x7FF,0x77E,0x6FE,0x67F,0x602,0x586,0x50D,0x497,0x425,0x3B6,0x34C,0x2E6,0x285,0x22A
,0x1D5,0x187,0x13E,0x0FD,0x0C2,0x08F,0x064,0x040,0x024,0x010,0x004,0x000,0x004,0x010,0x024,0x040
,0x064,0x08F,0x0C2,0x0FD,0x13E,0x187,0x1D5,0x22A,0x285,0x2E6,0x34C,0x3B6,0x425,0x497,0x50D,0x586
,0x602,0x67F,0x6FE,0x77E};

u32 Sine90[90]={ 0x7FF,0x88E,0x91C,0x9A9,0xA33,0xABB,0xB40,0xBC0,0xC3C,0xCB2,0xD23,0xD8D,0xDF1,0xE4C,0xEA0,0xEEC
,0xF2F,0xF69,0xF9A,0xFC2,0xFDF,0xFF3,0xFFD,0xFFD,0xFF3,0xFDF,0xFC2,0xF9A,0xF69,0xF2F,0xEEC,0xEA0
,0xE4C,0xDF1,0xD8D,0xD23,0xCB2,0xC3C,0xBC0,0xB40,0xABB,0xA33,0x9A9,0x91C,0x88E,0x7FF,0x770,0x6E2
,0x655,0x5CB,0x543,0x4BE,0x43E,0x3C2,0x34C,0x2DB,0x271,0x20D,0x1B2,0x15E,0x112,0x0CF,0x095,0x064
,0x03C,0x01F,0x00B,0x001,0x001,0x00B,0x01F,0x03C,0x064,0x095,0x0CF,0x112,0x15E,0x1B2,0x20D,0x271
,0x2DB,0x34C,0x3C2,0x43E,0x4BE,0x543,0x5CB,0x655,0x6E2,0x770};

u32 Sine80[80]={0x7FF,0x8A0,0x93F,0x9DD,0xA78,0xB0F,0xBA1,0xC2D,0xCB2,0xD31,0xDA7,0xE14,0xE77,0xED1,0xF1F,0xF63
,0xF9A,0xFC6,0xFE5,0xFF8,0xFFE,0xFF8,0xFE5,0xFC6,0xF9A,0xF63,0xF1F,0xED1,0xE77,0xE14,0xDA7,0xD31
,0xCB2,0xC2D,0xBA1,0xB0F,0xA78,0x9DD,0x93F,0x8A0,0x7FF,0x75E,0x6BF,0x621,0x586,0x4EF,0x45D,0x3D1
,0x34C,0x2CD,0x257,0x1EA,0x187,0x12D,0x0DF,0x09B,0x064,0x038,0x019,0x006,0x000,0x006,0x019,0x038
,0x064,0x09B,0x0DF,0x12D,0x187,0x1EA,0x257,0x2CD,0x34C,0x3D1,0x45D,0x4EF,0x586,0x621,0x6BF,0x75E};


u32 Sine70[70]={ 0x7FF,0x8B7,0x96D,0xA20,0xACE,0xB77,0xC19,0xCB2,0xD42,0xDC7,0xE40,0xEAC,0xF0A,0xF5A,0xF9A,0xFCB
,0xFEC,0xFFC,0xFFC,0xFEC,0xFCB,0xF9A,0xF5A,0xF0A,0xEAC,0xE40,0xDC7,0xD42,0xCB2,0xC19,0xB77,0xACE
,0xA20,0x96D,0x8B7,0x7FF,0x747,0x691,0x5DE,0x530,0x487,0x3E5,0x34C,0x2BC,0x237,0x1BE,0x152,0x0F4
,0x0A4,0x064,0x033,0x012,0x002,0x002,0x012,0x033,0x064,0x0A4,0x0F4,0x152,0x1BE,0x237,0x2BC,0x34C
,0x3E5,0x487,0x530,0x5DE,0x691,0x747};


u32 Sine61[61]={ 0x7FF,0x8D5,0x9A9,0xA78,0xB40,0xBFF,0xCB2,0xD59,0xDF1,0xE77,0xEEC,0xF4D,0xF9A,0xFD2,0xFF3,0xFFE
,0xFF3,0xFD2,0xF9A,0xF4D,0xEEC,0xE77,0xDF1,0xD59,0xCB2,0xBFF,0xB40,0xA78,0x9A9,0x8D5,0x7FF,0x729
,0x655,0x586,0x4BE,0x3FF,0x34C,0x2A5,0x20D,0x187,0x112,0x0B1,0x064,0x02C,0x00B,0x000,0x00B,0x02C
,0x064,0x0B1,0x112,0x187,0x20D,0x2A5,0x34C,0x3FF,0x4BE,0x586,0x655,0x729,0x7FF};


u32 Sine50[50]={ 0x7FF,0x900,0x9FC,0xAF1,0xBD9,0xCB2,0xD79,0xE29,0xEC0,0xF3C,0xF9A,0xFDA,0xFFA,0xFFA,0xFDA,0xF9A
,0xF3C,0xEC0,0xE29,0xD79,0xCB2,0xBD9,0xAF1,0x9FC,0x900,0x7FF,0x6FE,0x602,0x50D,0x425,0x34C,0x285
,0x1D5,0x13E,0x0C2,0x064,0x024,0x004,0x004,0x024,0x064,0x0C2,0x13E,0x1D5,0x285,0x34C,0x425,0x50D
,0x602,0x6FE};

u32 Sine40[40]={ 0x7FF,0x93F,0xA78,0xBA1,0xCB2,0xDA7,0xE77,0xF1F,0xF9A,0xFE5,0xFFE,0xFE5,0xF9A,0xF1F,0xE77,0xDA7
,0xCB2,0xBA1,0xA78,0x93F,0x7FF,0x6BF,0x586,0x45D,0x34C,0x257,0x187,0x0DF,0x064,0x019,0x000,0x019
,0x064,0x0DF,0x187,0x257,0x34C,0x45D,0x586,0x6BF};

u32 Sine31[31]={0x7FF,0x9A9,0xB40,0xCB2,0xDF1,0xEEC,0xF9A,0xFF3,0xFF3,0xF9A,0xEEC,0xDF1,0xCB2,0xB40,0x9A9,0x7FF
,0x655,0x4BE,0x34C,0x20D,0x112,0x064,0x00B,0x00B,0x064,0x112,0x20D,0x34C,0x4BE,0x655,0x7FF};

u32 Sine20[20]={ 0x7FF,0xA78,0xCB2,0xE77,0xF9A,0xFFE,0xF9A,0xE77,0xCB2,0xA78,0x7FF,0x586,0x34C,0x187,0x064,0x000
,0x064,0x187,0x34C,0x586};

u32 Sine10[10]={0x7FF,0xCB2,0xF9A,0xF9A,0xCB2,0x7FF,0x34C,0x064,0x064,0x34C};

typedef struct
{
	u16 Real_Fre;
	u16 Set_Fre;
	u8 Sin_Table_Num;	
}table;
//Sin��ѯ��
table sin_table[100]=
{
	{10000,4010,40},	//0
	{9863,995,10},		//1
	{9836,6085,61},		//2
	{9730,980,10},		//3
	{9600,5090,50},		//4
	{9474,3840,40},		//5
	{9351,947,10},		//6
	{9350,940,10},		//7
	{9231,2872,30},		//8
	{9114,920,10},		//9
	{9000,905,10},		//10
	{8889,895,10},		//11
	{8780,880,10},		//12
	{8675,875,10},		//13
	{8572,6085,70},		//14
	{8471,4300,50},		//15
	{8372,847,10},		//16
	{8276,836,10},		//17
	{8181,3330,40},		//18
	{8090,816,10},		//19
	{8000,4100,50},		//20
	{7912,796,10},		//21
	{7826,3230,40},		//22
	{7742,775,10},		//23
	{7579,4000,50},		//24
	{7500,6085,80},		//25
	{7377,4785,61},		//26
	{7347,736,10},		//27
	{7201,2971,40},		//28
	{7129,713,10},		//29
	{6990,705,10},		//30
	{6923,2871,40},		//31
	{6793,685,10},		//32
	{6729,673,10},		//33
	{6605,661,10},		//34
	{6487,2000,30},		//35
	{6429,4785,70},		//36
	{6316,634,10},		//37
	{6207,621,10},		//38
	{6102,611,10},		//39
	{6000,3105,50},		//40
	{5902,591,10},		//41
	{5807,581,10},		//42
	{5714,572,10},		//43
	{5625,4785,80},		//44
	{5496,552,10},		//45
	{5414,542,10},		//46
	{5294,532,10},		//47
	{5218,522,10},		//48
	{5107,512,10},		//49
	{5000,4785,90},		//50
	{4898,493,10},		//51
	{4800,2480,50},		//52
	{4721,2971,61},		//53
	{4615,462,10},		//54
	{4500,4785,100},	//55
	{4390,441,10},		//56
	{4311,432,10},		//57
	{4211,422,10},		//58
	{4091,411,10},		//59
	{4000,2002,50},		//60
	{3913,392,10},		//61
	{3789,3790,100},	//62
	{3711,743,20},		//63
	{3600,3601,100},	//64
	{3495,705,20},		//65
	{3396,685,20},		//66
	{3303,665,20},		//67
	{3214,643,20,},		//68
	{3117,943,30},		//69
	{3000,3003,100},	//70
	{2903,1171,40},		//71
	{2813,1131,40},		//72
	{2697,812,30}, 		//73
	{2609,1052,40},		//74
	{2500,1012,40},		//75
	{2400,2402,100},	//76
	{2307,927,40},		//77
	{2215,1110,50},		//78
	{2093,847,40},		//79
	{2000,2002,100},	//80
	{1894,1920,100},	//81
	{1800,1801,100},	//82
	{1702,1540,90},		//83
	{1601,1601,100},	//84
	{1500,1501,100},	//85
	{1398,702,50},		//86
	{1309,1311,100},	//87
	{1200,1201,100},	//88
	{1096,999,90},		//89
	{1000,1001,100},	//90
	{900,901,100},		//91
	{800,801,100},		//92
	{699,701,100},		//93
	{600,601,100},		//94
	{500,501,100},		//95
	{400,401,100},		//96
	{300,301,100},		//97
	{200,201,100},		//98
	{100,101,100},		//99
};



u16 Get_Sin_Table_Set_Fre(u8 num)
{
	u16 Set;
	Set = sin_table[num].Set_Fre;
	return Set;
}


u8 Get_Sin_Table_Num(u8 num)
{
	u8 x;
	x = sin_table[num].Sin_Table_Num;
	x = x * 10;
	return x;
}

void Set_Fre(u32 fre)
{
	u16 x_num=0,x_arr=0;
	u32 x_fre=0;
	u16 x_psc = 9;
	u32 num=0;
	num = fre / 100;
	num = 100 - num;
	x_num = sin_table[num].Sin_Table_Num;
	x_fre = sin_table[num].Set_Fre;
	x_arr=72000000/(100*x_fre*(x_psc+1));
	Timerx_Init(x_arr,x_psc);
	DMA1_Channel7->CCR&=~(1<<0);       //�ر�DMA����
	switch(x_num)			
	{
		case 10:
			DMA1_config(DMA1_Channel7,(u32)&DAC->DHR12R1,(u32)Sine10,x_num);	
			break;
		case 20:
			DMA1_config(DMA1_Channel7,(u32)&DAC->DHR12R1,(u32)Sine20,x_num);	
			break;
		case 30:
			DMA1_config(DMA1_Channel7,(u32)&DAC->DHR12R1,(u32)Sine31,x_num);	
			break;
		case 40:
			DMA1_config(DMA1_Channel7,(u32)&DAC->DHR12R1,(u32)Sine40,x_num);	
			break;
		case 50:
			DMA1_config(DMA1_Channel7,(u32)&DAC->DHR12R1,(u32)Sine50,x_num);	
			break;
		case 61:
			DMA1_config(DMA1_Channel7,(u32)&DAC->DHR12R1,(u32)Sine61,x_num);	
			break;
		case 70:
			DMA1_config(DMA1_Channel7,(u32)&DAC->DHR12R1,(u32)Sine70,x_num);	
			break;
		case 80:
			DMA1_config(DMA1_Channel7,(u32)&DAC->DHR12R1,(u32)Sine80,x_num);	
			break;
		case 90:
			DMA1_config(DMA1_Channel7,(u32)&DAC->DHR12R1,(u32)Sine90,x_num);	
			break;
		case 100:
			DMA1_config(DMA1_Channel7,(u32)&DAC->DHR12R1,(u32)Sine100,x_num);	
			break;
		default:
			break;
	}
}


//u32 Get_Sin_Table_Address(u8 num)
//{
//	u32 *address;
//	num = sin_table[num].Sin_Table_Num;
//	switch(num)			
//	{
//		case 1:
//			address = Sine10;
//		break;
//		case 2:
//			address = Sine20;
//		break;
//		case 3:
//			address = Sine31;
//		break;
//		case 4:
//			address = Sine40;
//		break;
//		case 5:
//			address = Sine50;
//		break;
//		case 6:
//			address = Sine61;
//		break;
//		case 7:
//			address = Sine70;
//		break;
//		case 8:
//			address = Sine80;
//		break;
//		case 9:
//			address = Sine90;
//		break;
//		case 10:
//			address = Sine100;
//		break;
//		default:
//			break;
//	}
//	return *address;
//}


