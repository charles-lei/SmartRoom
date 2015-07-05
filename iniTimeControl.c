
/*	�ļ�����iniTimeControl.c
	���ܣ�ʵ��ʱ�������DS1302��غ�������Ҫʵ�ֶ�ȡʱ�䣩
	���ߣ�����
	�������ڣ�2011-01-11
	�������ڣ�2011-01-11
	��Ҫע������⣺ע��ܽ��뵥Ƭ���ľ������Ӷ˿ڵĶ�Ӧ���ѽ����
*/


/*******************************�ļ��޸ļ�¼(S)***********************************/
/*1.
/*�޸�ǰ:
/*�޸�Ϊ:
/*����:
/*�޸���:
/********************************�ļ��޸ļ�¼(E)**********************************/
#include "iniTimeControl.h"
#include "STC12C5AXXXX.h"
#include "myDefine.h"
#include <intrins.h>
/********************************************************************
* ���� : Write_DS1302Init()
* ���� : ��DS1302��д�����ݡ��ʼ��ʾ�����ݾ������������õġ�
* ���� : ��
* ��� : ��
***********************************************************************/
void ini_Time_Control()
{
/*	DS1302_Write_Data(0x8e,0);
	DS1302_Write_Data(0x80,0x50);	//д����
	DS1302_Write_Data(0x8e,0);
	DS1302_Write_Data(0x82,0x59);	//д���
	DS1302_Write_Data(0x8e,0);
	DS1302_Write_Data(0x84,0x07);	//д��Сʱ
	DS1302_Write_Data(0x8e,0);
	DS1302_Write_Data(0x86,0x08);	//д����
	DS1302_Write_Data(0x8e,0);
	DS1302_Write_Data(0x88,0x08);	//д����
	DS1302_Write_Data(0x8e,0);
	DS1302_Write_Data(0x8a,0x05);	//д������
	DS1302_Write_Data(0x8e,0);
	DS1302_Write_Data(0x8c,0x08);	//д����	
*/  
    structTime iniDefaultTime = {11,1,1,23,99,50,5};
	DS1302_Set_Time(&iniDefaultTime);
}

/********************************************************************
* ���� :  DS1302_Write_Byte����
* ���� :  ��DS1302д��1Byte����
* ���� :  byteValue д�������
* ��� :  ��
***********************************************************************/
void DS1302_Write_Byte(uchar byteValue)
{
	uchar i;
	ACC = byteValue;
	T_RST = 1;
	for(i=8; i>0; i--)
	{
		T_IO = ACC0;
		T_CLK = 1;
		T_CLK = 0;
		ACC = ACC >> 1;
	}
}

/********************************************************************
* ����  :   DS1302_Read_Byte(void)
* ����  :   ��DS1302��ȡ1Byte����
* ����  :	��
* ����ֵ:   ACC
***********************************************************************/
uchar DS1302_Read_Byte(void)
{
	uchar i;
	T_RST = 1;
	for(i=8; i>0; i--)
	{
		ACC = ACC >>1;
		T_IO=1;
		ACC7 = T_IO;
		T_CLK = 1;
		T_CLK = 0;
	}
	return(ACC);
}

/********************************************************************
* ����   :   DS1302_Write_Data(uchar dataAddress, uchar dataValue)
* ����   :   ��DS1302д������
* ����   :   dataAddress: DS1302��ַ, dataValue: Ҫд������
* ����ֵ :   ��
***********************************************************************/
void DS1302_Write_Data(uchar dataAddress, uchar dataValue)
{
	T_CLK = 0;
	T_RST = 1;
	DS1302_Write_Byte(dataAddress);   // д��ַ 
	_nop_();
	_nop_();
	DS1302_Write_Byte(dataValue);     // д1Byte����
	T_CLK = 1;
	T_RST = 0;
}

/********************************************************************
* ����   :  DS1302_Read_Data(uchar dataAddress)
* ����   :  ��ȡDS1302ĳ��ַ������
* ����   :  dataAddress: DS1302��ַ
* ����ֵ :  ucDa :��ȡ������
***********************************************************************/
uchar DS1302_Read_Data(uchar dataAddress)
{
	uchar ucDa;
	T_RST = 0;
	T_CLK = 0;
	T_RST = 1;
	DS1302_Write_Byte(dataAddress);    //д��ַ������
	_nop_();
	_nop_();
	ucDa = DS1302_Read_Byte(); //��1Byte����
	T_CLK = 1;
	T_RST = 0;
	return(ucDa);
}

/********************************************************************
* ����   :  DS1302_Write_Time(uchar *pTime)
* ����   :  ��DS1302д��ʱ������(���ֽڷ�ʽ)
* ����   :  pTime: ʱ�����ݵ�ַ ��ʽΪ: �� �� ʱ �� �� ���� �� ����
* 						   8Byte (BCD��) 1B 1B 1B 1B 1B 1B  1B  1B
* ����ֵ :  ��
***********************************************************************/
/*void DS1302_Write_Time(uchar *pTime)
{
	uchar i;
	DS1302_Write_Data(0x8e, 0x00);          //��������,WP=0,д����
	T_RST = 0;
	T_CLK = 0;
	T_RST = 1;
	DS1302_Write_Byte(0xbe);          //0xbe:ʱ�Ӷ��ֽ�д����
	for(i=8; i>0; i--)            //8Byte = 7Byte ʱ������ + 1Byte ����
	{
		DS1302_Write_Byte(*pTime);   //д1Byte����
		pTime++;
	}
	T_CLK = 1;
	T_RST = 0;
}*/

