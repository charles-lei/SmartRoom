/*	文件名：iniInterrupt.c
	功能：实现中断功能（主要为温度采集和光强度采集）
	作者：雷力
	创建日期：2011-01-19
	作成日期：2011-01-30
	需要注意的问题：
*/

/**************************************************文件修改记录(S)**********************************************/
/*1.封装中断1中的液晶显示代码
/*修改前:中断中的局部变量改变为全局变量
/*修改为:
/*日期:2011-02-18
/*修改者:雷力
/****************************************************************************************************************
/*2.中断1中代码的优化，使中断执行时间尽可能的短
/*修改前:变量声明，温度采集函数，时间读取函数，液晶刷新函数都在中断中声明或执行
/*修改为:将变量声明为全局的，中断负责设置状态改变的标志，在程序主循环进行温度采集、时间读取、液晶刷新等操作
/*日期:2011-03-01
/*修改者:雷力
/**************************************************文件修改记录(E)**********************************************/
#include "iniInterrupt.h"
#include "STC12C5AXXXX.h"
#include "myDefine.h"
#include "iniTimeControl.h"
#include "iniLED.h"
#include "iniTemperatureSensor.h"
#include "iniBeem.h"
#include "iniKey.h"

//全局的(不得已而为之)，供两个中断用
extern KCS KeyControlState;//枚举类型，表示按键的控制状态
unsigned int preTemp = 0;  //记录上一次读取的温度
unsigned int curTemp = 0;	//记录当前温度
unsigned int countTemp = 0;	//用于计算某个温度段持续时间
structTime currentTime;		//记录当前时间
uchar PWM_ON = 10 ;//定义高电平时间		
uchar ringFlag = 0;	//报警标志	
uchar ledFlag = 0;//为了LED不闪烁，设此标志 
uchar ledFlag1 = 0;//主循环根据此标志决定报警和液晶显示内容
uchar tempFlag = 0;//达到一定条件时仅改变一次电机状态
uchar ledFlashCount = 0; //设置时间时led闪烁时间间隔：ledFlashCount*50ms

float curAD = 0.0;
float preAD = 0.0;
unsigned int countAD = 0;
uchar adFlag = 0;//达到一定条件时仅改变一次灯状态


void ini_Interrupt()
{
	delay_1ms(100);
	ini_Timer0();
	ini_Timer1();	
}


void ini_Timer0()
{
	TMOD = 0x01;			//定时/计数器模式控制寄存器
	IE 	 = 0x82;		//中断使能寄存器

	TH0  = 0xfc;			//1ms,11.0592MHZ
	TL0  = 0x66;	        
	IP = 0x02;
	TR0 = 1;			//定时/计数器控制寄存器TCON的TR0位 1：激活计数器0。0：停止。
}		

void ini_Timer1()
{
	TMOD |= 0x10;			//定时/计数器模式控制寄存器
	IE 	 |= 0x88;		//中断使能寄存器

	TH1  = 0x4c;			//50ms,11.0592MHZ
	TL1  = 0x00;	        
	TR1 = 1;			//定时/计数器控制寄存器TCON的TR1位 1：激活计数器1。0：停止。
}


/********************************************************************
* 名称 : Timer1() interrupt 3
* 功能 : 用定时器1 定时50MS用于电机及灯状态的改变
* 输入 : 无
* 输出 : 无
***********************************************************************/
void Timer1() interrupt 3 	//11.092MHZ 50MS
{	
 	TH1  = 0x4c;			//计数器0高8位
	TL1  = 0x00;	        //计数器0低8位   
			//读取数据时关闭所有中断


	ledFlashCount++;
	if(20 == ledFlashCount) ledFlashCount = 0;


	//计算某个温度段的持续时间,用countTemp计数表示,每加一表示加此中断执行一次所需时间
	/****************************计算开始**************************************/
	if(0 == countTemp)
	{	
		tempFlag = 0; 
		countTemp++;
		preTemp = curTemp;
	}
	else
	{
		if(curTemp < TEMP_ZERO && preTemp < TEMP_ZERO 
			|| curTemp >= TEMP_ZERO && curTemp < TEMP_FIRST && preTemp >= TEMP_ZERO && preTemp < TEMP_FIRST 
			|| curTemp >= TEMP_FIRST && curTemp < TEMP_RING && preTemp >= TEMP_FIRST && preTemp < TEMP_RING 
			|| curTemp >= TEMP_RING && preTemp >= TEMP_RING)
		{
			countTemp++;
			preTemp = curTemp;
		}
		else countTemp = 0;
		if(countTemp > TEMP_LASTTIME) 
		{
			countTemp = TEMP_LASTTIME;
			tempFlag = 1;
		}
	}
	/*****************************计算结束*************************************/
	
	//改变电机状态
	if(countTemp == TEMP_LASTTIME && tempFlag != 1) //持续约LASTIME*50ms,tempFlag标志表示刚持续到LASTTIME*50ms时只改变这一次电机状态
	{
		if(curTemp < TEMP_ZERO)
		{
			//停止风扇转动
			PWM_ON = 10;	
		}
		else if(curTemp >= TEMP_ZERO && curTemp < TEMP_FIRST)
		{
			//一档PWM
			PWM_ON = 1;	
		}
		else if(curTemp >= TEMP_FIRST && curTemp < TEMP_RING)
		{
			//二档PWM
			PWM_ON = 0;
		}
		else
		{
		 	PWM_ON = 10;
		}
	}

	//到达报警条件报警
	if(curTemp >= TEMP_RING && countTemp == TEMP_LASTTIME)
	{	
		ledFlag1 = 1;	//报警标志,用于在中断外做相应的操作（液晶显示及刷新,报警)
	}
	else
	{
		ledFlag1 = 0;	
	} 
	
	//AD模块调试代码
	#if _AD_DEBUG


	//计算某个光照度段的持续时间,用countAD计数表示,每加一表示加此中断执行一次所需时间
	/****************************计算开始**************************************/
	if(0 == countAD)
	{	
		adFlag = 0; 
		countAD++;
		preAD = curAD;
	}
	else
	{
		if(curAD <= LIGHT_XXXX && preAD < LIGHT_XXXX
			 || curAD >= LIGHT_XXXX && preAD >= LIGHT_XXXX)//LIGHT_XXXX为光强度数值，用于确定灯状态改变的临界点
		{
			countAD++;
			preAD = AD;
		}
		else countAD = 0;
		if(countAD > LIGHT_LASTTIME) 
		{
			countTemp = LIGHT_LASTTIME;
			adFlag = 1;
		}
	}
	/*****************************计算结束*************************************/
	
	//改变灯状态
	if(countAD == LIGHT_LASTTIME && adFlag != 1) //持续约LASTIME*50ms,adFlag标志表示刚持续到LASTTIME*50ms时只改变这一次状态
	{
		if(curAD <= LIGHT_XXXX)
		{
			//灯亮
			LIGHT = 1;	
		}
		else
		{
			//灯灭
			LIGHT = 0;	
		}
	}

	#endif
}

