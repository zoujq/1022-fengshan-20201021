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

char display_buff[2]={0,0};
char display_point=0;
char display_uv=0;
char display_touch_led=0;
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

	c_timer++;
  	if(c_timer>150)
  	{
  		c_end_flag=1;
  		c_timer=0;
  	}
  	
	//display_flash();						//P03
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
void init_exti0()
{
	P0M2 = 0x69;			      //P02设置为带SMT上拉输入
	PITS0 |= 0x01;					//INT0下降沿
	IE |= 0x01;							//打开INT0中断
}
void ISR_INT0(void) interrupt INT0_VECTOR
{
	P2_3=~P2_3;
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
		if(nec_data[3]==2)//
		{
			set_dingshi_time_plus();
			count0=0;
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
		check_nec();
		printf("NEC:%d,%d,%d,%d,\n\r",nec_data[0],nec_data[1],nec_data[2],nec_data[3]);	

		nec_data[0]=0;
		nec_data[1]=0;
		nec_data[2]=0;
		nec_data[3]=0;
	}
}


void main()
{
	
	SystemInit();						//
	init_printf();
//	init_ntc_adc();
	init_display();
 	init_TIMER0();
 	init_exti0();
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
		
		// key_check();
		// work_check();
		Delay_ms(1);
		counter++;
		//display_flash();

	}	
}





