#include "../include/sys/sys.h"
#include "../include/dev/usart.h"

#define AHB_CLK 180000000
// #define INTERVAL_10ms (AHB_CLK / 100) - 1
// #define INTERVAL_1ms (AHB_CLK / 1000) - 1

void  SysTick_Handler(void)
{
    mscount++;
}

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

void sysTickInterruptEnable(){
  STK->CTRL |= 1 << 1;
}

void sysTickInterruptDisable(){
  STK->CTRL &= ~(1 << 1);
}

void sysTick_init(uint32_t load){

	sysTick_Disable();
	STK->CTRL = 0;
	STK->LOAD = load - 1;
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

	uint32_t delayms = ((STK->LOAD + 1) * 1000) / AHB_CLK; 
	uint32_t ms = mscount * delayms;
	ms += ((STK->LOAD - STK->VAL) * delayms) / (STK->LOAD);
	return ms;
}

void __NVIC_SetPriority (enum IRQn_TypeDef IRQn, uint32_t priority) {
    
    priority=priority & 0xF;
    if ((int32_t)(IRQn) >= 0)
    {
        uint8_t x=(uint8_t)(priority<<4);
        NVIC->IP[IRQn] = x;
    }
    else
    {
      switch(IRQn)
      {
        //Memory management fault
        case -12:
          SCB->SHPR1 &= ~((uint32_t)((0xF<<4)<<0));
          SCB->SHPR1 |= (uint32_t)((priority<<4)<<0);
          break;
        //Bus Fault
        case -11:
          SCB->SHPR1 &= ~((uint32_t)((0xF<<4)<<8));
          SCB->SHPR1 |= (uint32_t)((priority<<4)<<8);
          break;
        //Usage Fault
        case -10:
          SCB->SHPR1 &= ~((uint32_t)((0xF<<4)<<16));
          SCB->SHPR1 |= (uint32_t)((priority<<4)<<16);
          break;
        //SVCall
        case -5:
          SCB->SHPR2 &= ~((uint32_t)((0xF<<4)<<24));
          SCB->SHPR2 |= (uint32_t)((priority<<4)<<24);
          break;
        //PendSV
        case -2:
          SCB->SHPR3 &= ~((uint32_t)((0xF<<4)<<16));
          SCB->SHPR3 |= (uint32_t)((priority<<4)<<16);
          break;
        //SysTick
        case -1:
          SCB->SHPR3 &= ~((uint32_t)((0xF<<4)<<24));
          SCB->SHPR3 |= (uint32_t)((priority<<4)<<24);
          break;
        default:
          return;
        

      }
    }
}

uint32_t __NVIC_GetPriority(enum IRQn_TypeDef IRQn)
{

    if ((int32_t)(IRQn) >= 0)
    {
        uint32_t priority =(uint32_t)(NVIC->IP[IRQn]>>4);
        return priority;
    }
    else
    {
      switch(IRQn)
      {
        //Memory management fault
        case -12:
          return (uint32_t)(((SCB->SHPR1>>0)>>4) & 0xF);
        //Bus Fault
        case -11:
          return (uint32_t)(((SCB->SHPR1>>8)>>4) & 0xF);
        //Usage Fault
        case -10:
          return (uint32_t)(((SCB->SHPR1>>16)>>4) & 0xF);
        //SVCall
        case -5:
          return (uint32_t)(((SCB->SHPR2>>24)>>4) & 0xF);
        //PendSV
        case -2:
          return (uint32_t)(((SCB->SHPR3>>16)>>4) & 0xF);
        //SysTick
        case -1:
          return (uint32_t)(((SCB->SHPR3>>24)>>4) & 0xF);
          break;
        default:
          return 0;
      }
    }
}


uint32_t __NVIC_GetActive(enum IRQn_TypeDef IRQn)
{
    return (NVIC->IABR[IRQn >> 5] & 1 << (IRQn & 0x1F)) != 0;
}

void __NVIC_EnableIRQn(enum IRQn_TypeDef IRQn)
{
    NVIC->ISER[IRQn >> 5] = 1 << (IRQn & 0x1F);
}

void __NVIC_DisableIRQn(enum IRQn_TypeDef IRQn)
{
    NVIC->ICER[IRQn >> 5] = 1 << (IRQn & 0x1F);
}

uint32_t __get_pending_IRQn(enum IRQn_TypeDef IRQn)
{
    return (NVIC->ISPR[IRQn >> 5] & 1 << (IRQn & 0x1F)) != 0;
}

void __clear_pending_IRQn(enum IRQn_TypeDef IRQn)
{
    NVIC->ICPR[IRQn >> 5] = 1 << (IRQn & 0x1F);
}

void __enable_irq()
{
    __set_PRIMASK(0);
}

void __disable_irq()
{
    __set_PRIMASK(1);
}

void __unset_BASEPRI(uint32_t value)
{
    //__set_BASEPRI(0); // don't certain about it
    __asm volatile ("MSR basepri, %0" : : "r" ((uint32_t)0) : "memory");
}

void __set_BASEPRI(uint32_t value)
{
  value =(value & 0xF)<<4; //according to programming manual basepri works on [7:4]
  __asm volatile ("MSR basepri, %0" : : "r" (value) : "memory");
}

uint32_t __get_PRIMASK()
{
  uint32_t result;

  __asm volatile ("MRS %0, primask" : "=r" (result) );
  return result;
}

void __set_PRIMASK(uint32_t priMask)
{
  __asm volatile ("MSR primask, %0" : : "r" (priMask) );
}

uint32_t __get_FAULTMASK()
{
  uint32_t result;

  __asm volatile ("MRS %0, faultmask" : "=r" (result) );
  return result;
}

void __set_FAULTMASK(uint32_t faultMask)
{
  //__asm volatile ("MSR primask, %0" : : "r" (faultMask) );
  __asm volatile ("MSR faultmask, %0" : : "r" (faultMask) );
}

void __enable_fault_irq()
{
    __set_FAULTMASK(1);
}

void __disable_fault_irq()
{
    __set_FAULTMASK(0);
}

void __enable_primask()
{
    __set_PRIMASK(1);
}

void __disable_primask()
{
    __set_PRIMASK(0);
}


//uint32_t ms = mscount * (1000 * (STK->LOAD + 1)) / AHB_CLK;