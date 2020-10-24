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

u32 counter=0;

int set_temp=90;
char display_mode=0;
char yuyue_start=0;

char kid_lock=0;
char led_buff=0;
u16 current_temp=0;
char err_code=0;
char start_work=0;

char dingshi_start=0;
u32 dingshi_counter=0;
char work_mode=0;

char uv_start=0;
u32 uv_counter=20*60*1000;
char last_work_mode=0;
u32 count0=0;
//================================================================================

void set_dingshi_time_plus()
{
	dingshi_counter+=0.5*3600000;
	if(dingshi_counter>6*3600000)
	{
		dingshi_counter=0.5*3600000;
	}
}

void display_dingshi_set()
{
	display_buff[0]=(dingshi_counter/3600000)%10;
	display_buff[1]=(dingshi_counter/3600000)/10;
	display_buff[2]='+';
	display_buff[3]='+';
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

			if(work_mode==0)
			{
				work_mode=1;
				dingshi_counter=1.5*3600*1000;

			}
			else
			{
				if(dingshi_start==1)
				{
					work_mode=0;
					dingshi_counter=0;
					dingshi_start=0;
					uv_start=0;
					uv_counter=0;

				}
				else
				{
					set_dingshi_time_plus();					
				}
			}
		}
		count0=0;
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
			count0++;
			if(count0%350==0)
			{
				static char i=0;
				if(i==0)
				{
					display_dingshi_set();					
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
			if(dingshi_counter>0)
			{
				dingshi_start=1;
			}
			else 
			{
				dingshi_start=0;
				if(uv_start==0)
				{
					uv_start=1;
					uv_counter=20*60*1000;
				}
				else if(uv_counter==0)
				{
					uv_start=0;
					work_mode=0;

				}
				
				
			}
		}

	}
	

}
void work_check()
{
	static char inited=0;
	static u16 count02=0;
	if(inited==0)
	{
		P1M3=GPIO_Out_PP;//fan
		P0M7=GPIO_Out_PP;//vu
		P1M4=GPIO_Out_PP;//vu_notice
		P1M6=GPIO_Out_PP;//jiare
		inited=1;
	}
	if(work_mode==1 )
	{
		if(dingshi_start==1)
		{
			P1_3=1;
			P1_6=1;
		}
		else
		{
			P1_3=0;
			P1_6=0;
		}
		if(uv_start==1)
		{
			P0_7=1;
			P1_4=1;
		}
		else
		{
			P0_7=0;
			P1_4=0;
		}
	}
	else
	{
		P1_3=0;
		P0_7=0;
		P1_4=0;
		P1_6=0;
	}

	if(last_work_mode!=work_mode)
	{
		
		if(last_work_mode==1 && work_mode==0)
		{
			count02++;
			if(count02<60000)
			{
				P1_6=1;
			}
			else
			{
				count02=0;
				P1_6=0;
				last_work_mode=work_mode;
			}
		}
		else
		{
			last_work_mode=work_mode;
		}
	}
	else
	{
		count02=0;
	}

}
/***********************************按键处理**************************************/
void on_off()
{

}

