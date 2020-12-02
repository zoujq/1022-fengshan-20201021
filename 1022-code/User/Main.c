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
void display_flash();
//================================================================================

char display_data1='X';
char display_data2='X';
char display_point=0;
char display_uv_led=0;
char display_touch_led=0;


char dingshi_start=0;
u32 dingshi_counter=0;
char uv_start=0;
u32 uv_counter=0;
char work_mode=0;
char last_hoted=0;
u32 nec_jian_ge=0;
u32 op_over_count=0;

char feng_gan_stop_flag=0;
u32 fan_delay_counter=0;



//================================================================================

void set_dingshi_time_plus()
{
	dingshi_counter+=30;
	if(dingshi_counter>6*60)
	{
		dingshi_counter=30;
	}
}

void set_dingshi_time_add()
{
	dingshi_counter+=30;
	if(dingshi_counter>6*60)
	{
		dingshi_counter=6*60;
	}
}
void set_dingshi_time_red()
{
	if(dingshi_counter>30)
	{
		dingshi_counter-=30;
	}
	else
	{
		dingshi_counter=30;
	}
}

void display_dingshi_set()
{
	display_data1=dingshi_counter/60;
	display_data2=(dingshi_counter)%60;
	if(display_data2>30)
	{
		display_data1+=1;
		display_data2=0;
	}
	else if(display_data2>0)
	{
		display_data2=5;
	}
	else
	{
		display_data2=0;
	}
	display_point=1;
}


void display_dingshi_time()
{
	static u16 i6=0;
	display_data1=dingshi_counter/60;
	display_data2=(dingshi_counter)%60;
	if(display_data2>30)
	{
		display_data1+=1;
		display_data2=0;
	}
	else if(display_data2>0)
	{
		display_data2=5;
	}
	else
	{
		display_data2=0;
	}
	
	if(i6==1)
	{
		display_point=1;
	} 
	else if(i6==50)
	{					
		display_point=0;					
	}
	else if(i6==100)
	{
		i6=0;
	}
	i6++;
}
void display_uv_time()
{
	display_data1=uv_counter/10;
	display_data2=uv_counter%10;
	display_point=0;	
	
}

void display_off()
{
	display_data1='X';
	display_data2='X';
	display_point=0;
}

void display_none()
{
	display_data1='+';
	display_data2='+';
	display_point=0;
}
void key_check()
{
	static u16 ON_TK=0;
	if(TouchKeyFlag )
	{		
		if(ON_TK==0)
		{
			ON_TK=1;
			if(work_mode==0)
			{
				work_mode=1;				
				dingshi_counter=90;
			}
			else
			{
				if(dingshi_start==1 || uv_start==1)
				{
					work_mode=0;
					dingshi_counter=0;
					dingshi_start=0;
					uv_start=0;
					uv_counter=0;

				}
				else
				{
					if(uv_counter==0)
					{
						set_dingshi_time_plus();	
						display_dingshi_set();		
					}						
				}
			}
			op_over_count=0;
		}
		
	}
	else
	{
		ON_TK=0;
	}

}
#define FAN P1_1
#define UV P0_7
#define JIARE P0_3
#define LED1_UV P1_2 
#define LED2_TOUCH P1_3 

void work_check()
{
	static char inited=0;
	static u16 count02=0;
	if(inited==0)
	{
		P1M1=GPIO_Out_PP;//fan
		P0M7=GPIO_Out_PP;//vu
		P0M3=GPIO_Out_PP;//jiare
		P1M2=GPIO_Out_PP;//LED uv 
		P1M3=GPIO_Out_PP;//LED2_TOUCH
		
		inited=1;
	}
	
	if(work_mode==0)
	{
		static u16 i5=0;
				
		if(i5==1)
		{
			display_touch_led=0x01;
		} 
		else if(i5==60)
		{					
			display_touch_led=0x00;					
		}
		else if(i5==120)
		{
			i5=0;
		}
		i5++;
		
		op_over_count=0;	
		display_uv_led=0;
		display_off();		
		FAN=0;
		JIARE=0;
		UV=0;
		dingshi_counter=0;
		dingshi_start=0;
		uv_start=0;
		uv_counter=0;
		
	}
	else
	{
		display_touch_led=1;
		if(op_over_count<300)
		{			
			op_over_count++;
			FAN=0;
			JIARE=0;
			UV=0;
			dingshi_start=0;
			uv_start=0;
			if(op_over_count==1 || op_over_count==100 || op_over_count==200 )
			{				
					if(dingshi_counter>0)
					{
						display_dingshi_set();
					}						
					else
					{
						display_uv_time();
					}
			}
			else if(op_over_count==50 || op_over_count==150 || op_over_count==250)
			{
				display_none();
			}
			if(op_over_count==300)
			{
					if(dingshi_counter>0)
					{
						display_dingshi_set();
						dingshi_start=1;
					}						
					else
					{
						display_uv_time();
						uv_start=1;
					}
			}
		
			
		}
		else
		{
			if(dingshi_counter>0)
			{
				FAN=1;
				JIARE=1;
				display_dingshi_time();
			}
			else
			{
				FAN=0;
				JIARE=0;
			}
			if(feng_gan_stop_flag==1)
			{
				uv_start=1;
				uv_counter=20;
				feng_gan_stop_flag=0;
				fan_delay_counter=10;
			}
			if(uv_counter>0)
			{
				if(fan_delay_counter>0)
				{
					static u16 i51=0;
					UV=0;
					if(i51==1)
					{
						display_uv_led=0x01;
					} 
					else if(i51==60)
					{					
						display_uv_led=0x00;					
					}
					else if(i51==120)
					{
						i51=0;
					}
					i51++;					
				}
				else
				{
					UV=1;
					display_uv_led=1;
				}
				
				display_uv_time();
			}
			else
			{
				UV=0;
				display_uv_led=0;
			}
			
		}		
		
	}
	if(last_hoted!=dingshi_start)
	{
		if(last_hoted==1 && dingshi_start==0)
		{
			fan_delay_counter=15700;
			last_hoted=dingshi_start;
		}
		else
		{
			last_hoted=dingshi_start;
		}
	}
	if(fan_delay_counter>0)
	{
		fan_delay_counter--;
		FAN=1;
	}
	
}


