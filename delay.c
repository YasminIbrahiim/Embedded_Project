void delay(void){
		NVIC_ST_CTRL_R = 0;
		NVIC_ST_RELOAD_R = 16000000-1;
		NVIC_ST_CURRENT_R = 0;
		NVIC_ST_CTRL_R = 0x05;
		while((NVIC_ST_CTRL_R&0x00010000)==0){};
		}

}