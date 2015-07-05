/*	文件名：myDefine.h
	功能：声明公用相关函数
	作者：雷力
	时间：2011-01-10
	需要注意的问题：1.最后应当根据实际环境改动相应的端口
					2.如果调试成功应当去掉程序中的所有用作调试的宏开关
*/

/*******************************文件修改记录(S)***********************************/
/*1.将所有用到的端口放到此文件中，便于集中管理
/*修改前:
/*修改为:
/*日期:2011-03-01
/*修改者:雷力
/********************************文件修改记录(E)**********************************/
#if !defined _MY_DEFINE_
#define _MY_DEFINE_
#include "STC12C5AXXXX.h"

#define true 1
#define false 0
#define uchar unsigned char
#define uint unsigned int
#define _DEBUG_ 1
#define _TEMP_DEBUG 0
#define _TIME_DEBUG 0
#define _LED_DEBUG 1
#define _AD_DEBUG 0

//定义电机档位温度界限
#define TEMP_ZERO 20  //30度以下
#define TEMP_FIRST 25	//30~35
#define TEMP_SECOND 27	//35~60
#define TEMP_RING 29	//报警温度
#define TEMP_LASTTIME 400  // 定义温度持续时间:400*中断1执行一次所需时间

//定义灯状态改变的光强度界限
#define LIGHT_XXXX 1000//AD数值需要硬件试验测试
#define LIGHT_LASTTIME 400  // 定义光强度持续时间:400*中断1执行一次所需时间

//定义AD转换通道
#define AD_CHANNEL 1

//PWM输出引脚
sbit PWM = P1^4;

//灯状态改变引脚
sbit LIGHT = P1^3;

//1602所占端口
sbit E = P2^4;		//1602使能引脚
sbit RW = P2^3;		//1602读写引脚	
sbit RS = P2^2;		//1602数据/命令选择引脚
#define LED_DATA P0 //P0为数据口

//DS18B20占用端口
sbit DQ = P2^0 ;//DS18b20_DQ;           //DS18B20数据口

//DS1302占用端口
sbit ACC0 = ACC^0;
sbit ACC7 = ACC^7;
sbit T_CLK = P1^2; //实时时钟时钟线引脚
sbit T_IO = P3^4; //实时时钟数据线引脚
sbit T_RST = P1^1; //实时时钟复位线引脚 

//按键口
sbit KEY_CONTROL = P1^5;
sbit KEY_ADD = P1^6;
sbit KEY_SUB = P1^7;

//公用函数
void delay_1ms(uint i);//1ms延时
//void delay_little(uint N);
uchar DEC_To_BCD(uchar decimal);
uchar BCD_To_DEC(uchar bcd);
//void delay_1us(uint m);
void DelayXus(uchar n);


#endif