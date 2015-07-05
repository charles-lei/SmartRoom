/*	�ļ�����iniTimeControl.h
	���ܣ�����ʱ�������DS1302��غ�������Ҫʵ�ֶ�ȡʱ�䣩
	���ߣ�����
	ʱ�䣺2011-01-11
	��Ҫע������⣺ע��ܽ��뵥Ƭ���ľ������Ӷ˿ڵĶ�Ӧ
*/

/*******************************�ļ��޸ļ�¼(S)***********************************/
/*1.
/*�޸�ǰ:
/*�޸�Ϊ:
/*����:
/*�޸���:
/********************************�ļ��޸ļ�¼(E)**********************************/
#if !defined _INI_TIME_CONTROL_H_
#define _INI_TIME_CONTROL_H_

#include "myDefine.h"
#include "STC12C5AXXXX.h"
typedef struct 
{
	uchar year;//����趨Ϊ��λ��
	uchar month;
	uchar day;
	uchar hour;
	uchar minute;
	uchar second;
	uchar week;
}structTime;



/*sbit ACC0 = ACC^0;
sbit ACC7 = ACC^7;
sbit T_CLK = P1^6; //ʵʱʱ��ʱ��������
sbit T_IO = P3^5; //ʵʱʱ������������
sbit T_RST = P1^7; //ʵʱʱ�Ӹ�λ������ 
*/


void ini_Time_Control(); //��ʼ��ʱ�������
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