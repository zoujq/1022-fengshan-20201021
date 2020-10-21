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

#define TK1 1<<15
#define TK2 1<<14
#define TK3 1<<13
#define TK4 1<<12
#define TK5 1<<11


extern void init_printf();
void init_ntc_adc();
void init_display();
unsigned int get_ntc_adc();
void  buzzer();
u16 get_temp();
void init_TIMER0();
void key_check();
//================================================================================

char display_buff[4]={0,0,0,0};
char display_point=0;
u32 yuyue_counter=0;
u32 dingshi_counter=0;
u32 counter=0;
char work_mode=0;
int set_temp=90;
char display_mode=0;
char yuyue_start=0;
char dingshi_start=0;
char kid_lock=0;
char led_buff=0;
u16 current_temp=0;
char err_code=0;
char start_work=0;
//================================================================================
void set_temp_plus()
{
	set_temp+=5;
	if(set_temp>=125)
	{
		set_temp=40;
	}
}
void set_yuyue_time_plus()
{
	yuyue_counter+=3600000;
	if(yuyue_counter>12*3600000)
	{
		yuyue_counter=0;
	}
}
void set_dingshi_time_plus()
{
	dingshi_counter+=3600000;
	if(dingshi_counter>12*3600000)
	{
		dingshi_counter=0;
	}
}
void display_yuyue_set()
{
	display_buff[0]=(yuyue_counter/3600000)%10;
	display_buff[1]=(yuyue_counter/3600000)/10;
	display_buff[2]='+';
	display_buff[3]='+';
	display_point=0;
}
void display_dingshi_set()
{
	display_buff[0]=(dingshi_counter/3600000)%10;
	display_buff[1]=(dingshi_counter/3600000)/10;
	display_buff[2]='+';
	display_buff[3]='+';
	display_point=0;
}
void display_yuyue_time()
{
	display_buff[0]=(((yuyue_counter+60000)%3600000)/60000)%10;
	display_buff[1]=(((yuyue_counter+60000)%3600000)/60000)/10;
	display_buff[2]=((yuyue_counter+60000)/3600000)%10;
	display_buff[3]=((yuyue_counter+60000)/3600000)/10;
	display_point=1;
}
void display_yuyue_time_no_point()
{
	display_buff[0]=(((yuyue_counter+60000)%3600000)/60000)%10;
	display_buff[1]=(((yuyue_counter+60000)%3600000)/60000)/10;
	display_buff[2]=((yuyue_counter+60000)/3600000)%10;
	display_buff[3]=((yuyue_counter+60000)/3600000)/10;
	display_point=0;
}

void display_dingshi_time()
{
	display_buff[0]=(((dingshi_counter+60000)%3600000)/60000)%10;
	display_buff[1]=(((dingshi_counter+60000)%3600000)/60000)/10;
	display_buff[2]=((dingshi_counter+60000)/3600000)%10;
	display_buff[3]=((dingshi_counter+60000)/3600000)/10;
	display_point=1;
}
void display_dingshi_time_no_point()
{
	display_buff[0]=(((dingshi_counter+60000)%3600000)/60000)%10;
	display_buff[1]=(((dingshi_counter+60000)%3600000)/60000)/10;
	display_buff[2]=((dingshi_counter+60000)/3600000)%10;
	display_buff[3]=((dingshi_counter+60000)/3600000)/10;
	display_point=0;
}

