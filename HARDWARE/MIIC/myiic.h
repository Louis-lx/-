#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//IIC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/6
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
   	   		   
//IO��������
#define SDA_IN()  {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}	//PB9����ģʽ
#define SDA_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;} //PB9���ģʽ
//IO��������	 
#define IIC_SCL    PBout(8) //SCL
#define IIC_SDA    PBout(9) //SDA	 
#define READ_SDA   PBin(9)  //����SDA 

//IIC���в�������
void MIIC_Init(void);                //��ʼ��IIC��IO��				 
void MIIC_Start(void);				//����IIC��ʼ�ź�
void MIIC_Stop(void);	  			//����IICֹͣ�ź�
void MIIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 MIIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 MIIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void MIIC_Ack(void);					//IIC����ACK�ź�
void MIIC_NAck(void);				//IIC������ACK�ź�

void MIIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 MIIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















