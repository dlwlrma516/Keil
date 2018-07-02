#include <TFT.h>
#include <delay.h>
#include <english_16x8.h>
void Tft_WR_DATA16(unsigned int inputdata)      //向TFT RAM内写入数据，RGB565
{
		unsigned char inputdatal,inputdatah;
		unsigned int x;
		x=inputdata;
		inputdatal=inputdata&0x00ff;
		inputdatah=(inputdata>>8)&0x00ff;

		Tft_CS_PIN=0; 
		Tft_RS_PIN=1;//高为数据，低为指令
		Tft_RD_PIN=1;

		Port0=inputdatah; 
		Tft_WR_PIN=0;
		Tft_WR_PIN=1;

		Port0=inputdatal;
		Tft_WR_PIN=0;
		Tft_WR_PIN=1;	 
		Tft_CS_PIN=1;
  
}
void Tft_Write_REG(char index)//写寄存器命令
{   
	 Tft_CS_PIN=0;
	 Tft_RD_PIN=1;
	 Tft_RS_PIN=0;

	 Port0=index;
	 Tft_WR_PIN=0;
   Tft_WR_PIN=1;

 
}
void Tft_Write_COMDATA(char inputdata)    //向指定寄存器写数据
{
		Tft_CS_PIN=0;
		Tft_RD_PIN=1;
		Tft_RS_PIN=1;

		Port0=inputdata;
		Tft_WR_PIN=0;
		Tft_WR_PIN=1;

}
void Tft_Write_REG_DATA(char index,char inputdata)    //向指定寄存器写数据
{
   	Tft_Write_REG(index);
 	  Tft_Write_COMDATA(inputdata);
}

