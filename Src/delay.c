#include "delay.h"

void delay_us(uint32_t nus)
{

 uint32_t temp;

 SysTick->LOAD = 9*nus;

 SysTick->VAL=0X00;//清空计数器

 SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源

 do

 {

  temp=SysTick->CTRL;//读取当前倒计数值

 }while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达

     SysTick->CTRL=0x00; //关闭计数器

    SysTick->VAL =0X00; //清空计数器

}

void delay_ms(uint16_t nms)

{

 uint32_t temp;

 SysTick->LOAD = 9000*nms;

 SysTick->VAL=0X00;//清空计数器

 SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源

 do

 {

  temp=SysTick->CTRL;//读取当前倒计数值

 }while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达

    SysTick->CTRL=0x00; //关闭计数器

    SysTick->VAL =0X00; //清空计数器

}