/***********************************红外解码**************************************/
u8 c_timer=0; 
u8 c_end_flag=0;
u8 c_start_flag=0;
u8 nec_buff[34];
u8 nec_index=0;
u8 nec_data[4];
void init_timer1()
{
	TCON1 = 0x00;						//
	TMOD = 0x00;						//
	// (65536-x)/(16000000/12)=0.05
	// x=65536-0.0001*16000000/12      100uS

	TH0 = 0xFF;
	TL0 = 0x7B;							//100us
	IE |= 0x08;							//打开T1中断
	TCON |= 0x40;						//使能T1
}
void ISR_Timer1(void)     interrupt TIMER1_VECTOR
{
  	c_timer++;
  	if(c_timer>150)
  	{
  		c_end_flag=1;
  		c_timer=0;
  	}
}	
void init_exti0()
{
	P1M7 = 0x69;			        	//P00设置为带SMT上拉输入
	PITS0 |= 0x01;						//INT0下降沿
	IE |= 0x01;							//打开INT0中断
}
void ISR_INT0(void) interrupt INT0_VECTOR
{
  	if(c_start_flag)
  	{
  		if(c_timer>135)
  		{
  			nec_index=0;
  		}
  		nec_buff[nec_index]=c_timer;
  		c_timer=0;
  		nec_index++;
  		if(nec_index>33)
  		{
  			nec_index=0;
  		}
  		c_end_flag=0;
  	}
  	else
  	{
  		c_start_flag=1;
  		c_timer=0;
  	}
}
void check_nec()
{
	if(nec_data[3]==1)
	{
		if(work_mode==0)
		{
			work_mode=1;
			dingshi_counter=1.5*3600*1000;
		}
		else
		{
			work_mode=0;
			dingshi_counter=0;
			dingshi_start=0;
			uv_start=0;
			uv_counter=0;
		}
	}
	else if(work_mode==1)
	{
		if(nec_data[3]==2)//定时
		{
			set_dingshi_time_plus()；
			count0=0；
		}
		else if(nec_data[3]==3)//uv
		{
			if(uv_start==0)
			{
				uv_start=1;
				uv_counter=20*60*1000;
			}
			else
			{
				uv_start=0;
				uv_counter=0;
			}
			
		}
	}
}
void decode_nec()
{
	if(nec_index && c_end_flag)
	{
		nec_data[0]=(nec_buff[1]<12 ? 0 : 1)<<0 |
					(nec_buff[2]<12 ? 0 : 1)<<1 |
					(nec_buff[3]<12 ? 0 : 1)<<2 |
					(nec_buff[4]<12 ? 0 : 1)<<3 |
					(nec_buff[5]<12 ? 0 : 1)<<4 |
					(nec_buff[6]<12 ? 0 : 1)<<5 |
					(nec_buff[7]<12 ? 0 : 1)<<6 |
					(nec_buff[8]<12 ? 0 : 1)<<7 ;
		nec_data[1]=(nec_buff[9]<12 ? 0 : 1)<<0 |
					(nec_buff[10]<12 ? 0 : 1)<<1 |
					(nec_buff[11]<12 ? 0 : 1)<<2 |
					(nec_buff[12]<12 ? 0 : 1)<<3 |
					(nec_buff[13]<12 ? 0 : 1)<<4 |
					(nec_buff[14]<12 ? 0 : 1)<<5 |
					(nec_buff[15]<12 ? 0 : 1)<<6 |
					(nec_buff[16]<12 ? 0 : 1)<<7 ;
		nec_data[2]=(nec_buff[17]<12 ? 0 : 1)<<0 |
					(nec_buff[18]<12 ? 0 : 1)<<1 |
					(nec_buff[19]<12 ? 0 : 1)<<2 |
					(nec_buff[20]<12 ? 0 : 1)<<3 |
					(nec_buff[21]<12 ? 0 : 1)<<4 |
					(nec_buff[22]<12 ? 0 : 1)<<5 |
					(nec_buff[23]<12 ? 0 : 1)<<6 |
					(nec_buff[24]<12 ? 0 : 1)<<7 ;
		nec_data[3]=(nec_buff[25]<12 ? 0 : 1)<<0 |
					(nec_buff[26]<12 ? 0 : 1)<<1 |
					(nec_buff[27]<12 ? 0 : 1)<<2 |
					(nec_buff[28]<12 ? 0 : 1)<<3 |
					(nec_buff[29]<12 ? 0 : 1)<<4 |
					(nec_buff[30]<12 ? 0 : 1)<<5 |
					(nec_buff[31]<12 ? 0 : 1)<<6 |
					(nec_buff[32]<12 ? 0 : 1)<<7 ;
		nec_index=0;
		check_nec()；
		nec_data[0]=0；
		nec_data[1]=0；
		nec_data[2]=0；
		nec_data[3]=0；
	}
}


void main()
{
	
	SystemInit();						//
	init_printf();
//	init_ntc_adc();
//	init_display();
//  init_TIMER0();
	EA = 1;
	CTK_Init();	
							

	//printf("start\n\r");	
//	buzzer();
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
		work_check();
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
#define DISPLAY_A P2_0
#define DISPLAY_B P2_1
#define DISPLAY_C P2_2
#define DISPLAY_D P2_3

//
#define DISPLAY_COM1 P3_4
#define DISPLAY_COM2 P3_5
#define DISPLAY_COM3 P2_4
#define DISPLAY_COM4 P0_2


void init_display()
{
	P2M0=GPIO_Out_PP;
	P2M1=GPIO_Out_PP;
	P2M2=GPIO_Out_PP;
	P2M3=GPIO_Out_PP;
	
	P3M4=GPIO_Out_PP;
	P3M5=GPIO_Out_PP;
	P2M4=GPIO_Out_PP;
	P0M2=GPIO_Out_PP;

	display_off();
}

void display_flash()
{
	static char position=0;
	
	DISPLAY_COM1=1;
	DISPLAY_COM2=1;
	DISPLAY_COM3=1;
	DISPLAY_COM4=1;
	if(position<3)
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
		// DISPLAY_A=(led_buff & 1)? 1:0; 
		// DISPLAY_B=(led_buff & 0x02)? 1:0; 
		// DISPLAY_E=(led_buff & 0x04)? 1:0; 
		// DISPLAY_D=(led_buff & 0x08)? 1:0; 
		// DISPLAY_C=(led_buff & 0x10)? 1:0; 
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
	if(dingshi_counter>0)
	{
		if(dingshi_start==1)
		{
			dingshi_counter--;			
		}
		
	}
	if(uv_counter>0)
	{
		if(uv_start==1)
		{
			uv_counter--;
		}
	}	
}
//void init
/*********************************END OF FILE************************************/










