/*************************************ADC************************************************/
//0~119℃
u16 code Temp_Table[1]={1

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
#define DISPLAY_COM3 P2_4
#define DISPLAY_COM2 P1_4
#define DISPLAY_COM4 P1_5
#define DISPLAY_COM5 P1_6


void init_display()
{
	P2M0=GPIO_Out_PP;
	P2M1=GPIO_Out_PP;
	P2M2=GPIO_Out_PP;
	P2M3=GPIO_Out_PP;
	
	P3M4=GPIO_Out_PP;
	P2M4=GPIO_Out_PP;
	P1M4=GPIO_Out_PP;
	P1M5=GPIO_Out_PP;
	P1M6=GPIO_Out_PP;

	//display_off();
	DISPLAY_A=1;
	DISPLAY_B=1;
	DISPLAY_C=1;
	DISPLAY_D=0;

	DISPLAY_COM1=1;
	DISPLAY_COM2=1;
	DISPLAY_COM3=1;
	DISPLAY_COM4=1;
	DISPLAY_COM5=1;
}
void display_close()
{
	DISPLAY_COM1=1;
	DISPLAY_COM2=1;
	DISPLAY_COM3=1;
	DISPLAY_COM4=1;
	DISPLAY_COM5=1;
}
void display_1(char c)
{
	switch(c)
	{
		case 0:
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=1;

			DISPLAY_COM1=0;;
			Delay_ms(1);
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=1;
			DISPLAY_C=0;
			DISPLAY_D=0;

			DISPLAY_COM5=0;
			Delay_ms(1);
			break;
		case 1:
			display_close();
			DISPLAY_A=0;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=0;

			DISPLAY_COM1=0;

			Delay_ms(1);
			display_close();
			DISPLAY_A=0;
			DISPLAY_B=0;
			DISPLAY_C=0;
			DISPLAY_D=0;

			DISPLAY_COM5=0;
			Delay_ms(1);
			break;
		case 2:
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=1;
			DISPLAY_C=0;
			DISPLAY_D=1;

			DISPLAY_COM1=0;

			Delay_ms(1);
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=0;
			DISPLAY_C=1;
			DISPLAY_D=0;

			DISPLAY_COM5=0;
			Delay_ms(1);
			break;
		case 3:
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=1;

			DISPLAY_COM1=0;

			Delay_ms(1);
			display_close();
			DISPLAY_A=0;
			DISPLAY_B=0;
			DISPLAY_C=1;
			DISPLAY_D=0;

			DISPLAY_COM5=0;
			Delay_ms(1);
			break;
		case 4:
			display_close();
			DISPLAY_A=0;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=0;

			DISPLAY_COM1=0;

			Delay_ms(1);
			display_close();
			DISPLAY_A=0;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=0;

			DISPLAY_COM5=0;
			Delay_ms(1);
			break;
		case 5:
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=0;
			DISPLAY_C=1;
			DISPLAY_D=1;

			DISPLAY_COM1=0;

			Delay_ms(1);
			display_close();
			DISPLAY_A=0;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=0;

			DISPLAY_COM5=0;
			Delay_ms(1);
			break;
		case 6:
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=0;
			DISPLAY_C=1;
			DISPLAY_D=1;

			DISPLAY_COM1=0;

			Delay_ms(1);
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=0;

			DISPLAY_COM5=0;
			Delay_ms(1);
			break;
		case 7:
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=0;

			DISPLAY_COM1=0;

			Delay_ms(1);
			display_close();
			DISPLAY_A=0;
			DISPLAY_B=0;
			DISPLAY_C=0;
			DISPLAY_D=0;

			DISPLAY_COM5=0;
			Delay_ms(1);
			break;
		case 8:
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=0;

			DISPLAY_COM1=0;

			Delay_ms(1);
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=1;
			DISPLAY_C=0;
			DISPLAY_D=0;

			DISPLAY_COM5=0;
			Delay_ms(1);
			break;
		case 9:
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=1;

			DISPLAY_COM1=0;

			Delay_ms(1);
			display_close();
			DISPLAY_A=0;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=0;

			DISPLAY_COM5=0;
			Delay_ms(1);
		break;

		default:
			display_close();
		break;
	}
}
void display_2(char c)
{
	switch(c)
	{
		case 0:
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=1;

			DISPLAY_COM3=0;
			Delay_ms(1);
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=1;
			DISPLAY_C=0;
			DISPLAY_D=0;

			DISPLAY_COM4=0;
			Delay_ms(1);
			break;
		case 1:
			display_close();
			DISPLAY_A=0;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=0;

			DISPLAY_COM3=0;

			Delay_ms(1);
			display_close();
			DISPLAY_A=0;
			DISPLAY_B=0;
			DISPLAY_C=0;
			DISPLAY_D=0;

			DISPLAY_COM4=0;
			Delay_ms(1);
			break;
		case 2:
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=1;
			DISPLAY_C=0;
			DISPLAY_D=1;

			DISPLAY_COM3=0;

			Delay_ms(1);
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=0;
			DISPLAY_C=1;
			DISPLAY_D=0;

			DISPLAY_COM4=0;
			Delay_ms(1);
			break;
		case 3:
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=1;

			DISPLAY_COM3=0;

			Delay_ms(1);
			display_close();
			DISPLAY_A=0;
			DISPLAY_B=0;
			DISPLAY_C=1;
			DISPLAY_D=0;

			DISPLAY_COM4=0;
			Delay_ms(1);
			break;
		case 4:
			display_close();
			DISPLAY_A=0;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=0;

			DISPLAY_COM3=0;

			Delay_ms(1);
			display_close();
			DISPLAY_A=0;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=0;

			DISPLAY_COM4=0;
			Delay_ms(1);
			break;
		case 5:
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=0;
			DISPLAY_C=1;
			DISPLAY_D=1;

			DISPLAY_COM3=0;

			Delay_ms(1);
			display_close();
			DISPLAY_A=0;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=0;

			DISPLAY_COM4=0;
			Delay_ms(1);
			break;
		case 6:
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=0;
			DISPLAY_C=1;
			DISPLAY_D=1;

			DISPLAY_COM3=0;

			Delay_ms(1);
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=0;

			DISPLAY_COM4=0;
			Delay_ms(1);
			break;
		case 7:
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=0;

			DISPLAY_COM3=0;

			Delay_ms(1);
			display_close();
			DISPLAY_A=0;
			DISPLAY_B=0;
			DISPLAY_C=0;
			DISPLAY_D=0;

			DISPLAY_COM4=0;
			Delay_ms(1);
			break;
		case 8:
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=1;

			DISPLAY_COM3=0;

			Delay_ms(1);
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=1;
			DISPLAY_C=0;
			DISPLAY_D=0;

			DISPLAY_COM4=0;
			Delay_ms(1);
			break;
		case 9:
			display_close();
			DISPLAY_A=1;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=1;

			DISPLAY_COM3=0;

			Delay_ms(1);
			display_close();
			DISPLAY_A=0;
			DISPLAY_B=1;
			DISPLAY_C=1;
			DISPLAY_D=0;

			DISPLAY_COM4=0;
			Delay_ms(1);
		break;

		default:
			display_close();
		break;
	}
}
void display_p(char c)
{
	if(c)
	{
		display_close();
		DISPLAY_D=1;
		DISPLAY_COM5=0;
		Delay_ms(1);
	}
	else
	{
		display_close();
		Delay_ms(1);
	}
}
void display_u(char c)
{
	if(c)
	{
		display_close();
		DISPLAY_A=1;
		DISPLAY_COM2=0;
		Delay_ms(1);
	}
	else
	{
		display_close();
		Delay_ms(1);
	}
}
void display_t(char c)
{
	if(c)
	{
		display_close();
		DISPLAY_D=1;
		DISPLAY_COM4=0;
		Delay_ms(1);
	}
	else
	{
		display_close();
		Delay_ms(1);
	}
}
void display_flash()
{
	display_1(5);
	display_2(6);
	display_p(0);
	display_u(0);
	display_t(1);
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
/*********************************END OF FILE************************************/










































