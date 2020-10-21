/********************************************************************************

注：本文件不建议用户自行修改！

*******************************************************************************/
#ifndef __YX23F01CB_GeneralKey_Touch_Lib_Build_Message_H__
#define __YX23F01CB_GeneralKey_Touch_Lib_Build_Message_H__

//================================================================================
#if (YXTouchLib_IC_BODY == IC_BODY_SOP16)

#if (YXTouchLib_TK_CH_MASK & 0x0001L)
#pragma message "TK2：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0002L)
#pragma message "TK7：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0004L)
#pragma message "TK11：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0008L)
#pragma message "TK12：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0010L)
#pragma message "TK13：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0020L)
#pragma message "TK14：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0040L)
#pragma message "TK15：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0080L)
#error          "Error：Please reconfigure YXTouchLib_TK_CH_MASK"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0100L)
#error          "Error：Please reconfigure YXTouchLib_TK_CH_MASK"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0200L)
#error          "Error：Please reconfigure YXTouchLib_TK_CH_MASK"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0400L)
#error          "Error：Please reconfigure YXTouchLib_TK_CH_MASK"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0800L)
#error          "Error：Please reconfigure YXTouchLib_TK_CH_MASK"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x1000L)
#error          "Error：Please reconfigure YXTouchLib_TK_CH_MASK"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x2000L)
#error          "Error：Please reconfigure YXTouchLib_TK_CH_MASK"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x4000L)
#error          "Error：Please reconfigure YXTouchLib_TK_CH_MASK"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x8000L)
#error          "Error：Please reconfigure YXTouchLib_TK_CH_MASK"
#endif

#elif (YXTouchLib_IC_BODY == IC_BODY_SOP20_DIP20)

#if (YXTouchLib_TK_CH_MASK & 0x0001L)
#pragma message "TK2：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0002L)
#pragma message "TK3：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0004L)
#pragma message "TK7：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0008L)
#pragma message "TK9：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0010L)
#pragma message "TK10：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0020L)
#pragma message "TK11：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0040L)
#pragma message "TK12：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0080L)
#pragma message "TK13：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0100L)
#pragma message "TK14：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0200L)
#pragma message "TK15：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0400L)
#error          "Error：Please reconfigure YXTouchLib_TK_CH_MASK"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0800L)
#error          "Error：Please reconfigure YXTouchLib_TK_CH_MASK"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x1000L)
#error          "Error：Please reconfigure YXTouchLib_TK_CH_MASK"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x2000L)
#error          "Error：Please reconfigure YXTouchLib_TK_CH_MASK"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x4000L)
#error          "Error：Please reconfigure YXTouchLib_TK_CH_MASK"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x8000L)
#error          "Error：Please reconfigure YXTouchLib_TK_CH_MASK"
#endif

#elif (YXTouchLib_IC_BODY == IC_BODY_SOP24)

#if (YXTouchLib_TK_CH_MASK & 0x0001L)
#pragma message "TK0：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0002L)
#pragma message "TK1：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0004L)
#pragma message "TK2：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0008L)
#pragma message "TK3：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0010L)
#pragma message "TK7：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0020L)
#pragma message "TK9：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0040L)
#pragma message "TK10：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0080L)
#pragma message "TK11：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0100L)
#pragma message "TK12：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0200L)
#pragma message "TK13：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0400L)
#pragma message "TK14：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0800L)
#pragma message "TK15：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x1000L)
#error          "Error：Please reconfigure YXTouchLib_TK_CH_MASK"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x2000L)
#error          "Error：Please reconfigure YXTouchLib_TK_CH_MASK"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x4000L)
#error          "Error：Please reconfigure YXTouchLib_TK_CH_MASK"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x8000L)
#error          "Error：Please reconfigure YXTouchLib_TK_CH_MASK"
#endif

#elif (YXTouchLib_IC_BODY == IC_BODY_SOP28)

#if (YXTouchLib_TK_CH_MASK & 0x0001L)
#pragma message "TK0：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0002L)
#pragma message "TK1：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0004L)
#pragma message "TK2：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0008L)
#pragma message "TK3：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0010L)
#pragma message "TK4：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0020L)
#pragma message "TK5：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0040L)
#pragma message "TK6：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0080L)
#pragma message "TK7：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0100L)
#pragma message "TK8：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0200L)
#pragma message "TK9：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0400L)
#pragma message "TK10：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x0800L)
#pragma message "TK11：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x1000L)
#pragma message "TK12：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x2000L)
#pragma message "TK13：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x4000L)
#pragma message "TK14：Enable"
#endif
#if (YXTouchLib_TK_CH_MASK & 0x8000L)
#pragma message "TK15：Enable"
#endif


