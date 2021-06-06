///////////////////////////////////////////////////////////////////////////////////////////////
/* 1- Tasneem Abo El-Esaad Abd El-Razik    1809846    Worked in hardware connection and testing
   2- Nadeen Mohamed Mohamed Ramez         1806466    Worked in hardware connection and testing
///////////////////////////////////////////////////////////////////////////////////////////////
*/
#include<stdio.h>
#include<math.h>
#include <stdint.h>
#include "E:\Tasneem\imp.docs\tm4c123gh6pm.h"
#define pi 3.14159265358979323846
double theta, dist;
int y;
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
//This function converts decimal degrees to radians 
double deg2rad(double deg) {
    return (deg * pi / 180);
}
//This function converts radians to decimal degrees 
double rad2deg(double rad) {
    return (rad * 180 / pi);
}
double distance(double lat1,double lon1,double lon2,double lat2)
{
    if ((lat1 == lat2) && (lon1 == lon2)) {
        return 0;
    }
    else {
        theta = lon1 - lon2;
        dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
        dist = acos(dist);
        dist = rad2deg(dist);
        dist = dist * 60 * 1.1515 * 1609.344; // distance is now in miles * 1609.344 in meters 
		//dist = (int)dist; 
    }

}; 
//this function output the data to the pins
void decoder_segment (unsigned char a,unsigned char b,unsigned char c){
	GPIO_PORTB_DATA_R&=~0xF0; // reset  the last 4pins for portB 
	GPIO_PORTA_DATA_R &=~0xF0; // reset  the last 4pins of portA
	GPIO_PORTE_DATA_R &=~ 0x1E; // reset output pins of portE
	GPIO_PORTB_DATA_R|=(b<<4);
	GPIO_PORTA_DATA_R |=(a<<4);
  GPIO_PORTE_DATA_R |=(c<<1);
}

void segment_display(unsigned int distance){ // this function display the units,tens and hundredth of the calculated distance
	unsigned char a,b,c;
	c=(distance/100);
	b=(distance/10)%10;
	a=(distance%10);
	decoder_segment(a,b,c);
}
void LED_init(void){    // use F1,F2,F3 of portF as an output
SYSCTL_RCGCGPIO_R |= 0x20;
while ((SYSCTL_PRGPIO_R&0x20) == 0){};
GPIO_PORTF_LOCK_R = 0x4C4F434B;
GPIO_PORTF_CR_R |= 0x0E;
GPIO_PORTF_DIR_R |= 0X0E;
GPIO_PORTF_DEN_R |= 0x0E;
GPIO_PORTF_AMSEL_R &= ~0x0E;
GPIO_PORTF_AFSEL_R &=~0x0E;
GPIO_PORTF_PCTL_R &= ~0x0000FFF0; 
}
void LED(unsigned int x){
	if (x > 100){
		GPIO_PORTF_DATA_R |= 0x02; };
   }

int main (){
  LED_init();
  portB_Int();
  portE_Int();
  portA_Int();
	y = distance(43.005,23.420006,23.42,43.00166);
	LED(y);
  segment_display(y);
}