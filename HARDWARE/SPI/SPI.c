#include "SPI.h"

void My_SPI_Init(){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
//	GPIO_ResetBits(GPIOE,GPIO_Pin_2);
//	GPIO_ResetBits(GPIOE,GPIO_Pin_3);
//	GPIO_ResetBits(GPIOE,GPIO_Pin_4);
//	GPIO_ResetBits(GPIOE,GPIO_Pin_5);
	CLK_HIGH;
	DIN_LOW;
	DC_LOW;
	RES_HIGH;
	
}


void My_SPI_WriteData(unsigned char  data ,char cmd){	
	
	int i = 0;
	if(cmd==0)
		DC_LOW;
	else if(cmd==1)
		DC_HIGH;

	for(;i<8 ; i ++){
		CLK_LOW;
		if(data&0x80){
			DIN_HIGH;
		}else{
			DIN_LOW;
		}
		CLK_HIGH;
		data<<=1;
		delay_us(1);
		CLK_LOW;
		DIN_LOW;
	}
}
