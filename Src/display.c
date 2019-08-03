#include "display.h"
#include "oled.h"
#include "menu.h"

//variables=======================================

extern MenuItem *menuNow;//现在菜单界面
extern SubOption *optNow;//现在所指选项

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
	if(!key)//没有按键按下，仅演示界面和选中选项
	{
		displayOption(optNow,1);
		//displayMenu(menuNow);
		return;
	}
	//有按键按下，根据按键功能
	
	//方向键
	if(key==KEY_UP||key==KEY_DOWN||key==KEY_LEFT||key==KEY_RIGHT)
	{
		if(0<optNow->optNum&&optNow->optNum<=6)//现在在规格6内
		{
			//顶格去除
			if(key==KEY_UP&&((optNow->optNum)==1||(optNow->optNum)==2))
				return;
			else if(key==KEY_DOWN&&((optNow->optNum)==5||(optNow->optNum)==6))
				return;
			else if(key==KEY_LEFT&&((optNow->optNum)%2==1))
				return;
			else if(key==KEY_RIGHT&&((optNow->optNum)%2==0))
				return;
			
			//上
			if(key==KEY_UP)
			{		
				displayOption(optNow,0);
			  optNow=optNow-2;
			}
			
			//下
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
			
			//左
			else if(key==KEY_LEFT)
			{
				displayOption(optNow,0);
				optNow=optNow-1;

			}
			
			//右
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
		
		else//超出规格	
		{
		return;//空
		}
		
		return;
	}
	//ESC键，返回主界面，指针恢复默认
	else if(key==KEY_ESC)
	{
		//恢复两个指针
		menuNow=menu;
		//optNow=menu->subOpt;
		optNow=menu[0].subOpt;
		//恢复默认值
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
	//+键或-键，执行对应callback
	else	if(key==KEY_PLUS||key==KEY_MINUS)
	{
		if(key==KEY_PLUS)//+callback
		optNow->KeyCallbackPlus();
		else//-callback
		optNow->KeyCallbackMinus();
		return;
	}
	//确认键（发送键），执行对应callback
	else if(key==KEY_CONFIRM)
	{
		optNow->KeyCallbackConfirm();//确认callback
		return;
	}
	else//未定义键
	{
	return;
	}
}


//显示菜单下每个选项(记得调用每个选项的callbackDisplay啊！
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

//将选中的选项框住/消除
//mode:1框住
//:0消除
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
