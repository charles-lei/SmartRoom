/*	文件名：iniTimeControl.h
	功能：声明时间控制器DS1302相关函数（主要实现读取时间）
	作者：雷力
	时间：2011-01-11
	需要注意的问题：注意管脚与单片机的具体连接端口的对应
*/

/*******************************文件修改记录(S)***********************************/
/*1.
/*修改前:
/*修改为:
/*日期:
/*修改者:
/********************************文件修改记录(E)**********************************/
#if !defined _INI_TIME_CONTROL_H_
#define _INI_TIME_CONTROL_H_

#include "myDefine.h"
#include "STC12C5AXXXX.h"
typedef struct 
{
	uchar year;//年份设定为两位数
	uchar month;
	uchar day;
	uchar hour;
	uchar minute;
	uchar second;
	uchar week;
}structTime;



/*sbit ACC0 = ACC^0;
sbit ACC7 = ACC^7;
sbit T_CLK = P1^6; //实时时钟时钟线引脚
sbit T_IO = P3^5; //实时时钟数据线引脚
sbit T_RST = P1^7; //实时时钟复位线引脚 
*/


void ini_Time_Control(); //初始化时间控制器
void DS1302_Write_Byte(uchar byteValue);
uchar DS1302_Read_Byte(void);
void DS1302_Write_Data(uchar dataAddress, uchar dataValue);
uchar DS1302_Read_Data(uchar dataAddress);
//void DS1302_Write_Time(uchar *pTime);
//void DS1302_Read_Time(uchar *pTime);
//void DS1302_Write_Register(uchar *pRegister);
//void DS1302_Read_Register(uchar *pRe6gister);
void DS1302_Set_Time(structTime *pTime);
void DS1302_Get_Time(structTime *pTime);


#endif