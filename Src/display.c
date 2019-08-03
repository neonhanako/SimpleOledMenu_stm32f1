#include "display.h"
#include "oled.h"
#include "menu.h"

//variables=======================================

extern MenuItem *menuNow;//���ڲ˵�����
extern SubOption *optNow;//������ָѡ��

extern MenuItem menu[MENU_NUM];
extern SubOption Menu_1[OPT_NUM_1];
extern SubOption Menu_2[OPT_NUM_2];
extern SubOption Menu_3[OPT_NUM_3];
extern SubOption Menu_4[OPT_NUM_4];

extern unsigned char val_1;
extern unsigned char val_2;
extern unsigned char val_3;
extern unsigned char val_4;
extern unsigned char val_5;
extern unsigned char val_6;
extern unsigned int val_7;
extern unsigned char val_8;

//function=======================================
void displayOled(unsigned char key)
{
	if(!key)//û�а������£�����ʾ�����ѡ��ѡ��
	{
		displayOption(optNow,1);
		//displayMenu(menuNow);
		return;
	}
	//�а������£����ݰ�������
	
	//�����
	if(key==KEY_UP||key==KEY_DOWN||key==KEY_LEFT||key==KEY_RIGHT)
	{
		if(0<optNow->optNum&&optNow->optNum<=6)//�����ڹ��6��
		{
			//����ȥ��
			if(key==KEY_UP&&((optNow->optNum)==1||(optNow->optNum)==2))
				return;
			else if(key==KEY_DOWN&&((optNow->optNum)==5||(optNow->optNum)==6))
				return;
			else if(key==KEY_LEFT&&((optNow->optNum)%2==1))
				return;
			else if(key==KEY_RIGHT&&((optNow->optNum)%2==0))
				return;
			
			//��
			if(key==KEY_UP)
			{		
				displayOption(optNow,0);
			  optNow=optNow-2;
			}
			
			//��
			else if(key==KEY_DOWN)
			{
				if(optNow->optNum+2>menuNow->subOptNum)
				return;
				else
				{	
					displayOption(optNow,0);
					optNow=optNow+2;
				}
			}
			
			//��
			else if(key==KEY_LEFT)
			{
				displayOption(optNow,0);
				optNow=optNow-1;

			}
			
			//��
			else if(key==KEY_RIGHT)
			{
			if(optNow->optNum+1>menuNow->subOptNum)
				return;
				else
				{	
					displayOption(optNow,0);
					optNow=optNow+1;

				}
			}
			
		}
		
		else//�������	
		{
		return;//��
		}
		
		return;
	}
	//ESC�������������棬ָ��ָ�Ĭ��
	else if(key==KEY_ESC)
	{
		//�ָ�����ָ��
		menuNow=menu;
		//optNow=menu->subOpt;
		optNow=menu[0].subOpt;
		//�ָ�Ĭ��ֵ
		 val_1=0;
		 val_2=1;
		 val_3=2;
		 val_4=3;
		 val_5=4;
		 val_6=5;
		 val_7=1000;
		 val_6=6;
		OLED_Clear();
		displayMenu(menuNow);
		return;
	}
	//+����-����ִ�ж�Ӧcallback
	else	if(key==KEY_PLUS||key==KEY_MINUS)
	{
		if(key==KEY_PLUS)//+callback
		optNow->KeyCallbackPlus();
		else//-callback
		optNow->KeyCallbackMinus();
		return;
	}
	//ȷ�ϼ������ͼ�����ִ�ж�Ӧcallback
	else if(key==KEY_CONFIRM)
	{
		optNow->KeyCallbackConfirm();//ȷ��callback
		return;
	}
	else//δ�����
	{
	return;
	}
}


//��ʾ�˵���ÿ��ѡ��(�ǵõ���ÿ��ѡ���callbackDisplay����
void displayMenu(MenuItem *menuNow)
{
	unsigned char i;
	SubOption *subOption=menuNow->subOpt;
 for(i=0;i<menuNow->subOptNum;i++)
	{
	subOption->display();
	subOption++;
	}
}

//��ѡ�е�ѡ���ס/����
//mode:1��ס
//:0����
void displayOption(SubOption *optNow,unsigned char mode)
{
	switch(optNow->optNum)
		{
		case 1:
			OLED_DrawRectangle(4,44,61,61,mode);
			break;
		case 2:
			OLED_DrawRectangle(68,44,125,61,mode);
			break;
		case 3:	
			OLED_DrawRectangle(4,24,61,41,mode);
			break;
		case 4:
			OLED_DrawRectangle(68,24,125,41,mode);
			break;
		case 5:
			OLED_DrawRectangle(4,4,61,21,mode);
			break;
		case 6:
			OLED_DrawRectangle(68,4,125,21,mode);
			break;
	}
}
