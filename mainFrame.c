/*	文件名：iniFrame.c
	功能：程序主框架
	作者：雷力
	时间：2011-12-20
	需要注意的问题：注意调试模式的宏定义开关,程序结构还需进一步优化，以清楚体现逻辑性
*/
#include "mainFrame.h"
#include "iniLED.h"
#include "iniTemperatureSensor.h"
#include "iniTimeControl.h"
#include "iniInterrupt.h"
#include "myDefine.h"
#include "STC12C5AXXXX.h"
#include "iniAD.h"
#include "iniKey.h"

//以下外部变量全部定义在iniIterrupt.c中
extern unsigned int curTemp;
extern structTime currentTime;
extern uchar ledFlag1;
extern uchar ledFlag;
extern uchar ringFlag;
extern float curAD;


/***********************************************华丽的分割线*********************************************/
void main()
{
	iniAllHardware();	//初始化所有部件
	run();
}
/***********************************************华丽的分割线*********************************************/
void iniAllHardware()
{
	//调试AD时需要将此开关打开
	#if _AD_DEBUG
	ini_AD();
	#endif

	ini_LED();
	ini_Temperature_Sensor();
	ini_Time_Control();
	ini_Interrupt();
}
/***********************************************华丽的分割线*********************************************/
void run()
{
 	while(true)
	{
		//读取数据时关闭所有中断
		EA = 0;
		DS1302_Get_Time(&currentTime);
		DS18B20_Read_Temperature(&curTemp);

		#if _AD_DEBUG
		curAD = AD_Average(AD_CHANNAL);
		#endif
		EA = 1;
		
		//液晶显示（时间、温度）
		if(ledFlag1)//报警标志
		{	
			if(1==ledFlag)
			{
				ledFlag = 0;
				ringFlag = 1;//此处报警代码
				LED1602_Enable(0x01);//清屏
				delay_1ms(50);
				LED1602_String(1,1,"THIS IS TOO HOT!");
			}
			LED1602_Char(2,7,curTemp /10 % 10 + 48);
			LED1602_Char(2,8,curTemp % 10 + 48);
		}
		else
		{		
			if(0==ledFlag)
			{
				ringFlag = 0;
				ledFlag = 1;
				LED1602_Enable(0x01);//清屏
				delay_1ms(50);
			}
			LED1602_Flash();//这个函数定义在iniInterrupt.c中;		
		} 
		onKey();//读取按键函数
	 }	
}