/********************************************************************
* 名称 : Timer1() interrupt 3
* 功能 : 用定时器0 定时1MS用于产生PWM
* 输入 : 无
* 输出 : 无
***********************************************************************/
void Timer0() interrupt 1	//11.092MHZ 1MS
{
	static uchar c = 0;
 	TH0  = 0xfc;			//计数器0高8位
	TL0  = 0x66;	
	if (c==PWM_ON)
    {
    	PWM = 1; 
    }
  	c++;
	if(c == CYCLE)
    {
   		c = 0;
		if(PWM_ON != 0) //如果左右时间是0 保持原来状态
	   		PWM = 0;
    }
	if(1==ringFlag) ring();	
}

/********************************************************************
* 名称 : L1602_Flash()
* 功能 : 刷新LED1602显示
* 输入 : 无
* 输出 : 无
***********************************************************************/
void LED1602_Flash()
{
	if(KeyControlState == HOUR_FLASH)
	{
		if(ledFlashCount <= 10)
		{
			LED1602_Char(2, 6, currentTime.hour / 10 % 10 + 48);
			LED1602_Char(2, 7, currentTime.hour % 10 + 48);
		}
		else
		{
 			LED1602_Char(2, 6,' ');
			LED1602_Char(2, 7,' ');
		}

	}
	else 
	{
		LED1602_Char(2, 6, currentTime.hour / 10 % 10 + 48);
		LED1602_Char(2, 7, currentTime.hour % 10 + 48);
	}
	if(KeyControlState == MINUTE_FLASH)
	{
		if(ledFlashCount <= 10)
		{
			LED1602_Char(2, 9, currentTime.minute / 10 % 10 + 48);
			LED1602_Char(2, 10, currentTime.minute % 10 + 48);
		}
		else
		{
 			LED1602_Char(2, 9,' ');
			LED1602_Char(2, 10,' ');
		}

	}
	else 
	{
		LED1602_Char(2, 9, currentTime.minute / 10 % 10 + 48);
		LED1602_Char(2, 10, currentTime.minute % 10 + 48);
	}

	if(KeyControlState == YEAR_FLASH)
	{
		if(ledFlashCount <= 10)
		{
			LED1602_Char(1, 8, currentTime.year / 10 % 10 + 48);
			LED1602_Char(1, 9, currentTime.year % 10 + 48);
		}
		else
		{
 			LED1602_Char(1, 8,' ');
			LED1602_Char(1, 9,' ');
		}

	}
	else 
	{
		LED1602_Char(1, 8, currentTime.year / 10 % 10 + 48);
		LED1602_Char(1, 9, currentTime.year % 10 + 48);
	}

	if(KeyControlState == MONTH_FLASH)
	{
		if(ledFlashCount <= 10)
		{
			LED1602_Char(1, 11, currentTime.month / 10 % 10 + 48);
			LED1602_Char(1, 12, currentTime.month % 10 + 48);
		}
		else
		{
 			LED1602_Char(1, 11,' ');
			LED1602_Char(1, 12,' ');
		}

	}
	else 
	{
		LED1602_Char(1, 11, currentTime.month / 10 % 10 + 48);
		LED1602_Char(1, 12, currentTime.month % 10 + 48);
	}
	if(KeyControlState == DAY_FLASH)
	{
		if(ledFlashCount <= 10)
		{
			LED1602_Char(1, 14, currentTime.day / 10 % 10 + 48);
			LED1602_Char(1, 15, currentTime.day % 10 + 48);
		}
		else
		{
 			LED1602_Char(1, 14,' ');
			LED1602_Char(1, 15,' ');
		}

	}
	else 
	{
		LED1602_Char(1, 14, currentTime.day / 10 % 10 + 48);
		LED1602_Char(1, 15, currentTime.day % 10 + 48);
	}
	LED1602_Char(2, 8, '-');
	LED1602_Char(2, 11, '-');
	LED1602_Char(2, 12, currentTime.second / 10 % 10 + 48);
	LED1602_Char(2, 13, currentTime.second % 10 + 48);
	LED1602_Char(1, 6, '2');
	LED1602_Char(1, 7, '0');
	LED1602_Char(1, 10, '-');
	LED1602_Char(1, 13, '-');;
	LED1602_Char(2, 15, curTemp /10 % 10 + 48);
	LED1602_Char(2, 16, curTemp % 10 + 48);			
}
