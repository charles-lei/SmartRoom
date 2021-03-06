
/*	文件名：iniLED.c
	功能：实现液晶12864的相关函数功能（主要包括初始化和显示）
	作者：雷力
	创建日期：2011-01-10
	作成日期：2011-01-17
	需要注意的问题： LED12864_Transfer_Data()数据口的设置,LED1602_Write(),LED1602_Enable()
*/


/*******************************文件修改记录(S)***********************************/
/*1.
/*修改前:
/*修改为:
/*日期�
/*修改者:
/********************************文件修改记录(E)**********************************/
#include "iniLED.h"
#include "myDefine.h"


/********************************************************************
* 名称 : ini_LED()
* 功能 : 初始化液晶
* 输入 : 无
* 输出 : 无
***********************************************************************/
void ini_LED()
{
	//LED12864_Ini_Char_Lib();
	//LED12864_Ini_Graphic_Lib();
	LED1602_Ini();
}

//以下是12864相关函数

/********************************************************************
* 名称 : LED12864_Ini_Char_Lib()
* 功能 : 初始化字符库
* 输入 : 无
* 输出 : 无
***********************************************************************/
/*
void LED12864_Ini_Char_Lib()
{
	delay_1ms(40);             //大于40MS的延时程序
	PSB = 1;                 //设置为8BIT并口工作模式
	delay_1ms(1);              //延时
	RES = 0;                 //复位
	delay_1ms(1);              //延时
	RES = 1;                 //复位置高
	delay_1ms(10);
	LED12864_Transfer_Data(0x30,0);  //Extended Function Set :8BIT设置,RE=0: basic instruction set, G=0 :graphic display OFF
	DelayXus(100);            //大于100uS的延时程序
	LED12864_Transfer_Data(0x30,0);  //Function Set
	DelayXus(37);             ////大于37uS的延时程序
	LED12864_Transfer_Data(0x08,0);  //Display on Control
	DelayXus(100);            //大于100uS的延时程序
	LED12864_Transfer_Data(0x10,0);  //Cursor Display Control光标设置
	DelayXus(100);            //大于100uS的延时程序
	LED12864_Transfer_Data(0x0C,0);  //Display Control,D=1,显示开
	DelayXus(100);            //大于100uS的延时程序
	LED12864_Transfer_Data(0x01,0);  //Display Clear
	DelayXus(100);             //大于100uS的延时程序
	LED12864_Transfer_Data(0x06,0);  //Enry Mode Set,光标从右向左加1位移动
	DelayXus(100);            //大于100uS的延时程序
}

*/
/********************************************************************
* 名称 : LED12864_Ini_Graphic_Lib()
* 功能 : 初始化图形库
* 输入 : 无
* 输出 : 无
***********************************************************************/
/*
void LED12864_Ini_Graphic_Lib()
{
	delay_1ms(40);             //大于40MS的延时程序
	PSB=1;                 //设置为8BIT并口工作模式
	delay_1ms(1);              //延时
	RES=0;                 //复位
	delay_1ms(1);              //延时
	RES=1;                 //复位置高
	DelayXus(10);	
	LED12864_Transfer_Data(0x36,0);  //Extended Function Set RE=1: extended instruction
	DelayXus(100);            //大于100uS的延时程序
	LED12864_Transfer_Data(0x36,0);  //Extended Function Set:RE=1: extended instruction set
	DelayXus(37);             ////大于37uS的延时程序
	LED12864_Transfer_Data(0x3E,0);  //EXFUNCTION(DL=8BITS,RE=1,G=1)
	DelayXus(100);            //大于100uS的延时程序
	LED12864_Transfer_Data(0x01,0);  //CLEAR SCREEN
    DelayXus(100);            //大于100uS的延时程序
}
*/
/********************************************************************
* 名称 : LED12864_Transfer_Data()
* 功能 : 显示字符
* 输入 : data1：向LED12864传送的数据或命令
* 输出 : 无
***********************************************************************/
/*
void LED12864_Transfer_Data(char data1,bit DI)  //传送数据或者命令,当DI=0是,传送命令,当DI=1,传送数据.
{
	//关于延迟世间，需要仔细阅读时序资料
	WRD=0;  //向LED写
	RS=DI;	//指令或数据
	DelayXus(1);
    P0=data1;                          //P0为12864与单片机的数据接口
	E=1;
	DelayXus(1);
	E=0;
 }
*/

