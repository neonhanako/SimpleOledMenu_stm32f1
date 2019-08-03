#include "menu.h"
#include "stm32f1xx_hal.h"
#include "oled.h"
#include "protocol.h"
//变量部分================================================================================================

extern MenuItem *menuNow;//现在菜单界面
extern SubOption *optNow;//现在所指选项

extern UART_HandleTypeDef huart1;

extern unsigned char val_1;
extern unsigned char val_2;
extern unsigned char val_3;
extern unsigned char val_4;
extern unsigned char val_5;
extern unsigned char val_6;
extern unsigned int val_7;
extern unsigned char val_8;

//函数部分=================================================================================================
//display---------------------------------------------
void CallbackDisplay1_1(void)
{
	OLED_ShowString(4,53,(unsigned char*)Menu_1[0].optName,8,sizeof(Menu_1[0].optName),1);
}	
void CallbackDisplay1_2(void)
{
	OLED_ShowString(68,53,(unsigned char*)Menu_1[1].optName,8,sizeof(Menu_1[1].optName),1);
}
void CallbackDisplay1_3(void)
{
	OLED_ShowString(4,33,(unsigned char*)Menu_1[2].optName,8,sizeof(Menu_1[2].optName),1);
}

void CallbackDisplay2_1(void)
{
	OLED_ShowString(4,53,(unsigned char*)Menu_2[0].optName,8,sizeof(Menu_2[0].optName),1);
	OLED_ShowNum(4,44,val_1,7,8,1);
}
void CallbackDisplay2_2(void)
{
	OLED_ShowString(68,53,(unsigned char*)Menu_2[1].optName,8,sizeof(Menu_2[1].optName),1);
	OLED_ShowNum(68,44,val_2,7,8,1);
}
void CallbackDisplay2_3(void)
{
	OLED_ShowString(4,33,(unsigned char*)Menu_2[2].optName,8,sizeof(Menu_2[2].optName),1);
	OLED_ShowNum(4,24,val_3,7,8,1);
}
void CallbackDisplay2_4(void)
{
	OLED_ShowString(68,33,(unsigned char*)Menu_2[3].optName,8,sizeof(Menu_2[3].optName),1);
	OLED_ShowNum(68,24,val_4,7,8,1);
}
void CallbackDisplay2_5(void)
{
	OLED_ShowString(4,13,(unsigned char*)Menu_2[4].optName,8,sizeof(Menu_2[4].optName),1);
	OLED_ShowNum(4,4,val_5,7,8,1);
}
void CallbackDisplay2_6(void)
{
	OLED_ShowString(68,13,(unsigned char*)Menu_2[5].optName,8,sizeof(Menu_2[5].optName),1);
	OLED_ShowNum(68,4,val_6,7,8,1);
}

void CallbackDisplay3_1(void)
{
	OLED_ShowString(4,53,(unsigned char*)Menu_3[0].optName,8,sizeof(Menu_3[0].optName),1);
	OLED_ShowNum(4,44,val_7,7,8,1);
}
void CallbackDisplay3_2(void)
{
	OLED_ShowString(68,53,(unsigned char*)Menu_3[1].optName,8,sizeof(Menu_3[1].optName),1);
	OLED_ShowNum(68,44,val_8,7,8,1);
}

void CallbackDisplay4_1(void)
{
	OLED_ShowString(4,53,(unsigned char*)Menu_4[0].optName,8,sizeof(Menu_4[0].optName),1);

}

//plus------------------------------------------------ok
void KeyCallbackPlus1_1(void)
{
	return;
}
void KeyCallbackPlus1_2(void)
{
	return;
}
void KeyCallbackPlus1_3(void)
{
	return;
}

