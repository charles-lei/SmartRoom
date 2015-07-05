/*	文件名：iniInterrupt.h
	功能：声明中断功能（主要为温度采集和光强度采集）
	作者：雷力
	时间：
	需要注意的问题：
*/


/*******************************文件修改记录(S)***********************************/
/*1.
/*修改前:
/*修改为:
/*日期�
/*修改者: 
/********************************文件修改记录(E)**********************************/
#if !defined _INI_INTERRUPT_
#define _INI_INTERRUPT_

#include "stc12c5axxxx.h"
#define CYCLE 10

void ini_Interrupt(); //初始化中断

void LED1602_Flash();

void ini_Timer0();

void ini_Timer1();

#endif