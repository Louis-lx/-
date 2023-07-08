#include "DHT11.h"


void DHT11_GPIO_Config(void)
{ 
  GPIO_InitTypeDef GPIO_InitStructure; 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);     
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;     
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

static void DHT11_Mode_Out(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;								   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

static void DHT11_Mode_IN(void)
{
 	  GPIO_InitTypeDef GPIO_InitStructure;
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	
	  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void DHT11_Reset() 
{      
	 DHT11_Mode_Out();
    DHT11_DQ_L; //DQ=0
    delay_ms(20);   
    DHT11_DQ_H; //DQ=1 
    delay_us(30);   
}
u8 DHT11_Check(void)    
{   
	u8 retry=0;
	DHT11_Mode_IN();
	while ((GPIO_ReadInputDataBit(DHT11_DQ_GPIO_PORT,DHT11_DQ_GPIO_PIN)==1)&&retry<100)//DHT11???40~80us
	 {
	   retry++;
	   delay_us(1);
	 }; 
	if(retry>=100)return 1;
	else retry=0;
  while ((GPIO_ReadInputDataBit(DHT11_DQ_GPIO_PORT,DHT11_DQ_GPIO_PIN)==0)&&retry<100)//DHT11????????40~80us
	 {
	   retry++;
	   delay_us(1);
	 };
	if(retry>=100)return 1;    
	return 0;
}

u8 DHT11_Read_Bit(void)  
{
	 u8 retry=0;
	while((GPIO_ReadInputDataBit(DHT11_DQ_GPIO_PORT,DHT11_DQ_GPIO_PIN)==1)&&retry<100)//???????
	{
	 retry++;
	 delay_us(1);
	}
	retry=0;
	while((GPIO_ReadInputDataBit(DHT11_DQ_GPIO_PORT,DHT11_DQ_GPIO_PIN)==0)&&retry<100)//??????
	{
	 retry++;
	 delay_us(1);
	}
	delay_us(40);
	if(GPIO_ReadInputDataBit(DHT11_DQ_GPIO_PORT,DHT11_DQ_GPIO_PIN)==1)
	return 1;
	else 
	return 0;   
}

u8 DHT11_Read_Byte(void)    
{        
    u8 i,dat;
    dat=0;
for (i=0;i<8;i++) 
{
   dat<<=1; 
    dat|=DHT11_Read_Bit();
    }    
    return dat;
}


u8 DHT11_Read_Data(u8 *temp,u8 *humi)    
{        
	u8 buf[5];
	u8 i;
	DHT11_Reset();
	if(DHT11_Check()==0)
	{
	 for(i=0;i<5;i++)
	 {
	  buf[i]=DHT11_Read_Byte();
	 }
	 if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
	 {
	  *humi=buf[0];
	  *temp=buf[2];
	 }
	}
	else return 1;
return 0;    
}


void DHT11_Init(void)
{     
	DHT11_GPIO_Config();
	DHT11_Reset();
	DHT11_Check();
}


	
		