#endif

//================================================================================
#if (YXTouchLib_DSCR > 255)
#error	"Error：Please setting YXTouchLib_DSCR < 256"
#endif

//================================================================================
#pragma message "CTK采样频率：Fosc/2"

//================================================================================
//================================================================================
#if ((YXTouchLib_PRSDIV > 3)|(YXTouchLib_PRSDIV == 0))
#error 	"Error：Please setting 1 <= YXTouchLib_PRSDIV <= 3" 
#elif (YXTouchLib_PRSDIV ==1)
#pragma message "CTK充放电频率：Fosc/4"
#elif (YXTouchLib_PRSDIV ==2)
#pragma message "CTK充放电频率：Fosc/8"
#elif (YXTouchLib_PRSDIV ==3)
#pragma message "CTK充放电频率：Fosc/16"
#endif
//================================================================================
#if (YXTouchLib_VD > 3)
#error 	"Error：Please setting YXTouchLib_VD < 4"
#elif (YXTouchLib_VD ==0)
#pragma message "CTK充电电源电压：2V "
#elif (YXTouchLib_VD ==1)
#pragma message "CTK充电电源电压：2.5V"
#elif (YXTouchLib_VD ==2)
#pragma message "CTK充电电源电压：3V"
#elif (YXTouchLib_VD ==3)
#pragma message "CTK充电电源电压：4V"
#endif

//================================================================================
#pragma message "CTK充放电伪随机：打开"

//================================================================================
#pragma message "CTK参考电压：0.60V"

//================================================================================
#if (YXTouchLib_RBS > 7)
#error 	"Error：Please setting YXTouchLib_RBS < 8"
#elif (YXTouchLib_RBS ==0)
#pragma message "CTK放电电阻：0.5"
#elif (YXTouchLib_RBS ==1)
#pragma message "CTK放电电阻：1"
#elif (YXTouchLib_RBS ==2)
#pragma message "CTK放电电阻：2"
#elif (YXTouchLib_RBS ==3)
#pragma message "CTK放电电阻：4"
#elif (YXTouchLib_RBS ==4)
#pragma message "CTK放电电阻：8"
#elif (YXTouchLib_RBS ==5)
#pragma message "CTK放电电阻：16"
#elif (YXTouchLib_RBS ==6)
#pragma message "CTK放电电阻：32"
#elif (YXTouchLib_RBS ==7)
#pragma message "CTK放电电阻：64"
#endif

//================================================================================
#pragma message "CTK调制电容：内置电容"

//================================================================================
#pragma message "CTK连续扫描模式：打开"

//================================================================================
#pragma message "CTK扫描补偿：关闭"

//================================================================================
#if ((YXTouchLib_CONFIRM_TOUCH_TIME == 0)|(YXTouchLib_CONFIRM_TOUCH_TIME > 255))
#error	"Error：Please setting 0 < YXTouchLib_CONFIRM_TOUCH_TIME < 256"
#endif

//================================================================================
#if ((YXTouchLib_CONFIRM_NOTOUCH_TIME == 0)|(YXTouchLib_CONFIRM_NOTOUCH_TIME > 255))
#error 	"Error：Please setting 0 < YXTouchLib_CONFIRM_NOTOUCH_TIME < 256"
#endif

//================================================================================
#if (YXTouchLib_Hysteresis == 0 )
#pragma message "触摸按键迟滞: 关闭"
#elif (YXTouchLib_Hysteresis > 255))
#error 	"Error：Please setting 0 < YXTouchLib_Hysteresis < 256"
#endif

//================================================================================
#if (((0 < YXTouchLib_CONFIRM_LONGTOUCH_TIME)&&(YXTouchLib_CONFIRM_LONGTOUCH_TIME <= YXTouchLib_CONFIRM_TOUCH_TIME))|(YXTouchLib_CONFIRM_LONGTOUCH_TIME > 65535))
#error 	"Error：Please setting YXTouchLib_CONFIRM_LONGTOUCH_TIME = 0 or YXTouchLib_CONFIRM_TOUCH_TIME < YXTouchLib_CONFIRM_LONGTOUCH_TIME < 65536"
#endif

//================================================================================
#if ((YXTouchLib_LIMIT_FACTOR == 1)|(YXTouchLib_LIMIT_FACTOR > 256))
#error 	"Error：Please setting 1 < YXTouchLib_LIMIT_FACTOR < 256"
#endif

