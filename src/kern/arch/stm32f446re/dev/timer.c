#include "../include/dev/timer.h"
#include "../include/sys/sys.h"
#include "../../../include/kstdio.h"
void DRV_TIMER_INIT()
{
    RCC->APB1ENR |= (1 << 5);
	
	TIM7->PSC = (90 - 1);
	
	TIM7->ARR = 1000;
	
	TIM7->CR1 |= (1UL << 0);
	
	TIM7->DIER |= (1);
	
	while(!(TIM7->SR & (1<<0)));
	
    __NVIC_EnableIRQn(TIM7_IRQn);

}

void TIM7_Handler(void)
{
	kprintf((uint8_t *)"%s", (uint8_t *)"TIM7 is here\n");
	uint32_t val = __NVIC_GetActive(TIM7_IRQn);
	kprintf((uint8_t *)"%s", (uint8_t *)"bit value : ");
	kprintf((uint8_t *)"%d", (uint8_t *)&val);
	kprintf((uint8_t *)"%s", (uint8_t *)"\n");
	// for(int i = 0; i < 1000000; i++);
	__NVIC_DisableIRQn(TIM7_IRQn);
	
}


