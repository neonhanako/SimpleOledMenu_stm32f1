#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

void protocolUart(unsigned char data1,unsigned char data2,unsigned char data3,unsigned char data4,unsigned char data5,unsigned char data6,unsigned char data7,unsigned char data8,unsigned char data9);
unsigned char sumCheck(unsigned char*data,unsigned char len);

#endif