//================================================================================
#if ((YXTouchLib_OVERHIGH_TIME == 0)|(YXTouchLib_OVERHIGH_TIME > 65536))
#error 	"Error：Please setting 0 < YXTouchLib_OVERHIGH_TIME < 65536"
#endif

//================================================================================
#if (YXTouchLib_OVERLOW_TIME == 0)
#pragma message "CTK低基准线复位: 关闭"
#elif ((YXTouchLib_OVERLOW_TIME > 65536)|(YXTouchLib_OVERLOW_TIME < YXTouchLib_CONFIRM_NOTOUCH_TIME))
#error 	"Error：Please setting YXTouchLib_CONFIRM_NOTOUCH_TIME < YXTouchLib_OVERLOW_TIME < 65536"
#else
#pragma message "CTK低基准线复位: 打开"
#endif

//================================================================================
#if ((YXTouchLib_NOISE_BARREL_CAPACITY <= 1)|(YXTouchLib_NOISE_BARREL_CAPACITY > 256))
#error 	"Error：Please setting 1 < YXTouchLib_NOISE_BARREL_CAPACITY < 256"
#endif

//================================================================================
#pragma message "CTK通道校准: 关闭"

#define	YXTouchLib_SETn_N_THRESHOLD		50

//================================================================================
#if (YXTouchLib_FILTER_DEPTH == 0)
#pragma message "CTK RawData递推中位值平均滤波: 关闭"
#elif ((YXTouchLib_FILTER_DEPTH >= 3)&&(YXTouchLib_FILTER_DEPTH <= 15))
#pragma message "CTK RawData递推中位值平均滤波: 打开"
#else
#error 	"Error：Please setting 3 <= YXTouchLib_FILTER_DEPTH <= 15"
#endif


#if (YXTouchLib_MULTIBUTTON == 0)
#pragma message "CTK 最强按键: 关闭"
#elif (YXTouchLib_MULTIBUTTON == 1)
#pragma message "CTK 最强按键: 打开"
#else
#error 	"Error：Please setting YXTouchLib_MULTIBUTTON = 0 or YXTouchLib_MULTIBUTTON = 1"
#endif


