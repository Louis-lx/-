#include "motor.h"

void MOTOR_GPIO_Init(void)
{		
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOB C Dʱ��
	
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;//��ӦIO��
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
	
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11|GPIO_Pin_15;//��ӦIO��
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
	
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5;//��ӦIO��
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIO
	
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;//��ӦIO��
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIO

  //IO output 0to prevent motor transfer
  //IO���0����ֹ�����ת
	GPIO_ResetBits(IN1_PORTA,IN1_PIN_A);	
	GPIO_ResetBits(IN2_PORTA,IN2_PIN_A);
	GPIO_ResetBits(IN1_PORTB,IN1_PIN_B);
	GPIO_ResetBits(IN2_PORTB,IN2_PIN_B);
	GPIO_ResetBits(IN1_PORTC,IN1_PIN_C);
	GPIO_ResetBits(IN2_PORTC,IN2_PIN_C);
	GPIO_ResetBits(IN1_PORTD,IN1_PIN_D);
	GPIO_ResetBits(IN2_PORTD,IN2_PIN_D);
	

	
}

void forward(){
	
	GPIO_SetBits(GPIOC,GPIO_Pin_6);
	GPIO_SetBits(GPIOC,GPIO_Pin_7);
	
	GPIO_SetBits(GPIOC,GPIO_Pin_8);
	GPIO_SetBits(GPIOC,GPIO_Pin_9);

	GPIO_SetBits(IN1_PORTA,IN1_PIN_A);	
	GPIO_SetBits(IN2_PORTB,IN2_PIN_B);	

	GPIO_SetBits(IN2_PORTC,IN2_PIN_C);	       
	GPIO_SetBits(IN1_PORTD,IN1_PIN_D);	
	

	
}
