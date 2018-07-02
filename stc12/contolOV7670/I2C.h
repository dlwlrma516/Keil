#ifndef I2C_H
#define I2C_H
#include "reg51.h"

#define SCCB_Writeadress  0x60
#define SCCB_Readadress   0x61
sbit I2C_SCL0=P1^0;
sbit I2C_SDA0=P1^1;
sbit SDA_STATE0=P1^1;

void InitI2C0(void);   //I2C��ʼ��
void StartI2C0(void);  //��ʼ�ź�
void StopI2C0(void);  //ֹͣ�ź�
void NoAck0(void);   //��Ӧ���ź�
void Ack0(void);
unsigned char TestAck0(void);
unsigned char I2CWrite0(unsigned char DData);   //дһ���ֽ�
unsigned char I2CRead0(void);  //��һ���ֽ�

#endif 