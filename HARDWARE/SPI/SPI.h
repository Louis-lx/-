#ifndef __SPI_H
#define __SPI_H

#include "sys.h"
#include "delay.h"

#define CLK_LOW  GPIO_ResetBits(GPIOE,GPIO_Pin_2)
#define CLK_HIGH  GPIO_SetBits(GPIOE,GPIO_Pin_2)

#define DIN_LOW GPIO_ResetBits(GPIOE,GPIO_Pin_3)
#define DIN_HIGH  GPIO_SetBits(GPIOE,GPIO_Pin_3)

#define RES_LOW  GPIO_ResetBits(GPIOE,GPIO_Pin_4)
#define RES_HIGH  GPIO_SetBits(GPIOE,GPIO_Pin_4)

#define DC_LOW  GPIO_ResetBits(GPIOE,GPIO_Pin_5)
#define DC_HIGH  GPIO_SetBits(GPIOE,GPIO_Pin_5)

void My_SPI_WriteData(unsigned char data,char cmd);	/*0 ÃüÁî  1 Êý¾Ý*/
void My_SPI_Init(void);

#endif
