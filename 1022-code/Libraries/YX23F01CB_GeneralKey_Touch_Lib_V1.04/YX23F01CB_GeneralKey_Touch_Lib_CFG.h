
/*******************************************************************************/
#ifndef __YX23F01CB_GeneralKey_Touch_Lib_CFG_H__
#define __YX23F01CB_GeneralKey_Touch_Lib_CFG_H__

/****************************************IC型号及封装选择********************************************/
#define IC_BODY_SOP20_DIP20                   0   //YX23F01CB	SOP20/DIP20
#define IC_BODY_SOP24                         1   //YX23F01CB	SOP24
#define IC_BODY_SOP28                         2   //YX23F01CB	SOP28
#define IC_BODY_SOP16                         3   //YX23F01CB	SOP16

// IC型号及封装选择
#define YXTouchLib_IC_BODY                    2
/****************************************************************************************************/


/***************************************设置需要检测的通道*******************************************/
// 设置需要检测的通道标志		 0: 不检测；1: 允许检测。
//      YX23F01CB-SOP28              TK15 TK14 TK13 TK12 TK11 TK10  TK9  TK8  TK7  TK6  TK5  TK4  TK3  TK2  TK1  TK0  
//      YX23F01CB-SOP24               NC   NC   NC   NC  TK15 TK14 TK13 TK12 TK11 TK10  TK9  TK7  TK3  TK2  TK1  TK0  
//      YX23F01CB-SOP20/DIP20         NC   NC   NC   NC   NC   NC  TK15 TK14 TK13 TK12 TK11 TK10  TK9  TK7  TK3  TK2  
//      YX23F01CB-SOP16               NC   NC   NC   NC   NC   NC   NC   NC   NC  TK15 TK14 TK13 TK12 TK11  TK7  TK2  
#define YXTouchLib_TK_CH_MASK  TKBIN(  1 ,  1 ,  1 ,  1 ,  1 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 )
/****************************************************************************************************/


/***************************************设置触摸相关寄存器*******************************************/
// 设置数据采样时钟个数，设置范围(0~255)。单个通道扫描时间 ≈ ((YXTouchLib_DSCR+1)*256 - 1)/(Fosc/2)
#define YXTouchLib_DSCR                         48

// 设置充放电频率，设置范围(1~3)。1->Fosc/4, 2->Fosc/8，3->Fosc/16
// 注：建议设置CTK充放电频率设置为Fosc/8，即本值设置为2
#define YXTouchLib_PRSDIV     					2

// 设置触摸充电电源电压，设置范围(0~3)：0->2v  1->2.5v 2->3v 3->4v，充电电压越大，触摸计数值越大
// 使用注意：必须保证芯片VDD电压 > 用户设置触摸充电电源电压+0.5V
#define YXTouchLib_VD                           2

// 设置触摸放电电阻，设置范围(0~7):0->放电电阻最小, 7->放电电阻最大,方向0(小)-->7(大), 放电电阻越小,触摸计数值越小
#define YXTouchLib_RBS                          6
/****************************************************************************************************/


/**************************************设置手指阈值相关参数******************************************/
// 设置确认手指触摸次数，即触摸有效状态消抖，设置范围(1~255)
// 【消抖时间 = YXTouchLib_CONFIRM_TOUCH_TIME × 单个按键扫描时间 × 开启的检测通道个数】
#define YXTouchLib_CONFIRM_TOUCH_TIME           2

// 设置确认手指离开次数，即触摸无效状态消抖，设置范围(1~255)
// 【消抖时间 = YXTouchLib_CONFIRM_NOTOUCH_TIME × 单个按键扫描时间 × 开启的检测通道个数】
#define YXTouchLib_CONFIRM_NOTOUCH_TIME         2

// 设置触摸迟滞，与触摸阈值配合使用，该值应略大于所设噪声阈值
#define YXTouchLib_Hysteresis                   15

// 噪声阈值，设置范围(5~50),用户应根据实际噪声情况设置该值，建议该值为最大噪声的绝对值的1.5倍
// 设置噪声阈值时注意需要与使用的CTK通达对应        //S0P28 //SOP24// SOP20/DIP20  //SOP16
#define YXTouchLib_SET0_N_THRESHOLD             10  //TK0	 //TK0	  //TK2		   //TK2	
#define YXTouchLib_SET1_N_THRESHOLD             10  //TK1	 //TK1	  //TK3		   //TK7
#define YXTouchLib_SET2_N_THRESHOLD             10	//TK2	 //TK2	  //TK7		   //TK11
#define YXTouchLib_SET3_N_THRESHOLD             10  //TK3	 //TK9    //TK9		   //TK12
#define YXTouchLib_SET4_N_THRESHOLD             10  //TK4	 //TK7	  //TK10	   //TK13
#define YXTouchLib_SET5_N_THRESHOLD             10  //TK5	 //TK9	  //TK11	   //TK14	
#define YXTouchLib_SET6_N_THRESHOLD             10  //TK6	 //TK10	  //TK12	   //TK15
#define YXTouchLib_SET7_N_THRESHOLD             10  //TK7	 //TK11	  //TK13	   //NC
#define YXTouchLib_SET8_N_THRESHOLD             10  //TK8	 //TK12	  //TK14	   //NC
#define YXTouchLib_SET9_N_THRESHOLD             10  //TK9	 //TK13	  //TK15	   //NC
#define YXTouchLib_SET10_N_THRESHOLD            10  //TK10	 //TK14	  //NC		   //NC
#define YXTouchLib_SET11_N_THRESHOLD            10  //TK11	 //TK15	  //NC		   //NC
#define YXTouchLib_SET12_N_THRESHOLD            10  //TK12	 //NC	  //NC		   //NC
#define YXTouchLib_SET13_N_THRESHOLD            10  //TK13	 //NC	  //NC		   //NC
#define YXTouchLib_SET14_N_THRESHOLD            10  //TK14	 //NC	  //NC		   //NC
#define YXTouchLib_SET15_N_THRESHOLD            10  //TK15	 //NC	  //NC		   //NC

