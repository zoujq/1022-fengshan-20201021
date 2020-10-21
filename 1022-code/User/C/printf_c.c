#include "YX23F01CB.h"
#include "YX23F01CB_SYS.h"
#include "YX23F01CB_IO_INIT.h"

//===================================================================================================
#define PRINTF_BAUDRATE  		9600   
void init_printf()
{
	P2M0 = 0xC1;				        //设置P20推完输出
	
	TXD_MAP = 0x20;						//TXD
	
	T4CON = 0x06;						//T4，波特率发生器

	SCON2 = 0x02;   // uart mode 1
	
	T4 = 65536.5 - (SYSCLK_FOSC / 16 / PRINTF_BAUDRATE); //


}

char putchar (char c)
{
	SBUF = c;

	while(!TI);

	TI = 0;
  return 0;
}