/********************************************************************
* 名称 : LED12864_Display_Char()
* 功能 : 显示字符
* 输入 : address：字符数组首地址
* 输出 : 无
***********************************************************************/
/*
void LED12864_Display_Char(uchar code *address)
{
	uchar i;
	LED12864_Transfer_Data(0x80,0);  //Set Graphic Display RAM Address
	DelayXus(100);
	for(i=0;i<32;i++)
	{
		LED12864_Transfer_Data(*address,1);
		address++;
	}
	
	LED12864_Transfer_Data(0x90,0);  //Set Graphic Display RAM Address
	DelayXus(100);
	for(i=32;i<64;i++)
	{
		LED12864_Transfer_Data(*address,1);
		address++;
	}
}
*/
/********************************************************************
* 名称 : LED12864_Display_Graphic()
* 功能 : 显示字符
* 输入 : address：字符数组首地址
* 输出 : 无
***********************************************************************/
/*
void LED12864_Display_Graphic(uchar code *address)
{

   int i,j;
//*******显示上半屏内容设置
   for(i=0;i<32;i++)              //
    { 
      LED12864_Transfer_Data((0x80 + i),0); //SET  垂直地址 VERTICAL ADD
      LED12864_Transfer_Data(0x80,0);       //SET  水平地址 HORIZONTAL ADD
      for(j=0;j<16;j++)
       {
        LED12864_Transfer_Data(*address,1);
         address++;
       }
    }	   
//*******显示下半屏内容设置
   for(i=0;i<32;i++)              //
    {
      LED12864_Transfer_Data((0x80 + i),0); //SET 垂直地址 VERTICAL ADD
      LED12864_Transfer_Data(0x88,0);       //SET 水平地址 HORIZONTAL ADD
      for(j=0;j<16;j++)
       {
         LED12864_Transfer_Data(*address,1);
         address++;
       }
    }
}*/

//以下是1602相关函数
/********************************************************************
* 名称 : LED1602_Convert(uchar In_Date)
* 功能 : 因为电路设计时，P0.0--P0.7接法刚好了资料中的相反，所以设计该函数。
* 输入 : 1602资料上的值
* 输出 : 送到1602的值
***********************************************************************/
/*uchar LED1602_Convert(uchar In_Date)
{
    uchar i, Out_Date = 0, temp = 0;
    for(i=0; i<8; i++)
    {
        temp = (In_Date >> i) & 0x01;
        Out_Date |= (temp << (7 - i));
    }
    return Out_Date;
}*/

/********************************************************************
* 名称 : LED1602_Enable(uchar del)
* 功能 : 1602命令函数
* 输入 : 输入的命令值
* 输出 : 无
***********************************************************************/

void LED1602_Enable(uchar del)
{
	//LED_DATA = LED1602_Convert(del);
	LED_DATA = del;
	RS = 0;
	RW = 0;
	E = 0;
	DelayXus(1);
	E = 1;
	DelayXus(1);
}

/********************************************************************
* 名称 : uchar LED1602_read()
* 功能 : 1602读数据函数
* 输入 : 无
* 输出 : 无
***********************************************************************/
/*uchar LED1602_Read()
{
	uchar r;
	RS = 1;
	RW = 1;
	E = 1;
	r = P0;
	return r;
}*/


/********************************************************************
* 名称 : LED1602_Write(uchar del)
* 功能 : 1602写数据函数
* 输入 : 需要写入1602的数据
* 输出 : 无
***********************************************************************/
void LED1602_Write(uchar del)
{
//	LED_DATA = LED1602_Convert(del);
	LED_DATA = del;
	RS = 1;
	RW = 0;
	E = 0;
	DelayXus(1);
	E = 1;
	DelayXus(1);
}

/********************************************************************
* 名称 : LED1602_Ini(void)
* 功能 : 1602初始化，请参考1602的资料
* 输入 : 无
* 输出 : 无
***********************************************************************/
void LED1602_Ini(void)
{
	LED1602_Enable(0x01);
	LED1602_Enable(0x38);
	LED1602_Enable(0x0c);
	LED1602_Enable(0x06);
	LED1602_Enable(0xd0);
}

/********************************************************************
* 名称 : L1602_char(uchar hang,uchar lie,char sign)
* 功能 : 改变液晶中某位的值，如果要让第一行，第五个字符显示"b" ，调用该函数如下
		 L1602_char(1,5,'b')
* 输入 : 行，列，需要输入1602的数据
* 输出 : 无
***********************************************************************/
void LED1602_Char(uchar hang,uchar lie,char sign)
{
	uchar a;
	if(hang == 1) a = 0x80;
	if(hang == 2) a = 0xc0;
	a = a + lie - 1;
	LED1602_Enable(a);
	LED1602_Write(sign);
}

/********************************************************************
* 名称 : L1602_String(uchar hang,uchar lie,uchar *p)
* 功能 : 改变液晶中某位的值，如果要让第一行，第五个字符开始显示"ab cd ef" ，调用该函数如下
	 	 L1602_String(1,5,"ab cd ef;")
* 输入 : 行，列，需要输入1602的数据
* 输出 : 无
***********************************************************************/
void LED1602_String(uchar hang,uchar lie,uchar *p)
{
	uchar a;
	if(hang == 1) a = 0x80;
	if(hang == 2) a = 0xc0;
	a = a + lie - 1;
	LED1602_Enable(a);
	while(1)
	{
		if(*p == '\0') break;
		LED1602_Write(*p);
		p++;
	}
}