// 触摸阈值：取值需根据实际情况，触摸阈值应至少保证对通道噪声值3倍以上，5倍以上更佳
// 设置触摸阈值时注意需要与使用的CTK通达对应		//SOP28 //S0P24 //SOP20/DIP20 //SOP16
#define YXTouchLib_SET0_F_THRESHOLD				120	//TK0	 //TK0	 //TK2		   //TK2	
#define YXTouchLib_SET1_F_THRESHOLD				120	//TK1	 //TK1	 //TK3		   //TK7
#define YXTouchLib_SET2_F_THRESHOLD				120	//TK2	 //TK2	 //TK7		   //TK11
#define YXTouchLib_SET3_F_THRESHOLD				120	//TK3	 //TK3	 //TK9		   //TK12
#define YXTouchLib_SET4_F_THRESHOLD				120	//TK4	 //TK7	 //TK10		   //TK13
#define YXTouchLib_SET5_F_THRESHOLD				120	//TK5	 //TK9	 //TK11		   //TK14	
#define YXTouchLib_SET6_F_THRESHOLD				120	//TK6	 //TK10	 //TK12		   //TK15
#define YXTouchLib_SET7_F_THRESHOLD				120	//TK7	 //TK11	 //TK13		   //NC
#define YXTouchLib_SET8_F_THRESHOLD				120	//TK8	 //TK12	 //TK14		   //NC
#define YXTouchLib_SET9_F_THRESHOLD				120	//TK9	 //TK13	 //TK15		   //NC
#define YXTouchLib_SET10_F_THRESHOLD			120	//TK10	 //TK14	 //NC		   //NC
#define YXTouchLib_SET11_F_THRESHOLD			120	//TK11	 //TK15	 //NC		   //NC
#define YXTouchLib_SET12_F_THRESHOLD			120	//TK12	 //NC	 //NC		   //NC
#define YXTouchLib_SET13_F_THRESHOLD			120	//TK13	 //NC	 //NC		   //NC
#define YXTouchLib_SET14_F_THRESHOLD			120	//TK14	 //NC	 //NC		   //NC
#define YXTouchLib_SET15_F_THRESHOLD			120	//TK15	 //NC	 //NC		   //NC
/****************************************************************************************************/


/**************************************设置基线更新相关参数******************************************/
// 设置触摸按键最长有效时间计数值，用于触摸长按键或适应外界条件变化		
//			设置范围(0~65535)
//          0: 关闭此功能
//			非0: 当Differ连续大于手指阈值(YXTouchLib_SETx_F_THRESHOLD)的时长超过了所设的该值后，系统将自动更新当前Baseline。
// 注意：YXTouchLib_CONFIRM_LONGTOUCH_TIME非0时，必须大于用户设置确认手指触摸次数(YXTouchLib_CONFIRM_TOUCH_TIME)
// 最长有效时间 ≈ YXTouchLib_CONFIRM_LONGTOUCH_TIME * 单个按键扫描时间 * 开启的检测通道个数
#define YXTouchLib_CONFIRM_LONGTOUCH_TIME		1000

// 设置毛刺的判断条件，用于过滤由于特殊情况造成的剧烈触摸值抖动
//			设置范围(0~255)
//		    0: 不判断毛刺；
//          非0: 当触摸值 > YXTouchLib_LIMIT_FACTOR * YXTouchLib_SETx_F_THRESHOLD 时判断为毛刺
//			举例：触摸阈值为100，该值为3，则认为Differ值大于300时为毛刺，此时按键无效
#define YXTouchLib_LIMIT_FACTOR					0

// 设置毛刺消除计数值，配合YXTouchLib_LIMIT_FACTOR使用。用于当由于外界条件造成触摸计数值长时间过高时的基线更新，如有硬物置于触摸按键上等
//			设置范围(0~65535)
//          0: 关闭此功能
//			非0: 当Differ连续大于毛刺(YXTouchLib_LIMIT_FACTOR * YXTouchLib_TKx_F_THRESHOLD)的时长超过了所设的该值后，系统将自动更新当前Baseline
#define YXTouchLib_OVERHIGH_TIME				300

// 设置低基准线复位计数值
//          0: 关闭此功能
//			非0: 当Differ连续低于负噪声阈值(-YXTouchLib_SETx_N_THRESHOLD)的时长超过了所设的该值后，系统将自动更新当前Baseline
#define YXTouchLib_OVERLOW_TIME					100

// 设置噪声桶容量大小
//			设置范围(0~255)
//          系统会对在±噪声(YXTouchLib_SETx_N_THRESHOLD)之间的Differ进行累加，当累加的和大于正噪声桶或小于负噪声桶时，将对Baseline+2或-2。
#define YXTouchLib_NOISE_BARREL_CAPACITY		80

/****************************************************************************************************/

#endif /*__YX23F01CB_GeneralKey_Touch_Lib_CFG_H__*/

/******************************************************************************************************

 ******************************************************************************************************/
