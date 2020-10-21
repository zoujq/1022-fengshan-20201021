
/********************************************************************************

注：本文件不建议用户自行修改！

*******************************************************************************/
//===================================================================================================
#include "YX_DEFINE.H"
#include "YX23F01CB_GeneralKey_Touch_Lib_V1.04\YX23F01CB_GeneralKey_Touch_Lib_CFG.h"
#include "YX23F01CB_GeneralKey_Touch_Lib_V1.04\YX23F01CB_GeneralKey_Touch_Filter.h"
#include "YX23F01CB_GeneralKey_Touch_Lib_V1.04\YX23F01CB_GeneralKey_Touch_Multibutton.h"

//===================================================================================================
#define HexadecimalToBinary(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p)	\
(																\
	(a<<15)+(b<<14)+(c<<13)+(d<<12)+							\
	(e<<11)+(f<<10)+(g<<9)+(h<<8)+								\
	(i<<7)+(j<<6)+(k<<5)+(l<<4)+								\
	(m<<3)+(n<<2)+(o<<1)+(p<<0)									\
)
#define TKBIN HexadecimalToBinary

//===================================================================================================
#if (YXTouchLib_IC_BODY == IC_BODY_SOP16)
#pragma message "IC Body: YX23F01CB-SOP16"
#define TK_CH_MAX  		7
uc8 CODE_INTERNAL_INDEX[TK_CH_MAX] = {2, 7, 11, 12, 13, 14, 15};

#elif (YXTouchLib_IC_BODY == IC_BODY_SOP20_DIP20)
#pragma message "IC Body: YX23F01CB-SOP20/DIP20"
#define TK_CH_MAX  		10
uc8 CODE_INTERNAL_INDEX[TK_CH_MAX] = {2, 3, 7, 9, 10, 11, 12, 13, 14, 15};

#elif (YXTouchLib_IC_BODY == IC_BODY_SOP24)
#pragma message "IC Body: YX23F01CB-SOP24"
#define TK_CH_MAX  		12
uc8 CODE_INTERNAL_INDEX[TK_CH_MAX] = {0, 1, 2, 3, 7, 9, 10, 11, 12, 13, 14, 15};

#elif (YXTouchLib_IC_BODY == IC_BODY_SOP28)
#pragma message "IC Body: YX23F01CB-SOP28"
#define TK_CH_MAX  		16
uc8 CODE_INTERNAL_INDEX[TK_CH_MAX] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

#else
#define TK_CH_MAX  		1
uc8 CODE_INTERNAL_INDEX[TK_CH_MAX] = {0};
#error "No IC Body,Please reconfigure YXTouchLib_IC_BODY"
#endif

//===================================================================================================
#include "YX23F01CB_GeneralKey_Touch_Lib_V1.04\YX23F01CB_GeneralKey_Touch_Lib_Build_Message.h"

//===================================================================================================
#if ((YXTouchLib_TK_CH_MASK & (0xFFFF >> (16 - TK_CH_MAX))) == 0)
#error "No channel is enabled,Please reconfigure YXTouchLib_TK_CH_MASK"
#endif

//===================================================================================================
//开启的检测通道个数
#define YXTouchLib_OPENED_TK_AMOUNT \
((YXTouchLib_TK_CH_MASK>> 0 & 0x01L)+(YXTouchLib_TK_CH_MASK>> 1 & 0x01L)+(YXTouchLib_TK_CH_MASK>> 2 & 0x01L)+(YXTouchLib_TK_CH_MASK>> 3 & 0x01L)+\
 (YXTouchLib_TK_CH_MASK>> 4 & 0x01L)+(YXTouchLib_TK_CH_MASK>> 5 & 0x01L)+(YXTouchLib_TK_CH_MASK>> 6 & 0x01L)+(YXTouchLib_TK_CH_MASK>> 7 & 0x01L)+\
 (YXTouchLib_TK_CH_MASK>> 8 & 0x01L)+(YXTouchLib_TK_CH_MASK>> 9 & 0x01L)+(YXTouchLib_TK_CH_MASK>>10 & 0x01L)+(YXTouchLib_TK_CH_MASK>>11 & 0x01L)+\
 (YXTouchLib_TK_CH_MASK>>12 & 0x01L)+(YXTouchLib_TK_CH_MASK>>13 & 0x01L)+(YXTouchLib_TK_CH_MASK>>14 & 0x01L)+(YXTouchLib_TK_CH_MASK>>15 & 0x01L))

#define  USERDATA  YXTouchLib_OPENED_TK_AMOUNT 

//===================================================================================================
#define YXTouchLib_NOISE_THRESHOLD { \
 YXTouchLib_SET0_N_THRESHOLD,  YXTouchLib_SET1_N_THRESHOLD,  YXTouchLib_SET2_N_THRESHOLD,  YXTouchLib_SET3_N_THRESHOLD,  \
 YXTouchLib_SET4_N_THRESHOLD,  YXTouchLib_SET5_N_THRESHOLD,  YXTouchLib_SET6_N_THRESHOLD,  YXTouchLib_SET7_N_THRESHOLD,  \
 YXTouchLib_SET8_N_THRESHOLD,  YXTouchLib_SET9_N_THRESHOLD,  YXTouchLib_SET10_N_THRESHOLD, YXTouchLib_SET11_N_THRESHOLD, \
 YXTouchLib_SET12_N_THRESHOLD, YXTouchLib_SET13_N_THRESHOLD, YXTouchLib_SET14_N_THRESHOLD, YXTouchLib_SET15_N_THRESHOLD  \
}