void KeyCallbackPlus2_1(void)
{
	OLED_ShowNum(4,44,val_1,7,8,0);
	val_1++;
	OLED_ShowNum(4,44,val_1,7,8,1);
	return;
}
void KeyCallbackPlus2_2(void)
{
	OLED_ShowNum(68,44,val_2,7,8,0);
	val_2++;
	OLED_ShowNum(68,44,val_2,7,8,1);
	return;
}
void KeyCallbackPlus2_3(void)
{
	OLED_ShowNum(4,24,val_3,7,8,0);
	val_3++;
	OLED_ShowNum(4,24,val_3,7,8,1);
	return;
}
void KeyCallbackPlus2_4(void)
{
	OLED_ShowNum(68,24,val_4,7,8,0);
	val_4++;
	OLED_ShowNum(68,24,val_4,7,8,1);
	return;
}
void KeyCallbackPlus2_5(void)
{
	OLED_ShowNum(4,4,val_5,7,8,0);
	val_5++;
	OLED_ShowNum(4,4,val_5,7,8,1);
	return;
}
void KeyCallbackPlus2_6(void)
{
	OLED_ShowNum(68,4,val_6,7,8,0);
	val_6++;
	OLED_ShowNum(68,4,val_6,7,8,1);
	return;
}

void KeyCallbackPlus3_1(void)
{
	OLED_ShowNum(4,44,val_7,7,8,0);
	val_7++;
	OLED_ShowNum(4,44,val_7,7,8,1);
	return;
}
void KeyCallbackPlus3_2(void)
{
	OLED_ShowNum(68,44,val_8,7,8,0);
	val_8++;
	OLED_ShowNum(68,44,val_8,7,8,1);
	return;
}

void KeyCallbackPlus4_1(void)
{
	return;
}

//minus---------------------------------------------------ok
void KeyCallbackMinus1_1(void)
{
	return;
}
void KeyCallbackMinus1_2(void)
{
	return;
}
void KeyCallbackMinus1_3(void)
{
	return;
}

void KeyCallbackMiuns2_1(void)
{
	OLED_ShowNum(4,44,val_1,7,8,0);
	val_1--;
	OLED_ShowNum(4,44,val_1,7,8,1);
	return;
}
void KeyCallbackMinus2_2(void)
{
	OLED_ShowNum(68,44,val_2,7,8,0);
	val_2--;
	OLED_ShowNum(68,44,val_2,7,8,1);
	return;
}
void KeyCallbackMinus2_3(void)
{
	OLED_ShowNum(4,24,val_3,7,8,0);
	val_3--;
	OLED_ShowNum(4,24,val_3,7,8,1);
	return;
}
void KeyCallbackMinus2_4(void)
{
	OLED_ShowNum(68,24,val_4,7,8,0);
	val_4--;
	OLED_ShowNum(68,24,val_4,7,8,1);
	return;
}
void KeyCallbackMinus2_5(void)
{
	OLED_ShowNum(4,4,val_5,7,8,0);
	val_5--;
	OLED_ShowNum(4,4,val_5,7,8,1);
	return;
}
void KeyCallbackMinus2_6(void)
{
	OLED_ShowNum(68,4,val_6,7,8,0);
	val_6--;
	OLED_ShowNum(68,4,val_6,7,8,1);
	return;
}

void KeyCallbackMinus3_1(void)
{
	OLED_ShowNum(4,44,val_7,7,8,0);
	val_7--;
	OLED_ShowNum(4,44,val_7,7,8,1);
	return;
}
void KeyCallbackMinus3_2(void)
{
	OLED_ShowNum(68,44,val_8,7,8,0);
	val_8--;
	OLED_ShowNum(68,44,val_8,7,8,1);
	return;
}

void KeyCallbackMinus4_1(void)
{
	return;
}

//confirm--------------------------------------------------ok
void KeyCallbackConfirm1_1(void)
{
	menuNow=menuNow+1;
	optNow=menuNow->subOpt;
	OLED_Clear();
	displayMenu(menuNow);
	return;
}
void KeyCallbackConfirm1_2(void)
{
	menuNow=menuNow+2;
	optNow=menuNow->subOpt;
	OLED_Clear();
	displayMenu(menuNow);
	return;
}
void KeyCallbackConfirm1_3(void)
{
	menuNow=menuNow+3;
	optNow=menuNow->subOpt;
	OLED_Clear();
	displayMenu(menuNow);
	return;
}
	