void display_off()
{
	display_buff[0]=8;
	display_buff[1]=8;
	display_buff[2]=8;
	display_buff[3]=8;
	display_point=1;
}
void display_set_temp()
{
	display_buff[0]=set_temp%10;
	display_buff[1]=(set_temp%100)/10;
	if(set_temp>99)
	{
		display_buff[2]=1;
	}
	else
	{
		display_buff[2]='+';
	}
	
	display_buff[3]='+';
	display_point=0;

}
void display_none()
{
	display_buff[0]='+';
	display_buff[1]='+';
	display_buff[2]='+';
	display_buff[3]='+';
	display_point=0;
}
void key_check()
{
	static u16 last_TK=0;
	static u32 count0=0;
	static u16 i3=0;
	if(err_code)
	{
		display_buff[0]='+';
		display_buff[1]=err_code;
		display_buff[2]='E';
		display_buff[3]='+';
		display_point=0;
		return;
	}
	if(TouchKeyFlag )
	{		
		if(last_TK!=TouchKeyFlag)
		{
			last_TK=TouchKeyFlag;

			if(kid_lock==0)
			{
				if(TouchKeyFlag == TK1)
				{
					 buzzer();
					 if(work_mode==0)
					 {
					 	work_mode=1;
					 	display_set_temp();
					 	led_buff=0x03;
					 	count0=0;
					 }
					 else
					 {
					 	work_mode=0;
					 	display_mode=0;
					 	dingshi_start=0;
					 	yuyue_start=0;
					 	yuyue_counter=0;
					 	dingshi_counter=0;
					 	set_temp=90;

					 }
				}
				if(work_mode==1)
				{
					if(TouchKeyFlag == TK2)
					{
						 buzzer();
						 set_temp_plus();
						 display_set_temp();
						 count0=0;
						 display_mode=0;
					}
					else if(TouchKeyFlag == TK3)
					{	
						buzzer();
						if(yuyue_start==1)
						{
							yuyue_start=0;							
							display_set_temp();
							yuyue_counter=0;
							led_buff&=~0x04;		
							display_mode=0;

						}
						else
						{
							set_yuyue_time_plus();
							display_yuyue_set();
							count0=0;
							display_mode=1;
							led_buff|=0x04;
						}
						

					}
					else if(TouchKeyFlag == TK4)
					{
						 buzzer();
						 if(dingshi_start==1)
						 {
						 	dingshi_start=0;
							dingshi_counter=0;
							display_yuyue_set();
							led_buff&=~0x08;
							display_mode=0;							
						 }
						 else
						 {								 
						 	display_mode=2;
						 	set_dingshi_time_plus();
							display_dingshi_set();
							count0=0;
							led_buff|=0x08;
						 }
					}
					
				}

			}
		
			
		}
		else if(TouchKeyFlag == TK5 && work_mode==1)
		{
			
			i3++;
			if(i3==1200)
			{
			 	buzzer();
			 	if(kid_lock==0)
			 	{
			 		kid_lock=1;
			 		led_buff|=0x10;
			 	}
			 	else
			 	{
			 		kid_lock=0;
			 		led_buff&=~0x10;
			 	}
			}
		}
		
		
	}
	else{
		last_TK=0;
		i3=0;
	}

	if(work_mode==0)
	{
		static u16 i5=0;
		display_off();
		count0=0;		
		if(i5==1)
		{
			led_buff=0x01;
		} 
		else if(i5==400)
		{					
			led_buff=0x00;					
		}
		else if(i5==800)
		{
			i5=0;
		}
		i5++;
	}
	else
	{		
		if(count0<2100)
		{
			start_work=0;
			count0++;
			if(count0%350==0)
			{
				static char i=0;
				if(i==0)
				{
					if(display_mode==0)
					{
						display_set_temp();	
					}
					else if(display_mode==1)
					{
						display_yuyue_set();
					}
					else if(display_mode==2)
					{
						display_dingshi_set();
					}

					
					i=1;
				}
				else
				{
					display_none();
					i=0;
				}
				
			}

		}
		else
		{
			start_work=1;
			if(display_mode==0)
			{
				display_set_temp();
				if(yuyue_counter>0)
				{
					display_mode=1;
				}
				else if(dingshi_counter>0)
				{
					display_mode=2;
				}
			}
			if(display_mode==1)
			{	
				if(yuyue_counter>0)
				{
					static u16 i1=0;
					yuyue_start=1;				
					if(i1==1)
					{
						display_yuyue_time();
					} 
					else if(i1==500)
					{
						display_yuyue_time_no_point();
					}
					else if(i1==1000)
					{
						i1=0;
					}
					i1++;
				}
				else
				{
					if(dingshi_counter==0)
					{
						display_mode=0;
					}
					else
					{
						display_mode=2;
					}					
					led_buff&=~0x04;

				}
						

			}
			if(display_mode==2)
			{	
				dingshi_start=1;
				if(yuyue_counter==0)
				{
					if(dingshi_counter>0)
					{
						static u16 i2=0;
						static char rr=0;
						
						if(i2++<4000)
						{
							if(i2%500==0)
							{
								if(rr==0)
								{
									display_dingshi_time();
									rr=1;
								}
								else
								{
									display_dingshi_time_no_point();
									rr=0;
								}
								
							}
						}
						else if(i2<7000)
						{
							display_set_temp();
						}
						else
						{
							i2=0;
						}
							
						
					}
					else
					{
						display_mode=0;
						led_buff&=~0x08;
						work_mode=0;
						kid_lock=0;
					}	
				}
				else
				{
					display_mode=1;
				}				
							

			}
		}
		


	}
}
void hot_check()
{
	static char inited=0;
	current_temp=get_temp();
	if(inited==0)
	{
		P1M1=GPIO_Out_PP;//hot
		inited=1;
	}
	if(work_mode==1 && yuyue_counter==0 && start_work==1)
	{
		if(set_temp>current_temp)
		{
			P1_1=1;
		}
		else
		{
			P1_1=0;
		}
	}
	else
	{
		P1_1=0;
	}
}

