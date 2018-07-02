//SCCB(SeriaI Camera ControlBus)是简化的I2C协议，SIO-l是串行时钟输入线，SIO-O是串行双向数据线，分别相当于I2C协议的SCL和SDA。SCCB的总线时序与I2C基本相同
#include<I2C.h>
#include<delay.h>
#include "reg51.h"
void InitI2C0(void)
{
	P1 = 0xff;
}
void StartI2C0(void)	     //启动I2C总线，即发送I2C初始条件
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

void StopI2C0(void)      //结束I2C总线，即发送I2C结束条件
{
	I2C_SDA0=0;			 //sbit I2C_SDA0=P1^1;	 SCCB数据口	  SIO-D	    输入/输出
    delay_us(1);
 
    I2C_SCL0=1;			 //sbit I2C_SCL0=P1^0;	 SCCB时钟口   SIO-C		输入
    delay_us(1);  

    I2C_SDA0=1;
    delay_us(1);
 

}
unsigned char I2CWrite0(unsigned char DData)
{
	unsigned char j,tem;

	for(j=0;j<8;j++) 	 //先高位后低位
	{
		if((DData<<j)&0x80)
		{
			I2C_SDA0=1;	   //数据线
		}
		else
		{
			I2C_SDA0=0;	  
		}
		delay_us(1);	  //                进行数据传送时，在SCL呈现高电平期间，SDA上的电平必须保持稳定
		I2C_SCL0=1;		  //时钟下降沿		只有在SCL为低电平期间，才允许SDA上的电平改变状态
		delay_us(1);
		I2C_SCL0=0;;
		delay_us(1);

	}										  //接收器在第9个时钟脉冲之前的低电平期间将SDA线拉低，并且确保在该时钟的高电平期间为稳定的低电平。
	delay_us(1);							  //由接收器反馈一个应答信号。 应答信号为低电平时，规定为有效应答位（ACK简称应答位），
	I2C_SCL0=1;			  //时钟线拉高			表示接收器已经成功地接收了该字节；应答信号为高电平时，规定为非应答位（NACK），一
	delay_us(1000);							  //般表示接收器接收该字节没有成功。
	if(SDA_STATE0==1)	  //SDA的状态？？数据线
	{
		tem=0;  		  //发送失败
	}
	else
	{
		tem=1;   		  //发送成功
	}
	I2C_SCL0=0;			 //时钟线拉低
	delay_us(1);	
	return(tem);  
}