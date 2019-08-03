#include "key.h"
#include "delay.h"
#include "stm32f1xx_hal.h"
//variables----------------------------------------------------

unsigned char key_press;
	
//function-----------------------------------------------------
unsigned char detectKey(void)
{
	unsigned char val_col=0xff;
	unsigned char val_row=0xff;
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_14;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
							
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2, GPIO_PIN_RESET);


	delay_us(1);

	val_row&=(unsigned char)((HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_4)<<0)|
                     (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_6)<<1)|
                     (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_8)<<2)|
                     (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)<<3));
        if(val_row!=0X0F)
        {
            delay_ms(20);       //消抖 延时后再读一次
						val_row&=(unsigned char)((HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_4)<<0)|
															 (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_6)<<1)|
															 (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_8)<<2)|
															 (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)<<3));
            if(val_row!=0X0F)
            {
//                    /* 交换输入信号读取行线值 */

							GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_8;
							GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
							GPIO_InitStruct.Pull = GPIO_NOPULL;
							GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
							HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
							
							GPIO_InitStruct.Pin = GPIO_PIN_7;
							GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
							GPIO_InitStruct.Pull = GPIO_NOPULL;
							GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
							HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

							GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_14;
							GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
							GPIO_InitStruct.Pull = GPIO_PULLUP;
							HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
							
							GPIO_InitStruct.Pin = GPIO_PIN_2;
							GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
							GPIO_InitStruct.Pull = GPIO_PULLUP;
							HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

							HAL_GPIO_WritePin(GPIOG, GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_8, GPIO_PIN_RESET);//0-3写0
							HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
							
							delay_ms(2);
//                    /* 读入行线值 */
							
							val_col&=(unsigned char)((HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_10)<<0)|
						 (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12)<<1)|
						 (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_14)<<2)|
						 (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_2)<<3));
							
							//等松手
							while((unsigned char)((HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_10)<<0)|
						 (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12)<<1)|
						 (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_14)<<2)|
						 (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_2)<<3))!=0x0f)
							{}
							
							switch(val_row)
							{
								case 0x07://一行
									switch(val_col)
									{
									case 0x07:
									key_press=16;
									break;
									case 0x0b:
									key_press=12;									
									break;
									case 0x0d:
									key_press=8;									
									break;
									case 0x0e:
									key_press=4;										
									break;
									}
									break;
								case 0x0b://二行
									switch(val_col)
									{
									case 0x07:
									key_press=15;										
									break;
									case 0x0b:
									key_press=11;										
									break;
									case 0x0d:
									key_press=7;									
									break;
									case 0x0e:
									key_press=3;										
									break;
									}
									break;
								case 0x0d://三行
									switch(val_col)
									{
									case 0x07:
									key_press=14;										
									break;
									case 0x0b:
									key_press=10;										
									break;
									case 0x0d:
									key_press=6;										
									break;
									case 0x0e:
									key_press=2;										
									break;
									}
									break;
								case 0x0e://四行
									switch(val_col)
									{
									case 0x07:
									key_press=13;										
									break;
									case 0x0b:
									key_press=9;										
									break;
									case 0x0d:
									key_press=5;										
									break;
									case 0x0e:
									key_press=1;										
									break;
									}
									break;
								default:
									key_press=0;
										
							}
              return key_press;

            }

        }
        else{
				key_press=0;
				}
				return key_press;
}



