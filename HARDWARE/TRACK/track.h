#ifndef _TRACK_H
#define _TRACK_H

#include "sys.h"

#define D_AD_VALUE	  330 		//确定左右传感器差值
#define LEFT_MAX 			4095   	//左传感器峰值
#define RIGHT_MAX 		4095  	//右传感器峰值
#define LEFT_THERSH 	2831			//左传感器阈值
#define RIGHT_THERSH 	1502		//右传感器阈值
#define LEFT_SPAN			4875		//传感器向左移动跳跃差值
#define RIGHT_SPAN 	  -4712		//传感器向右移动跳跃差值   

/****************函数声明********************/
extern int GetTraceDate(void);
extern void GetParament(void);

#endif

