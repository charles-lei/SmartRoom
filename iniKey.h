
/*	文件名：iniKey.h
	功能：声明按键处理相关函数
	作者：雷力
	时间：2011-03-01
	需要注意的问题：
*/


/*******************************文件修改记录(S)***********************************/
/*1.
/*修改前:
/*修改为:
/*日期?
/*修改者:
/********************************文件修改记录(E)**********************************/
#if !defined _INIKEY_H_
#define _INIKEY_H_
typedef enum
{
	NO_FLASH,YEAR_FLASH,MONTH_FLASH,DAY_FLASH,HOUR_FLASH,MINUTE_FLASH
}KCS;
void onKey();//相应按键函数

#endif