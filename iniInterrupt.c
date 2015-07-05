/*	�ļ�����iniInterrupt.c
	���ܣ�ʵ���жϹ��ܣ���ҪΪ�¶Ȳɼ��͹�ǿ�Ȳɼ���
	���ߣ�����
	�������ڣ�2011-01-19
	�������ڣ�2011-01-30
	��Ҫע������⣺
*/

/**************************************************�ļ��޸ļ�¼(S)**********************************************/
/*1.��װ�ж�1�е�Һ����ʾ����
/*�޸�ǰ:�ж��еľֲ������ı�Ϊȫ�ֱ���
/*�޸�Ϊ:
/*����:2011-02-18
/*�޸���:����
/****************************************************************************************************************
/*2.�ж�1�д�����Ż���ʹ�ж�ִ��ʱ�価���ܵĶ�
/*�޸�ǰ:�����������¶Ȳɼ�������ʱ���ȡ������Һ��ˢ�º��������ж���������ִ��
/*�޸�Ϊ:����������Ϊȫ�ֵģ��жϸ�������״̬�ı�ı�־���ڳ�����ѭ�������¶Ȳɼ���ʱ���ȡ��Һ��ˢ�µȲ���
/*����:2011-03-01
/*�޸���:����
/**************************************************�ļ��޸ļ�¼(E)**********************************************/
#include "iniInterrupt.h"
#include "STC12C5AXXXX.h"
#include "myDefine.h"
#include "iniTimeControl.h"
#include "iniLED.h"
#include "iniTemperatureSensor.h"
#include "iniBeem.h"
#include "iniKey.h"

//ȫ�ֵ�(�����Ѷ�Ϊ֮)���������ж���
extern KCS KeyControlState;//ö�����ͣ���ʾ�����Ŀ���״̬
unsigned int preTemp = 0;  //��¼��һ�ζ�ȡ���¶�
unsigned int curTemp = 0;	//��¼��ǰ�¶�
unsigned int countTemp = 0;	//���ڼ���ĳ���¶ȶγ���ʱ��
structTime currentTime;		//��¼��ǰʱ��
uchar PWM_ON = 10 ;//����ߵ�ƽʱ��		
uchar ringFlag = 0;	//������־	
uchar ledFlag = 0;//Ϊ��LED����˸����˱�־ 
uchar ledFlag1 = 0;//��ѭ�����ݴ˱�־����������Һ����ʾ����
uchar tempFlag = 0;//�ﵽһ������ʱ���ı�һ�ε��״̬
uchar ledFlashCount = 0; //����ʱ��ʱled��˸ʱ������ledFlashCount*50ms

float curAD = 0.0;
float preAD = 0.0;
unsigned int countAD = 0;
uchar adFlag = 0;//�ﵽһ������ʱ���ı�һ�ε�״̬


void ini_Interrupt()
{
	delay_1ms(100);
	ini_Timer0();
	ini_Timer1();	
}


void ini_Timer0()
{
	TMOD = 0x01;			//��ʱ/������ģʽ���ƼĴ���
	IE 	 = 0x82;		//�ж�ʹ�ܼĴ���

	TH0  = 0xfc;			//1ms,11.0592MHZ
	TL0  = 0x66;	        
	IP = 0x02;
	TR0 = 1;			//��ʱ/���������ƼĴ���TCON��TR0λ 1�����������0��0��ֹͣ��
}		

void ini_Timer1()
{
	TMOD |= 0x10;			//��ʱ/������ģʽ���ƼĴ���
	IE 	 |= 0x88;		//�ж�ʹ�ܼĴ���

	TH1  = 0x4c;			//50ms,11.0592MHZ
	TL1  = 0x00;	        
	TR1 = 1;			//��ʱ/���������ƼĴ���TCON��TR1λ 1�����������1��0��ֹͣ��
}


