#ifndef _TRACK_H
#define _TRACK_H

#include "sys.h"

#define D_AD_VALUE	  330 		//ȷ�����Ҵ�������ֵ
#define LEFT_MAX 			4095   	//�󴫸�����ֵ
#define RIGHT_MAX 		4095  	//�Ҵ�������ֵ
#define LEFT_THERSH 	2831			//�󴫸�����ֵ
#define RIGHT_THERSH 	1502		//�Ҵ�������ֵ
#define LEFT_SPAN			4875		//�����������ƶ���Ծ��ֵ
#define RIGHT_SPAN 	  -4712		//�����������ƶ���Ծ��ֵ   

/****************��������********************/
extern int GetTraceDate(void);
extern void GetParament(void);

#endif

