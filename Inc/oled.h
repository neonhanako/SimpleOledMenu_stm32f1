//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : Evk123
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : 0.69寸OLED 接口演示例程(STM32F103ZE系列IIC)
//              说明: 
//              ----------------------------------------------------------------
//              GND   电源地
//              VCC   接5V或3.3v电源
//              SCL   接PD6（SCL）
//              SDA   接PD7（SDA）            
//              ----------------------------------------------------------------
//Copyright(C) 中景园电子2014/3/16
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////
#ifndef __OLED_H__
#define __OLED_H__			  	 
#include "stdlib.h"	
#include "stdint.h"
#include "stm32f1xx_hal.h"
#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED IIC端口定义----------------  					   

#define OLED_CS_Clr()  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET)//CS
#define OLED_CS_Set()  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET)

#define OLED_RST_Clr() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET)//RES
#define OLED_RST_Set() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET)

#define OLED_DC_Clr() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET)//DC
#define OLED_DC_Set() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET)

#define OLED_WR_Clr() HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET)
#define OLED_WR_Set() HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET)

#define OLED_RD_Clr() HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET)
#define OLED_RD_Set() HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET)


//使用4线串行接口时使用 

#define OLED_SCLK_Clr(void) HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET)//CLK
#define OLED_SCLK_Set(void) HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET)

#define OLED_SDIN_Clr(void) HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET)//DIN
#define OLED_SDIN_Set(void) HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET)
 		     
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

typedef unsigned          char u8;
typedef unsigned short     int u16;
typedef unsigned           int u32;

//OLED控制用函数
void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
u32 OLED_Pow(u8 m, u8 n);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);
void OLED_ShowChar(u8 x, u8 y, u8 chr, u8 size, u8 mode);
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size, u8 mode);
void OLED_ShowString(u8 x, u8 y, const u8 *p, u8 size,u8 len, u8 mode);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);

//补充
void OLED_Refresh_Gram(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot) ;
void OLED_DrawLine(u8 x0, u8 y, u8 x1, u8 t);
void OLED_DrawRow(u8 x, u8 y0, u8 y1, u8 t);
void OLED_DrawRectangle(u8 x0, u8 y0, u8 x1, u8 y1, u8 t);

#endif  
	 



