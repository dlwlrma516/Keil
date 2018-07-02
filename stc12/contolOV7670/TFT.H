#ifndef TFT_H
#define TFT_H
#include "reg51.h"
#define	BLACK	0x0000
#define	BLUE	0x001F
#define	RED 	0xF800
#define	GREEN 	0x07E0
#define CYAN	0x07FF
#define MAGENTA 0xF81F
#define YELLOW	0xFFE0
#define WHITE	0xFFFF		
#define AM         001  //011
#define BGR        1
#define Port0    P0
#define Port0MDOUT    P0MDOUT
//TFT �����ߣ�TFT�����ó�8λģʽ  
//P0^7-----------------D15    ��λ
//P0^6-----------------D14
//P0^5-----------------D13
//P0^4-----------------D12
//P0^3-----------------D11
//P0^2-----------------D10
//P0^1-----------------D9
//P0^0-----------------D8 
sbit Tft_CS_PIN=P2^0;//Ƭѡ���ƶ�  ֱ�ӽӵ�
sbit Tft_RS_PIN=P2^1;//RS=1�����ݣ�RS=0��ָ��
sbit Tft_WR_PIN=P2^2;//������д������
sbit Tft_RD_PIN=P2^3;//�����ض�������
sbit Tft_RST_PIN=P2^4;//��λ��
sbit Tft_BLK_PIN=P2^7;//����
void Tft_Init(void);
unsigned int Tft_ReadID(void);
void TftClear(unsigned int Color);
void TftWrite16(unsigned int index);
unsigned int BGR2RGB(unsigned int color);
void Tft_WR_DATA16(unsigned int inputdata);
void TftWrite(unsigned int index,unsigned int inputdata);
void Tft_SetCursor(unsigned int Xpos, unsigned int Ypos);
unsigned int Tft_ReadPoint(unsigned int Xpos,unsigned int Ypos);
void TftWR_SingleStr(unsigned char inputdata,unsigned int color,unsigned int xcolor);
void TftWR_Str(unsigned int x,unsigned int y,unsigned char *s,unsigned int color,unsigned int xcolor);
void Tft_SetBackground(unsigned int StartX,unsigned int StartY,unsigned int LongX,unsigned int LongY);
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);

#endif   