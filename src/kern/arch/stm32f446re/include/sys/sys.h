#ifndef __SYS_H
#define __SYS_H
#include<stdint.h>

#define STK  ((SysTick_Typedef*) 0xE000E010)

volatile uint32_t mscount;

typedef struct 
{
	volatile uint32_t CTRL;  // enable SysTick , clock sourcee , systick interrupt and count flag
	volatile uint32_t LOAD;  // 24 bits reload register , maximum count
	volatile uint32_t VAL;   // 24 bits current value register
	volatile uint32_t CALIB; // Calibration Register
}SysTick_Typedef;

void sysTick_init();
void sysTick_Enable(void);
void sysTick_Disable(void);
uint32_t getSysTickCount(void);
void updateSysTickCount(uint32_t);
uint32_t getTime(void);
void SysTick_Handler(void);

#endif