#ifndef XPT2046_H_
#define XPT2046_H_

#include<reg52.h>
#include<intrins.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

sbit CLK=P3^6;	//ʱ������
sbit CS=P3^5;	//Ƭѡ
sbit DIN=P3^4;	//�������������
sbit DOUT=P3^7;	//�������������

uint Read_AD_Value(uchar cmd);
uint Read_AD();
void Write_AD(uchar dat);


#endif