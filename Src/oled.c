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
//////////////////////////////////////////////////////////////////////////////////?

#include "oled.h"
#include "stdlib.h"	 
#include "oledfonts.h"
#include "delay.h"


typedef unsigned          char u8;
typedef unsigned short     int u16;
typedef unsigned           int u32;

//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 	

u8 OLED_GRAM[128][8];	

void OLED_WR_Byte(unsigned dat,unsigned cmd)
{	
	u8 i;			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
	OLED_CS_Clr();
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;   
	}				 		  
	OLED_CS_Set();
	OLED_DC_Set();   	  
} 

	void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
}   	


/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_WR_Byte(0x00,0);		//low column start address
		OLED_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_WR_Byte(fill_Data,1);
			}
	}
}


/***********************Delay****************************************/
void Delay_50ms(unsigned int Del_50ms)
{
	unsigned int m;
	for(;Del_50ms>0;Del_50ms--)
		for(m=6245;m>0;m--);
}

void Delay_1ms(unsigned int Del_1ms)
{
	unsigned char j;
	while(Del_1ms--)
	{	
		for(j=0;j<123;j++);
	}
}

   	  
//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	u8 i, n;  
	for(i = 0; i < 8; i++)
	{
		for(n = 0; n < 128; n++)
		{
			OLED_GRAM[n][i] = 0X00;
		}
	}			
	OLED_Refresh_Gram();//更新显示
}
void OLED_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x02,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA); 
	} //更新显示
}
/** 
  * @name	void OLED_ShowChar(u8 x, u8 y, u8 chr, u8 size, u8 mode)
  * @brief  显示字符
  * @param	x: 0~127	y: 0~63		chr:字符	size:字体大小	
  *			mode:1 正常显示 0 反白显示
  * @retval	none
  */
void OLED_ShowChar(u8 x, u8 y, u8 chr, u8 size, u8 mode)
{      			    
	u8 temp, t, t1;
	u8 y0 = y;
	/*得到字体一个字符对应点阵集所占的字节数*/
	u8 csize = size;		
	chr = chr - ' ';//得到偏移后的值		 
    for (t = 0; t < csize-1; t++)
    {   
		switch (size)
		{
			case 16:
			//	temp = F8X16[chr][t]; 	
			temp = F8X16[chr][t];
				break;
			case 8:
				temp = F6x8[chr][t];
				break;
			default :
				return;						//没有的字库
		}
        for (t1 = 0; t1 < 8; t1++)
		{
			(temp & 0x80) ? OLED_DrawPoint(x, y, mode) : OLED_DrawPoint(x, y, !mode);
			temp <<= 1;
			y++;
			if ((y - y0) == size)
			{
				y = y0;
				x++;
				break;
			}
		}  	 
    }
	OLED_Refresh_Gram();
}
/** 
  * @name	void OLED_ShowString(u8 x, u8, y,const u8 *p, u8 mode)
  * @brief  显示字符串
  * @param	x: 0~127	y: 0~63		*p:字符串	size:字体大小	
  *			mode:1 正常显示 0 反白显示
  * @retval	none
  */
void OLED_ShowString(u8 x, u8 y, const u8 *p, u8 size,u8 len, u8 mode)
{
	u8 i=0;
	//while ((*p <= '~') && (*p >= ' '))	//判断是不是非法字符！
	for(i=0;i<len;i++)
	{
		if (x > (128 - (size / 2)))
		{
			x = 0;
			y += size;
		}
        if (y > (64 - size))
		{
			y = x = 0; 
			OLED_Clear();
		}
        OLED_ShowChar(x, y, *p, size, mode);	 
        x += size / 2;
		x++;
		x++;
        p++;
	}
}
//m^n函数
u32 OLED_Pow(u8 m, u8 n)
{
	u32 result = 1;
	while (n--)
	{
		result *= m;
	}
	return result;
}			  
/** 
  * @name	void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
  * @brief  OLED显示数
  * @param	x: 0~127	y: 0~63		num:数值(0~4294967295)	len:数字长度	size:字体大小	
  *			mode:1 正常显示 0 反白显示
  * @retval	none
  */ 		  
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size, u8 mode)
{         	
	u8 t, temp;
	u8 enshow = 0;						   
	for(t = 0; t < len; t++)//0 1
	{
		temp = (num / OLED_Pow(10, len - t - 1)) % 10;
		if(enshow == 0 && t < (len - 1))
		{
			
			if(temp == 0)
			{
				OLED_ShowChar(x + (size) * t, y, ' ', size, mode);
				continue;
			}
			else
			{
				enshow = 1;
			}
		}
	 	OLED_ShowChar(x + (size) * t, y, temp + '0', size, mode); 
	}
}
//显示汉字//中景圆
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}

