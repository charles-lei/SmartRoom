/*	�ļ�����iniInterrupt.h
	���ܣ������жϹ��ܣ���ҪΪ�¶Ȳɼ��͹�ǿ�Ȳɼ���
	���ߣ�����
	ʱ�䣺
	��Ҫע������⣺
*/


/*******************************�ļ��޸ļ�¼(S)***********************************/
/*1.
/*�޸�ǰ:
/*�޸�Ϊ:
/*���ڣ
/*�޸���: 
/********************************�ļ��޸ļ�¼(E)**********************************/
#if !defined _INI_INTERRUPT_
#define _INI_INTERRUPT_

#include "stc12c5axxxx.h"
#define CYCLE 10

void ini_Interrupt(); //��ʼ���ж�

void LED1602_Flash();

void ini_Timer0();

void ini_Timer1();

#endif