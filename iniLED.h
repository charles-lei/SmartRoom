
/*	�ļ�����iniLED.h
	���ܣ�����Һ��12864����غ������ܣ���Ҫ������ʼ������ʾ��
	���ߣ�����
	ʱ�䣺2011-01-10
	��Ҫע������⣺
*/


/*******************************�ļ��޸ļ�¼(S)***********************************/
/*1.
/*�޸�ǰ:
/*�޸�Ϊ:
/*���ڣ
/*�޸���:
/********************************�ļ��޸ļ�¼(E)**********************************/
#if !defined _INILED_H_
#define _INILED_H_

#include "STC12C5AXXXX.h"
#include "myDefine.h"

//12864��ռ�˿�
/*sbit RS  = P2^5;
sbit WRD = P2^6;
sbit E   = P2^7;
sbit PSB = P2^2;
sbit RES = P2^4;*/

//1602��ռ�˿�
//���������Ųο�����
/*sbit E = P2^7;		//1602ʹ������
sbit RW = P2^6;		//1602��д����	
sbit RS = P2^5;		//1602����/����ѡ������
*/
void ini_LED(); //��ʼ��Һ��

//void LED12864_Ini_Char_Lib(void);				//��ʼ���ֿ�

//void LED12864_Ini_Graphic_Lib(void);           //LCD��ʾͼƬ(��չ)��ʼ������

//void LED12864_Transfer_Data(char data1,bit DI);  //�������ݻ�������,��DI=0��,��������,��DI=1,��������.

//void LED12864_Display_Char(uchar code *address);//��ʾ����

//void LED12864_Display_Graphic(uchar code *address);//��ʾͼ��

//uchar LED1602_Convert(uchar In_Date);

void LED1602_Enable(uchar del);

void LED1602_Write(uchar del);

void LED1602_Ini(void);

void LED1602_Char(uchar hang,uchar lie,char sign);

void LED1602_String(uchar hang,uchar lie,uchar *p);


#endif