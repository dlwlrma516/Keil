#include<reg52.h>

typedef unsigned char u8;
typedef unsigned int u16;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 code smgduan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x76};

u8 disp[3];
u8 Time;

sbit IRIN=P3^2;
u8 IrValue[6];

void delay(u16 i)
{
     while(i--);
}

void IrInit()
{
	IT0=1;
	EX0=1;
	EA=1;	
	IRIN=1;
}

void display()
{
     u8 i;
	 for(i=0;i<3;i++)
	 {
		 switch(i)
		 {
		     case 0:LSA=0;LSB=0;LSC=0;break;
			 case 1:LSA=1;LSB=0;LSC=0;break;
			 case 2:LSA=0;LSB=1;LSC=0;break;
		 }
		 P0=disp[2-i];
		 delay(100);
		 P0=0x00;
	  }
}


void main()
{
	  IrInit();
	  while(1)
	  {
	  	   disp[0]=smgduan[IrValue[2]/16];
		   disp[1]=smgduan[IrValue[2]%16];
		   disp[2]=smgduan[16];
		   display();
	  }
}

void ReadIr()interrupt 0
{
	  u8 j,k;
	  u16 err;
	  Time=0;
	  delay(700);
	  if(IRIN==0)
	  {	  
	      err=1000;
		  while((IRIN==0)&&(err>0))
		  {
		  		  delay(1);
				  err--;
		  }
		  if(IRIN==1)
		  {
			  err=500;
			  while((IRIN==1)&&(err>0))
			  {
			  		  delay(1);
					  err--;
			  }
			  for(k=0;k<4;k++)
              {
                	for(j=0;j<8;j++)
                    {
					       err=60;
						   while((IRIN==0)&&(err>0))
						   {
						   		 delay(1);
								 err--;
						   }
						   err=500;
						   while((IRIN==1)&&(err>0))			 //计算高电平的长度
						   {
						   		 delay(10);		   //0.1ms
								 Time++;
								 err--;				 
								 if(Time>30)	   //3ms
								 {
									 return;
								 }
							}
							 IrValue[k]>>=1;
							 if(Time>=8)
							 {
							 	 IrValue[k]|=0x80;
							 }
							 Time=0;
					} 
			 }
		  }
		  if(IrValue[2]!=~IrValue[3])
		  {
				   return;
		  }  
		  
	  }
}
