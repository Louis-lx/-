#include "UART.h"

void UART2_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;            
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;

	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	
	USART_Init(USART2,&USART_InitStructure);
	USART_Cmd(USART2,ENABLE);
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	//USART_ITConfig(USART2,USART_IT_TXE,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStructure);
	
}

void send_String(char *DataString)
{
	int i = 0;
	USART_ClearFlag(USART2,USART_FLAG_TC);
	while(DataString[i] != '\0')										
	{
		USART_SendData(USART2,DataString[i]);								
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC) == 0);	
		USART_ClearFlag(USART2,USART_FLAG_TC);								
		i++;
	}

}


void send_Data (u8 Data)
{
		USART_ClearFlag(USART2,USART_FLAG_TC);
	
		USART_SendData(USART2,Data);								
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC) == 0);	
		USART_ClearFlag(USART2,USART_FLAG_TC);								
}

void Uart2Sendd(unsigned char *p_data, unsigned int uiSize)
{	
	unsigned int i;
	for(i = 0; i < uiSize; i++)
	{
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
		USART_SendData(USART2, *p_data++);		
	}
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
}


