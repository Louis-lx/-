#ifndef __OLED_SPI_H
#define __OLED_SPI_H


#include "SPI.h"
#include "sys.h"
#include "SPI.h"
#include "delay.h"


void OLED_WrCmd(unsigned char cmd);
void OLED_WrDat(unsigned char data);
void OLED_Fill(unsigned char bmp_dat);
void OLED_Set_Pos(unsigned char x, unsigned char y) ;
void OLED_SPI_Init(void);
void OLED_P6x8Str(unsigned char x, unsigned char y,unsigned char ch[]);

#endif