void main()
{
	
	SystemInit();						//
	init_printf();
	init_ntc_adc();
	init_display();
  init_TIMER0();
	EA = 1;
	CTK_Init();	
							

	//printf("start\n\r");	
	buzzer();
	while(1)
	{

		if(OneCycleScanDone)
		{
			TouchRawDataFilter();		//
			Touch_Signal_Handle();
			TouchMultibuttonHandle();	//
			OneCycleScanDone = 0;

		}
		
		key_check();
		hot_check();		
		Delay_ms(1);
		counter++;

	}	
}





/*************************************ADC************************************************/
//0~119℃
u16 code Temp_Table[120]={
	3783,3768,3752,3736,3720,3702,3684,3666,3647,3627,3607,3586,3564,3542,3519,3495,3471,
	3446,3421,3395,3368,3340,3312,3284,3255,3225,3194,3163,3132,3100,3067,3034,3000,2966,
	2932,2897,2861,2825,2789,2753,2716,2679,2641,2604,2566,2528,2490,2452,2414,2375,2337,
	2298,2260,2222,2183,2145,2107,2069,2032,1994,1957,1920,1883,1847,1811,1775,1740,1705,
	1670,1636,1602,1568,1535,1502,1470,1439,1407,1377,1346,1317,1287,1259,1230,1202,1175,
	1148,1122,1096,1071,1046,1022,998,975,952,930,908,886,865,845,825,805,786,767,749,731,
	714,696,680,664,648,632,617,602,588,574,560,547,534,521,508
};

void init_ntc_adc()
{
	
	P0M2 = 0x01;				        //
	ADCC0 = 0x80;						//
	Delay_50us(1);						//
	ADCC1 = 2;						//
	ADCC2 = 0x4B;						//	
}
unsigned int get_ntc_adc()
{
	ADCC0 |= 0x40;					//
	while(!(ADCC0&0x20));			//
	ADCC0 &=~ 0x20;					//
	return ADCR;
}

u16 get_temp()
{
	u16 n=0;
	u16 ntc_adc=get_ntc_adc();
	
	for(n=0;n<120;n++)
	{
		if(Temp_Table[n]<ntc_adc)
		{
			break;
		}
	}
	// printf("ntc_adc:%d,wen_du:%d\n", ntc_adc,n);
	if(ntc_adc==0)
	{
		err_code=2;
	}
	else if(ntc_adc==4095)
	{
		err_code=1;
	}

	return n;

}