//========================补充函数==========================
//更新显示
void OLED_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA); 
	}   
}

//画点 
//x:0~127
//y:0~63
//t:1 填充 0,清空				   
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;//超出范围了.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;	    
}


//填充/清空
//x1,y1,x2,y2 填充区域的对角坐标
//确保x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 
//dot:0,清空;1,填充	  
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
{  
	u8 x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
	}													    
	OLED_Refresh_Gram();//更新显示
}
/** 
  * @name	void OLED_DrawLine(u8 x, u8 y, u8 t)
  * @brief  画水平线
  * @param	x0: 0~127	y: 0~63		x1:	0~127	t:1 填充 0 清空
  * @retval	none
  */
void OLED_DrawLine(u8 x0, u8 y, u8 x1, u8 t)
{
	 u8 x_0, x_1, i;
	if (x0 > x1)	//判断x0与x1的大小
	{
		x_0 = x1;
		x_1 = x0;
	}
	else
	{
		x_0 = x0;
		x_1 = x1;
	}
	
	for (i = x_0 ; i <= x_1; i++)	//依次画点
	{
		OLED_DrawPoint(i, y, t);
	}
	OLED_Refresh_Gram();//更新显示
}

/** 
  * @name	void OLED_DrawRow(u8 x0, u8 y, u8 x1, u8 t)
  * @brief  画竖直线
  * @param	x: 0~127	y0: 0~63		y1:	0~63	t:1 填充 0 清空
  * @retval	none
  */
void OLED_DrawRow(u8 x, u8 y0, u8 y1, u8 t)
{
	 u8 y_0, y_1, i;
	if (y0 > y1)	//判断y0与y1的大小
	{
		y_0 = y1;
		y_1 = y0;
	}
	else
	{
		y_0 = y0;
		y_1 = y1;
	}
	
	for (i = y_0 ; i <= y_1; i++)	//依次画点
	{
		OLED_DrawPoint(x, i, t);
	}
	OLED_Refresh_Gram();//更新显示
}
/** 
  * @name	void OLED_DrawRow(u8 x0, u8 y, u8 x1, u8 t)
  * @brief  画矩形
  * @param	x0: 0~127	y0: 0~63	x1: 0~127	y1:	0~63	t:1 填充 0 清空
  * @retval	none
  */
void OLED_DrawRectangle(u8 x0, u8 y0, u8 x1, u8 y1, u8 t)
{
	 u8 y_0, y_1, x_0, x_1, i;
	if (y0 > y1)	//判断y0与y1的大小
	{
		y_0 = y1;
		y_1 = y0;
	}
	else
	{
		y_0 = y0;
		y_1 = y1;
	}
	
	if (x0 > x1)	//判断x0与x1的大小
	{
		x_0 = x1;
		x_1 = x0;
	}
	else
	{
		x_0 = x0;
		x_1 = x1;
	}
	
	for (i = x_0 ; i <= x_1; i++)	//依次画点
	{
		OLED_DrawPoint(i, y0, t);
		OLED_DrawPoint(i, y1, t);
	}
	
	for (i = y_0 ; i <= y_1; i++)	//依次画点
	{
		OLED_DrawPoint(x0, i, t);
		OLED_DrawPoint(x1, i, t);
	}
	OLED_Refresh_Gram();//更新显示
}

//==========================================================

//初始化oled					    
void OLED_Init(void)
{ 	
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_15, GPIO_PIN_SET);
	
  OLED_RST_Set();
	delay_ms(100);
	OLED_RST_Clr();
	delay_ms(100);
	OLED_RST_Set(); 
					  
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x02,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
	OLED_Clear();
	OLED_Set_Pos(0,0); 		
}  





