/********************************************************************
* ����   :  DS1302_Read_Time(uchar *pTime)
* ����   :  ��ȡDS1302ʱ������
* ����   :  pSecDa: ʱ�����ݵ�ַ ��ʽΪ: �� �� ʱ �� �� ���� ��
* 					       7Byte (BCD��) 1B 1B 1B 1B 1B 1B   1B
* ����ֵ :  ucDa :��ȡ������
***********************************************************************/
/*void DS1302_Read_Time(uchar *pTime)
{
	uchar i;
	T_RST = 0;
	T_CLK = 0;
	T_RST = 1;
	DS1302_Write_Byte(0xbf);               //0xbf:ʱ�Ӷ��ֽڶ�����
	for(i=8; i>0; i--)
	{
		*pTime = DS1302_Read_Byte();   //��1Byte����
		pTime++;
	}
	T_CLK = 1;
	T_RST = 0;
}*/

/********************************************************************
* ����   :  DS1302_Write_Register(uchar *pRegister)
* ����   :  ��DS1302�Ĵ�����д������(���ֽڷ�ʽ)
* ����   :  pReDa: �Ĵ������ݵ�ַ
* ����ֵ :  ��
***********************************************************************/
/*void DS1302_Write_Register(uchar *pRegister)
{
	
	uchar i;
	DS1302_Write_Data(0x8e,0x00);         //��������,WP=0,д����
	T_RST = 0;
	T_CLK = 0;
	T_RST = 1;
	DS1302_Write_Byte(0xfe);       //0xbe:ʱ�Ӷ��ֽ�д����
	for(i=31; i>0; i--)        //31Byte �Ĵ�������
	{
		DS1302_Write_Byte(*pRegister); //д1Byte����
		pRegister++;
	}
	T_CLK = 1;
	T_RST = 0;
}*/


/********************************************************************
* ����   :  DS1302_Read_Register(uchar *pRegister)
* ����   :  ��ȡDS1302�Ĵ�������
* ����   :  pRegister: �Ĵ������ݵ�ַ
* ����ֵ :  ��
***********************************************************************/
/*void DS1302_Read_Register(uchar *pRegister)
{
	uchar i;
	T_RST = 0;
	T_CLK = 0;
	T_RST = 1;
	DS1302_Write_Byte(0xff);            //0xbf:ʱ�Ӷ��ֽڶ�����
	for(i=31; i>0; i--)             //31Byte �Ĵ�������
	{
		*pRegister = DS1302_Read_Byte(); //��1Byte����
		pRegister++;
	}
	T_CLK = 1;
	T_RST = 0;
}*/

/********************************************************************
* ����  :  DS1302_Set_Time(uchar *pTime)
* ����  :  ���ó�ʼʱ��
* ����  :  pTime: ��ʼʱ���ַ����ʼʱ���ʽΪ: �� �� ʱ �� �� ���� ��
* 								   7Byte (BCD��) 1B 1B 1B 1B 1B 1B  1B
* ����ֵ: ��
***********************************************************************/
void DS1302_Set_Time(structTime *pTime)
{
	//uchar i;
	uchar ucAddr = 0x80;
	DS1302_Write_Data(0x8e, 0x00);            //��������,WP=0,д����
	DS1302_Write_Data(ucAddr,DEC_To_BCD(pTime->second));
	DS1302_Write_Data(ucAddr+2,DEC_To_BCD(pTime->minute));
	DS1302_Write_Data(ucAddr+4,DEC_To_BCD(pTime->hour));
	DS1302_Write_Data(ucAddr+6,DEC_To_BCD(pTime->day));
	DS1302_Write_Data(ucAddr+8,DEC_To_BCD(pTime->month));
	DS1302_Write_Data(ucAddr+10,DEC_To_BCD(pTime->week));
	DS1302_Write_Data(ucAddr+12,DEC_To_BCD(pTime->year));
	//for(i=7; i>0; i--)
	//{
	//	DS1302_Write_Data(ucAddr, *pTime);   // �� �� ʱ �� �� ���� ��
	//	pTime++;
	//	ucAddr += 2;
	//}
	DS1302_Write_Data(0x8e, 0x80);            //��������,WP=1,д����
}

/********************************************************************
* ����   : DS1302_Get_Time(structTime *pTime)
* ����   : ��ȡDS1302��ǰʱ��
* ����   : pTime: ���浱ǰʱ���ַ����ǰʱ���ʽΪ: �� �� ʱ �� �� ���� ��
*                                         7Byte (BCD��) 1B 1B 1B 1B 1B  1B  1B
* ����ֵ : ��
***********************************************************************/
void DS1302_Get_Time(structTime *pTime)
{
	//uchar i;
	//uchar ucAddr = 0x81;
	/*for(i=0; i<7; i++)
	{
		pTime[i] = DS1302_Read_Data(ucAddr);    //��ʽΪ: �� �� ʱ �� �� ���� ��
		ucAddr += 2;
	}*/
	DS1302_Write_Data(0x8f, 0);
	pTime->second = BCD_To_DEC(DS1302_Read_Data(0x81));
	DS1302_Write_Data(0x8f, 0);
	pTime->minute = BCD_To_DEC(DS1302_Read_Data(0x83));
	DS1302_Write_Data(0x8f, 0);
	pTime->hour = BCD_To_DEC(DS1302_Read_Data(0x85));
	DS1302_Write_Data(0x8f, 0);
	pTime->day = BCD_To_DEC(DS1302_Read_Data(0x87));
	DS1302_Write_Data(0x8f, 0);
	pTime->month = BCD_To_DEC(DS1302_Read_Data(0x89));
	DS1302_Write_Data(0x8f, 0);
	pTime->week = BCD_To_DEC(DS1302_Read_Data(0x8b));
	DS1302_Write_Data(0x8f, 0);
	pTime->year = BCD_To_DEC(DS1302_Read_Data(0x8d));
}