//================================================================================
#if ((YXTouchLib_SET0_N_THRESHOLD <= 4 )|(YXTouchLib_SET0_N_THRESHOLD > YXTouchLib_SETn_N_THRESHOLD))
#error 	"Error：Please setting 4 < YXTouchLib_SET0_N_THRESHOLD <= YXTouchLib_SETn_N_THRESHOLD"
#endif
#if ((YXTouchLib_SET1_N_THRESHOLD <= 4 )|(YXTouchLib_SET1_N_THRESHOLD > YXTouchLib_SETn_N_THRESHOLD))
#error 	"Error：Please setting 4 < YXTouchLib_SET1_N_THRESHOLD <= YXTouchLib_SETn_N_THRESHOLD"
#endif
#if ((YXTouchLib_SET2_N_THRESHOLD <= 4 )|(YXTouchLib_SET2_N_THRESHOLD > YXTouchLib_SETn_N_THRESHOLD))
#error 	"Error：Please setting 4 < YXTouchLib_SET2_N_THRESHOLD <= YXTouchLib_SETn_N_THRESHOLD"
#endif
#if ((YXTouchLib_SET3_N_THRESHOLD <= 4 )|(YXTouchLib_SET3_N_THRESHOLD > YXTouchLib_SETn_N_THRESHOLD))
#error 	"Error：Please setting 4 < YXTouchLib_SET3_N_THRESHOLD <= YXTouchLib_SETn_N_THRESHOLD"
#endif
#if ((YXTouchLib_SET4_N_THRESHOLD <= 4 )|(YXTouchLib_SET4_N_THRESHOLD > YXTouchLib_SETn_N_THRESHOLD))
#error 	"Error：Please setting 4 < YXTouchLib_SET4_N_THRESHOLD <= YXTouchLib_SETn_N_THRESHOLD"
#endif
#if ((YXTouchLib_SET5_N_THRESHOLD <= 4 )|(YXTouchLib_SET5_N_THRESHOLD > YXTouchLib_SETn_N_THRESHOLD))
#error 	"Error：Please setting 4 < YXTouchLib_SET5_N_THRESHOLD <= YXTouchLib_SETn_N_THRESHOLD"
#endif
#if ((YXTouchLib_SET6_N_THRESHOLD <= 4 )|(YXTouchLib_SET6_N_THRESHOLD > YXTouchLib_SETn_N_THRESHOLD))
#error 	"Error：Please setting 4 < YXTouchLib_SET6_N_THRESHOLD <= YXTouchLib_SETn_N_THRESHOLD"
#endif
#if ((YXTouchLib_SET7_N_THRESHOLD <= 4 )|(YXTouchLib_SET7_N_THRESHOLD > YXTouchLib_SETn_N_THRESHOLD))
#error 	"Error：Please setting 4 < YXTouchLib_SET7_N_THRESHOLD <= YXTouchLib_SETn_N_THRESHOLD"
#endif
#if ((YXTouchLib_SET8_N_THRESHOLD <= 4 )|(YXTouchLib_SET8_N_THRESHOLD > YXTouchLib_SETn_N_THRESHOLD))
#error 	"Error：Please setting 4 < YXTouchLib_SET8_N_THRESHOLD <= YXTouchLib_SETn_N_THRESHOLD"
#endif
#if ((YXTouchLib_SET9_N_THRESHOLD <= 4 )|(YXTouchLib_SET9_N_THRESHOLD > YXTouchLib_SETn_N_THRESHOLD))
#error 	"Error：Please setting 4 < YXTouchLib_SET9_N_THRESHOLD <= YXTouchLib_SETn_N_THRESHOLD"
#endif
#if ((YXTouchLib_SET10_N_THRESHOLD <= 4 )|(YXTouchLib_SET10_N_THRESHOLD > YXTouchLib_SETn_N_THRESHOLD))
#error 	"Error：Please setting 4 < YXTouchLib_SET10_N_THRESHOLD <= YXTouchLib_SETn_N_THRESHOLD"
#endif
#if ((YXTouchLib_SET11_N_THRESHOLD <= 4 )|(YXTouchLib_SET11_N_THRESHOLD > YXTouchLib_SETn_N_THRESHOLD))
#error 	"Error：Please setting 4 < YXTouchLib_SET11_N_THRESHOLD <= YXTouchLib_SETn_N_THRESHOLD"
#endif
#if ((YXTouchLib_SET12_N_THRESHOLD <= 4 )|(YXTouchLib_SET12_N_THRESHOLD > YXTouchLib_SETn_N_THRESHOLD))
#error 	"Error：Please setting 4 < YXTouchLib_SET12_N_THRESHOLD <= YXTouchLib_SETn_N_THRESHOLD"
#endif
#if ((YXTouchLib_SET13_N_THRESHOLD <= 4 )|(YXTouchLib_SET13_N_THRESHOLD > YXTouchLib_SETn_N_THRESHOLD))
#error 	"Error：Please setting 4 < YXTouchLib_SET13_N_THRESHOLD <= YXTouchLib_SETn_N_THRESHOLD"
#endif
#if ((YXTouchLib_SET14_N_THRESHOLD <= 4 )|(YXTouchLib_SET14_N_THRESHOLD > YXTouchLib_SETn_N_THRESHOLD))
#error 	"Error：Please setting 4 < YXTouchLib_SET14_N_THRESHOLD <= YXTouchLib_SETn_N_THRESHOLD"
#endif
#if ((YXTouchLib_SET15_N_THRESHOLD <= 4 )|(YXTouchLib_SET15_N_THRESHOLD > YXTouchLib_SETn_N_THRESHOLD))
#error 	"Error：Please setting 4 < YXTouchLib_SET15_N_THRESHOLD <= YXTouchLib_SETn_N_THRESHOLD"
#endif

