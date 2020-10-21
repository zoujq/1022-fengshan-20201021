#ifndef _Delay_C_
#define _Delay_C_
#include "YX23F01CB.h"
#include "YX23F01CB_SYS.h"
#include "YX23F01CB_IO_INIT.h"
/*********************************************************************************************************************/
void Delay_50us(unsigned int n)	   
{
	unsigned char i;
	while(n--)
	{
		for(i=0;i<71;i++);
	}
}
void Delay_ms(unsigned int delay_nms)
{
	while(delay_nms--)
	{
		Delay_50us(20);
	}
}
/*********************************************************************************************************************/
#endif