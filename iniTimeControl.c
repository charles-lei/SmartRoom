
/*	文件名：iniTimeControl.c
	功能：实现时间控制器DS1302相关函数（主要实现读取时间）
	作者：雷力
	创建日期：2011-01-11
	作成日期：2011-01-11
	需要注意的问题：注意管脚与单片机的具体连接端口的对应（已解决）
*/


/*******************************文件修改记录(S)***********************************/
/*1.
/*修改前:
/*修改为:
/*日期:
/*修改者:
/********************************文件修改记录(E)**********************************/
#include "iniTimeControl.h"
#include "STC12C5AXXXX.h"
#include "myDefine.h"
#include <intrins.h>
/********************************************************************
* 名称 : Write_DS1302Init()
* 功能 : 往DS1302中写入数据。最开始显示的数据就是在这里设置的。
* 输入 : 无
* 输出 : 无
***********************************************************************/
void ini_Time_Control()
{
/*	DS1302_Write_Data(0x8e,0);
	DS1302_Write_Data(0x80,0x50);	//写入秒
	DS1302_Write_Data(0x8e,0);
	DS1302_Write_Data(0x82,0x59);	//写入分
	DS1302_Write_Data(0x8e,0);
	DS1302_Write_Data(0x84,0x07);	//写入小时
	DS1302_Write_Data(0x8e,0);
	DS1302_Write_Data(0x86,0x08);	//写入日
	DS1302_Write_Data(0x8e,0);
	DS1302_Write_Data(0x88,0x08);	//写入月
	DS1302_Write_Data(0x8e,0);
	DS1302_Write_Data(0x8a,0x05);	//写入星期
	DS1302_Write_Data(0x8e,0);
	DS1302_Write_Data(0x8c,0x08);	//写入年	
*/  
    structTime iniDefaultTime = {11,1,1,23,99,50,5};
	DS1302_Set_Time(&iniDefaultTime);
}

/********************************************************************
* 名称 :  DS1302_Write_Byte（）
* 功能 :  往DS1302写入1Byte数据
* 输入 :  byteValue 写入的数据
* 输出 :  无
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
* 名称  :   DS1302_Read_Byte(void)
* 功能  :   从DS1302读取1Byte数据
* 输入  :	无
* 返回值:   ACC
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
* 名称   :   DS1302_Write_Data(uchar dataAddress, uchar dataValue)
* 功能   :   往DS1302写入数据
* 输入   :   dataAddress: DS1302地址, dataValue: 要写的数据
* 返回值 :   无
***********************************************************************/
void DS1302_Write_Data(uchar dataAddress, uchar dataValue)
{
	T_CLK = 0;
	T_RST = 1;
	DS1302_Write_Byte(dataAddress);   // 写地址 
	_nop_();
	_nop_();
	DS1302_Write_Byte(dataValue);     // 写1Byte数据
	T_CLK = 1;
	T_RST = 0;
}

/********************************************************************
* 名称   :  DS1302_Read_Data(uchar dataAddress)
* 功能   :  读取DS1302某地址的数据
* 输入   :  dataAddress: DS1302地址
* 返回值 :  ucDa :读取的数据
***********************************************************************/
uchar DS1302_Read_Data(uchar dataAddress)
{
	uchar ucDa;
	T_RST = 0;
	T_CLK = 0;
	T_RST = 1;
	DS1302_Write_Byte(dataAddress);    //写地址，命令
	_nop_();
	_nop_();
	ucDa = DS1302_Read_Byte(); //读1Byte数据
	T_CLK = 1;
	T_RST = 0;
	return(ucDa);
}

/********************************************************************
* 名称   :  DS1302_Write_Time(uchar *pTime)
* 功能   :  往DS1302写入时钟数据(多字节方式)
* 输入   :  pTime: 时钟数据地址 格式为: 秒 分 时 日 月 星期 年 控制
* 						   8Byte (BCD码) 1B 1B 1B 1B 1B 1B  1B  1B
* 返回值 :  无
***********************************************************************/
/*void DS1302_Write_Time(uchar *pTime)
{
	uchar i;
	DS1302_Write_Data(0x8e, 0x00);          //控制命令,WP=0,写操作
	T_RST = 0;
	T_CLK = 0;
	T_RST = 1;
	DS1302_Write_Byte(0xbe);          //0xbe:时钟多字节写命令
	for(i=8; i>0; i--)            //8Byte = 7Byte 时钟数据 + 1Byte 控制
	{
		DS1302_Write_Byte(*pTime);   //写1Byte数据
		pTime++;
	}
	T_CLK = 1;
	T_RST = 0;
}*/

