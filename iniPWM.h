/***************************************************************
*�ļ�����iniPWM.h
*���ܣ�����PWM���β�������غ�������Ҫʵ�ֲ��������PWM��
*���ߣ�����
*ʱ�䣺2011-01-18
*��Ҫע������⣺ע��ܽ��뵥Ƭ���ľ������Ӷ˿ڵĶ�Ӧ
*****************************************************************/

/*******************************�ļ��޸ļ�¼(S)***********************************/
/*1.
/*�޸�ǰ:
/*�޸�Ϊ:
/*����:
/*�޸���:
/********************************�ļ��޸ļ�¼(E)**********************************/
#if !defined _INI_PWM_H_
#define _INI_PWM_H_

#include "myDefine.h"
//#include "STC12C5AXXXX.h"

void ini_PCA_PWM();
//void ini_Timer_PWM();
void PWM_PCAProduce_PWM(uchar mark,uchar space);//��PCA����PWM
//void PWM_TimerProduce_PWM(uchar mark,uchar space);//�ö�ʱ������PWM
   

#endif