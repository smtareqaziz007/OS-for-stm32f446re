#include "../include/sys/sys.h"
#include "../include/dev/usart.h"

#define AHB_CLK 180000000
#define INTERVAL_10ms (AHB_CLK / 100) - 1
#define INTERVAL_1ms (AHB_CLK / 1000) - 1
volatile uint32_t mscount;

void sysTick_Enable(){

	if(STK->CTRL & 1 << 0) return;

	else{

		mscount = 0;
		STK->CTRL |= 1 << 0;
		//_USART_WRITE(USART2, (uint8_t *) "Enable korchi\n\r");
	}
}

void sysTick_Disable(){

	STK->CTRL &= ~(1 << 0);
}

void sysTick_init(){

	sysTick_Disable();
	STK->CTRL = 0;
	STK->LOAD = INTERVAL_10ms;
	STK->VAL = 0;
	mscount = 0;
	STK->CTRL |= 7 << 0;
	//sysTick_Enable();
}

uint32_t getSysTickCount(){

	return STK->VAL;
}


void updateSysTickCount(uint32_t reload){

	sysTick_Disable();
	STK->LOAD = reload - 1;
	STK->VAL = 0;
}

uint32_t getTime(){

	uint32_t ms = mscount * 10;
	ms += ((STK->LOAD - STK->VAL) * 10) / (STK->LOAD);
	return ms;
}



//uint32_t ms = mscount * (1000 * (STK->LOAD + 1)) / AHB_CLK;