/***********************************红外解码**************************************/
u8 c_timer=0; 
u8 c_end_flag=0;
u8 c_start_flag=0;
xdata u8 nec_buff[34];
u8 nec_index=0;
xdata u8 nec_data[4];
void init_TIMER0()
{
	TCON1 = 0x00;						//
	TMOD = 0x00;						//
	
	TH0 = 0xFF;
	TL0 = 0x7B;							//100us
	IE |= 0x02;							//
	TCON |= 0x10;						//
    
}

void TIMER0_Rpt(void) interrupt TIMER0_VECTOR  //时基100us
{
	static u32 tt=0;

	c_timer++;
	if(c_timer>150)
	{
		c_end_flag=1;
		c_timer=0;
	}
  if(tt++>600000)
	{
		tt=0;
		if(work_mode==1)		
		{			
			if(dingshi_counter>0)
			{
				if(dingshi_start==1)
				{
					dingshi_counter--;	
					if(dingshi_counter==0)
					{
						feng_gan_stop_flag=1;
						dingshi_start=0;
					}
				}
				
			}
			if(uv_counter>0)
			{
				if(uv_start==1 && fan_delay_counter==0)
				{
					uv_counter--;
					if(uv_counter==0)
					{
						uv_start=0;
						work_mode=0;
					}
				}
			}
		}		
	}
	nec_jian_ge++;
}	
void init_exti0()
{
	P3M5 = 0x69;			      //P35设置为带SMT上拉输入
	PITS4 = 0x04;					//INT17下降沿	
	PINTE2 = 0x02;
	IE2 |= 0x01;							//打开INT17中断
	
}

