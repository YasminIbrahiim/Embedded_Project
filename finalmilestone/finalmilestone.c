 #include<stdio.h>
#include<stdio.h>
#include<math.h>
#include <stdint.h>
#include "c:\Users\ea\Downloads\tm4c123gh6pm.h"
#include <string.h>
#include "TM4C123.h"
#define pi 3.14159265358979323846
#define CR         0x0d
#define LF         0x0a
char data[100];
char ch;
char longi[9];
char lati[9];
int	    	 longDegrees;
float a;
int	    	 latDegrees;
double lon;
double lat;

int y ;
double deg2rad(double deg);
double rad2deg(double rad);
double distance(double lat1,double lon1,double lon2,double lat2);
int Update_distance(double lat, double lon);
int call_back(int(*ptr)());

void LED(unsigned int x);
void segment_display(unsigned int distance);
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
  GPIO_PORTE_DATA_R |=(c<<1);
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
void UART_Init(void){
SYSCTL_RCGCUART_R |= 0x00000002;
SYSCTL_RCGCGPIO_R |= 0x00000002;
while ((SYSCTL_PRGPIO_R &=0x00000002)==0){};
UART1_CTL_R &= ~0x01;
UART1_IBRD_R = 104;	
UART1_FBRD_R = 11;
UART1_LCRH_R =0x00000070 ;	
UART1_CTL_R |= 0x301; 
GPIO_PORTB_AFSEL_R |=0x03 ; 
GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFFFF00)+0x00000011;
GPIO_PORTB_DEN_R |= 0x03;
GPIO_PORTB_AMSEL_R &=~0x03 ; 
}
uint8_t InChar(void){
while((UART1_FR_R&0x0010)!=0){};
	return((uint8_t)(UART1_DR_R&0xFF));
	
}

void delay(void){
		NVIC_ST_CTRL_R = 0;
		NVIC_ST_RELOAD_R = 16000000-1;
		NVIC_ST_CURRENT_R = 0;
		NVIC_ST_CTRL_R = 0x05;
		while((NVIC_ST_CTRL_R&0x00010000)==0){};
		}


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

	return (final/100);
}

void segment_display(unsigned int distance){ // this function display the units,tens and hundredth of the calculated distance
	unsigned char a,b,c;
	c=(distance/100);
	b=(distance/10)%10;
	a=(distance%10);
	decoder_segment(a,b,c);
}
void LED(unsigned int x){
	if (x > 100){
		GPIO_PORTF_DATA_R |= 0x02; };
   }
int call_back(int(*ptr)()){
	return (*ptr) (); 
}


double theta, dist;
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
		    return dist; 		// in meters 
    }

}
//This function converts decimal degrees to radians 
double deg2rad(double deg) {
    return (deg * pi / 180);
}
//This function converts radians to decimal degrees 
double rad2deg(double rad) {
    return (rad * 180 / pi);
}
	double s ;
	double v;				
int  m;
int minutes;
double degrees;
double longit;
double latit;
double check(){
	int k = 0 ;
	int j = 0;
	int n = 0;
	int i = 0;

	do{
		ch = InChar();
		if (ch == '$') {
			
			data[i] = ch;
	
			do {
				ch = InChar();
				
					i++;
					data[i] = ch;
				

			} while (ch != '\0');
			data[i + 1] = '\0';
			
			if ((data[0] == '$') && (data[1] == 'G') && (data[2] == 'P') && (data[3] == 'G') && (data[4] == 'G') && (data[5] == 'A')) {
				if (data[6] == ',') {
					k = 7;
					while (data[k] != ',') {
						k++;
					}
					k++;
					
					while (data[k] != ',') {
						lati[j] = data[k];
						k++;
						j++;
					}
					k = k + 3;
					while (data[k] != ',') {
						longi[n] = data[k];
						k++;
						n++;
					}
					
	s = str_to_num (longi);
	minutes = (int)(s/1000);
	degrees = (s - (double) minutes)/60;
	longit = minutes + degrees;				
	
	v = str_to_num(lati);
	minutes = (int)(v/100);
	degrees = (v - (double) minutes)/60;
	latit = minutes + degrees;

	m = Update_distance(latit , longit);
	

				}
			}
		}
		  
	} while ( m < 100);
	 
}
int d;
double prev_lat = 0 ;
double prev_lon = 0 ;
double Total_distance = 0;
int Update_distance(double lati, double loni){
        
    if ((prev_lat != 0 ) && (prev_lon != 0)){
		  while( Total_distance < 100){
         Total_distance += distance(prev_lat , prev_lon, loni ,lati );
           prev_lat = lati;
           prev_lon = loni;
					delay();		
			check();	
}				
		    d = (int) Total_distance;
	LED(d);
  segment_display(d);
  
		   
        }   		
			prev_lat = lati;
      prev_lon = loni;
				delay();
				check();
			return d;						
		  } 

int main (){  
	LED_init();
  portB_Int();
  portE_Int();
  portA_Int();
	UART_Init();
	check();
		
	}