void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{ 
	Tft_Write_REG(0x2A);
	Tft_Write_COMDATA(x1>>8);
	Tft_Write_COMDATA(x1);
	Tft_Write_COMDATA(x2>>8);
	Tft_Write_COMDATA(x2);

	Tft_Write_REG(0x2B);
	Tft_Write_COMDATA(y1>>8);
	Tft_Write_COMDATA(y1);
	Tft_Write_COMDATA(y2>>8);
	Tft_Write_COMDATA(y2);	
	Tft_Write_REG(0x2c);								 
}
void Tft_Init(void)//tft初始化
{
	 	Tft_RST_PIN=1;
		delay(200); 
		Tft_RST_PIN=0;//硬件复位
		delay(200);
		Tft_RST_PIN=1;
		delay(200); 
		P2=0xff; //屏灯打开
		delay(200);

  	    Tft_RD_PIN=1;
		Tft_WR_PIN=1;
		Tft_RST_PIN=0;
		delayms(20);	//此处保证要有5ms以上才能保证复位稳定,推荐20ms
		Tft_RST_PIN=1;	
		delayms(20);	//此处保证要有5ms以上才能保证复位稳定,推荐20ms		


		  //************* Start Initial Sequence **********//
		Tft_Write_REG(0xcf); 
		Tft_Write_COMDATA(0x00);
		Tft_Write_COMDATA(0xc1);
		Tft_Write_COMDATA(0x30);

		Tft_Write_REG(0xed); 
		Tft_Write_COMDATA(0x64);
		Tft_Write_COMDATA(0x03);
		Tft_Write_COMDATA(0x12);
		Tft_Write_COMDATA(0x81);

		Tft_Write_REG(0xcb); 
		Tft_Write_COMDATA(0x39);
		Tft_Write_COMDATA(0x2c);
		Tft_Write_COMDATA(0x00);
		Tft_Write_COMDATA(0x34);
		Tft_Write_COMDATA(0x02);

		Tft_Write_REG(0xea); 
		Tft_Write_COMDATA(0x00);
		Tft_Write_COMDATA(0x00);

		Tft_Write_REG(0xe8); 
		Tft_Write_COMDATA(0x85);
		Tft_Write_COMDATA(0x10);
		Tft_Write_COMDATA(0x79);

		Tft_Write_REG(0xC0); //Power control
		Tft_Write_COMDATA(0x23); //VRH[5:0]

		Tft_Write_REG(0xC1); //Power control
		Tft_Write_COMDATA(0x11); //SAP[2:0];BT[3:0]

		Tft_Write_REG(0xC2);
		Tft_Write_COMDATA(0x11);

		Tft_Write_REG(0xC5); //VCM control
		Tft_Write_COMDATA(0x3d);
		Tft_Write_COMDATA(0x30);

		Tft_Write_REG(0xc7); 
		Tft_Write_COMDATA(0xaa);

		Tft_Write_REG(0x3A); 
		Tft_Write_COMDATA(0x55);

		Tft_Write_REG(0x36); // Memory Access Control
		Tft_Write_COMDATA(0xa8); //0x08

		Tft_Write_REG(0xB1); // Frame Rate Control
		Tft_Write_COMDATA(0x00);
		Tft_Write_COMDATA(0x11);

		Tft_Write_REG(0xB6); // Display Function Control
		Tft_Write_COMDATA(0x0a);
		Tft_Write_COMDATA(0xa2);

		Tft_Write_REG(0xF2); // 3Gamma Function Disable
		Tft_Write_COMDATA(0x00);

		Tft_Write_REG(0xF7);
		Tft_Write_COMDATA(0x20);

		Tft_Write_REG(0xF1);
		Tft_Write_COMDATA(0x01);
		Tft_Write_COMDATA(0x30);

		Tft_Write_REG(0x26); //Gamma curve selected
		Tft_Write_COMDATA(0x01);

		Tft_Write_REG(0xE0); //Set Gamma
		Tft_Write_COMDATA(0x0f);
		Tft_Write_COMDATA(0x3f);
		Tft_Write_COMDATA(0x2f);
		Tft_Write_COMDATA(0x0c);
		Tft_Write_COMDATA(0x10);
		Tft_Write_COMDATA(0x0a);
		Tft_Write_COMDATA(0x53);
		Tft_Write_COMDATA(0xd5);
		Tft_Write_COMDATA(0x40);
		Tft_Write_COMDATA(0x0a);
		Tft_Write_COMDATA(0x13);
		Tft_Write_COMDATA(0x03);
		Tft_Write_COMDATA(0x08);
		Tft_Write_COMDATA(0x03);
		Tft_Write_COMDATA(0x00);

		Tft_Write_REG(0xE1); //Set Gamma
		Tft_Write_COMDATA(0x00);
		Tft_Write_COMDATA(0x00);
		Tft_Write_COMDATA(0x10);
		Tft_Write_COMDATA(0x03);
		Tft_Write_COMDATA(0x0f);
		Tft_Write_COMDATA(0x05);
		Tft_Write_COMDATA(0x2c);
		Tft_Write_COMDATA(0xa2);
		Tft_Write_COMDATA(0x3f);
		Tft_Write_COMDATA(0x05);
		Tft_Write_COMDATA(0x0e);
		Tft_Write_COMDATA(0x0c);
		Tft_Write_COMDATA(0x37);
		Tft_Write_COMDATA(0x3c);
		Tft_Write_COMDATA(0x0F);
		Tft_Write_REG(0x11); //Exit Sleep
		delayms(80);//此处必须要延时80ms或者更多
		Tft_Write_REG(0x29); //display on

		delayms(1000);

  
}
void TftClear(unsigned int Color)               //将屏幕填充成指定的颜色
{
		unsigned long index = 0;

		Address_set(0,0,320-1,240-1);    

		for(index = 0; index < 76800; index++)
		{
			Tft_WR_DATA16(Color);

		} 

 
}
void TftWR_SingleStr(unsigned char inputdata,unsigned int color,unsigned int xcolor)   //显示一个8x16点阵的ascii字符
{

	unsigned char avl,i,n;
	//TftWrite16(0x0022);  
	for (i=0;i<16;i++)
	{ 
	  avl=(english[inputdata-32][i]);
	  for (n=0;n<8;n++)
	   {
	     if(avl&0x80) Tft_WR_DATA16(color);  //字符颜色
	         else Tft_WR_DATA16(xcolor);     //背景颜色
       
	     avl<<=1;
	   }
	}
	}
void TftWR_Str(unsigned int x,unsigned int y,unsigned char *s,unsigned int color,unsigned int xcolor)  //在指定座标显示一串8x16点阵的ascii字符
{
	unsigned int k=0;
	while (*s) 
	{
		 Tft_SetBackground(y,x+k,15,8);
		 TftWR_SingleStr( *s,color,xcolor);
		 k=k+8;
		 s++;

	}

}  
void Tft_SetBackground(unsigned int StartX,unsigned int StartY,unsigned int LongX,unsigned int LongY)//设置窗口区域
{
  Address_set(StartY,StartX,StartY+LongY-1,StartX+LongX-1);
}
void Tft_SetCursor(unsigned int Xpos, unsigned int Ypos)//设置屏幕座标
{
 
	TftWrite(0x20, Xpos);
	TftWrite(0x21, Ypos);
}