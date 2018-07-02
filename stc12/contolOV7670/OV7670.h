#ifndef OV7670_H
#define OV7670_H

void set_Cmos7670reg(void);
unsigned char Cmos7670_init(void);
unsigned char WrCmos7670(unsigned regID, unsigned regDat);
unsigned char rdCmos7670Reg(unsigned regID, unsigned *regDat);
void Cmos7670_Size(unsigned int Startx,unsigned int Starty,unsigned int width,unsigned int height);

#endif