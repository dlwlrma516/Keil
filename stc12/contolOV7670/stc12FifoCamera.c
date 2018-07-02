#include "reg51.h"
#include "TFT.h"
#include "delay.h"
#include "OV7670.h"
#include "I2C.h"

void Ext_Interrupt_Init (void);
//���Ŷ���:	
sbit cmos1_cs = P3^6;
sbit cmos1_dir = P3^5;	
sbit cmos2_cs = P3^7;
sbit WR_CONTROL=P1^7;			

//FIFO control lines
sbit FIFO_WR=P1^2;	         //WR��������HREF��ͬ����FIFO_WE FIFO_WE��дʹ�ܣ��͵�ƽ��Ч   
sbit FIFO_WRST=P1^3;
sbit FIFO_RCK=P1^4;
sbit FIFO_RRST=P1^6;
sbit FIFO_OE=P1^5;			 //  CMOS RSTֱ�ӽ�vcc
sbit CMOS_VSYNC=P3^3;		 
//FIFO D0-7 ֱ�Ӷ�ӦLCD D08-D15



void main(void)
{
	int i,j;
	cmos2_cs=1;
	cmos1_cs=0;			  //Ƭѡ����ѡ��
	cmos1_dir=1;		  //DIR�Ӹ� ���input �ұ�output
	FIFO_OE=0;
	FIFO_RRST=1;																	   //����λʱ��
	FIFO_RCK=0;
	FIFO_RCK=1;
	FIFO_RRST=0;          //FIFO��ָ�븴λ      ����λ��д��λ��0.1ms�ĳ�ʼ������ 
	FIFO_RCK=0;           //��ʱ��0101    
	FIFO_RCK=1;	
	FIFO_RCK=0;
	FIFO_RCK=1;
	FIFO_RCK=0;																		   //FIFO_RE ��ʹ��ֱ�ӽӵ�
	FIFO_RRST=1;		 //����λ�͵�ƽ��Ч
	FIFO_OE=1;           //����FIFO����˿�Ϊ����̬	���ʹ��(active low)
	delay(10);

	Tft_Init();          //TFT��ʼ��
	TftClear(RED);       //����
	TftWR_Str(20,100,"STC89C52 Camera Test ",RED,BLACK);
	delay_ms(10);
	while(1!=Cmos7670_init());			//���ɹ���ʼ��cmos7670ʱΪ1���˳�ѭ��
	TftClear(BLACK);
	TftWR_Str(60,110,"OV7670  Init  SUCCESS!  ",RED,BLACK);
	
	Address_set(0,0,320-1,240-1);		 //�� ��
	delay_ms(500);
	
	
	Tft_CS_PIN=0;  //FIFO������TFT��ʾ	//Ƭѡ���ƶ�  ֱ�ӽӵ�
	Tft_RS_PIN=1;  //RS=1�����ݣ�RS=0��ָ��
	cmos1_cs=1;	   //74LVC245(U4) G	   U4��DIGֱ�ӽ�VCC 1

	Ext_Interrupt_Init();
	EA = 1;		   //�ж��ܿ���


	while(1)					   //���ϵ�ˢ��ͼ��
	{
		FIFO_OE=0;			 //���ʹ�ܵ͵�ƽ��Ч
		FIFO_RRST=1;																	   //����λʱ��
    	FIFO_RCK=0;
	    FIFO_RCK=1;
    	FIFO_RRST=0;          //FIFO��ָ�븴λ      ����λ��д��λ��0.1ms�ĳ�ʼ������ 
	    FIFO_RCK=0;           //��ʱ��0101    
	    FIFO_RCK=1;	
    	FIFO_RCK=0;
    	FIFO_RCK=1;
	    FIFO_RCK=0;
	    FIFO_RRST=1;		 //����λ�͵�ƽ��Ч												//FIFO_REֱ�ӽӵ�	  
		for(i = 0; i < 9600; i ++)	//QVGA format,240 lines;320dots every line	
		{
			for(j = 0; j <16; j ++)				//ʮ��λ�������ֽڣ���ΪRGB565 һ����240*320���㣬���ԣ�һ���������ֽ���ɣ��ٳ�2
			{																	  //��ʹ��ʱ�� tft��ov7670
				FIFO_RCK=0;		  //��FIFO_RE��OE��Ϊ�͵�ƽ����RCK�źŵ����������ݣ�������DI7��DI0���
 				Tft_WR_PIN=0;
				FIFO_RCK=1;	
				Tft_WR_PIN=1;     //������д������tft��ʾ

			}
	    }	   	  
	}
}
void Ext_Interrupt_Init (void)		//�ⲿ�жϳ�ʼ������
{
    EX1=1;  	//�����ⲿ�ж� 1����P33���ţ�EX1Ϊ�ж�1��P33����		 OV7670��VSYNC	��ֱͬ��
	IT1=1;      //���ó� �͵�ƽ������ʽ��IT0=1Ϊ�½��ش���
}
								   //FIFO������Ҫ��ʱ��FIFO��״̬��·�ͳ�һ���źţ�����ֹFIFO��д����������FIFO��д���ݶ�������
void INT1_ISR (void) interrupt 2	   //�½��ش���
{
						  		 //��WRST��RRST��Ϊ�͵�ƽʱ�����ݵ������������ӵ�ַ0��ʼ
	FIFO_WRST=0;   //д��λ         
	FIFO_WRST=1;					  //VSYNC
	FIFO_WR=1;	}//дʹ��			  //HREF
	/*��������£�VSYNC��HREFӦΪ�ߵ�ƽ��һ֡��ʱ���ڣ�VSYNC�½���һ�Σ�HREF�½���320�Σ���VSYNCΪ�½��ر�ɵ͵�ƽ��HREF����Ҳ�ǣ�������
	��˵��һ֡д����ʱ�����жϣ�ʹд��λ����FIFO_WRΪ1����ô��HREFҲ�Զ���Ϊ�ߵ�ƽ��������ʱ��VSYNCҲ��ɸߵ�ƽ��������ô��
	ͨ��sn74lvc1g00��· 2 ����������� ��ʹY�ӿڵ�FIFO_WE��0��д�����ɼ����ӵ�ַ0��ʼ*/   