//SCCB(SeriaI Camera ControlBus)�Ǽ򻯵�I2CЭ�飬SIO-l�Ǵ���ʱ�������ߣ�SIO-O�Ǵ���˫�������ߣ��ֱ��൱��I2CЭ���SCL��SDA��SCCB������ʱ����I2C������ͬ
#include<I2C.h>
#include<delay.h>
#include "reg51.h"
void InitI2C0(void)
{
	P1 = 0xff;
}
void StartI2C0(void)	     //����I2C���ߣ�������I2C��ʼ����
{
    I2C_SDA0=1;    						//I2C_SCL0=P1^0   I2C_SDA0=P1^1
    delay_us(1);

    I2C_SCL0=1;	   
    delay_us(1);
 
    I2C_SDA0=0;
    delay_us(1);

    I2C_SCL0=0;	 
    delay_us(1);


}

void StopI2C0(void)      //����I2C���ߣ�������I2C��������
{
	I2C_SDA0=0;			 //sbit I2C_SDA0=P1^1;	 SCCB���ݿ�	  SIO-D	    ����/���
    delay_us(1);
 
    I2C_SCL0=1;			 //sbit I2C_SCL0=P1^0;	 SCCBʱ�ӿ�   SIO-C		����
    delay_us(1);  

    I2C_SDA0=1;
    delay_us(1);
 

}
unsigned char I2CWrite0(unsigned char DData)
{
	unsigned char j,tem;

	for(j=0;j<8;j++) 	 //�ȸ�λ���λ
	{
		if((DData<<j)&0x80)
		{
			I2C_SDA0=1;	   //������
		}
		else
		{
			I2C_SDA0=0;	  
		}
		delay_us(1);	  //                �������ݴ���ʱ����SCL���ָߵ�ƽ�ڼ䣬SDA�ϵĵ�ƽ���뱣���ȶ�
		I2C_SCL0=1;		  //ʱ���½���		ֻ����SCLΪ�͵�ƽ�ڼ䣬������SDA�ϵĵ�ƽ�ı�״̬
		delay_us(1);
		I2C_SCL0=0;;
		delay_us(1);

	}										  //�������ڵ�9��ʱ������֮ǰ�ĵ͵�ƽ�ڼ佫SDA�����ͣ�����ȷ���ڸ�ʱ�ӵĸߵ�ƽ�ڼ�Ϊ�ȶ��ĵ͵�ƽ��
	delay_us(1);							  //�ɽ���������һ��Ӧ���źš� Ӧ���ź�Ϊ�͵�ƽʱ���涨Ϊ��ЧӦ��λ��ACK���Ӧ��λ����
	I2C_SCL0=1;			  //ʱ��������			��ʾ�������Ѿ��ɹ��ؽ����˸��ֽڣ�Ӧ���ź�Ϊ�ߵ�ƽʱ���涨Ϊ��Ӧ��λ��NACK����һ
	delay_us(1000);							  //���ʾ���������ո��ֽ�û�гɹ���
	if(SDA_STATE0==1)	  //SDA��״̬����������
	{
		tem=0;  		  //����ʧ��
	}
	else
	{
		tem=1;   		  //���ͳɹ�
	}
	I2C_SCL0=0;			 //ʱ��������
	delay_us(1);	
	return(tem);  
}