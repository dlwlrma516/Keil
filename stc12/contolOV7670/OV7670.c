#include<I2C.h>
#include<delay.h>
unsigned char WrCmos7670(unsigned char regID, unsigned char regDat)	     //��CMOSָ���Ĵ�����дֵ
{			 //WrCmos7670(0x12, mmm)  �Ĵ�����ַ   ��д��ָ���Ĵ�����ֵ							 
	StartI2C0();				     //����I2C���ߣ�������I2C��ʼ����							 //CMOS PWDM�ӵ� ���� ���� ����0 �ڵ�1
	if(0==I2CWrite0(0x42))           //CMOS������ַ��д��																 �����ýڵ�ģʽ
	{													   //ov7670���ƼĴ�����˵��������ʹ��enable=1����ʹ��disable=0д��ַ0x42 ����ַ0x43
		StopI2C0();					//��I2CWrite0(0x42)�ķ���ֵΪ0 ����ʧ��					
		return(0);
	}
	delay_us(1);
  	if(0==I2CWrite0(regID))         //CMOS�Ĵ�����ַ
	{
		StopI2C0();
		return 0;
	}
	delay_us(1);
  	if(0==I2CWrite0(regDat))       //��д��ָ���Ĵ�����ֵ
	{
		StopI2C0();
		return(0);
	}
  	StopI2C0();
	
  	return(1);
}
void set_Cmos7670reg(void)   //CMOS�Ĵ�������
{

	WrCmos7670(0x3a, 0x04);	  //�л������ѡ�� 0000 0100  TSLB �����ø�Ƭ [3]0
	WrCmos7670(0x40, 0xd0);	  //ͨ�ÿ���15     1101 0000  �����Χ00��ff RGB565 COM15
	WrCmos7670(0x12, 0x14);	  //ͨ�ÿ���7	   0001 0100  0����λ 100 10Bayer RAW ��ɫ��0 ��ʹ��
	WrCmos7670(0x32, 0x80);	  //HREF���� 1000 0000 
	WrCmos7670(0x17, 0x16);	  //HSTART	 �����ʽ��Ƶ��ʼ 0001 0110 000
	WrCmos7670(0x18, 0x04);	  //HSTOP	 �����ʽ��Ƶ���� 0000 0100	000
	WrCmos7670(0x19, 0x02);	  //VSTRT	 �����ʽ��Ƶ��ʼ 0000 0010	10
	WrCmos7670(0x1a, 0x7b);	  //VSTOP	 �����ʽ��Ƶ���� 0111 1011	01
	WrCmos7670(0x03, 0x06);	  //VREF     ֡��ֵ�������   0000 0110
	WrCmos7670(0x0c, 0x00);	  //ͨ�ÿ���3 0000 0000��̬ ��ֹ����ʹ�� DCWʹ��
	WrCmos7670(0x3e, 0x00);	  //ͨ�ÿ���14 0000 0000 ����PCLK ���Ų��������ֶ�����
	WrCmos7670(0x70, 0x3a);	  //SCALING_XSC     0011 1010 
	WrCmos7670(0x71, 0x35);	  //SCALING_YSC     0011 0101 ��ΪĬ��ֵ
	WrCmos7670(0x72, 0x11);	  //SCALING_DCWCTR	0001 0001
	WrCmos7670(0x73, 0x00);	  //SCALING_PC	    0000 0000 
	WrCmos7670(0xa2, 0x02);	  //SCALING_PC LK_DELAY  0000 0010
	WrCmos7670(0x11, 0x81);	  //CLKRC �ڲ�ʱ��  1000 0001
	
	WrCmos7670(0x7a, 0x20);	  //SLOP ٤��������߶�б��
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
	
	WrCmos7670(0x13, 0xe0);	  //ͨ�ÿ���8 1110 0000
	WrCmos7670(0x00, 0x00);	  //AGC�Զ�������� Ĭ��0000 0000
	
	WrCmos7670(0x10, 0x00);	  //AECH�ع�ֵ 0000 0000 ��λ
	WrCmos7670(0x0d, 0x00);	  //ͨ�ÿ���4  0000 0000 00ȫ����
	WrCmos7670(0x14, 0x28);	  //ͨ�ÿ���9 COM9 0010 0000 010 8X �Զ������޶�
	WrCmos7670(0xa5, 0x05);	  //BD50MAX 0000 0101 50Hz�����˲�����������
	WrCmos7670(0xab, 0x07);	  //BD60MAX 0000 0111 60Hz�����˲�����������
	WrCmos7670(0x24, 0x75);	  //AEW AGC/AEC-�ȶ������������ޣ�
	WrCmos7670(0x25, 0x63);	  //AEB AGC/AEC-�ȶ������������ޣ�
	WrCmos7670(0x26, 0xA5);	  //VPT AGC/AEC������������ 1010 ���ٵ��������� 0101 ���ٵ���������
	WrCmos7670(0x9f, 0x78);	  //HAECC1 0111 1000 ����ֱ��ͼ��AEC/AGC����1
	WrCmos7670(0xa0, 0x68);	  //HAECC2 0110 1000 ����ֱ��ͼ��AEC/AGC����2
	WrCmos7670(0xa6, 0xdf);	  //HAECC3 1100 1111 ����ֱ��ͼ��AEC/AGC����3
	WrCmos7670(0xa7, 0xdf);	  //HAECC4 1100 1111 ����ֱ��ͼ��AEC/AGC����4
	WrCmos7670(0xa8, 0xf0);	  //HAECC5 1111 0000 ����ֱ��ͼ��AEC/AGC����5 Ĭ��ֵ
	WrCmos7670(0xa9, 0x90);	  //HAECC6 1001 0000 ����ֱ��ͼ��AEC/AGC����6
	WrCmos7670(0xaa, 0x94);	  //HAECC7 1001 0100 AEC��ʽѡ�� 1����ֱ��ͼ��AEC�㷨
	WrCmos7670(0x13, 0xe5);	  //ͨ�ÿ���8 COM7 1110 0101 ʹ�ܿ���AGC/AEC�㷨 AEC�����Ʋ��� 1�����˲����� AGC��AWB��AECʹ��

    WrCmos7670(0x0e, 0x61);
	WrCmos7670(0x0f, 0x4b);   //ͨ�ÿ���6 COM6 0100 1011 1�ڹ�ѧ�������ʱ��ֹHREF
	WrCmos7670(0x16, 0x02);
	WrCmos7670(0x1e, 0x05);	  //MVFP ˮƽ����/��ֱ��תʹ�� 0011 0101 1ˮƽ����ʹ�� 1��ֱ��תʹ�� 1������̫��ʹ��
	WrCmos7670(0x21, 0x02);	  //ADCCTR1 ����
	WrCmos7670(0x22, 0x01);	  //ADCCTR2 ����
	WrCmos7670(0x29, 0x07);
	WrCmos7670(0x33, 0x0b);	  //CHLF�й����е�������
	WrCmos7670(0x35, 0x0b);
	WrCmos7670(0x37, 0x1d);	  //ADC���� ����
	WrCmos7670(0x38, 0x71);	  //ACOM ADC��ģ�⹲ģ���� ����
	WrCmos7670(0x39, 0x2a);	  //OFON ADCƫ�ƿ��� ����
	WrCmos7670(0x3c, 0x78);	  //ͨ�ÿ���12 COM12 0111 1000 ��VSYNCSΪ��ʱû��HREF
	WrCmos7670(0x4d, 0x40);
	WrCmos7670(0x4e, 0x20);
	WrCmos7670(0x69, 0x00);	  //GFIX Ĭ��ֵ 0000 0000�̶�������� 1X Gr��Gb��R��Bͨ���̶�����ֵ
	WrCmos7670(0x6b, 0x60);	  //DBLV 0110 0000 ��·PLL �ڲ�LD0ʹ��
	WrCmos7670(0x74, 0x19);
	WrCmos7670(0x8d, 0x4f);
	WrCmos7670(0x8e, 0x00);
	WrCmos7670(0x8f, 0x00);
	WrCmos7670(0x90, 0x00);
	WrCmos7670(0x91, 0x00);
	WrCmos7670(0x92, 0x00);	  //DM_LNL ���еͰ�λ 
	WrCmos7670(0x96, 0x00);
	WrCmos7670(0x9a, 0x80);
	WrCmos7670(0xb0, 0x84);
	WrCmos7670(0xb1, 0x0c);	  //ABLC1 0000 1010  ��ֹ�ڵ�ƽУ����ABLC��ʹ��
	WrCmos7670(0xb2, 0x0e);
	WrCmos7670(0xb3, 0x82);	  //THL_DLT 1000 0010 �Զ��ڵ�ƽУ����ABLC��Ŀ��ֵ
	WrCmos7670(0xb8, 0x0a);

	WrCmos7670(0x43, 0x14);	  //AWBC1 ���� Ĭ��ֵ
	WrCmos7670(0x44, 0xf0);	  //AWBC2 ���� Ĭ��ֵ
	WrCmos7670(0x45, 0x34);	  //AWBC3 ���� 
	WrCmos7670(0x46, 0x58);	  //AWBC4 ���� 
	WrCmos7670(0x47, 0x28);	  //AWBC5 ����
	WrCmos7670(0x48, 0x3a);	  //AWBC6 ����
	WrCmos7670(0x59, 0x88);	  //RSVD AWB����
	WrCmos7670(0x5a, 0x88);	  //RSVD AWB����
	WrCmos7670(0x5b, 0x44);	  //RSVD AWB����
	WrCmos7670(0x5c, 0x67);	  //RSVD AWB����
	WrCmos7670(0x5d, 0x49);	  //RSVD AWB����
	WrCmos7670(0x5e, 0x0e);	  //RSVD AWB����
	WrCmos7670(0x64, 0x04);	  //LCC3 ��ͷ����ѡ��3-Gͨ���Ĳ���ϵ��LCC5[2]=1��ЧR,G,Bͨ������ϵ��LCC5[2]=0��Ч
	WrCmos7670(0x65, 0x20);	  //LCC4 ��ͷ����ѡ��4-���ⲹ���İ뾶
	WrCmos7670(0x66, 0x05);	  //LCC5 ��ͷ����ѡ��5 ��ͷ����ѡ��
	WrCmos7670(0x94, 0x04);	  //LCC6 ��ͷУ��ѡ��6 ��LCC5[2]=1��Ч
	WrCmos7670(0x95, 0x08);	  //LCC7 ��ͷУ��ѡ��7 ��LCC5[2]=1��Ч
	WrCmos7670(0x6c, 0x0a);	  //AWBCTR3 AWB����3
	WrCmos7670(0x6d, 0x55);	  //AWBCTR2 AWB����2
	WrCmos7670(0x6e, 0x11);	  //AWBCTR1 AWB����1
	WrCmos7670(0x6f, 0x9f);	  //AWBCTR0 AWB����0
	WrCmos7670(0x6a, 0x40);	  //GGAIN Gͨ��AWM���� 0100 0000
	WrCmos7670(0x01, 0x40);	  //BLUE AWB-��ɫͨ������  0100 0000
	WrCmos7670(0x02, 0x40);	  //RED AWB-��ɫͨ������   0100 0000
	WrCmos7670(0x13, 0xe7);	  //ͨ�ÿ���8 COM8 1110 0111 1ʹ�ܿ���AGC/AEC�㷨 ���������봹ֱͬ�� �����ƹ����� AGC/AWB/AECʹ��
	WrCmos7670(0x15, 0x00);   //ͨ�ÿ���10 COM10 Ĭ��ֵ ��HREFת��HSYNC 0PCLK������� PLCK���� HREF���� ��PCLK���½���VSYNC�ı� 
	                          // VSYNC����Ч HSYNC����Ч
	
	
	WrCmos7670(0x4f, 0x80);	  //MTX1 ɫ�ʾ���ϵ��1 1000 0000
	WrCmos7670(0x50, 0x80);	  //MTX2 ɫ�ʾ���ϵ��2 1000 0000
	WrCmos7670(0x51, 0x00);	  //MTX3 ɫ�ʾ���ϵ��3 0000 0000
	WrCmos7670(0x52, 0x22);	  //MTX4 ɫ�ʾ���ϵ��4 0010 0010
	WrCmos7670(0x53, 0x5e);	  //MTX5 ɫ�ʾ���ϵ��5 0101 1110
	WrCmos7670(0x54, 0x80);	  //MTX6 ɫ�ʾ���ϵ��6 1000 0000
	WrCmos7670(0x58, 0x9e);	  //MTXS ɫ�ʾ���ϵ��5~0�ķ��� 1001 1110
	
	WrCmos7670(0x41, 0x08);	  //ͨ�ÿ���16 COM16 Ĭ��ֵ 0000 0001
	WrCmos7670(0x3f, 0x00);	  //EDGE ��Ե��ǿ���� ��Ե��ǿϵ��
	
	WrCmos7670(0x74, 0x11);	  //REG74 �Ĵ���74 0001 0001 01���������ֶ����� 1X	  
	WrCmos7670(0x75, 0x05);	  //REG75 �Ĵ���75 0000 0101 4:0��Ե��ǿ����
	WrCmos7670(0x76, 0xc1);	  //REG76 �Ĵ���76 1100 0001 1�ڵ�У��ʹ��	 1�׵�У��ʹ�� 4:0��Ե��ǿ����
	WrCmos7670(0x4c, 0x00);	  //DNSTH��������ǿ�� Ĭ��ֵ
	WrCmos7670(0x77, 0x01);	  //REG77 �Ĵ���77 0000 0001 ����ȥ��ƫ��
	WrCmos7670(0x3d, 0xc2);	  //ͨ�ÿ���13 COM13 1010 0010 
	WrCmos7670(0x4b, 0x01);	  //GRB4B 0000 0001 �Ĵ���4B λ[0]:UVƽ��ʹ��
	WrCmos7670(0xc9, 0x60);	  //SATCTR 0110 0000 ���Ͷȿ���
	WrCmos7670(0x41, 0x38);	  //ͨ�ÿ���16COM16 0011 1000
	WrCmos7670(0x56, 0x40);	  //CONTRAS �Աȶȿ��� Ĭ��ֵ
	
	WrCmos7670(0x34, 0x11);	  //ARBLM �й����вο���ѹ���� Ĭ��ֵ
	WrCmos7670(0x3b, 0x02);   //ͨ�ÿ���11 0000 0010 ��ֹҹ��ģʽ 00 ����ͨģʽһ�� 0����50/60H�Զ���� 0�����˲���ֵѡ�� ѡ��BD60ST 1 �ع�ʱ�����С�������˲���������
								
	WrCmos7670(0xa4, 0x09);	  //NT_CTRL 0000 1001 1֡�ʼ��� 01��4x����������
	WrCmos7670(0x96, 0x00);
	WrCmos7670(0x97, 0x30);
	WrCmos7670(0x98, 0x20);
	WrCmos7670(0x99, 0x30);
	WrCmos7670(0x9a, 0x84);
	WrCmos7670(0x9b, 0x29);
	WrCmos7670(0x9c, 0x03);
	WrCmos7670(0x9d, 0x4c);	  //BD50ST 0100 1100 50Hz�����˲�����ֵ
	WrCmos7670(0x9e, 0x3f);	  //BD60ST 0011 1111 60Hz�����˲�����ֵ
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
	WrCmos7670(0x09, 0x00);	  //ͨ�ÿ���2 COM2 0000 0000 ����������� 2X		   
	
	
}
unsigned char Cmos7670_init(void)     //CMOS��ʼ��
{	
	InitI2C0();	   //P1 = 0xff; ��ʼ��IO
	if(0==WrCmos7670(0x12, 0x80)) 	//COM7 1000 0000 SCCB�Ĵ�����λ 1��λ 0����λ
		return 0 ;					//����ֵΪ0 ��λʧ��
	delay_ms(2);
  	set_Cmos7670reg();			   //CMOS�Ĵ�������																																	 
	return 1; 	                   //1 ��ʼ���ɹ�0 ��ʼ��ʧ��
} 
