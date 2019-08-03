#include "protocol.h"
#include "stm32f1xx_hal.h"

//����==================================================
static unsigned char txBuffer[100];

extern UART_HandleTypeDef huart1;

//����==================================================

void protocolUart(unsigned char data1,unsigned char data2,unsigned char data3,unsigned char data4,unsigned char data5,unsigned char data6,unsigned char data7,unsigned char data8,unsigned char data9)
{
	txBuffer[0]=0xAA;//֡ͷ
	txBuffer[1]=0xAF;
	txBuffer[2]=0x05;//��ʶ��
	txBuffer[3]=0x01;
	txBuffer[4]=0x06;
	txBuffer[5]=data1;
	txBuffer[6]=data2;
	txBuffer[7]=data3;
	txBuffer[8]=data4;
	txBuffer[9]=data5;
	txBuffer[10]=data6;
	txBuffer[11]=data7;
	txBuffer[12]=data8;
	txBuffer[13]=data9;
	txBuffer[14]=sumCheck(&(txBuffer[5]),9);//��У��	
	
	//����
		while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY)//�ȴ����
	{}
		if(!HAL_UART_Transmit(&huart1,txBuffer,15,0xff))//�������ݣ�������11
	{
			while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY)//�ȴ����
			{}
	}
	else
	{}
}


//��У��ר��
unsigned char sumCheck(unsigned char*data,unsigned char len)
{
	unsigned char i;
	unsigned char sum=0;
	for(i=0;i<len;i++)
	{
	sum+=*(data+i);
	}
	return sum;
}
