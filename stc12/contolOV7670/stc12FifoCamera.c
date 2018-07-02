#include "reg51.h"
#include "TFT.h"
#include "delay.h"
#include "OV7670.h"
#include "I2C.h"

void Ext_Interrupt_Init (void);
//引脚定义:	
sbit cmos1_cs = P3^6;
sbit cmos1_dir = P3^5;	
sbit cmos2_cs = P3^7;
sbit WR_CONTROL=P1^7;			

//FIFO control lines
sbit FIFO_WR=P1^2;	         //WR是用来和HREF共同控制FIFO_WE FIFO_WE是写使能，低电平有效   
sbit FIFO_WRST=P1^3;
sbit FIFO_RCK=P1^4;
sbit FIFO_RRST=P1^6;
sbit FIFO_OE=P1^5;			 //  CMOS RST直接接vcc
sbit CMOS_VSYNC=P3^3;		 
//FIFO D0-7 直接对应LCD D08-D15



void main(void)
{
	int i,j;
	cmos2_cs=1;
	cmos1_cs=0;			  //片选拉低选中
	cmos1_dir=1;		  //DIR接高 左边input 右边output
	FIFO_OE=0;
	FIFO_RRST=1;																	   //读复位时序
	FIFO_RCK=0;
	FIFO_RCK=1;
	FIFO_RRST=0;          //FIFO读指针复位      读复位和写复位各0.1ms的初始化脉冲 
	FIFO_RCK=0;           //读时针0101    
	FIFO_RCK=1;	
	FIFO_RCK=0;
	FIFO_RCK=1;
	FIFO_RCK=0;																		   //FIFO_RE 读使能直接接地
	FIFO_RRST=1;		 //读复位低电平有效
	FIFO_OE=1;           //设置FIFO输出端口为高阻态	输出使能(active low)
	delay(10);

	Tft_Init();          //TFT初始化
	TftClear(RED);       //清屏
	TftWR_Str(20,100,"STC89C52 Camera Test ",RED,BLACK);
	delay_ms(10);
	while(1!=Cmos7670_init());			//当成功初始化cmos7670时为1，退出循环
	TftClear(BLACK);
	TftWR_Str(60,110,"OV7670  Init  SUCCESS!  ",RED,BLACK);
	
	Address_set(0,0,320-1,240-1);		 //列 行
	delay_ms(500);
	
	
	Tft_CS_PIN=0;  //FIFO数据送TFT显示	//片选控制端  直接接地
	Tft_RS_PIN=1;  //RS=1，数据；RS=0，指令
	cmos1_cs=1;	   //74LVC245(U4) G	   U4的DIG直接接VCC 1

	Ext_Interrupt_Init();
	EA = 1;		   //中断总开关


	while(1)					   //不断地刷新图像
	{
		FIFO_OE=0;			 //输出使能低电平有效
		FIFO_RRST=1;																	   //读复位时序
    	FIFO_RCK=0;
	    FIFO_RCK=1;
    	FIFO_RRST=0;          //FIFO读指针复位      读复位和写复位各0.1ms的初始化脉冲 
	    FIFO_RCK=0;           //读时针0101    
	    FIFO_RCK=1;	
    	FIFO_RCK=0;
    	FIFO_RCK=1;
	    FIFO_RCK=0;
	    FIFO_RRST=1;		 //读复位低电平有效												//FIFO_RE直接接地	  
		for(i = 0; i < 9600; i ++)	//QVGA format,240 lines;320dots every line	
		{
			for(j = 0; j <16; j ++)				//十六位，两个字节，因为RGB565 一共是240*320个点，所以（一个点由两字节组成）再乘2
			{																	  //读使能时序 tft读ov7670
				FIFO_RCK=0;		  //当FIFO_RE和OE均为低电平，在RCK信号的上升沿数据，数据由DI7到DI0输出
 				Tft_WR_PIN=0;
				FIFO_RCK=1;	
				Tft_WR_PIN=1;     //上升沿写数据入tft显示

			}
	    }	   	  
	}
}
void Ext_Interrupt_Init (void)		//外部中断初始化函数
{
    EX1=1;  	//开启外部中断 1，即P33引脚，EX1为中断1，P33引脚		 OV7670的VSYNC	垂直同步
	IT1=1;      //设置成 低电平触发方式，IT0=1为下降沿触发
}
								   //FIFO已满或将要满时用FIFO的状态电路送出一个信号，以阻止FIFO的写操作继续从FIFO种写数据而造成溢出
void INT1_ISR (void) interrupt 2	   //下降沿触发
{
						  		 //当WRST和RRST均为低电平时，数据的输入和输出均从地址0开始
	FIFO_WRST=0;   //写复位         
	FIFO_WRST=1;					  //VSYNC
	FIFO_WR=1;	}//写使能			  //HREF
	/*正常情况下，VSYNC和HREF应为高电平，一帧的时间内，VSYNC下降沿一次，HREF下降沿320次，当VSYNC为下降沿变成低电平（HREF可能也是？？），
	则说明一帧写完这时进入中断，使写复位，置FIFO_WR为1，那么当HREF也自动变为高电平（即正常时，VSYNC也变成高电平？？）那么，
	通过sn74lvc1g00单路 2 输入正与非门 则使Y接口的FIFO_WE置0，写操作可继续从地址0开始*/   