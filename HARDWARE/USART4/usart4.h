#ifndef __USART4_H
#define __USART4_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 
#include "OLED_SPI.h"

void uart4_init(u32 bound);
void u4_printf(char* fmt,...);  
void usart3_send(u8 data);
void usart4_send(u8 data);
#endif

