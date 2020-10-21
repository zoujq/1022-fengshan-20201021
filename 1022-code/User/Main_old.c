//================================================================================
#define  ALLOCATE_EXTERN
#include "YX23F01CB.h"
#include "YX23F01CB_SYS.h"
#include "YX23F01CB_IO_INIT.h"
#include "YX23F01CB_GeneralKey_Touch_Lib_V1.04\YX23F01CB_GeneralKey_Touch_Lib.h"
#include "YX23F01CB_GeneralKey_Touch_Lib_V1.04\YX23F01CB_GeneralKey_Touch_Filter.h"
#include "YX23F01CB_GeneralKey_Touch_Lib_V1.04\YX23F01CB_GeneralKey_Touch_Multibutton.h"
#include "YX23F01CB_TouchUartDebug_Lib_V1.00\YX23F01CB_TouchUartDebug_Lib_CFG.h"
#include "YX23F01CB_TouchUartDebug_Lib_V1.00\YX23F01CB_TouchUartDebug_Lib.h"
#include "delay.h"
#include <stdio.h>
#include "pt.h"

#define TK1 1<<15
#define TK2 1<<14
#define TK3 1<<13
#define TK4 1<<12
#define TK5 1<<11


extern void init_printf();
void init_ntc_adc();
void init_display();
void display_temp(unsigned char temp);
unsigned int get_ntc_adc();
void  buzzer();
u16 get_temp();
void init_TIMER0();
static int dislay(struct pt *pt);
//================================================================================

char display_buff[4]={0,0,0,0};
char display_point=0;
u32 yuyue_counter=0;
u32 dingshi_counter=0;
u32 counter=0;
char work_mode=0;
int set_temp=0;
char display_mode=0;

static struct pt pt1, pt2;
//================================================================================
void main()
{
	u16 last_TK=0;
	u16 temp=0;
	SystemInit();						//时钟初始化函数(默认Fosc=Fcpu=16M)
//	IO_Init();
	init_printf();
//	init_ntc_adc();
	init_display();
    init_TIMER0();
	EA = 1;
	CTK_Init();	
							

	//printf("start\n\r");

	P0M3=GPIO_Out_PP;//buzzer

//	temp=get_temp();

	PT_INIT(&pt1);
  	PT_INIT(&pt2);
	while(1)
	{
//		display_temp(temp);
		if(OneCycleScanDone)
		{
			TouchRawDataFilter();		//RawData滤波函数，如需使能数据滤波，需在YX23F01CB_GeneralKey_Touch_Filter.h中设置滤波深度，此函数不可删除
			Touch_Signal_Handle();
			TouchMultibuttonHandle();	//最强按键处理函数，如果大于等于两个按键同时有效，那么触摸信号最强的按键判断为有效，其他按键无效
			OneCycleScanDone = 0;

		}
		
		if(TouchKeyFlag )
		{
			extern ux16	XDATA_RawDataBuf[];			
			
			if(last_TK!=TouchKeyFlag)
			{
				last_TK=TouchKeyFlag;
				buzzer();
			}
//			printf("TouchKeyFlag=0x%X,XDATA_RawDataBuf[0]=%d\n\r",TouchKeyFlag,XDATA_RawDataBuf[0]);
			
//			if(TouchKeyFlag == TK1)
//			{
//				 printf("TK1\n\r");
//			}
//			else if(TouchKeyFlag == TK2)
//			{
//				 printf("TK2\n\r");
//			}
//			else if(TouchKeyFlag == TK3)
//			{
//				 printf("TK3\n\r");
//			}
//			else if(TouchKeyFlag == TK4)
//			{
//				 printf("TK4\n\r");
//			}
//			else if(TouchKeyFlag == TK5)
//			{
//				 printf("TK5\n\r");
//			}
		}
		else{
			last_TK=0;
		}
		dislay(&pt1);
		
	    // printf("start%d\n\r",sizeof(long));
		
//		printf("%d,temp=%d\n\r",get_ntc_adc(),get_temp());
		// Delay_ms(3000);
	}
}