//================================================================================
#if ((YXTouchLib_SET0_F_THRESHOLD <= 24 )|(YXTouchLib_SET0_F_THRESHOLD > (YXTouchLib_DSCR+1)*256-1))
#error 	"Error：Please setting 24 < YXTouchLib_SET0_F_THRESHOLD <= (YXTouchLib_DSCR+1)*256+1"
#endif
#if ((YXTouchLib_SET1_F_THRESHOLD <= 24 )|(YXTouchLib_SET1_F_THRESHOLD > (YXTouchLib_DSCR+1)*256-1))
#error 	"Error：Please setting 24 < YXTouchLib_SET1_F_THRESHOLD <= (YXTouchLib_DSCR+1)*256+1"
#endif
#if ((YXTouchLib_SET2_F_THRESHOLD <= 24 )|(YXTouchLib_SET2_F_THRESHOLD > (YXTouchLib_DSCR+1)*256-1))
#error 	"Error：Please setting 24 < YXTouchLib_SET2_F_THRESHOLD <= (YXTouchLib_DSCR+1)*256+1"
#endif
#if ((YXTouchLib_SET3_F_THRESHOLD <= 24 )|(YXTouchLib_SET3_F_THRESHOLD > (YXTouchLib_DSCR+1)*256-1))
#error 	"Error：Please setting 24 < YXTouchLib_SET3_F_THRESHOLD <= (YXTouchLib_DSCR+1)*256+1"
#endif
#if ((YXTouchLib_SET4_F_THRESHOLD <= 24 )|(YXTouchLib_SET4_F_THRESHOLD > (YXTouchLib_DSCR+1)*256-1))
#error 	"Error：Please setting 24 < YXTouchLib_SET4_F_THRESHOLD <= (YXTouchLib_DSCR+1)*256+1"
#endif
#if ((YXTouchLib_SET5_F_THRESHOLD <= 24 )|(YXTouchLib_SET5_F_THRESHOLD > (YXTouchLib_DSCR+1)*256-1))
#error 	"Error：Please setting 24 < YXTouchLib_SET5_F_THRESHOLD <= (YXTouchLib_DSCR+1)*256+1"
#endif
#if ((YXTouchLib_SET6_F_THRESHOLD <= 24 )|(YXTouchLib_SET6_F_THRESHOLD > (YXTouchLib_DSCR+1)*256-1))
#error 	"Error：Please setting 24 < YXTouchLib_SET6_F_THRESHOLD <= (YXTouchLib_DSCR+1)*256+1"
#endif
#if ((YXTouchLib_SET7_F_THRESHOLD <= 24 )|(YXTouchLib_SET7_F_THRESHOLD > (YXTouchLib_DSCR+1)*256-1))
#error 	"Error：Please setting 24 < YXTouchLib_SET7_F_THRESHOLD <= (YXTouchLib_DSCR+1)*256+1"
#endif
#if ((YXTouchLib_SET8_F_THRESHOLD <= 24 )|(YXTouchLib_SET8_F_THRESHOLD > (YXTouchLib_DSCR+1)*256-1))
#error 	"Error：Please setting 24 < YXTouchLib_SET8_F_THRESHOLD <= (YXTouchLib_DSCR+1)*256+1"
#endif
#if ((YXTouchLib_SET9_F_THRESHOLD <= 24 )|(YXTouchLib_SET9_F_THRESHOLD > (YXTouchLib_DSCR+1)*256-1))
#error 	"Error：Please setting 24 < YXTouchLib_SET9_F_THRESHOLD <= (YXTouchLib_DSCR+1)*256+1"
#endif
#if ((YXTouchLib_SET10_F_THRESHOLD <= 24 )|(YXTouchLib_SET10_F_THRESHOLD > (YXTouchLib_DSCR+1)*256-1))
#error 	"Error：Please setting 24 < YXTouchLib_SET10_F_THRESHOLD <= (YXTouchLib_DSCR+1)*256+1"
#endif
#if ((YXTouchLib_SET11_F_THRESHOLD <= 24 )|(YXTouchLib_SET11_F_THRESHOLD > (YXTouchLib_DSCR+1)*256-1))
#error 	"Error：Please setting 24 < YXTouchLib_SET11_F_THRESHOLD <= (YXTouchLib_DSCR+1)*256+1"
#endif
#if ((YXTouchLib_SET12_F_THRESHOLD <= 24 )|(YXTouchLib_SET12_F_THRESHOLD > (YXTouchLib_DSCR+1)*256-1))
#error 	"Error：Please setting 24 < YXTouchLib_SET12_F_THRESHOLD <= (YXTouchLib_DSCR+1)*256+1"
#endif
#if ((YXTouchLib_SET13_F_THRESHOLD <= 24 )|(YXTouchLib_SET13_F_THRESHOLD > (YXTouchLib_DSCR+1)*256-1))
#error 	"Error：Please setting 24 < YXTouchLib_SET13_F_THRESHOLD <= (YXTouchLib_DSCR+1)*256+1"
#endif
#if ((YXTouchLib_SET14_F_THRESHOLD <= 24 )|(YXTouchLib_SET14_F_THRESHOLD > (YXTouchLib_DSCR+1)*256-1))
#error 	"Error：Please setting 24 < YXTouchLib_SET14_F_THRESHOLD <= (YXTouchLib_DSCR+1)*256+1"
#endif
#if ((YXTouchLib_SET15_F_THRESHOLD <= 24 )|(YXTouchLib_SET15_F_THRESHOLD > (YXTouchLib_DSCR+1)*256-1))
#error 	"Error：Please setting 24 < YXTouchLib_SET15_F_THRESHOLD <= (YXTouchLib_DSCR+1)*256+1"
#endif

#endif /* __YX23F01CB_GeneralKey_Touch_Lib_Build_Message_H__ */

/******************************************************************************************************

 ******************************************************************************************************/

