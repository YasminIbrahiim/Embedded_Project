#include "E:\nadeen lab\tm4c123gh6pm.h"
#include <stdint.h>
void SystemInit(){};
void portB_Int(void){
	SYSCTL_RCGCGPIO_R |= 0x02;
while ((SYSCTL_PRGPIO_R&0x02) == 0){};
GPIO_PORTB_CR_R = 0xFF;
GPIO_PORTB_DIR_R =0xFF;
GPIO_PORTB_DEN_R =0xFF;
GPIO_PORTB_AMSEL_R =0x00;
GPIO_PORTB_AFSEL_R =0x00;
GPIO_PORTB_PCTL_R =0x00000000;
	GPIO_PORTB_DATA_R =0x00;
}
void portE_Int(void){
	SYSCTL_RCGCGPIO_R |= 0x10;
while ((SYSCTL_PRGPIO_R&0x10) ==0){};
GPIO_PORTE_DIR_R =0x0F;
GPIO_PORTE_DEN_R = 0x0F;
GPIO_PORTE_AMSEL_R =0x00;
GPIO_PORTE_AFSEL_R =0x00;
GPIO_PORTE_PCTL_R =0x00000000;
	GPIO_PORTE_DATA_R = 0x00;
}
void decoder_segment (unsigned char a,unsigned char b,unsigned char c){
		GPIO_PORTB_DATA_R=0x00;
		GPIO_PORTB_DATA_R=a;
		GPIO_PORTB_DATA_R |=(b<<4);
	GPIO_PORTE_DATA_R =c;}

	void segment_display(unsigned int distance){
		unsigned char a,b,c;
		c=(distance/100);
	b=(distance/10)%10;
	a=(distance%10);
		decoder_segment(a,b,c);}
	
	

	int main(){
		portB_Int();
		portE_Int();
		segment_display(333);
	}
		

