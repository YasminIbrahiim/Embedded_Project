#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h>
#define CR         0x0d
#define LF         0x0a
#include <stdint.h>
#include "E:\Tasneem\imp.docs\tm4c123gh6pm.h"
void SystemInit(){};
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

	
	
								
		
										
								
				
	



