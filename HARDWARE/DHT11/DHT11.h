#ifndef __DHT11_H
#define __DHT11_H

#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
#include "delay.h"
#include "OLED_SPI.h"

#define    RCC_DHT11                          RCC_AHB1Periph_GPIOE
#define    DHT11_DQ_GPIO_PORT                 GPIOE
#define    DHT11_DQ_GPIO_PIN                  GPIO_Pin_0


#define    DHT11_DQ_L	            GPIO_ResetBits ( DHT11_DQ_GPIO_PORT, DHT11_DQ_GPIO_PIN ) 
#define    DHT11_DQ_H	            GPIO_SetBits ( DHT11_DQ_GPIO_PORT, DHT11_DQ_GPIO_PIN ) 


void DHT11_Init(void);
u8 DHT11_Read_Data(u8 *temp,u8 *humi)   ;

#endif


