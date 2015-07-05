/*	�ļ�����iniFrame.c
	���ܣ����������
	���ߣ�����
	ʱ�䣺2011-12-20
	��Ҫע������⣺ע�����ģʽ�ĺ궨�忪��,����ṹ�����һ���Ż�������������߼���
*/
#include "mainFrame.h"
#include "iniLED.h"
#include "iniTemperatureSensor.h"
#include "iniTimeControl.h"
#include "iniInterrupt.h"
#include "myDefine.h"
#include "STC12C5AXXXX.h"
#include "iniAD.h"
#include "iniKey.h"

//�����ⲿ����ȫ��������iniIterrupt.c��
extern unsigned int curTemp;
extern structTime currentTime;
extern uchar ledFlag1;
extern uchar ledFlag;
extern uchar ringFlag;
extern float curAD;


/***********************************************�����ķָ���*********************************************/
void main()
{
	iniAllHardware();	//��ʼ�����в���
	run();
}
/***********************************************�����ķָ���*********************************************/
void iniAllHardware()
{
	//����ADʱ��Ҫ���˿��ش�
	#if _AD_DEBUG
	ini_AD();
	#endif

	ini_LED();
	ini_Temperature_Sensor();
	ini_Time_Control();
	ini_Interrupt();
}
/***********************************************�����ķָ���*********************************************/
void run()
{
 	while(true)
	{
		//��ȡ����ʱ�ر������ж�
		EA = 0;
		DS1302_Get_Time(&currentTime);
		DS18B20_Read_Temperature(&curTemp);

		#if _AD_DEBUG
		curAD = AD_Average(AD_CHANNAL);
		#endif
		EA = 1;
		
		//Һ����ʾ��ʱ�䡢�¶ȣ�
		if(ledFlag1)//������־
		{	
			if(1==ledFlag)
			{
				ledFlag = 0;
				ringFlag = 1;//�˴���������
				LED1602_Enable(0x01);//����
				delay_1ms(50);
				LED1602_String(1,1,"THIS IS TOO HOT!");
			}
			LED1602_Char(2,7,curTemp /10 % 10 + 48);
			LED1602_Char(2,8,curTemp % 10 + 48);
		}
		else
		{		
			if(0==ledFlag)
			{
				ringFlag = 0;
				ledFlag = 1;
				LED1602_Enable(0x01);//����
				delay_1ms(50);
			}
			LED1602_Flash();//�������������iniInterrupt.c��;		
		} 
		onKey();//��ȡ��������
	 }	
}