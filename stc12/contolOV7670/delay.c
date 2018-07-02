#include <delay.h>
void delay_us(unsigned int time)
 {     
   while (time--);
 }		  
void delay_ms(unsigned int time)
	 {
	  while(time--) delay_us(100);  		 
	 }
void delay( unsigned long time)
{
	 unsigned int i = 0;

	while(time--)
	{
		for (i = 0; i < 2; i++)
		{}
	}
}

void delayms(int count)  // /* X1ms */
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<1000;j++);
}