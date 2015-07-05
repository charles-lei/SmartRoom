/*	�ļ�����myDefine.h
	���ܣ�����������غ���
	���ߣ�����
	ʱ�䣺2011-01-10
	��Ҫע������⣺1.���Ӧ������ʵ�ʻ����Ķ���Ӧ�Ķ˿�
					2.������Գɹ�Ӧ��ȥ�������е������������Եĺ꿪��
*/

/*******************************�ļ��޸ļ�¼(S)***********************************/
/*1.�������õ��Ķ˿ڷŵ����ļ��У����ڼ��й���
/*�޸�ǰ:
/*�޸�Ϊ:
/*����:2011-03-01
/*�޸���:����
/********************************�ļ��޸ļ�¼(E)**********************************/
#if !defined _MY_DEFINE_
#define _MY_DEFINE_
#include "STC12C5AXXXX.h"

#define true 1
#define false 0
#define uchar unsigned char
#define uint unsigned int
#define _DEBUG_ 1
#define _TEMP_DEBUG 0
#define _TIME_DEBUG 0
#define _LED_DEBUG 1
#define _AD_DEBUG 0

//��������λ�¶Ƚ���
#define TEMP_ZERO 20  //30������
#define TEMP_FIRST 25	//30~35
#define TEMP_SECOND 27	//35~60
#define TEMP_RING 29	//�����¶�
#define TEMP_LASTTIME 400  // �����¶ȳ���ʱ��:400*�ж�1ִ��һ������ʱ��

//�����״̬�ı�Ĺ�ǿ�Ƚ���
#define LIGHT_XXXX 1000//AD��ֵ��ҪӲ���������
#define LIGHT_LASTTIME 400  // �����ǿ�ȳ���ʱ��:400*�ж�1ִ��һ������ʱ��

//����ADת��ͨ��
#define AD_CHANNEL 1

//PWM�������
sbit PWM = P1^4;

//��״̬�ı�����
sbit LIGHT = P1^3;

//1602��ռ�˿�
sbit E = P2^4;		//1602ʹ������
sbit RW = P2^3;		//1602��д����	
sbit RS = P2^2;		//1602����/����ѡ������
#define LED_DATA P0 //P0Ϊ���ݿ�

//DS18B20ռ�ö˿�
sbit DQ = P2^0 ;//DS18b20_DQ;           //DS18B20���ݿ�

//DS1302ռ�ö˿�
sbit ACC0 = ACC^0;
sbit ACC7 = ACC^7;
sbit T_CLK = P1^2; //ʵʱʱ��ʱ��������
sbit T_IO = P3^4; //ʵʱʱ������������
sbit T_RST = P1^1; //ʵʱʱ�Ӹ�λ������ 

//������
sbit KEY_CONTROL = P1^5;
sbit KEY_ADD = P1^6;
sbit KEY_SUB = P1^7;

//���ú���
void delay_1ms(uint i);//1ms��ʱ
//void delay_little(uint N);
uchar DEC_To_BCD(uchar decimal);
uchar BCD_To_DEC(uchar bcd);
//void delay_1us(uint m);
void DelayXus(uchar n);


#endif