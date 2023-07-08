#include "pid.h"

static double   ProportionA=23;                               //�������� Proportional Const
static double   IntegralA=1;                                 //���ֳ��� Integral Const
static double   DerivativeA=2;

int SPEED_PID_A(int now,int set)
{
	static int  LastError;	//Error[-1]
	static int  PrevError;  //Error[-2]
  int iError,Output;      //��ǰ���
//Pwm+=Kp[e(k)-e(k-1)]+Ki*e(k)  +Kd[e(k)-2e(k-1)+e(k-2)]	

//  Outpid=(Proportion * iError)                   //E[k]��
//              -(Integral * LastError)      			 //E[k-1]��
//              +(Derivative * PrevError);   			 //E[k-2]��
	
	iError=set-now;
	Output = ((ProportionA * (iError - LastError)) + (IntegralA * iError) + (DerivativeA * (iError - 2*LastError + PrevError)));	
  PrevError=LastError;                     //�洢�������´μ���
  LastError=iError;
  return Output;                                      //��������ֵ
}

static double   ProportionB=13; //���ٶȻ�P=70,I=25,D=35 -> P=12,I=0.4,D=0.8                            //�������� Proportional Const
static double   IntegralB=0.9;                                //���ֳ��� Integral Const
static double   DerivativeB=1;//10.0.4.0.93
								
int SPEED_PID_B(int now,int set)
{
	static int  LastError;	//Error[-1]
	static int  PrevError;  //Error[-2]
  int iError,Output;      //��ǰ���
//Pwm+=Kp[e(k)-e(k-1)]+Ki*e(k)  +Kd[e(k)-2e(k-1)+e(k-2)]	

//  Outpid=(Proportion * iError)                   //E[k]��
//              -(Integral * LastError)      			 //E[k-1]��
//              +(Derivative * PrevError);   			 //E[k-2]��
	
	iError=set-now;
	Output = ((ProportionB * (iError - LastError)) + (IntegralB * iError) + (DerivativeB * (iError - 2*LastError + PrevError)));	
  PrevError=LastError;                     //�洢�������´μ���
  LastError=iError;
  return Output;                                      //��������ֵ
}
static double   ProportionC=21;                               //�������� Proportional Const
static double   IntegralC=2;                                 //���ֳ��� Integral Const
static double   DerivativeC=0.5;

int SPEED_PID_C(int now,int set)
{
	static int  LastError;	//Error[-1]
	static int  PrevError;  //Error[-2]
  int iError,Output;      //��ǰ���
//Pwm+=Kp[e(k)-e(k-1)]+Ki*e(k)  +Kd[e(k)-2e(k-1)+e(k-2)]	

//  Outpid=(Proportion * iError)                   //E[k]��
//              -(Integral * LastError)      			 //E[k-1]��
//              +(Derivative * PrevError);   			 //E[k-2]��
	
	iError=set-now;
	Output = ((ProportionC * (iError - LastError)) + (IntegralC * iError) + (DerivativeC * (iError - 2*LastError + PrevError)));	
  PrevError=LastError;                     //�洢�������´μ���
  LastError=iError;
  return Output;                                      //��������ֵ
}
static double   ProportionD=22;                               //�������� Proportional Const
static double   IntegralD=2;                                 //���ֳ��� Integral Const
static double   DerivativeD=0.5;

int SPEED_PID_D(int now,int set)
{
	static int  LastError;	//Error[-1]
	static int  PrevError;  //Error[-2]
  int iError,Output;      //��ǰ���
//Pwm+=Kp[e(k)-e(k-1)]+Ki*e(k)  +Kd[e(k)-2e(k-1)+e(k-2)]	

//  Outpid=(Proportion * iError)                   //E[k]��
//              -(Integral * LastError)      			 //E[k-1]��
//              +(Derivative * PrevError);   			 //E[k-2]��
	
	iError=set-now;
	Output = ((ProportionD * (iError - LastError)) + (IntegralD * iError) + (DerivativeD * (iError - 2*LastError + PrevError)));	
  PrevError=LastError;                     //�洢�������´μ���
  LastError=iError;
  return Output;                                      //��������ֵ
}


static double  P=1.2;//P=2.5 D=1-> P=2.5 D=10->P=2.5 D=5 ->P=1.8 D=5 ->P=1.8 D=10 ->P=1.8 D=15 ->P=1.5 D=25 ->P=1.5 D=30                             //��������
static double  I=0; //2.33                                //���ֳ���
static double  D=0.1;

//���ֲ��� 35.3 0 5.3
int Position_PD_ABCD(int now,int set)
{
	static float Bias,Output,Last_Bias,inral;
	//Pwm+=Kp*e(k) + Ki*��e(k) + Kd[e(k)-e(k-1)]	
	Bias=now-set;
	inral+=Bias;
	Output=P*Bias+I*inral+D*(Bias-Last_Bias);
	Last_Bias=Bias;
	return Output;
}
