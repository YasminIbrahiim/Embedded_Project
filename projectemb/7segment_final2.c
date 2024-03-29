// this code is used to dispaly different 3 digit number on a 7 segments using tiva and also introduce a function to convert string to double 

#include<stdio.h>
#include<math.h>
#include <stdint.h>
#include<string.h>
#include "E:\nadeen lab\tm4c123gh6pm.h"
#include "tm4c123.h"

void SystemInit(){};
void portB_Int(void){ // use last 4pins of portB as an output
	SYSCTL_RCGCGPIO_R |= 0x02;
while ((SYSCTL_PRGPIO_R&0x02) == 0){};
GPIO_PORTB_DIR_R |=0xF0;
GPIO_PORTB_DEN_R |=0xF0;
GPIO_PORTB_AMSEL_R &=~0xF0;
GPIO_PORTB_AFSEL_R &=~0xF0;
GPIO_PORTB_PCTL_R &=~0xFFFF0000;
}
void portA_Int(void){ // use last 4pins of portA as an output
	SYSCTL_RCGCGPIO_R |= 0x01;
while ((SYSCTL_PRGPIO_R&0x01) == 0){};
GPIO_PORTA_DIR_R |=0xF0;
GPIO_PORTA_DEN_R |=0xF0;
GPIO_PORTA_AMSEL_R &=~0xF0;
GPIO_PORTA_AFSEL_R &=~0xF0;
GPIO_PORTA_PCTL_R &=~0xFFFF0000;
}
void portE_Int(void){ // use pin1 nto pin4 of portE as an output
	SYSCTL_RCGCGPIO_R |= 0x10;
while ((SYSCTL_PRGPIO_R&0x10) ==0){};
GPIO_PORTE_DIR_R |=0x1E;
GPIO_PORTE_DEN_R |= 0x1E;
GPIO_PORTE_AMSEL_R &=~0x1E;
GPIO_PORTE_AFSEL_R &=~0x1E;
GPIO_PORTE_PCTL_R &=~0x000FFFF0;
}
//this function output the data to the pins
void decoder_segment (unsigned char a,unsigned char b,unsigned char c){
		GPIO_PORTB_DATA_R&=~0xF0; // reset  the last 4pins for portB 
	GPIO_PORTA_DATA_R &=~0xF0; // reset  the last 4pins of portA
		GPIO_PORTE_DATA_R &=~ 0x1E; // reset output pins of portE
	GPIO_PORTB_DATA_R|=(b<<4);
		GPIO_PORTA_DATA_R |=(a<<4);
	GPIO_PORTE_DATA_R |=(c<<1);}

	void segment_display(unsigned int distance){ // this function display the units,tens and hundredth of the calculated distance
		unsigned char a,b,c;
		c=(distance/100);
	b=(distance/10)%10;
	a=(distance%10);
		decoder_segment(a,b,c);}
	
		//this function is used to convert string to double
double str_to_num(const char* str) {
	double final = 0;
	int count = 0;
	int dec_point = 0;
	int dec_num;
	for (; *str; str++) {
		if (*str == '.') {
			dec_point = 1;
			continue;
		}
		dec_num = *str - '0';
		if (dec_num >= 0 && dec_num <= 9) {
			if (dec_point == 1) {
				count++;
			}
			final = (final * 10.0) + dec_num;

		}
	}
	final = final / pow(10.0, count);

	return final;
}
double y;
char x[] = { '2','3','4','.','8' };
int main()
{
	 SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2) );
SystemInit();
 
	portB_Int();
		portE_Int();
		portA_Int();
		segment_display(424);
	y = str_to_num(x);
}