/*************************************ADC************************************************/
u16 code Temp_Table[100]={
3815,3788,3761,3734,3707,3680,3653,3626,3599,3572,3545,3518,3491,3464,3437,3410,3383,3356,
	3329,3302,3275,3248,3221,3194,3167,3140,3113,3086,3059,3032,3005,2978,2951,2924,2897,2870,
	2843,2816,2789,2762,2735,2708,2681,2654,2627,2600,2573,2546,2519,2492,2465,2438,2411,2384,
	2357,2330,2303,2276,2249,2222,2195,2168,2141,2114,2087,2060,2033,2006,1979,1952,1925,1898,
	1871,1844,1817,1790,1763,1736,1709,1682,1655,1628,1601,1574,1547,1520,1493,1466,1439,1412,
	1385,1358,1331,1304,1277,1250,1223,1196,1169,1142
};

void init_ntc_adc()
{
	
	P0M2 = 0x01;				        //P02设置为模拟输入
	ADCC0 = 0x80;						//打开ADC转换电源
	Delay_50us(1);						//延时50us，确保ADC系统稳定
	ADCC1 = 2;						//选择外部通道2
	ADCC2 = 0x4B;						//转换结果12位数据，数据右对齐，ADC时钟16分频

	//NTC POWER
	P2M0=GPIO_Out_PP;	
	P2_0=1;
	
	
}
unsigned int get_ntc_adc()
{
		ADCC0 |= 0x40;					//启动ADC转换
		while(!(ADCC0&0x20));			//等待ADC转换结束
		ADCC0 &=~ 0x20;					//清除标志位
		return ADCR;
}

u16 get_temp()
{
	u16 n=0;
	u16 ntc_adc=get_ntc_adc();
	
	for(n=0;n<100;n++)
	{
		if(Temp_Table[n]<ntc_adc)
		{
			break;
		}
	}
	return n;

}


/************************************数码管***************************************/
//阳极
#define DISPLAY_A P2_6
#define DISPLAY_B P2_4
#define DISPLAY_C P3_4
#define DISPLAY_D P2_2
#define DISPLAY_E P2_1
#define DISPLAY_F P2_5
#define DISPLAY_G P3_5
#define DISPLAY_H P2_3
//阴极
#define DISPLAY_COM1 P0_7
#define DISPLAY_COM2 P0_1
#define DISPLAY_COM3 P0_0
#define DISPLAY_COM4 P2_7

