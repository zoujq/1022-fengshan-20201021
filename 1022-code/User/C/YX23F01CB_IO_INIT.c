
/*******************************************************************************/
#include	"YX23F01CB.h"
#include	"YX23F01CB_IO_INIT.h"

/****************************************************************************
* Function Name  :
* Description    :
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/
void IO_Init(void)
{
	P0 = 0X00;
	P0M0 = GPIO_In_AN; //
	P0M1 = GPIO_In_AN; //
	P0M2 = GPIO_In_AN; //
	P0M3 = GPIO_In_AN; //
	P0M4 = GPIO_In_AN; //
	P0M5 = GPIO_In_AN; //
	P0M6 = GPIO_In_AN; //
	P0M7 = GPIO_In_AN; //

	P1M0 = GPIO_In_AN; //
	P1M1 = GPIO_In_AN; //
	P1M2 = GPIO_In_AN; //
	P1M3 = GPIO_In_AN; //
	P1M4 = GPIO_In_AN; //
	P1M5 = GPIO_In_AN; //
	P1M6 = GPIO_In_AN; //
	P1M7 = GPIO_In_AN; //

	P2 = 0X00;
	P2M0 = GPIO_In_AN; //SW_SDA
	P2M1 = GPIO_In_AN; //
	P2M2 = GPIO_In_AN; //SW_SCK
	P2M3 = GPIO_In_AN; //
	P2M4 = GPIO_In_AN; //
	P2M5 = GPIO_In_AN; //
	P2M6 = GPIO_In_AN; //
	P2M7 = GPIO_In_AN; //

	P3 = 0X00;
	P3M4 = GPIO_In_AN; //
	P3M5 = GPIO_In_AN; //
}

/*********************************END OF FILE************************************/

