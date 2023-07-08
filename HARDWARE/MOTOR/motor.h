#ifndef _MOTOR_H
#define _MOTOR_H

#include "sys.h"

/*--------Motor_A control pins--------*/	
#define PWM_PORTA GPIOC			 //PWMA . ..................................  m .        	右前                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
#define PWM_PIN_A GPIO_Pin_6 //PWMA
#define PWMA 	  TIM8->CCR1	 //PWMA


#define IN1_PORTA GPIOA			 //AIN1
#define IN1_PIN_A GPIO_Pin_3 //AIN1
#define AIN1 	  PAout(3)		 //AIN1

#define IN2_PORTA GPIOA			 //AIN2
#define IN2_PIN_A GPIO_Pin_2 //AIN2
#define AIN2 	  PAout(2)		 //AIN2

/*
	AIN1 = 0;		前进
	AIN2 = 1;
*/


/*------------------------------------*/

/*--------Motor_B control pins--------*/												//左前
#define PWM_PORTB GPIOC			 //PWMB
#define PWM_PIN_B GPIO_Pin_7 //PWMB                                                                                                                                                                                                                                                                                                    cgg
#define PWMB 	  TIM8->CCR2	 //PWMB



#define IN1_PORTB GPIOA			 //BIN1
#define IN1_PIN_B GPIO_Pin_4 //BIN1
#define BIN1 	  PAout(4)		 //BIN1

#define IN2_PORTB GPIOA			 //BIN2
#define IN2_PIN_B GPIO_Pin_5 //BIN2
#define BIN2 	  PAout(5)		 //BIN2

/*
	BIN1 = 0;		前进
	BIN2 = 1;
*/

/*------------------------------------*/

/*--------Motor_C control pins--------*/						/*右后*/
#define PWM_PORTC GPIOC			 //PWMC
#define PWM_PIN_C GPIO_Pin_8 //PWMC
#define PWMC 	  TIM8->CCR3	 //PWMC


#define IN1_PORTC GPIOE			  //CIN1
#define IN1_PIN_C GPIO_Pin_12	//CIN1
#define CIN1 	  PEout(12)		  //CIN1

#define IN2_PORTC GPIOC			 //CIN2
#define IN2_PIN_C GPIO_Pin_5 //CIN2
#define CIN2 	  PCout(5)		 //CIN2

/*
		CIN1 = 1;		前进
		CIN2 = 0;
*/
/*------------------------------------*/

/*--------Motor_D control pins--------*/
		
#define PWM_PORTD GPIOC			 //PWMD			/*左后*/
#define PWM_PIN_D GPIO_Pin_9 //PWMD
#define PWMD 	  TIM8->CCR4	 //PWMD


#define IN1_PORTD GPIOB			  //DIN1
#define IN1_PIN_D GPIO_Pin_11	//DIN1
#define DIN1 	  PBout(11)		  //DIN1

#define IN2_PORTD GPIOB			  //DIN2
#define IN2_PIN_D GPIO_Pin_15	//DIN2
#define DIN2 	  PBout(15)		  //DIN2

/*
	DIN1 = 0;		前进s
	DIN2 = 1;
*/
/*------------------------------------*/

void MOTOR_GPIO_Init(void);
void forward(void);
#endif
