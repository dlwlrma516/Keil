#include"XPT2046.h"

void Write_AD(uchar dat)
{
	 uchar i;
	 CLK=0;
	 for(i=0;i<8;i++)
	 {
	 	  DIN=dat>>7;
		  dat<<=1;
		  CLK=0;
		  CLK=1;
	 }
}

uint Read_AD()
{
	 uint Value=0;
	 uchar i;
	 CLK=0;
	 for(i=0;i<12;i++)
	 {
	     Value<<=1;
		 CLK=1;
		 CLK=0;
		 Value|=DOUT;
	 }
	 return Value;
}

uint Read_AD_Value(uchar cmd)
{
	uint AD_Value;
	uchar i;
	CLK=0;
	CS=0;
	Write_AD(cmd);
	for(i=0;i<6;i++);
	CLK=1;
	_nop_();
	_nop_();
	CLK=0;
	_nop_();
	_nop_();
	AD_Value=Read_AD();
	CS=1;
	return AD_Value;
}