void init_display()
{
	P2M6=GPIO_Out_PP;
	P2M4=GPIO_Out_PP;
	P3M4=GPIO_Out_PP;
	P2M2=GPIO_Out_PP;
	P2M1=GPIO_Out_PP;
	P2M5=GPIO_Out_PP;
	P3M5=GPIO_Out_PP;
	P2M3=GPIO_Out_PP;
	
	P0M7=GPIO_Out_PP;
	P0M1=GPIO_Out_PP;
	P0M0=GPIO_Out_PP;
	P2M7=GPIO_Out_PP;
	DISPLAY_COM1=1;
	DISPLAY_COM2=1;
	DISPLAY_COM3=1;
	DISPLAY_COM4=1;

}
static int dislay(struct pt *pt)
{
	static u32 t0=0;
	PT_BEGIN(pt);
	while(1)
	{
		switch(display_mode)
		{
			case 0:
				display_buff[0]=8;
				display_buff[1]=8;
				display_buff[2]=8;
				display_buff[3]=8;
				display_point=1;
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			default:

				break;
		}
	}
	PT_END(pt);
}
void display_flash()
{
	static char position=0;
	
	DISPLAY_COM1=1;
	DISPLAY_COM2=1;
	DISPLAY_COM3=1;
	DISPLAY_COM4=1;
	switch(display_buff[position])
	{
		case 0:		
			DISPLAY_A=1;DISPLAY_B=1;DISPLAY_C=1;DISPLAY_D=1;DISPLAY_E=1;DISPLAY_F=1;DISPLAY_G=0;		
	
			break;
		case 1:
			DISPLAY_A=0;DISPLAY_B=1;DISPLAY_C=1;DISPLAY_D=0;DISPLAY_E=0;DISPLAY_F=0;DISPLAY_G=0;
			break;
		case 2:
			DISPLAY_A=1;DISPLAY_B=1;DISPLAY_C=0;DISPLAY_D=1;DISPLAY_E=1;DISPLAY_F=0;DISPLAY_G=1;
			break;
		case 3:
			DISPLAY_A=1;DISPLAY_B=1;DISPLAY_C=1;DISPLAY_D=1;DISPLAY_E=0;DISPLAY_F=0;DISPLAY_G=1;
			break;
		case 4:
			DISPLAY_A=0;DISPLAY_B=1;DISPLAY_C=1;DISPLAY_D=0;DISPLAY_E=0;DISPLAY_F=1;DISPLAY_G=1;	
			break;
		case 5:
			DISPLAY_A=1;DISPLAY_B=0;DISPLAY_C=1;DISPLAY_D=1;DISPLAY_E=0;DISPLAY_F=1;DISPLAY_G=1;	
			break;
		case 6:
			DISPLAY_A=1;DISPLAY_B=0;DISPLAY_C=1;DISPLAY_D=1;DISPLAY_E=1;DISPLAY_F=1;DISPLAY_G=1;	
			break;
		case 7:
			DISPLAY_A=1;DISPLAY_B=1;DISPLAY_C=1;DISPLAY_D=0;DISPLAY_E=0;DISPLAY_F=0;DISPLAY_G=0;	
			break;
		case 8:
			DISPLAY_A=1;DISPLAY_B=1;DISPLAY_C=1;DISPLAY_D=1;DISPLAY_E=1;DISPLAY_F=1;DISPLAY_G=1;	
			break;
		case 9:
			DISPLAY_A=1;DISPLAY_B=1;DISPLAY_C=1;DISPLAY_D=1;DISPLAY_E=0;DISPLAY_F=1;DISPLAY_G=1;
			break;
		case 'E':
			DISPLAY_A=1;DISPLAY_B=0;DISPLAY_C=0;DISPLAY_D=1;DISPLAY_E=1;DISPLAY_F=1;DISPLAY_G=1;	
			break;		
		case '+':
			DISPLAY_A=0;DISPLAY_B=0;DISPLAY_C=0;DISPLAY_D=0;DISPLAY_E=0;DISPLAY_F=0;DISPLAY_G=0;	
			break;	
		default:
			
			break;
	
	}
	if(display_point)
	{
		DISPLAY_H=1;
	}
	if(position==0)
	{		
		DISPLAY_COM1=0;
		DISPLAY_COM2=1;
		DISPLAY_COM3=1;
		DISPLAY_COM4=1;

	}
	else if(position==1) 
	{
		DISPLAY_COM1=1;
		DISPLAY_COM2=0;
		DISPLAY_COM3=1;
		DISPLAY_COM4=1;
	}
	else if(position==2)
	{
		DISPLAY_COM1=1;
		DISPLAY_COM2=1;
		DISPLAY_COM3=0;
		DISPLAY_COM4=1;
	}
	else if(position==3)
	{
		DISPLAY_COM1=1;
		DISPLAY_COM2=1;
		DISPLAY_COM3=1;
		DISPLAY_COM4=0;
	}
	position++;
	if(position>3)
	{
		position=0;
	}
}
void display_temp(unsigned char temp)
{
	char b_1=0;
	char b_2=0;
	char b_3=0;
	if(temp>120)
	{
		temp=120;
	}
	display_buff[0]=temp%10;
	display_buff[1]=(temp%100)/10;
	display_buff[2]=temp/100;
	display_buff[3]=0;
	display_point=1;

}
void  buzzer()
{
	int i=0;
	
	for(i=0;i<500;i++){
		P0_3=1;
		Delay_50us(3);
		P0_3=0;
		Delay_50us(3);
	}
	
	
}
void init_TIMER0()
{
	TCON1 = 0x00;						//Tx0定时器时钟为Fosc/12
	TMOD = 0x00;						//16位重装载定时器/计数器

	//Tim0计算时间 	= (65536 - 0xFACB) * (1 / (Fosc /Timer分频系数))
	//				= 1333 / (16000000 / 12)
	//				= 1 ms

	//定时1ms
	//反推初值 	= 65536 - ((1/1000) / (1/(Fosc / Timer分频系数)))
	//		   	= 65536 - ((1/1000) / (1/(16000000 / 12)))
	//			= 65536 - 1333
	//			= 0xFACB
	
	TH0 = 0xFA;
	TL0 = 0xCB;							//T0定时时间1ms
	IE |= 0x02;							//打开T0中断
	TCON |= 0x10;						//使能T0
    
}

void TIMER0_Rpt(void) interrupt TIMER0_VECTOR
{
	// P0_3 =~ P0_3;
	display_flash();						//P03翻转
	if(yuyue_counter>0)
	{
		yuyue_counter--;
		if(yuyue_counter==0)
		{
			work_mode=1;
		}
	}
	else if(dingshi_counter>0)
	{
		dingshi_counter--;
		if(dingshi_counter==0)
		{
			work_mode=0;
		}
	}
	counter++;
}
//void init
/*********************************END OF FILE************************************/










































