/*********************************************************************************
 *	文件名：iniTemperatureSensor.c
 *	功能：实现温度传感器DS18B20相关函数（主要实现采集温度）
 *	作者：雷力
 *	时间：2011-01-11
 *	需要注意的问题：注意DQ管脚与单片机的具体连接端口的对应
 *********************************************************************************/


/*******************************文件修改记录(S)***********************************
 *  1.将读取温度函数修改:
 *  修改前:uchar DS18B20_Read_Temperature();
 *  修改为:void DS18B20_Read_Temperature(uchar *pTemp);
 *  日期：2011-02-05
 *  修改者:雷力
 ********************************文件修改记录(E)**********************************/
#if !defined _INI_TEMPERERATURE_SENSOR_H_
#define _INI_TEMPERERATURE_SENSOR_H_


#include "myDefine.h"
#include "STC12C5AXXXX.h"
#define jump_ROM 0xCC
#define start 0x44
#define read_EEROM 0xBE
//#define DS18b20_DQ P2^0 

//sbit DQ = P2^3 ;//DS18b20_DQ;           //DS18B20数据口

void ini_Temperature_Sensor(); //初始化温度传感器
//void DS18B20_Write_Bit(uchar bitValue);//写位值
void DS18B20_Write_Byte(uchar byteValue);//写字节值
void DS18B20_Reset(void);//复位
//uchar DS18B20_Read_Bit(void);//读一位
uchar DS18B20_Read_Byte(void);//读一个字节


void DS18B20_Read_Temperature(unsigned int *pTemp);//读取温度



#endif