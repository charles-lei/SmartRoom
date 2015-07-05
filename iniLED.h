
/*	ÎÄ¼şÃû£ºiniLED.h
	¹¦ÄÜ£ºÉùÃ÷Òº¾§12864µÄÏà¹Øº¯Êı¹¦ÄÜ£¨Ö÷Òª°üÀ¨³õÊ¼»¯ºÍÏÔÊ¾£©
	×÷Õß£ºÀ×Á¦
	Ê±¼ä£º2011-01-10
	ĞèÒª×¢ÒâµÄÎÊÌâ£º
*/


/*******************************ÎÄ¼şĞŞ¸Ä¼ÇÂ¼(S)***********************************/
/*1.
/*ĞŞ¸ÄÇ°:
/*ĞŞ¸ÄÎª:
/*ÈÕÆÚ£
/*ĞŞ¸ÄÕß:
/********************************ÎÄ¼şĞŞ¸Ä¼ÇÂ¼(E)**********************************/
#if !defined _INILED_H_
#define _INILED_H_

#include "STC12C5AXXXX.h"
#include "myDefine.h"

//12864ËùÕ¼¶Ë¿Ú
/*sbit RS  = P2^5;
sbit WRD = P2^6;
sbit E   = P2^7;
sbit PSB = P2^2;
sbit RES = P2^4;*/

//1602ËùÕ¼¶Ë¿Ú
//ÕâÈı¸öÒı½Å²Î¿¼×ÊÁÏ
/*sbit E = P2^7;		//1602Ê¹ÄÜÒı½Å
sbit RW = P2^6;		//1602¶ÁĞ´Òı½Å	
sbit RS = P2^5;		//1602Êı¾İ/ÃüÁîÑ¡ÔñÒı½Å
*/
void ini_LED(); //³õÊ¼»¯Òº¾§

//void LED12864_Ini_Char_Lib(void);				//³õÊ¼»¯×Ö¿â

//void LED12864_Ini_Graphic_Lib(void);           //LCDÏÔÊ¾Í¼Æ¬(À©Õ¹)³õÊ¼»¯³ÌĞò

//void LED12864_Transfer_Data(char data1,bit DI);  //´«ËÍÊı¾İ»òÕßÃüÁî,µ±DI=0ÊÇ,´«ËÍÃüÁî,µ±DI=1,´«ËÍÊı¾İ.

//void LED12864_Display_Char(uchar code *address);//ÏÔÊ¾ºº×Ö

//void LED12864_Display_Graphic(uchar code *address);//ÏÔÊ¾Í¼ĞÎ

//uchar LED1602_Convert(uchar In_Date);

void LED1602_Enable(uchar del);

void LED1602_Write(uchar del);

void LED1602_Ini(void);

void LED1602_Char(uchar hang,uchar lie,char sign);

void LED1602_String(uchar hang,uchar lie,uchar *p);


#endif