#ifndef __MQTT_H
#define __MQTT_H

#include "sys.h"
#include "UART.h"
#include "string.h"
#include "delay.h"
#include "FreeRTOS.h"
#include "task.h"

void WiFi_Init(int k);		/*i = 1 ∞¢¿Ô‘∆ 	 ∑Ò‘Úouriot*/

void Connect_MQTT_Service(void);
void Subscribe_Set(void);
void Subscribe_replay(void);
void Connect_MQTT_Serive_New(char * s);
void Post_ToAliyun(void);
void Keep_live(void);
void ssss(void);

char * SendDataPart(char * str);

void Send_Data_TO_AliYun(char * ss);
void Send_Data_TO_AliYun_Test(char * ss);

void Connect_EMQX( char *ID ,  char *user ,  char *sec);
void EMQX_SubscribeMessage(char * New);
void Send_Data_TO_EMQX(char * topic  ,char *msg);
#endif

