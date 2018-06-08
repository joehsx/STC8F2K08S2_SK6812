#include "reg51.h"
#include "intrins.h"

sfr     P1M0        =   0x92;
sfr     P1M1        =   0x91;
sbit Din = P1^6;

#define COLOR_NUM 7
#define LIGHT_NUM 30
struct color
{
		unsigned char red;
		unsigned char green;
		unsigned char blue;
};

struct color rainbow[] = {
	{0xFF, 0x00, 0x00},		// red
	{0x00, 0xFF, 0x00},	// oringe
	{0x00, 0x00, 0xFF},	// yellow
	{0xFF, 0xFF, 0x00},		// green
	{0xFF, 0x00, 0xFF},	// blue
	{0, 0, 0xFF},		// indigo
	{0x8B, 0, 0xFF},	// violet
	{0, 0, 0},			// off
};

//measured value: high level: 0.2917 low level: 0.9583
#define CODE0 {Din=1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();\
				Din=0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();\
				_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();\	
				_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();\	
			  }

//measured value:	high level:0.5833  low level:0.6667		  
#define CODE1 {Din=1;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();\
					_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();\
			Din = 0;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();\
					_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();\
			}


//>80 measured value 91			
void Reset()
{
	unsigned int i;
	Din = 0;
	for(i=0;i<280;i++)
	;
}

void Delayms(unsigned long k)		
{ 
    unsigned long i,j;  
    for(i=0; i<k; i++)  
    for(j=0; j<800; j++)      
    ;  
}


void send_data(unsigned char r, unsigned char g, unsigned char b)
{
	unsigned char a;
		for(a=0;a<8;a++)
		{
			if(r&0x80)
			CODE1
			else
			CODE0
			
			r=r<<1;
		}
		
		for(a=8;a<16;a++)
		{
			if(g&0x80)
			CODE1
			else
			CODE0
			
			g=g<<1;
		}
		
		for(a=16;a<24;a++)
		{
			if(b&0x80)
			CODE1
			else
			CODE0
			
			b=b<<1;
		}
}
void main()
{
		unsigned char color,light;
    P1M0 = 0xff;                                //set P1.0~P1.7 pp
    P1M1 = 0x00;
	
    while (1){
	for(color = 0; color < COLOR_NUM; color++) {
		// 1. lighten all the lights
		for(light = 0; light < LIGHT_NUM; light++)
			send_data(rainbow[color].red, rainbow[color].green, rainbow[color].blue);
		Reset();
		Delayms(500);
	}
		
	};
}
