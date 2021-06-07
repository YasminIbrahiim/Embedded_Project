#include<stdio.h>
#include<math.h>
#include <stdint.h>
#include "c:\Users\ea\Downloads\tm4c123gh6pm.h"
void UART_Init(void){
SYSCTL_RCGCUART_R |= 0x00000002;
SYSCTL_RCGCGPIO_R |= 0x00000002;
while((SYSCTL_PRGPIO_R&0x00000002)==0){};
UART1_IBRD_R = 104;	
UART1_FBRD_R = 11;
GPIO_PORTB_CR_R = 0x03;
GPIO_PORTB_DEN_R |= 0x03;
GPIO_PORTB_DIR_R |= 0x02;
GPIO_PORTB_AFSEL_R |=0x03 ; 	
GPIO_PORTB_AMSEL_R &=~0x03 ; 
UART1_LCRH_R =0x00000070 ;	
GPIO_PORTB_PCTL_R |= 0x00000011;
UART1_CTL_R |= 0x301; 	
}
uint8_t InChar(void){
while((UART1_FR_R&0x0010)!=0){};
	return((uint8_t)(UART1_DR_R&0xFF));
}



int main(){
UART_Init();
InChar();
}





















