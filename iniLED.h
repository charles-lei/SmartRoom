
/*	文件名：iniLED.h
	功能：声明液晶12864的相关函数功能（主要包括初始化和显示）
	作者：雷力
	时间：2011-01-10
	需要注意的问题：
*/


/*******************************文件修改记录(S)***********************************/
/*1.
/*修改前:
/*修改为:
/*日期�
/*修改者:
/********************************文件修改记录(E)**********************************/
#if !defined _INILED_H_
#define _INILED_H_

#include "STC12C5AXXXX.h"
#include "myDefine.h"

//12864所占端口
/*sbit RS  = P2^5;
sbit WRD = P2^6;
sbit E   = P2^7;
sbit PSB = P2^2;
sbit RES = P2^4;*/

//1602所占端口
//这三个引脚参考资料
/*sbit E = P2^7;		//1602使能引脚
sbit RW = P2^6;		//1602读写引脚	
sbit RS = P2^5;		//1602数据/命令选择引脚
*/
void ini_LED(); //初始化液晶

//void LED12864_Ini_Char_Lib(void);				//初始化字库

//void LED12864_Ini_Graphic_Lib(void);           //LCD显示图片(扩展)初始化程序

//void LED12864_Transfer_Data(char data1,bit DI);  //传送数据或者命令,当DI=0是,传送命令,当DI=1,传送数据.

//void LED12864_Display_Char(uchar code *address);//显示汉字

//void LED12864_Display_Graphic(uchar code *address);//显示图形

//uchar LED1602_Convert(uchar In_Date);

void LED1602_Enable(uchar del);

void LED1602_Write(uchar del);

void LED1602_Ini(void);

void LED1602_Char(uchar hang,uchar lie,char sign);

void LED1602_String(uchar hang,uchar lie,uchar *p);


#endif