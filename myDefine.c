/*	文件名：myDefine.c
	功能：实现公用相关函数
	作者：雷力
	时间：2011-01-10
	需要注意的问题：延时函数应根据具体环境做相应的调整
*/
#include "myDefine.h"
#include "INTRINS.H"
/********************************************************************
* 名称 : delay_1ms()
* 功能 : 延时子程序，延时时间为 1ms * i
* 输入 : i (延时一毫秒的个数)
* 输出 : 无
***********************************************************************/
void delay_1ms(uint i)//1*i ms延时
{
	uchar x,j;
	for(j=0;j<i;j++)
	for(x=0;x<=148;x++);	
}
/********************************************************************
* 名称 : void delay_1us() 
* 功能 : 延时1*m us
* 输入 : m (延时一微秒的个数)
* 输出 : 无
***********************************************************************/
/*void delay_1us(uint m)            //延时程序
 {
	unsigned int i,j;
	for(i=0;i<m;i++)
		for(j=0;j<10;j++);
 }*/

/********************************************************************
* 名称 : delay_little()
* 功能 : 延时函数
* 输入 : 无
* 输出 : 无
***********************************************************************/
/*void delay_little(uint N)
{
	int i;
	for(i=0; i<N; i++)
	;
}*/

/**************************************
延时X微秒(STC12C5A60S2@12M)
不同的工作环境,需要调整此函数
此延时函数是使用1T的指令周期进行计算,与传统的12T的MCU不同
**************************************/
void DelayXus(uchar n)
{
    while (n--)
    {
        _nop_();
        _nop_();
    }
}
/********************************************************************
* 名称 : DEC_To_BCD(uchar decimal)
* 功能 : DEC码转换为BCD码
* 输入 : dec码
* 输出 : bcd码
***********************************************************************/
uchar DEC_To_BCD(uchar decimal)
{
	uchar bcd;
	bcd = 0;
	while(decimal >= 10)
	{              
		decimal -= 10;                         
		bcd++;
	} 
	bcd <<= 4;
	bcd |= decimal;
	return bcd;
}


/********************************************************************
* 名称 : BCD_To_DEC(uchar bcd)
* 功能 : BCD码转换为DEC码
* 输入 : bcd码
* 输出 : dec码
***********************************************************************/
uchar BCD_To_DEC(uchar bcd)
{
	uchar data1;
	data1 = bcd & 0x0f;     //取BCD低4位
	bcd = bcd & 0x70;       //剔除BCD的最高位和低4位。
	data1 += bcd >> 1;
	data1 += bcd >> 3;      //用位移代替乘法运算
	return data1;
}
