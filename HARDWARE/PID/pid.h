#ifndef _PID_H
#define _PID_H

#include "sys.h"

int SPEED_PID_A(int now,int set);
int SPEED_PID_B(int now,int set);
int SPEED_PID_C(int now,int set);
int SPEED_PID_D(int now,int set);
int Position_PD_ABCD(int now,int set);

#endif
