/********************************************************************************

注：本文件不建议用户自行修改！

*******************************************************************************/
#include "YX23F01CB.h"
#include "YX23F01CB_GeneralKey_Touch_Lib_V1.04\YX23F01CB_GeneralKey_Touch_Lib.h"
#include "YX23F01CB_GeneralKey_Touch_Lib_V1.04\YX23F01CB_GeneralKey_Touch_Filter.h"
#include "YX23F01CB_GeneralKey_Touch_Lib_V1.04\YX23F01CB_GeneralKey_Touch_Lib_CFG.h"


//===================================================================================================
/***********************************调用相关库参数，用户不需修改************************************/
#define HexadecimalToBinary(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p)	\
(																\
	(a<<15)+(b<<14)+(c<<13)+(d<<12)+							\
	(e<<11)+(f<<10)+(g<<9)+(h<<8)+								\
	(i<<7)+(j<<6)+(k<<5)+(l<<4)+								\
	(m<<3)+(n<<2)+(o<<1)+(p<<0)									\
)

#define TKBIN HexadecimalToBinary

#define YXTouchLib_OPENED_TK_AMOUNT \
((YXTouchLib_TK_CH_MASK>> 0 & 0x01L)+(YXTouchLib_TK_CH_MASK>> 1 & 0x01L)+(YXTouchLib_TK_CH_MASK>> 2 & 0x01L)+(YXTouchLib_TK_CH_MASK>> 3 & 0x01L)+\
 (YXTouchLib_TK_CH_MASK>> 4 & 0x01L)+(YXTouchLib_TK_CH_MASK>> 5 & 0x01L)+(YXTouchLib_TK_CH_MASK>> 6 & 0x01L)+(YXTouchLib_TK_CH_MASK>> 7 & 0x01L)+\
 (YXTouchLib_TK_CH_MASK>> 8 & 0x01L)+(YXTouchLib_TK_CH_MASK>> 9 & 0x01L)+(YXTouchLib_TK_CH_MASK>>10 & 0x01L)+(YXTouchLib_TK_CH_MASK>>11 & 0x01L)+\
 (YXTouchLib_TK_CH_MASK>>12 & 0x01L)+(YXTouchLib_TK_CH_MASK>>13 & 0x01L)+(YXTouchLib_TK_CH_MASK>>14 & 0x01L)+(YXTouchLib_TK_CH_MASK>>15 & 0x01L))
 
extern ux16	XDATA_RawData[];					//滤波后RawData
extern ux16	XDATA_RawDataBuf[];					//采集所得RawData

//===================================================================================================
#if YXTouchLib_FILTER_DEPTH	
ux16 XDATA_RawData_Filter[YXTouchLib_OPENED_TK_AMOUNT][YXTouchLib_FILTER_DEPTH];
#endif	

//===================================================================================================
#if YXTouchLib_FILTER_DEPTH						//使能滤波
static void BubbleSort(u16 fui_ArrData_a[], u8 fuc_Len)
{
    u16 fui_Temp = 0;
    u8 fuc_i = 0, fuc_j = 0;
    for (fuc_i=0; fuc_i<fuc_Len-1; fuc_i++)
	{
        for (fuc_j=0; fuc_j<fuc_Len-1-fuc_i; fuc_j++) 
		{ 
            if (fui_ArrData_a[fuc_j] > fui_ArrData_a[fuc_j+1]) 
			{ 
                fui_Temp = fui_ArrData_a[fuc_j];
                fui_ArrData_a[fuc_j] = fui_ArrData_a[fuc_j+1];
                fui_ArrData_a[fuc_j+1] = fui_Temp;
            }
        }	
	}
}
#endif	


void TouchRawDataFilter(void)
{
#if YXTouchLib_FILTER_DEPTH						
//使能滤波
	unsigned char fuc_i = 0, fuc_j = 0, fuc_z = 0;
	unsigned long ful_Num[YXTouchLib_OPENED_TK_AMOUNT] = {0x00};
	for(fuc_i = 0; fuc_i < YXTouchLib_OPENED_TK_AMOUNT; fuc_i++)
	{
		XDATA_RawData_Filter[fuc_i][YXTouchLib_FILTER_DEPTH-1] = XDATA_RawDataBuf[fuc_i];
		for(fuc_j = 0; fuc_j<YXTouchLib_FILTER_DEPTH-1; fuc_j++)
		{
			XDATA_RawData_Filter[fuc_i][fuc_j] = XDATA_RawData_Filter[fuc_i][fuc_j+1];
		}
		BubbleSort(XDATA_RawData_Filter[fuc_i],YXTouchLib_FILTER_DEPTH);
		for(fuc_z = 1; fuc_z<YXTouchLib_FILTER_DEPTH-1; fuc_z++)
		{
			ful_Num[fuc_i] += XDATA_RawData_Filter[fuc_i][fuc_z];
		}
		ful_Num[fuc_i] /=  (YXTouchLib_FILTER_DEPTH-2);
		XDATA_RawData[fuc_i] = (u16)(ful_Num[fuc_i]);	
	}
#else											//没有使能滤波
	unsigned char fuc_i = 0;
	for(fuc_i = 0;fuc_i < YXTouchLib_OPENED_TK_AMOUNT;fuc_i++)
	{
		XDATA_RawData[fuc_i] = XDATA_RawDataBuf[fuc_i];
	}	
#endif
}

/******************************************************************************************************

 ******************************************************************************************************/
