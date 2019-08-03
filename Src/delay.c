#include "delay.h"

void delay_us(uint32_t nus)
{

 uint32_t temp;

 SysTick->LOAD = 9*nus;

 SysTick->VAL=0X00;//��ռ�����

 SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ

 do

 {

  temp=SysTick->CTRL;//��ȡ��ǰ������ֵ

 }while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��

     SysTick->CTRL=0x00; //�رռ�����

    SysTick->VAL =0X00; //��ռ�����

}

void delay_ms(uint16_t nms)

{

 uint32_t temp;

 SysTick->LOAD = 9000*nms;

 SysTick->VAL=0X00;//��ռ�����

 SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ

 do

 {

  temp=SysTick->CTRL;//��ȡ��ǰ������ֵ

 }while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��

    SysTick->CTRL=0x00; //�رռ�����

    SysTick->VAL =0X00; //��ռ�����

}
