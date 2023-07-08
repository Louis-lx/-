#ifndef __UART_H
#define __UART_H

#include "sys.h"


void UART2_Init(void);
void send_String(char *DataString);
void send_Data(u8 Data);
void Uart2Sendd(unsigned char *p_data, unsigned int uiSize);
#endif