/***************************************************************************/
//
#define DISPLAY_A P2_6
#define DISPLAY_B P2_4
#define DISPLAY_C P3_4
#define DISPLAY_D P2_2
#define DISPLAY_E P2_1
#define DISPLAY_F P2_5
#define DISPLAY_G P3_5
#define DISPLAY_H P2_3
//
#define DISPLAY_COM1 P0_7
#define DISPLAY_COM2 P0_1
#define DISPLAY_COM3 P0_0
#define DISPLAY_COM4 P2_7

#define DISPLAY_LED P1_2

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

	P1M2=GPIO_Out_PP;//KEY LEDS
	display_off();
}

void display_flash()
{
	static char position=0;
	
	DISPLAY_COM1=1;
	DISPLAY_COM2=1;
	DISPLAY_COM3=1;
	DISPLAY_COM4=1;
	DISPLAY_LED=1;
	if(position<4)
	{
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
	}
	else
	{
		DISPLAY_A=(led_buff & 1)? 1:0; 
		DISPLAY_B=(led_buff & 0x02)? 1:0; 
		DISPLAY_E=(led_buff & 0x04)? 1:0; 
		DISPLAY_D=(led_buff & 0x08)? 1:0; 
		DISPLAY_C=(led_buff & 0x10)? 1:0; 
	}
	
	if(display_point)
	{
		DISPLAY_H=1;
	}
	else
	{
		DISPLAY_H=0;
	}
	if(position==0)
	{		
		DISPLAY_COM1=0;
		DISPLAY_COM2=1;
		DISPLAY_COM3=1;
		DISPLAY_COM4=1;
		DISPLAY_LED=1;

	}
	else if(position==1) 
	{
		DISPLAY_COM1=1;
		DISPLAY_COM2=0;
		DISPLAY_COM3=1;
		DISPLAY_COM4=1;
		DISPLAY_LED=1;
	}
	else if(position==2)
	{
		DISPLAY_COM1=1;
		DISPLAY_COM2=1;
		DISPLAY_COM3=0;
		DISPLAY_COM4=1;
		DISPLAY_LED=1;
	}
	else if(position==3)
	{
		DISPLAY_COM1=1;
		DISPLAY_COM2=1;
		DISPLAY_COM3=1;
		DISPLAY_COM4=0;
		DISPLAY_LED=1;
	}
	else if(position==4)
	{
		DISPLAY_COM1=1;
		DISPLAY_COM2=1;
		DISPLAY_COM3=1;
		DISPLAY_COM4=1;
		DISPLAY_LED=0;
	}
	position++;
	if(position>4)
	{
		position=0;
	}
}

void  buzzer()
{
	static char inited=0;
	int i=0;
	if(inited==0)
	{
		P0M3 = 0xC2;                        //P03设置为推挽输出
		PWM3_MAP = 0x03;					//PWM3映射P03口
		PWM3P = 0x20;						//PWM周期为0xFF
		PWM3D = 0x10;						//PWM占空比设置
		PWM3C = 0x97; 						//使能PWM3，关闭中断，允许输出，时钟4分频
		inited=1;
	}	
	PWM3C = 0x97;	
	Delay_ms(200);
	PWM3C = 0x07;
	
	
}
void init_TIMER0()
{
	TCON1 = 0x00;						//
	TMOD = 0x00;						//
	
	TH0 = 0xFA;
	TL0 = 0xCB;							//
	IE |= 0x02;							//
	TCON |= 0x10;						//
    
}

void TIMER0_Rpt(void) interrupt TIMER0_VECTOR
{
	// P0_3 =~ P0_3;
	display_flash();						//P03
	if(yuyue_counter>0)
	{
		if(yuyue_start==1)
		{
			yuyue_counter--;
		}
		
	}
	else if(dingshi_counter>0)
	{
		if(dingshi_start==1)
		{
			dingshi_counter--;			
		}
		
	}	
}
//void init
/*********************************END OF FILE************************************/










