/********************************************************************
* ���� : Timer1() interrupt 3
* ���� : �ö�ʱ��1 ��ʱ50MS���ڵ������״̬�ĸı�
* ���� : ��
* ��� : ��
***********************************************************************/
void Timer1() interrupt 3 	//11.092MHZ 50MS
{	
 	TH1  = 0x4c;			//������0��8λ
	TL1  = 0x00;	        //������0��8λ   
			//��ȡ����ʱ�ر������ж�


	ledFlashCount++;
	if(20 == ledFlashCount) ledFlashCount = 0;


	//����ĳ���¶ȶεĳ���ʱ��,��countTemp������ʾ,ÿ��һ��ʾ�Ӵ��ж�ִ��һ������ʱ��
	/****************************���㿪ʼ**************************************/
	if(0 == countTemp)
	{	
		tempFlag = 0; 
		countTemp++;
		preTemp = curTemp;
	}
	else
	{
		if(curTemp < TEMP_ZERO && preTemp < TEMP_ZERO 
			|| curTemp >= TEMP_ZERO && curTemp < TEMP_FIRST && preTemp >= TEMP_ZERO && preTemp < TEMP_FIRST 
			|| curTemp >= TEMP_FIRST && curTemp < TEMP_RING && preTemp >= TEMP_FIRST && preTemp < TEMP_RING 
			|| curTemp >= TEMP_RING && preTemp >= TEMP_RING)
		{
			countTemp++;
			preTemp = curTemp;
		}
		else countTemp = 0;
		if(countTemp > TEMP_LASTTIME) 
		{
			countTemp = TEMP_LASTTIME;
			tempFlag = 1;
		}
	}
	/*****************************�������*************************************/
	
	//�ı���״̬
	if(countTemp == TEMP_LASTTIME && tempFlag != 1) //����ԼLASTIME*50ms,tempFlag��־��ʾ�ճ�����LASTTIME*50msʱֻ�ı���һ�ε��״̬
	{
		if(curTemp < TEMP_ZERO)
		{
			//ֹͣ����ת��
			PWM_ON = 10;	
		}
		else if(curTemp >= TEMP_ZERO && curTemp < TEMP_FIRST)
		{
			//һ��PWM
			PWM_ON = 1;	
		}
		else if(curTemp >= TEMP_FIRST && curTemp < TEMP_RING)
		{
			//����PWM
			PWM_ON = 0;
		}
		else
		{
		 	PWM_ON = 10;
		}
	}

	//���ﱨ����������
	if(curTemp >= TEMP_RING && countTemp == TEMP_LASTTIME)
	{	
		ledFlag1 = 1;	//������־,�������ж�������Ӧ�Ĳ�����Һ����ʾ��ˢ��,����)
	}
	else
	{
		ledFlag1 = 0;	
	} 
	
	//ADģ����Դ���
	#if _AD_DEBUG


	//����ĳ�����նȶεĳ���ʱ��,��countAD������ʾ,ÿ��һ��ʾ�Ӵ��ж�ִ��һ������ʱ��
	/****************************���㿪ʼ**************************************/
	if(0 == countAD)
	{	
		adFlag = 0; 
		countAD++;
		preAD = curAD;
	}
	else
	{
		if(curAD <= LIGHT_XXXX && preAD < LIGHT_XXXX
			 || curAD >= LIGHT_XXXX && preAD >= LIGHT_XXXX)//LIGHT_XXXXΪ��ǿ����ֵ������ȷ����״̬�ı���ٽ��
		{
			countAD++;
			preAD = AD;
		}
		else countAD = 0;
		if(countAD > LIGHT_LASTTIME) 
		{
			countTemp = LIGHT_LASTTIME;
			adFlag = 1;
		}
	}
	/*****************************�������*************************************/
	
	//�ı��״̬
	if(countAD == LIGHT_LASTTIME && adFlag != 1) //����ԼLASTIME*50ms,adFlag��־��ʾ�ճ�����LASTTIME*50msʱֻ�ı���һ��״̬
	{
		if(curAD <= LIGHT_XXXX)
		{
			//����
			LIGHT = 1;	
		}
		else
		{
			//����
			LIGHT = 0;	
		}
	}

	#endif
}

