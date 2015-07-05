/*********************************************************************************
 *	�ļ�����iniTemperatureSensor.c
 *	���ܣ�ʵ���¶ȴ�����DS18B20��غ�������Ҫʵ�ֲɼ��¶ȣ�
 *	���ߣ�����
 *	ʱ�䣺2011-01-11
 *	��Ҫע������⣺ע��DQ�ܽ��뵥Ƭ���ľ������Ӷ˿ڵĶ�Ӧ
 *********************************************************************************/


/*******************************�ļ��޸ļ�¼(S)***********************************
 *  1.����ȡ�¶Ⱥ����޸�:
 *  �޸�ǰ:uchar DS18B20_Read_Temperature();
 *  �޸�Ϊ:void DS18B20_Read_Temperature(uchar *pTemp);
 *  ���ڣ�2011-02-05
 *  �޸���:����
 ********************************�ļ��޸ļ�¼(E)**********************************/
#if !defined _INI_TEMPERERATURE_SENSOR_H_
#define _INI_TEMPERERATURE_SENSOR_H_


#include "myDefine.h"
#include "STC12C5AXXXX.h"
#define jump_ROM 0xCC
#define start 0x44
#define read_EEROM 0xBE
//#define DS18b20_DQ P2^0 

//sbit DQ = P2^3 ;//DS18b20_DQ;           //DS18B20���ݿ�

void ini_Temperature_Sensor(); //��ʼ���¶ȴ�����
//void DS18B20_Write_Bit(uchar bitValue);//дλֵ
void DS18B20_Write_Byte(uchar byteValue);//д�ֽ�ֵ
void DS18B20_Reset(void);//��λ
//uchar DS18B20_Read_Bit(void);//��һλ
uchar DS18B20_Read_Byte(void);//��һ���ֽ�


void DS18B20_Read_Temperature(unsigned int *pTemp);//��ȡ�¶�



#endif