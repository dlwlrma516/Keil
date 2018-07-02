#include<I2C.h>
#include<delay.h>
unsigned char WrCmos7670(unsigned char regID, unsigned char regDat)	     //向CMOS指定寄存器内写值
{			 //WrCmos7670(0x12, mmm)  寄存器地址   待写入指定寄存器的值							 
	StartI2C0();				     //启动I2C总线，即发送I2C初始条件							 //CMOS PWDM接地 类型 输入 工作0 节电1
	if(0==I2CWrite0(0x42))           //CMOS器件地址（写）																 不采用节电模式
	{													   //ov7670控制寄存器的说明，其中使能enable=1，非使能disable=0写地址0x42 读地址0x43
		StopI2C0();					//若I2CWrite0(0x42)的返回值为0 则发送失败					
		return(0);
	}
	delay_us(1);
  	if(0==I2CWrite0(regID))         //CMOS寄存器地址
	{
		StopI2C0();
		return 0;
	}
	delay_us(1);
  	if(0==I2CWrite0(regDat))       //待写入指定寄存器的值
	{
		StopI2C0();
		return(0);
	}
  	StopI2C0();
	
  	return(1);
}
void set_Cmos7670reg(void)   //CMOS寄存器配置
{

	WrCmos7670(0x3a, 0x04);	  //行缓冲测试选项 0000 0100  TSLB 可设置负片 [3]0
	WrCmos7670(0x40, 0xd0);	  //通用控制15     1101 0000  输出范围00到ff RGB565 COM15
	WrCmos7670(0x12, 0x14);	  //通用控制7	   0001 0100  0不复位 100 10Bayer RAW 彩色条0 非使能
	WrCmos7670(0x32, 0x80);	  //HREF控制 1000 0000 
	WrCmos7670(0x17, 0x16);	  //HSTART	 输出格式行频开始 0001 0110 000
	WrCmos7670(0x18, 0x04);	  //HSTOP	 输出格式行频结束 0000 0100	000
	WrCmos7670(0x19, 0x02);	  //VSTRT	 输出格式场频开始 0000 0010	10
	WrCmos7670(0x1a, 0x7b);	  //VSTOP	 输出格式场频结束 0111 1011	01
	WrCmos7670(0x03, 0x06);	  //VREF     帧数值方向控制   0000 0110
	WrCmos7670(0x0c, 0x00);	  //通用控制3 0000 0000三态 禁止缩放使能 DCW使能
	WrCmos7670(0x3e, 0x00);	  //通用控制14 0000 0000 正常PCLK 缩放参数不能手动调节
	WrCmos7670(0x70, 0x3a);	  //SCALING_XSC     0011 1010 
	WrCmos7670(0x71, 0x35);	  //SCALING_YSC     0011 0101 均为默认值
	WrCmos7670(0x72, 0x11);	  //SCALING_DCWCTR	0001 0001
	WrCmos7670(0x73, 0x00);	  //SCALING_PC	    0000 0000 
	WrCmos7670(0xa2, 0x02);	  //SCALING_PC LK_DELAY  0000 0010
	WrCmos7670(0x11, 0x81);	  //CLKRC 内部时钟  1000 0001
	
	WrCmos7670(0x7a, 0x20);	  //SLOP 伽马曲线最高段斜率
	WrCmos7670(0x7b, 0x1c);	  //GAM1
	WrCmos7670(0x7c, 0x28);	  //GAM2
	WrCmos7670(0x7d, 0x3c);	  //GAM3
	WrCmos7670(0x7e, 0x55);	  //GAM4
	WrCmos7670(0x7f, 0x68);	  //GAM5
	WrCmos7670(0x80, 0x76);	  //GAM6
	WrCmos7670(0x81, 0x80);	  //GAM7
	WrCmos7670(0x82, 0x88);	  //GAM8
	WrCmos7670(0x83, 0x8f);	  //GAM9
	WrCmos7670(0x84, 0x96);	  //GAM10
	WrCmos7670(0x85, 0xa3);	  //GAM11
	WrCmos7670(0x86, 0xaf);	  //GAM12
	WrCmos7670(0x87, 0xc4);	  //GAM13
	WrCmos7670(0x88, 0xd7);	  //GAM14
	WrCmos7670(0x89, 0xe8);	  //GAM15
	
	WrCmos7670(0x13, 0xe0);	  //通用控制8 1110 0000
	WrCmos7670(0x00, 0x00);	  //AGC自动增益控制 默认0000 0000
	
	WrCmos7670(0x10, 0x00);	  //AECH曝光值 0000 0000 高位
	WrCmos7670(0x0d, 0x00);	  //通用控制4  0000 0000 00全窗口
	WrCmos7670(0x14, 0x28);	  //通用控制9 COM9 0010 0000 010 8X 自动增益限度
	WrCmos7670(0xa5, 0x05);	  //BD50MAX 0000 0101 50Hz条纹滤波器步长限制
	WrCmos7670(0xab, 0x07);	  //BD60MAX 0000 0111 60Hz条纹滤波器步长限制
	WrCmos7670(0x24, 0x75);	  //AEW AGC/AEC-稳定运行区域（上限）
	WrCmos7670(0x25, 0x63);	  //AEB AGC/AEC-稳定运行区域（下限）
	WrCmos7670(0x26, 0xA5);	  //VPT AGC/AEC快速运行区域 1010 快速调整区上限 0101 快速调整区下限
	WrCmos7670(0x9f, 0x78);	  //HAECC1 0111 1000 基于直方图的AEC/AGC控制1
	WrCmos7670(0xa0, 0x68);	  //HAECC2 0110 1000 基于直方图的AEC/AGC控制2
	WrCmos7670(0xa6, 0xdf);	  //HAECC3 1100 1111 基于直方图的AEC/AGC控制3
	WrCmos7670(0xa7, 0xdf);	  //HAECC4 1100 1111 基于直方图的AEC/AGC控制4
	WrCmos7670(0xa8, 0xf0);	  //HAECC5 1111 0000 基于直方图的AEC/AGC控制5 默认值
	WrCmos7670(0xa9, 0x90);	  //HAECC6 1001 0000 基于直方图的AEC/AGC控制6
	WrCmos7670(0xaa, 0x94);	  //HAECC7 1001 0100 AEC公式选择 1基于直方图的AEC算法
	WrCmos7670(0x13, 0xe5);	  //通用控制8 COM7 1110 0101 使能快速AGC/AEC算法 AEC不限制步长 1条纹滤波器打开 AGC、AWB、AEC使能

    WrCmos7670(0x0e, 0x61);
	WrCmos7670(0x0f, 0x4b);   //通用控制6 COM6 0100 1011 1在光学黑行输出时禁止HREF
	WrCmos7670(0x16, 0x02);
	WrCmos7670(0x1e, 0x05);	  //MVFP 水平镜像/竖直翻转使能 0011 0101 1水平镜像使能 1竖直翻转使能 1消除黑太阳使能
	WrCmos7670(0x21, 0x02);	  //ADCCTR1 保留
	WrCmos7670(0x22, 0x01);	  //ADCCTR2 保留
	WrCmos7670(0x29, 0x07);
	WrCmos7670(0x33, 0x0b);	  //CHLF感光阵列电流控制
	WrCmos7670(0x35, 0x0b);
	WrCmos7670(0x37, 0x1d);	  //ADC控制 保留
	WrCmos7670(0x38, 0x71);	  //ACOM ADC和模拟共模控制 保留
	WrCmos7670(0x39, 0x2a);	  //OFON ADC偏移控制 保留
	WrCmos7670(0x3c, 0x78);	  //通用控制12 COM12 0111 1000 在VSYNCS为低时没有HREF
	WrCmos7670(0x4d, 0x40);
	WrCmos7670(0x4e, 0x20);
	WrCmos7670(0x69, 0x00);	  //GFIX 默认值 0000 0000固定增益控制 1X Gr、Gb、R、B通道固定增益值
	WrCmos7670(0x6b, 0x60);	  //DBLV 0110 0000 旁路PLL 内部LD0使能
	WrCmos7670(0x74, 0x19);
	WrCmos7670(0x8d, 0x4f);
	WrCmos7670(0x8e, 0x00);
	WrCmos7670(0x8f, 0x00);
	WrCmos7670(0x90, 0x00);
	WrCmos7670(0x91, 0x00);
	WrCmos7670(0x92, 0x00);	  //DM_LNL 空行低八位 
	WrCmos7670(0x96, 0x00);
	WrCmos7670(0x9a, 0x80);
	WrCmos7670(0xb0, 0x84);
	WrCmos7670(0xb1, 0x0c);	  //ABLC1 0000 1010  禁止黑电平校正（ABLC）使能
	WrCmos7670(0xb2, 0x0e);
	WrCmos7670(0xb3, 0x82);	  //THL_DLT 1000 0010 自动黑电平校正（ABLC）目标值
	WrCmos7670(0xb8, 0x0a);

	WrCmos7670(0x43, 0x14);	  //AWBC1 保留 默认值
	WrCmos7670(0x44, 0xf0);	  //AWBC2 保留 默认值
	WrCmos7670(0x45, 0x34);	  //AWBC3 保留 
	WrCmos7670(0x46, 0x58);	  //AWBC4 保留 
	WrCmos7670(0x47, 0x28);	  //AWBC5 保留
	WrCmos7670(0x48, 0x3a);	  //AWBC6 保留
	WrCmos7670(0x59, 0x88);	  //RSVD AWB控制
	WrCmos7670(0x5a, 0x88);	  //RSVD AWB控制
	WrCmos7670(0x5b, 0x44);	  //RSVD AWB控制
	WrCmos7670(0x5c, 0x67);	  //RSVD AWB控制
	WrCmos7670(0x5d, 0x49);	  //RSVD AWB控制
	WrCmos7670(0x5e, 0x0e);	  //RSVD AWB控制
	WrCmos7670(0x64, 0x04);	  //LCC3 镜头补偿选项3-G通道的补偿系数LCC5[2]=1有效R,G,B通道补偿系数LCC5[2]=0有效
	WrCmos7670(0x65, 0x20);	  //LCC4 镜头补偿选项4-避免补偿的半径
	WrCmos7670(0x66, 0x05);	  //LCC5 镜头补偿选项5 镜头补偿选择
	WrCmos7670(0x94, 0x04);	  //LCC6 镜头校正选项6 在LCC5[2]=1有效
	WrCmos7670(0x95, 0x08);	  //LCC7 镜头校正选项7 在LCC5[2]=1有效
	WrCmos7670(0x6c, 0x0a);	  //AWBCTR3 AWB控制3
	WrCmos7670(0x6d, 0x55);	  //AWBCTR2 AWB控制2
	WrCmos7670(0x6e, 0x11);	  //AWBCTR1 AWB控制1
	WrCmos7670(0x6f, 0x9f);	  //AWBCTR0 AWB控制0
	WrCmos7670(0x6a, 0x40);	  //GGAIN G通道AWM增益 0100 0000
	WrCmos7670(0x01, 0x40);	  //BLUE AWB-蓝色通道增益  0100 0000
	WrCmos7670(0x02, 0x40);	  //RED AWB-红色通道增益   0100 0000
	WrCmos7670(0x13, 0xe7);	  //通用控制8 COM8 1110 0111 1使能快速AGC/AEC算法 步长限制与垂直同步 开条纹过滤器 AGC/AWB/AEC使能
	WrCmos7670(0x15, 0x00);   //通用控制10 COM10 默认值 由HREF转到HSYNC 0PCLK连续输出 PLCK反相 HREF反相 在PCLK的下降沿VSYNC改变 
	                          // VSYNC负有效 HSYNC负有效
	
	
	WrCmos7670(0x4f, 0x80);	  //MTX1 色彩矩阵系数1 1000 0000
	WrCmos7670(0x50, 0x80);	  //MTX2 色彩矩阵系数2 1000 0000
	WrCmos7670(0x51, 0x00);	  //MTX3 色彩矩阵系数3 0000 0000
	WrCmos7670(0x52, 0x22);	  //MTX4 色彩矩阵系数4 0010 0010
	WrCmos7670(0x53, 0x5e);	  //MTX5 色彩矩阵系数5 0101 1110
	WrCmos7670(0x54, 0x80);	  //MTX6 色彩矩阵系数6 1000 0000
	WrCmos7670(0x58, 0x9e);	  //MTXS 色彩矩阵系数5~0的符号 1001 1110
	
	WrCmos7670(0x41, 0x08);	  //通用控制16 COM16 默认值 0000 0001
	WrCmos7670(0x3f, 0x00);	  //EDGE 边缘增强调整 边缘增强系数
	
	WrCmos7670(0x74, 0x11);	  //REG74 寄存器74 0001 0001 01数字增益手动控制 1X	  
	WrCmos7670(0x75, 0x05);	  //REG75 寄存器75 0000 0101 4:0边缘增强下限
	WrCmos7670(0x76, 0xc1);	  //REG76 寄存器76 1100 0001 1黑点校正使能	 1白点校正使能 4:0边缘增强下限
	WrCmos7670(0x4c, 0x00);	  //DNSTH噪声抑制强度 默认值
	WrCmos7670(0x77, 0x01);	  //REG77 寄存器77 0000 0001 噪声去除偏移
	WrCmos7670(0x3d, 0xc2);	  //通用控制13 COM13 1010 0010 
	WrCmos7670(0x4b, 0x01);	  //GRB4B 0000 0001 寄存器4B 位[0]:UV平均使能
	WrCmos7670(0xc9, 0x60);	  //SATCTR 0110 0000 饱和度控制
	WrCmos7670(0x41, 0x38);	  //通用控制16COM16 0011 1000
	WrCmos7670(0x56, 0x40);	  //CONTRAS 对比度控制 默认值
	
	WrCmos7670(0x34, 0x11);	  //ARBLM 感光阵列参考电压控制 默认值
	WrCmos7670(0x3b, 0x02);   //通用控制11 0000 0010 禁止夜晚模式 00 和普通模式一样 0机制50/60H自动侦测 0条纹滤波器值选择 选择BD60ST 1 曝光时间可以小于条纹滤波器的限制
								
	WrCmos7670(0xa4, 0x09);	  //NT_CTRL 0000 1001 1帧率减半 01在4x增益插入空行
	WrCmos7670(0x96, 0x00);
	WrCmos7670(0x97, 0x30);
	WrCmos7670(0x98, 0x20);
	WrCmos7670(0x99, 0x30);
	WrCmos7670(0x9a, 0x84);
	WrCmos7670(0x9b, 0x29);
	WrCmos7670(0x9c, 0x03);
	WrCmos7670(0x9d, 0x4c);	  //BD50ST 0100 1100 50Hz条纹滤波器的值
	WrCmos7670(0x9e, 0x3f);	  //BD60ST 0011 1111 60Hz条纹滤波器的值
	WrCmos7670(0x78, 0x04);
	
	WrCmos7670(0x79, 0x01);
	WrCmos7670(0xc8, 0xf0);
	WrCmos7670(0x79, 0x0f);
	WrCmos7670(0xc8, 0x00);
	WrCmos7670(0x79, 0x10);
	WrCmos7670(0xc8, 0x7e);
	WrCmos7670(0x79, 0x0a);
	WrCmos7670(0xc8, 0x80);
	WrCmos7670(0x79, 0x0b);
	WrCmos7670(0xc8, 0x01);
	WrCmos7670(0x79, 0x0c);
	WrCmos7670(0xc8, 0x0f);
	WrCmos7670(0x79, 0x0d);
	WrCmos7670(0xc8, 0x20);
	WrCmos7670(0x79, 0x09);
	WrCmos7670(0xc8, 0x80);
	WrCmos7670(0x79, 0x02);
	WrCmos7670(0xc8, 0xc0);
	WrCmos7670(0x79, 0x03);
	WrCmos7670(0xc8, 0x40);
	WrCmos7670(0x79, 0x05);
	WrCmos7670(0xc8, 0x30);
	WrCmos7670(0x79, 0x26);
	WrCmos7670(0x09, 0x00);	  //通用控制2 COM2 0000 0000 输出驱动能力 2X		   
	
	
}
unsigned char Cmos7670_init(void)     //CMOS初始化
{	
	InitI2C0();	   //P1 = 0xff; 初始化IO
	if(0==WrCmos7670(0x12, 0x80)) 	//COM7 1000 0000 SCCB寄存器复位 1复位 0不复位
		return 0 ;					//返回值为0 复位失败
	delay_ms(2);
  	set_Cmos7670reg();			   //CMOS寄存器配置																																	 
	return 1; 	                   //1 初始化成功0 初始化失败
} 
