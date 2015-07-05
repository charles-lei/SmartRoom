
/*	文件名：iniTemperatureSensor.c
	功能：实现温度传感器DS18B20相关函数（主要实现采集温度）
	作者：雷力
	创建日期：2011-01-11
	作成日期：2011-01-11
	需要注意的问题：注意DQ管脚与单片机的具体连接端口的对应
*/


/*******************************文件修改记录(S)***********************************/
/*1.将读取温度函数修改:
/*修改前:uchar DS18B20_Read_Temperature();
/*修改为:void DS18B20_Read_Temperature(uchar *pTemp);
/*日期：2011-02-05
/*修改者:雷力
/********************************文件修改记录(E)**********************************/
#include "iniTemperatureSensor.h"
#include "STC12C5AXXXX.h"
#include "myDefine.h"

void ini_Temperature_Sensor()
{
	DS18B20_Reset();
	DS18B20_Write_Byte(jump_ROM);
	DS18B20_Write_Byte(start);
	while (!DQ);                    //等待转换完成
	DS18B20_Reset();
	DS18B20_Write_Byte(jump_ROM);
	DS18B20_Write_Byte(read_EEROM);
}

/********************************************************************
* 名称 : DS18B20_Reset()
* 功能 : 复位DS18B20
* 输入 : 无
* 输出 : 无
***********************************************************************/
void DS18B20_Reset()
{
	CY = 1;
	while(CY)
	{
        DQ = 0;                     //送出低电平复位信号
        DelayXus(240);              //延时至少480us
        DelayXus(240);
        DQ = 1;                     //释放数据线
        DelayXus(60);               //等待60us
        CY = DQ;                    //检测存在脉冲
        DelayXus(240);              //等待设备释放数据线
        DelayXus(180);
	}
}

/********************************************************************
* 名称 : DS18B20_Read_Bit()
* 功能 : 从DS18B20读一个位值
* 输入 : 无
* 输出 : 从DS18B20读出的一个位值
***********************************************************************/
/*uchar DS18B20_Read_Bit(void)
{
	uchar i;
	DQ = 0;
	DQ = 1;
	for(i=0; i<3; i++);
	return(DQ);
}*/

/********************************************************************
* 名称 : DS18B20_Write_Bit()
* 功能 : 向DS18B20写一位
* 输入 : bitval（要对DS18B20写入的位值）
* 输出 : 无
***********************************************************************/
/*void DS18B20_Write_Bit(uchar bitValue)
{
	DQ=0;
	if(bitValue==1)
		DQ=1;
	delay_little(5);
	DQ=1;
}*/

/********************************************************************
* 名称 : DS18B20_Read_Byte()
* 功能 : 从DS18B20读一个字节
* 输入 : 无
* 输出 : 从DS18B20读到的值
***********************************************************************/
uchar DS18B20_Read_Byte(void)
{
   uchar i;
   uchar dat = 0;

    for (i=0; i<8; i++)             //8位计数器
    {
        dat >>= 1;
        DQ = 0;                     //开始时间片
        DelayXus(1);                //延时等待
        DQ = 1;                     //准备接收
        DelayXus(1);                //接收延时
        if (DQ) dat |= 0x80;        //读取数据
        DelayXus(60);               //等待时间片结束
    }
    return dat;
}

/********************************************************************
* 名称 : DS18B20_Write_Byte()
* 功能 : 向DS18B20写一个字节
* 输入 : ucharValue（要对DS18B20写入的命令值）
* 输出 : 无
***********************************************************************/
void DS18B20_Write_Byte(uchar byteValue)
{
 char i;

    for (i=0; i<8; i++)             //8位计数器
    {
        DQ = 0;                     //开始时间片
        DelayXus(1);                //延时等待
        byteValue >>= 1;                  //送出数据
        DQ = CY;
        DelayXus(60);               //等待时间片结束
        DQ = 1;                     //恢复数据线
        DelayXus(1);                //恢复延时
    }
}

/********************************************************************
* 名称 : DS18B20_Read_temperature(unsigned int *pTemp)
* 功能 : 读取温度
* 输入 : pTemp,指向温度
* 输出 : 十进制温度数值
***********************************************************************/
void DS18B20_Read_Temperature(unsigned int *pTemp)
{
    uchar TMPL = 0;
	uchar TMPH = 0;
   	ini_Temperature_Sensor();
    TMPL = DS18B20_Read_Byte();
	TMPH = DS18B20_Read_Byte();
	if(pTemp) *pTemp = TMPL / 16 + TMPH * 16;
}
