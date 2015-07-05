
/*	�ļ�����iniKey.h
	���ܣ���������������غ���
	���ߣ�����
	�������ڣ�2011-03-01
	�������ڣ�2011-03-04
	��Ҫע������⣺���������Щ���࣬�����ۣ����Է�װ�Ľ�
*/


/*******************************�ļ��޸ļ�¼(S)***********************************/
/*1.
/*�޸�ǰ:
/*�޸�Ϊ:
/*����?
/*�޸���:
/********************************�ļ��޸ļ�¼(E)**********************************/
#include "iniKey.h"
#include "myDefine.h"
//#include "iniInterrupt.h"
#include "iniTimeControl.h"
extern structTime currentTime;

KCS KeyControlState = NO_FLASH;//����״̬����

void onKey()
{
	if(0 == KEY_CONTROL)
	{
		delay_1ms(20);//��������
		if(0 == KEY_CONTROL)
		{
			//���ݵ�ǰ״̬�ı䵽��һ״̬
			switch(KeyControlState)
		 	{   
			case NO_FLASH:       
				KeyControlState = YEAR_FLASH;		
				break;
			case YEAR_FLASH:
				KeyControlState = MONTH_FLASH;
				break;
			case MONTH_FLASH:
				KeyControlState = DAY_FLASH;
				break;
			case DAY_FLASH:
				KeyControlState = HOUR_FLASH;
				break; 
			case HOUR_FLASH:
				KeyControlState = MINUTE_FLASH;
				break;
			case MINUTE_FLASH:
				KeyControlState = NO_FLASH;
				break;
			default: break;
			}
		}
		while(!KEY_CONTROL);
	}
	else if(0 == KEY_ADD)
	{
		delay_1ms(20);
		if(0 == KEY_ADD)
		{
			//���ݵ�ǰ״̬���м�1����
			switch(KeyControlState)
		 	{   
			case YEAR_FLASH:
				//KeyControlState = MONTH_FLASH;
				if(99 == currentTime.year) currentTime.year = 0;			
				else currentTime.year++;
				DS1302_Set_Time(&currentTime);
				break;
			case MONTH_FLASH:
				if(12 == currentTime.month) currentTime.month = 1;			
				else currentTime.month++;
				DS1302_Set_Time(&currentTime);
				break;
			case DAY_FLASH:
				switch(currentTime.month)
				{
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					if(31 == currentTime.day) currentTime.day = 1;
					else currentTime.day++;
					break;
				case 4:
				case 6:
				case 9:
				case 11:
					if(30 == currentTime.day) currentTime.day = 1;
					else currentTime.day++;
					break;
				case 2:		
					if(0 != currentTime.year%4)
					{
						if(28 == currentTime.day) currentTime.day = 1;
						else currentTime.day++;
						break;
					}
					else
					{
						if(29 == currentTime.day) currentTime.day = 1;
						else currentTime.day++;
						break;
					}
				default:break;
				}
				DS1302_Set_Time(&currentTime);
				break; 
			case HOUR_FLASH:
				if(23 == currentTime.hour) currentTime.hour = 0;			
				else currentTime.hour++;
				DS1302_Set_Time(&currentTime);
				break;
			case MINUTE_FLASH:
				if(59 == currentTime.minute) currentTime.minute = 0;			
				else currentTime.minute++;
				DS1302_Set_Time(&currentTime);
				break;
			default: break;
			}
		}
		while(!KEY_ADD);
	}
	else if(0 == KEY_SUB)
	{
		delay_1ms(20);
		if(0 == KEY_SUB)
		{
			//���ݵ�ǰ״̬���м�1����
			switch(KeyControlState)
		 	{   
			case YEAR_FLASH:
				//KeyControlState = MONTH_FLASH;
				if(0 == currentTime.year) currentTime.year = 99;			
				else currentTime.year--;
				DS1302_Set_Time(&currentTime);
				break;
			case MONTH_FLASH:
				if(1 == currentTime.month) currentTime.month = 12;			
				else currentTime.month--;
				DS1302_Set_Time(&currentTime);
				break;
			case DAY_FLASH:
				switch(currentTime.month)
				{
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					if(1 == currentTime.day) currentTime.day = 31;
					else currentTime.day--;
					break;
				case 4:
				case 6:
				case 9:
				case 11:
					if(1 == currentTime.day) currentTime.day = 30;
					else currentTime.day--;
					break;
				case 2:		
					if(0 != currentTime.year%4)
					{
						if(1 == currentTime.day) currentTime.day = 28;
						else currentTime.day--;
						break;
					}
					else
					{
						if(1 == currentTime.day) currentTime.day = 29;
						else currentTime.day--;
						break;
					}
				default:break;
				}
				DS1302_Set_Time(&currentTime);
				break; 
			case HOUR_FLASH:
				if(0 == currentTime.hour) currentTime.hour = 23;			
				else currentTime.hour--;
				DS1302_Set_Time(&currentTime);
				break;
			case MINUTE_FLASH:
				if(0 == currentTime.minute) currentTime.minute = 59;			
				else currentTime.minute--;
				DS1302_Set_Time(&currentTime);
				break;
			default: break;
			}
		}
		while(!KEY_SUB);
	}
}
