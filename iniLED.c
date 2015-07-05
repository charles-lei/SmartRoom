
/*	�ļ�����iniLED.c
	���ܣ�ʵ��Һ��12864����غ������ܣ���Ҫ������ʼ������ʾ��
	���ߣ�����
	�������ڣ�2011-01-10
	�������ڣ�2011-01-17
	��Ҫע������⣺ LED12864_Transfer_Data()���ݿڵ�����,LED1602_Write(),LED1602_Enable()
*/


/*******************************�ļ��޸ļ�¼(S)***********************************/
/*1.
/*�޸�ǰ:
/*�޸�Ϊ:
/*���ڣ
/*�޸���:
/********************************�ļ��޸ļ�¼(E)**********************************/
#include "iniLED.h"
#include "myDefine.h"


/********************************************************************
* ���� : ini_LED()
* ���� : ��ʼ��Һ��
* ���� : ��
* ��� : ��
***********************************************************************/
void ini_LED()
{
	//LED12864_Ini_Char_Lib();
	//LED12864_Ini_Graphic_Lib();
	LED1602_Ini();
}

//������12864��غ���

/********************************************************************
* ���� : LED12864_Ini_Char_Lib()
* ���� : ��ʼ���ַ���
* ���� : ��
* ��� : ��
***********************************************************************/
/*
void LED12864_Ini_Char_Lib()
{
	delay_1ms(40);             //����40MS����ʱ����
	PSB = 1;                 //����Ϊ8BIT���ڹ���ģʽ
	delay_1ms(1);              //��ʱ
	RES = 0;                 //��λ
	delay_1ms(1);              //��ʱ
	RES = 1;                 //��λ�ø�
	delay_1ms(10);
	LED12864_Transfer_Data(0x30,0);  //Extended Function Set :8BIT����,RE=0: basic instruction set, G=0 :graphic display OFF
	DelayXus(100);            //����100uS����ʱ����
	LED12864_Transfer_Data(0x30,0);  //Function Set
	DelayXus(37);             ////����37uS����ʱ����
	LED12864_Transfer_Data(0x08,0);  //Display on Control
	DelayXus(100);            //����100uS����ʱ����
	LED12864_Transfer_Data(0x10,0);  //Cursor Display Control�������
	DelayXus(100);            //����100uS����ʱ����
	LED12864_Transfer_Data(0x0C,0);  //Display Control,D=1,��ʾ��
	DelayXus(100);            //����100uS����ʱ����
	LED12864_Transfer_Data(0x01,0);  //Display Clear
	DelayXus(100);             //����100uS����ʱ����
	LED12864_Transfer_Data(0x06,0);  //Enry Mode Set,�����������1λ�ƶ�
	DelayXus(100);            //����100uS����ʱ����
}

*/
/********************************************************************
* ���� : LED12864_Ini_Graphic_Lib()
* ���� : ��ʼ��ͼ�ο�
* ���� : ��
* ��� : ��
***********************************************************************/
/*
void LED12864_Ini_Graphic_Lib()
{
	delay_1ms(40);             //����40MS����ʱ����
	PSB=1;                 //����Ϊ8BIT���ڹ���ģʽ
	delay_1ms(1);              //��ʱ
	RES=0;                 //��λ
	delay_1ms(1);              //��ʱ
	RES=1;                 //��λ�ø�
	DelayXus(10);	
	LED12864_Transfer_Data(0x36,0);  //Extended Function Set RE=1: extended instruction
	DelayXus(100);            //����100uS����ʱ����
	LED12864_Transfer_Data(0x36,0);  //Extended Function Set:RE=1: extended instruction set
	DelayXus(37);             ////����37uS����ʱ����
	LED12864_Transfer_Data(0x3E,0);  //EXFUNCTION(DL=8BITS,RE=1,G=1)
	DelayXus(100);            //����100uS����ʱ����
	LED12864_Transfer_Data(0x01,0);  //CLEAR SCREEN
    DelayXus(100);            //����100uS����ʱ����
}
*/
/********************************************************************
* ���� : LED12864_Transfer_Data()
* ���� : ��ʾ�ַ�
* ���� : data1����LED12864���͵����ݻ�����
* ��� : ��
***********************************************************************/
/*
void LED12864_Transfer_Data(char data1,bit DI)  //�������ݻ�������,��DI=0��,��������,��DI=1,��������.
{
	//�����ӳ����䣬��Ҫ��ϸ�Ķ�ʱ������
	WRD=0;  //��LEDд
	RS=DI;	//ָ�������
	DelayXus(1);
    P0=data1;                          //P0Ϊ12864�뵥Ƭ�������ݽӿ�
	E=1;
	DelayXus(1);
	E=0;
 }
*/

/********************************************************************
* ���� : LED12864_Display_Char()
* ���� : ��ʾ�ַ�
* ���� : address���ַ������׵�ַ
* ��� : ��
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
* ���� : LED12864_Display_Graphic()
* ���� : ��ʾ�ַ�
* ���� : address���ַ������׵�ַ
* ��� : ��
***********************************************************************/
/*
void LED12864_Display_Graphic(uchar code *address)
{

   int i,j;
//*******��ʾ�ϰ�����������
   for(i=0;i<32;i++)              //
    { 
      LED12864_Transfer_Data((0x80 + i),0); //SET  ��ֱ��ַ VERTICAL ADD
      LED12864_Transfer_Data(0x80,0);       //SET  ˮƽ��ַ HORIZONTAL ADD
      for(j=0;j<16;j++)
       {
        LED12864_Transfer_Data(*address,1);
         address++;
       }
    }	   
//*******��ʾ�°�����������
   for(i=0;i<32;i++)              //
    {
      LED12864_Transfer_Data((0x80 + i),0); //SET ��ֱ��ַ VERTICAL ADD
      LED12864_Transfer_Data(0x88,0);       //SET ˮƽ��ַ HORIZONTAL ADD
      for(j=0;j<16;j++)
       {
         LED12864_Transfer_Data(*address,1);
         address++;
       }
    }
}*/

//������1602��غ���
/********************************************************************
* ���� : LED1602_Convert(uchar In_Date)
* ���� : ��Ϊ��·���ʱ��P0.0--P0.7�ӷ��պ��������е��෴��������Ƹú�����
* ���� : 1602�����ϵ�ֵ
* ��� : �͵�1602��ֵ
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
* ���� : LED1602_Enable(uchar del)
* ���� : 1602�����
* ���� : ���������ֵ
* ��� : ��
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
* ���� : uchar LED1602_read()
* ���� : 1602�����ݺ���
* ���� : ��
* ��� : ��
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
* ���� : LED1602_Write(uchar del)
* ���� : 1602д���ݺ���
* ���� : ��Ҫд��1602������
* ��� : ��
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
* ���� : LED1602_Ini(void)
* ���� : 1602��ʼ������ο�1602������
* ���� : ��
* ��� : ��
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
* ���� : L1602_char(uchar hang,uchar lie,char sign)
* ���� : �ı�Һ����ĳλ��ֵ�����Ҫ�õ�һ�У�������ַ���ʾ"b" �����øú�������
		 L1602_char(1,5,'b')
* ���� : �У��У���Ҫ����1602������
* ��� : ��
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
* ���� : L1602_String(uchar hang,uchar lie,uchar *p)
* ���� : �ı�Һ����ĳλ��ֵ�����Ҫ�õ�һ�У�������ַ���ʼ��ʾ"ab cd ef" �����øú�������
	 	 L1602_String(1,5,"ab cd ef;")
* ���� : �У��У���Ҫ����1602������
* ��� : ��
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