void KeyCallbackConfirm2_1(void)
{
//	while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY)//等待完成
//	{}
//	if(!HAL_UART_Transmit(&huart1,(unsigned char*)optNow->optName,sizeof(optNow->optName),0xff))
//	{
//			while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY)//等待完成
//			{}
//			HAL_UART_Transmit(&huart1,&val_1,1,0xff);	
//			while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY)//等待完成
//			{}
//	}
//	else
//	{}
	protocolUart(val_1,val_2,val_3,val_4,val_5,val_6,val_7>>8,val_7,val_8);
	return;
}
void KeyCallbackConfirm2_2(void)
{
//	while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY)//等待完成
//	{}
//	if(!HAL_UART_Transmit(&huart1,(unsigned char*)optNow->optName,sizeof(optNow->optName),0xff))
//	{
//			while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY)//等待完成
//			{}
//			HAL_UART_Transmit(&huart1,&val_2,1,0xff);	
//			while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY)//等待完成
//			{}
//	}
//	else
//	{}
		protocolUart(val_1,val_2,val_3,val_4,val_5,val_6,val_7>>8,val_7,val_8);
	  return;
}
void KeyCallbackConfirm2_3(void)
{
//	while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY)//等待完成
//	{}
//	if(!HAL_UART_Transmit(&huart1,(unsigned char*)optNow->optName,sizeof(optNow->optName),0xff))
//	{
//			while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY)//等待完成
//			{}
//			HAL_UART_Transmit(&huart1,&val_3,1,0xff);	
//			while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY)//等待完成
//			{}
//	}
//	else
//	{}
		protocolUart(val_1,val_2,val_3,val_4,val_5,val_6,val_7>>8,val_7,val_8);
		return;
}
void KeyCallbackConfirm2_4(void)
{
//	while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY)//等待完成
//	{}
//	if(!HAL_UART_Transmit(&huart1,(unsigned char*)optNow->optName,sizeof(optNow->optName),0xff))
//	{
//			while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY)//等待完成
//			{}
//			HAL_UART_Transmit(&huart1,&val_4,1,0xff);	
//			while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY)//等待完成
//			{}
//	}
//	else
//	{}
		protocolUart(val_1,val_2,val_3,val_4,val_5,val_6,val_7>>8,val_7,val_8);
		return;
}
void KeyCallbackConfirm2_5(void)
{
//	while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY)//等待完成
//	{}
//	if(!HAL_UART_Transmit(&huart1,(unsigned char*)optNow->optName,sizeof(optNow->optName),0xff))
//	{
//			while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY)//等待完成
//			{}
//			HAL_UART_Transmit(&huart1,&val_5,1,0xff);	
//			while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY)//等待完成
//			{}
//	}
//	else
//	{}
		protocolUart(val_1,val_2,val_3,val_4,val_5,val_6,val_7>>8,val_7,val_8);
		return;
}
void KeyCallbackConfirm2_6(void)
{
//	while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY)//等待完成
//	{}
//	if(!HAL_UART_Transmit(&huart1,(unsigned char*)optNow->optName,sizeof(optNow->optName),0xff))
//	{
//			while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY)//等待完成
//			{}
//			HAL_UART_Transmit(&huart1,&val_6,1,0xff);	
//			while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY)//等待完成
//			{}
//	}
//	else
//	{}
		protocolUart(val_1,val_2,val_3,val_4,val_5,val_6,val_7>>8,val_7,val_8);
		return;
}

void KeyCallbackConfirm3_1(void)
{
	protocolUart(val_1,val_2,val_3,val_4,val_5,val_6,val_7>>8,val_7,val_8);
	return;
}
void KeyCallbackConfirm3_2(void)
{
	protocolUart(val_1,val_2,val_3,val_4,val_5,val_6,val_7>>8,val_7,val_8);
	return;
}

void KeyCallbackConfirm4_1(void)
{
	return;
}