/********************************************************************
* ���� : Timer1() interrupt 3
* ���� : �ö�ʱ��0 ��ʱ1MS���ڲ���PWM
* ���� : ��
* ��� : ��
***********************************************************************/
void Timer0() interrupt 1	//11.092MHZ 1MS
{
	static uchar c = 0;
 	TH0  = 0xfc;			//������0��8λ
	TL0  = 0x66;	
	if (c==PWM_ON)
    {
    	PWM = 1; 
    }
  	c++;
	if(c == CYCLE)
    {
   		c = 0;
		if(PWM_ON != 0) //�������ʱ����0 ����ԭ��״̬
	   		PWM = 0;
    }
	if(1==ringFlag) ring();	
}

/********************************************************************
* ���� : L1602_Flash()
* ���� : ˢ��LED1602��ʾ
* ���� : ��
* ��� : ��
***********************************************************************/
void LED1602_Flash()
{
	if(KeyControlState == HOUR_FLASH)
	{
		if(ledFlashCount <= 10)
		{
			LED1602_Char(2, 6, currentTime.hour / 10 % 10 + 48);
			LED1602_Char(2, 7, currentTime.hour % 10 + 48);
		}
		else
		{
 			LED1602_Char(2, 6,' ');
			LED1602_Char(2, 7,' ');
		}

	}
	else 
	{
		LED1602_Char(2, 6, currentTime.hour / 10 % 10 + 48);
		LED1602_Char(2, 7, currentTime.hour % 10 + 48);
	}
	if(KeyControlState == MINUTE_FLASH)
	{
		if(ledFlashCount <= 10)
		{
			LED1602_Char(2, 9, currentTime.minute / 10 % 10 + 48);
			LED1602_Char(2, 10, currentTime.minute % 10 + 48);
		}
		else
		{
 			LED1602_Char(2, 9,' ');
			LED1602_Char(2, 10,' ');
		}

	}
	else 
	{
		LED1602_Char(2, 9, currentTime.minute / 10 % 10 + 48);
		LED1602_Char(2, 10, currentTime.minute % 10 + 48);
	}

	if(KeyControlState == YEAR_FLASH)
	{
		if(ledFlashCount <= 10)
		{
			LED1602_Char(1, 8, currentTime.year / 10 % 10 + 48);
			LED1602_Char(1, 9, currentTime.year % 10 + 48);
		}
		else
		{
 			LED1602_Char(1, 8,' ');
			LED1602_Char(1, 9,' ');
		}

	}
	else 
	{
		LED1602_Char(1, 8, currentTime.year / 10 % 10 + 48);
		LED1602_Char(1, 9, currentTime.year % 10 + 48);
	}

	if(KeyControlState == MONTH_FLASH)
	{
		if(ledFlashCount <= 10)
		{
			LED1602_Char(1, 11, currentTime.month / 10 % 10 + 48);
			LED1602_Char(1, 12, currentTime.month % 10 + 48);
		}
		else
		{
 			LED1602_Char(1, 11,' ');
			LED1602_Char(1, 12,' ');
		}

	}
	else 
	{
		LED1602_Char(1, 11, currentTime.month / 10 % 10 + 48);
		LED1602_Char(1, 12, currentTime.month % 10 + 48);
	}
	if(KeyControlState == DAY_FLASH)
	{
		if(ledFlashCount <= 10)
		{
			LED1602_Char(1, 14, currentTime.day / 10 % 10 + 48);
			LED1602_Char(1, 15, currentTime.day % 10 + 48);
		}
		else
		{
 			LED1602_Char(1, 14,' ');
			LED1602_Char(1, 15,' ');
		}

	}
	else 
	{
		LED1602_Char(1, 14, currentTime.day / 10 % 10 + 48);
		LED1602_Char(1, 15, currentTime.day % 10 + 48);
	}
	LED1602_Char(2, 8, '-');
	LED1602_Char(2, 11, '-');
	LED1602_Char(2, 12, currentTime.second / 10 % 10 + 48);
	LED1602_Char(2, 13, currentTime.second % 10 + 48);
	LED1602_Char(1, 6, '2');
	LED1602_Char(1, 7, '0');
	LED1602_Char(1, 10, '-');
	LED1602_Char(1, 13, '-');;
	LED1602_Char(2, 15, curTemp /10 % 10 + 48);
	LED1602_Char(2, 16, curTemp % 10 + 48);			
}