/********************************************************************
* 名称   :  DS1302_Read_Time(uchar *pTime)
* 功能   :  读取DS1302时钟数据
* 输入   :  pSecDa: 时钟数据地址 格式为: 秒 分 时 日 月 星期 年
* 					       7Byte (BCD码) 1B 1B 1B 1B 1B 1B   1B
* 返回值 :  ucDa :读取的数据
***********************************************************************/
/*void DS1302_Read_Time(uchar *pTime)
{
	uchar i;
	T_RST = 0;
	T_CLK = 0;
	T_RST = 1;
	DS1302_Write_Byte(0xbf);               //0xbf:时钟多字节读命令
	for(i=8; i>0; i--)
	{
		*pTime = DS1302_Read_Byte();   //读1Byte数据
		pTime++;
	}
	T_CLK = 1;
	T_RST = 0;
}*/

/********************************************************************
* 名称   :  DS1302_Write_Register(uchar *pRegister)
* 功能   :  往DS1302寄存器数写入数据(多字节方式)
* 输入   :  pReDa: 寄存器数据地址
* 返回值 :  无
***********************************************************************/
/*void DS1302_Write_Register(uchar *pRegister)
{
	
	uchar i;
	DS1302_Write_Data(0x8e,0x00);         //控制命令,WP=0,写操作
	T_RST = 0;
	T_CLK = 0;
	T_RST = 1;
	DS1302_Write_Byte(0xfe);       //0xbe:时钟多字节写命令
	for(i=31; i>0; i--)        //31Byte 寄存器数据
	{
		DS1302_Write_Byte(*pRegister); //写1Byte数据
		pRegister++;
	}
	T_CLK = 1;
	T_RST = 0;
}*/


/********************************************************************
* 名称   :  DS1302_Read_Register(uchar *pRegister)
* 功能   :  读取DS1302寄存器数据
* 输入   :  pRegister: 寄存器数据地址
* 返回值 :  无
***********************************************************************/
/*void DS1302_Read_Register(uchar *pRegister)
{
	uchar i;
	T_RST = 0;
	T_CLK = 0;
	T_RST = 1;
	DS1302_Write_Byte(0xff);            //0xbf:时钟多字节读命令
	for(i=31; i>0; i--)             //31Byte 寄存器数据
	{
		*pRegister = DS1302_Read_Byte(); //读1Byte数据
		pRegister++;
	}
	T_CLK = 1;
	T_RST = 0;
}*/

/********************************************************************
* 名称  :  DS1302_Set_Time(uchar *pTime)
* 功能  :  设置初始时间
* 输入  :  pTime: 初始时间地址。初始时间格式为: 秒 分 时 日 月 星期 年
* 								   7Byte (BCD码) 1B 1B 1B 1B 1B 1B  1B
* 返回值: 无
***********************************************************************/
void DS1302_Set_Time(structTime *pTime)
{
	//uchar i;
	uchar ucAddr = 0x80;
	DS1302_Write_Data(0x8e, 0x00);            //控制命令,WP=0,写操作
	DS1302_Write_Data(ucAddr,DEC_To_BCD(pTime->second));
	DS1302_Write_Data(ucAddr+2,DEC_To_BCD(pTime->minute));
	DS1302_Write_Data(ucAddr+4,DEC_To_BCD(pTime->hour));
	DS1302_Write_Data(ucAddr+6,DEC_To_BCD(pTime->day));
	DS1302_Write_Data(ucAddr+8,DEC_To_BCD(pTime->month));
	DS1302_Write_Data(ucAddr+10,DEC_To_BCD(pTime->week));
	DS1302_Write_Data(ucAddr+12,DEC_To_BCD(pTime->year));
	//for(i=7; i>0; i--)
	//{
	//	DS1302_Write_Data(ucAddr, *pTime);   // 秒 分 时 日 月 星期 年
	//	pTime++;
	//	ucAddr += 2;
	//}
	DS1302_Write_Data(0x8e, 0x80);            //控制命令,WP=1,写保护
}

/********************************************************************
* 名称   : DS1302_Get_Time(structTime *pTime)
* 功能   : 读取DS1302当前时间
* 输入   : pTime: 保存当前时间地址。当前时间格式为: 秒 分 时 日 月 星期 年
*                                         7Byte (BCD码) 1B 1B 1B 1B 1B  1B  1B
* 返回值 : 无
***********************************************************************/
void DS1302_Get_Time(structTime *pTime)
{
	//uchar i;
	//uchar ucAddr = 0x81;
	/*for(i=0; i<7; i++)
	{
		pTime[i] = DS1302_Read_Data(ucAddr);    //格式为: 秒 分 时 日 月 星期 年
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