void ISR_INT16_17(void)  interrupt INT16_17_VECTOR
{
	PINTF2 &=~ 0x02;				//清除INT17中断标志位		

		if(c_timer>50)
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
		c_timer=0;

}
void chu_li_nec()
{
	if(nec_data[0]==0 && nec_data[1]==0xff)
	{
		if(nec_jian_ge<3000)
		{
			return;
		}
		nec_jian_ge=0;
		if(nec_data[2]==0)
		{
			if(work_mode==0)
			{
				work_mode=1;
				dingshi_counter=90;
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
		else if(work_mode==1 && uv_start==0)
		{
			if(uv_counter==0)
			{
				if(nec_data[2]==0x08)//
				{
										
					set_dingshi_time_add();				
					op_over_count=0;
				}
				else if(nec_data[2]==0x0A)//
				{
						
					set_dingshi_time_red();				
					op_over_count=0;
				}
			}
			
		}
		if(nec_data[2]==0x02)//uv
		{
			if(uv_start==0)
			{
				work_mode=1;
				uv_start=0;
				uv_counter=20;
				dingshi_counter=0;
				dingshi_start=0;
				op_over_count=0;
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
	}
	
}
extern char putchar (char c);
void decode_nec()
{
	if(nec_index && c_end_flag)
	{
		nec_data[0]=(nec_buff[1]<0x0F ? 0 : 1)<<0 |
					(nec_buff[2]<0x0F ? 0 : 1)<<1 |
					(nec_buff[3]<0x0F ? 0 : 1)<<2 |
					(nec_buff[4]<0x0F ? 0 : 1)<<3 |
					(nec_buff[5]<0x0F ? 0 : 1)<<4 |
					(nec_buff[6]<0x0F ? 0 : 1)<<5 |
					(nec_buff[7]<0x0F ? 0 : 1)<<6 |
					(nec_buff[8]<0x0F ? 0 : 1)<<7 ;
		nec_data[1]=(nec_buff[9]<0x0F ? 0 : 1)<<0 |
					(nec_buff[10]<0x0F ? 0 : 1)<<1 |
					(nec_buff[11]<0x0F ? 0 : 1)<<2 |
					(nec_buff[12]<0x0F ? 0 : 1)<<3 |
					(nec_buff[13]<0x0F ? 0 : 1)<<4 |
					(nec_buff[14]<0x0F ? 0 : 1)<<5 |
					(nec_buff[15]<0x0F ? 0 : 1)<<6 |
					(nec_buff[16]<0x0F ? 0 : 1)<<7 ;
		nec_data[2]=(nec_buff[17]<0x0F ? 0 : 1)<<0 |
					(nec_buff[18]<0x0F ? 0 : 1)<<1 |
					(nec_buff[19]<0x0F ? 0 : 1)<<2 |
					(nec_buff[20]<0x0F ? 0 : 1)<<3 |
					(nec_buff[21]<0x0F ? 0 : 1)<<4 |
					(nec_buff[22]<0x0F ? 0 : 1)<<5 |
					(nec_buff[23]<0x0F ? 0 : 1)<<6 |
					(nec_buff[24]<0x0F ? 0 : 1)<<7 ;
		nec_data[3]=(nec_buff[25]<0x0F ? 0 : 1)<<0 |
					(nec_buff[26]<0x0F ? 0 : 1)<<1 |
					(nec_buff[27]<0x0F ? 0 : 1)<<2 |
					(nec_buff[28]<0x0F ? 0 : 1)<<3 |
					(nec_buff[29]<0x0F ? 0 : 1)<<4 |
					(nec_buff[30]<0x0F ? 0 : 1)<<5 |
					(nec_buff[31]<0x0F ? 0 : 1)<<6 |
					(nec_buff[32]<0x0F ? 0 : 1)<<7 ;
			nec_index=0;
			chu_li_nec();

		
		
//		putchar(0x56);
//		putchar(nec_data[0]);
//		putchar(nec_data[1]);
//	  putchar(nec_data[2]);
//		putchar(nec_data[3]);
		
		{
			int i=0;
			for(i=0;i<33;i++)
			{
				nec_buff[i]=0;
			}
			
		}

	}
}







/*************************************ADC************************************************/


/***************************************************************************/
//
//#define DISPLAY_A P2_5  P2_1
//#define DISPLAY_B P2_4  P3_4
//#define DISPLAY_C P2_2  P1_4
//#define DISPLAY_D P2_3  P2_4
//#define DISPLAY_E P2_1  P2_5
//#define DISPLAY_F P1_4  P2_2
//#define DISPLAY_G P3_4  P2_3

#define DISPLAY_A  P2_1
#define DISPLAY_B  P3_4
#define DISPLAY_C  P2_4
#define DISPLAY_D  P2_5
#define DISPLAY_E  P0_2
#define DISPLAY_F  P2_2
#define DISPLAY_G  P2_3
#define DISPLAY_DP P2_0//P2_0//  printf("%s\n", );

//
#define DISPLAY_COM1 P1_6
#define DISPLAY_COM2 P1_5



void init_display()
{
	P2M1=GPIO_Out_PP;
	P3M4=GPIO_Out_PP;
	P2M4=GPIO_Out_PP;
	P2M5=GPIO_Out_PP;
	P0M2=GPIO_Out_PP;
	P2M2=GPIO_Out_PP;
	P2M3=GPIO_Out_PP;
	P2M0=GPIO_Out_PP;
	
	P1M6=GPIO_Out_PP;
	P1M5=GPIO_Out_PP;

	//display_off();
	DISPLAY_A=0;
	DISPLAY_B=0;
	DISPLAY_C=0;
	DISPLAY_D=0;
	DISPLAY_E=0;
	DISPLAY_F=0;
	DISPLAY_G=0;
	DISPLAY_DP=0;

	DISPLAY_COM1=1;
	DISPLAY_COM2=1;

}
void display_close()
{
	DISPLAY_A=0;
	DISPLAY_B=0;
	DISPLAY_C=0;
	DISPLAY_D=0;
	DISPLAY_E=0;
	DISPLAY_F=0;
	DISPLAY_G=0;
	DISPLAY_DP=0;
	DISPLAY_COM1=1;
	DISPLAY_COM2=1;

}


void display_1(char c,char b)
{
//	display_point
	
	
	DISPLAY_COM1=1;
	DISPLAY_COM2=1;
	
	switch(c)
	{
		case 0:
			DISPLAY_A=1;	DISPLAY_B=1;	DISPLAY_C=1;	DISPLAY_D=1;	DISPLAY_E=1;	DISPLAY_F=1;	DISPLAY_G=0;
			break;
		case 1:
			DISPLAY_A=0;	DISPLAY_B=1;	DISPLAY_C=1;	DISPLAY_D=0;	DISPLAY_E=0;	DISPLAY_F=0;	DISPLAY_G=0;
			break;
		case 2:
			DISPLAY_A=1;	DISPLAY_B=1;	DISPLAY_C=0;	DISPLAY_D=1;	DISPLAY_E=1;	DISPLAY_F=0;	DISPLAY_G=1;
			break;
		case 3:
			DISPLAY_A=1;	DISPLAY_B=1;	DISPLAY_C=1;	DISPLAY_D=1;	DISPLAY_E=0;	DISPLAY_F=0;	DISPLAY_G=1;
			break;
		case 4:
			DISPLAY_A=0;	DISPLAY_B=1;	DISPLAY_C=1;	DISPLAY_D=0;	DISPLAY_E=0;	DISPLAY_F=1;	DISPLAY_G=1;
			break;
		case 5:
			DISPLAY_A=1;	DISPLAY_B=0;	DISPLAY_C=1;	DISPLAY_D=1;	DISPLAY_E=0;	DISPLAY_F=1;	DISPLAY_G=1;
			break;
		case 6:
			DISPLAY_A=1;	DISPLAY_B=0;	DISPLAY_C=1;	DISPLAY_D=1;	DISPLAY_E=1;	DISPLAY_F=1;	DISPLAY_G=1;
			break;
		case 7:
			DISPLAY_A=1;	DISPLAY_B=1;	DISPLAY_C=1;	DISPLAY_D=0;	DISPLAY_E=0;	DISPLAY_F=0;	DISPLAY_G=0;
			break;
		case 8:
			DISPLAY_A=1;	DISPLAY_B=1;	DISPLAY_C=1;	DISPLAY_D=1;	DISPLAY_E=1;	DISPLAY_F=1;	DISPLAY_G=1;
			break;
		case 9:
			DISPLAY_A=1;	DISPLAY_B=1;	DISPLAY_C=1;	DISPLAY_D=1;	DISPLAY_E=0;	DISPLAY_F=1;	DISPLAY_G=1;
			break;
		default:
			DISPLAY_A=0;	DISPLAY_B=0;	DISPLAY_C=0;	DISPLAY_D=0;	DISPLAY_E=0;	DISPLAY_F=0;	DISPLAY_G=0;
			break;
		
	}
	if(b==1)
	{
		DISPLAY_COM1=0;
		DISPLAY_COM2=1;
		if(display_point)
		{
				DISPLAY_DP=1;
		}
		else
		{
				DISPLAY_DP=0;
		}
	}
	else if(b==2)
	{
		DISPLAY_COM1=1;
		DISPLAY_COM2=0;
		DISPLAY_DP=0;
	}
	
	
}
void display_uv_(char c)
{
	if(c)
	{
		LED1_UV=1;
	}
	else
	{
		LED1_UV=0;
	}
}
void display_touch_(char c)
{
	if(c)
	{
		LED2_TOUCH=1;
	}
	else
	{
		LED2_TOUCH=0;
	}
}
void display_flash()
{
	display_1(display_data1,1);
	Delay_ms(4);
	display_1(display_data2,2);
	display_uv_(display_uv_led);
	display_touch_(display_touch_led);
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

//void init




void main()
{
	u32 ts=0;
	SystemInit();						//
	//init_printf();
	init_display();
 	init_TIMER0();
 	init_exti0();
	EA = 1;
	CTK_Init();	
							

	//printf("start\n\r");	
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
		decode_nec();
		Delay_ms(4);
		display_flash();
		work_check();

//		if(ts++>200)
//		{
//			ts=0;
//			// char work_mode=0;
//			// char dingshi_start=0;
//			// u32 dingshi_counter=0;
//			// char uv_start=0;
//			// u32 uv_counter=0;
//			
//			// char last_hoted=0;
//			// u32 op_over_count=0;

//			// char feng_gan_stop_flag=0;
//			// u32 fan_delay_counter=0;

//			// putchar(work_mode);
//			// putchar(dingshi_start);
//			// putchar(dingshi_counter&0xff);
//			// putchar(uv_start);
//			// putchar(uv_counter&0xff);
//			// putchar(last_hoted);
//			// putchar(op_over_count&0xff);
//			// putchar(feng_gan_stop_flag);
//			// putchar(fan_delay_counter&0xff);
//			// putchar('\n');

//		}

	}	
}


/*********************************END OF FILE************************************/




































