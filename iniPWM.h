/***************************************************************
*文件名：iniPWM.h
*功能：声明PWM波形产生的相关函数（主要实现产生所需的PWM）
*作者：雷力
*时间：2011-01-18
*需要注意的问题：注意管脚与单片机的具体连接端口的对应
*****************************************************************/

/*******************************文件修改记录(S)***********************************/
/*1.
/*修改前:
/*修改为:
/*日期:
/*修改者:
/********************************文件修改记录(E)**********************************/
#if !defined _INI_PWM_H_
#define _INI_PWM_H_

#include "myDefine.h"
//#include "STC12C5AXXXX.h"

void ini_PCA_PWM();
//void ini_Timer_PWM();
void PWM_PCAProduce_PWM(uchar mark,uchar space);//用PCA产生PWM
//void PWM_TimerProduce_PWM(uchar mark,uchar space);//用定时器产生PWM
   

#endif