#define YXTouchLib_FINGER_THRESHOLD { \
 YXTouchLib_SET0_F_THRESHOLD,  YXTouchLib_SET1_F_THRESHOLD,  YXTouchLib_SET2_F_THRESHOLD,  YXTouchLib_SET3_F_THRESHOLD,  \
 YXTouchLib_SET4_F_THRESHOLD,  YXTouchLib_SET5_F_THRESHOLD,  YXTouchLib_SET6_F_THRESHOLD,  YXTouchLib_SET7_F_THRESHOLD,  \
 YXTouchLib_SET8_F_THRESHOLD,  YXTouchLib_SET9_F_THRESHOLD,  YXTouchLib_SET10_F_THRESHOLD, YXTouchLib_SET11_F_THRESHOLD, \
 YXTouchLib_SET12_F_THRESHOLD, YXTouchLib_SET13_F_THRESHOLD, YXTouchLib_SET14_F_THRESHOLD, YXTouchLib_SET15_F_THRESHOLD  \
}

//===================================================================================================
uc16	CODE_TK_CH_MASK                 = YXTouchLib_TK_CH_MASK;
uc8		CODE_CHANNEL_CALIBRATE_SW       = 0;
uc8		CODE_CALIBRATE_DEFLECTED_AREA   = 20;
uc8		CODE_CALIBRATE_TARGET_LINE      = 0;
uc8		CODE_DSCR                       = YXTouchLib_DSCR;
uc8		CODE_CTKDS_PRSDIV               = (0 << 4) | (1 << 3) | YXTouchLib_PRSDIV;
uc8		CODE_VD_RV                      = (YXTouchLib_VD << 4) | 0;
uc8		CODE_RBS                        = (0 << 7) | YXTouchLib_RBS;
uc8		CODE_Continue_Scan_SW           = 1;
uc8		CODE_OFFSET_SW                  = 0;
uc16	CODE_OVERHIGH_TIME              = YXTouchLib_OVERHIGH_TIME;
uc16	CODE_OVERLOW_TIME               = YXTouchLib_OVERLOW_TIME;
uc8		CODE_CONFIRM_TOUCH_TIME         = YXTouchLib_CONFIRM_TOUCH_TIME;
uc8		CODE_CONFIRM_NOTOUCH_TIME       = YXTouchLib_CONFIRM_NOTOUCH_TIME;
uc8		CODE_LIMIT_FACTOR               = YXTouchLib_LIMIT_FACTOR;
uc8		CODE_BARREL_CAPACITY            = YXTouchLib_NOISE_BARREL_CAPACITY;
uc16	CODE_NOISE_THRESHOLD[16]        = YXTouchLib_NOISE_THRESHOLD;
uc16	CODE_FINGER_THRESHOLD[16]       = YXTouchLib_FINGER_THRESHOLD;
uc8		CODE_OPENED_TK_AMOUNT           = YXTouchLib_OPENED_TK_AMOUNT;
uc8		CODE_Hysteresis					= YXTouchLib_Hysteresis;
uc8 	CODE_TK_CH_MAX                  = TK_CH_MAX;
uc8		CODE_FILTER_DEPTH				= YXTouchLib_FILTER_DEPTH;

//===================================================================================================
ux16	XDATA_RawData 	 [YXTouchLib_OPENED_TK_AMOUNT];
ux16	XDATA_RawDataBuf [YXTouchLib_OPENED_TK_AMOUNT];
sx16 	XDATA_BaseLine	 [YXTouchLib_OPENED_TK_AMOUNT];
ux16 	XDATA_OverLowCnt [YXTouchLib_OPENED_TK_AMOUNT];
ux16 	XDATA_OverHighCnt[YXTouchLib_OPENED_TK_AMOUNT];
ux8 	XDATA_TouchCnt   [YXTouchLib_OPENED_TK_AMOUNT];
ux8 	XDATA_NoTouchCnt [YXTouchLib_OPENED_TK_AMOUNT];
sx16 	XDATA_DifferAccum[YXTouchLib_OPENED_TK_AMOUNT];
ux16	XDATA_LongRstCnt [YXTouchLib_OPENED_TK_AMOUNT];
ux16	XDATA_THRNoiseCnt[YXTouchLib_OPENED_TK_AMOUNT];
ux8  	XDATA_AccessIndex[TK_CH_MAX];
ux16	XDATA_CONFIRM_LONGTOUCH_TIME	= YXTouchLib_CONFIRM_LONGTOUCH_TIME;
ux16	XDATA_THRESHOLD_NOISE_TIME		= YXTouchLib_CONFIRM_LONGTOUCH_TIME;
ux8		XDATA_THRESHOLD_RATIO			= 10;
ux8		XDATA_FineTuning				= 2;

/******************************************************************************************************

 ******************************************************************************************************/
 