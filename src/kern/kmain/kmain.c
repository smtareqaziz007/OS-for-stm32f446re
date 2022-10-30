#include "../include/sys_init.h"
#include "../include/kmain.h"
#include "../include/kstdio.h"
#include "../arch/stm32f446re/include/sys/sys.h"
#include "../arch/stm32f446re/include/dev/timer.h"
#include <stdint.h>

void testEnableDisableFaultIRQ(void);
void testSetPriorityGetPriority(void);
void testEnableDisableIRQ(void);
void testSetPrimaskGetPrimask(void);
void testSetBASEPRIunsetBASEPRI(void);
void testEnableIRQnAndGetActive(void);
void testFaultMask(void);
void testEnableNVICdisableNVIC(void);

void func(){

	uint32_t a = 2 , b = 3;
	a = a + b;
	for(uint32_t i = 0 ; i < 700000 ; i++){}
}

void kmain(void)
{
	__sys_init();
	sysTick_init(1800000);

	uint32_t cases = 12;
	//uint32_t a = 12345678;
    //float x = 9.09;
    // uint8_t c[100];
    // char ch;

	kprintf((uint8_t*)"%s",(uint8_t*)"\n\n\n");
	kprintf((uint8_t*)"%s",(uint8_t*)"-----------------------------");
	kprintf((uint8_t*)"%s",(uint8_t*)"\n");

	kprintf((uint8_t*)"%s",(uint8_t*)"Booting duOS: ");
	kprintf((uint8_t*)"%s",(uint8_t*)"Version: 1.0\n");
	kprintf((uint8_t*)"%s",(uint8_t*)"Welcome .... \n");

	while(cases--){

		kprintf((uint8_t*)"%s",(uint8_t*)"\n");
		kprintf((uint8_t*)"%s",(uint8_t*)"1. Test set priority get priority\n");
		kprintf((uint8_t*)"%s",(uint8_t*)"2. Test enable disable IRQ\n");
		kprintf((uint8_t*)"%s",(uint8_t*)"3. Test set primask get primask\n");
		kprintf((uint8_t*)"%s",(uint8_t*)"4. Test set basepri unset basepri\n");
		kprintf((uint8_t*)"%s",(uint8_t*)"5. Test enable IRQn and get active\n");
		kprintf((uint8_t*)"%s",(uint8_t*)"6. Test Faultmask\n");
		kprintf((uint8_t*)"%s",(uint8_t*)"7. Test enable disable fault IRQ\n");
		kprintf((uint8_t*)"%s",(uint8_t*)"8. Test enable disable NVIC IRQn\n");
		kprintf((uint8_t*)"%s",(uint8_t*)"9. Exit\n\n");
		kprintf((uint8_t*)"%s",(uint8_t*)"choose option : ");

		int op;
		kscanf((uint8_t*) "%d", (uint8_t*) &op);
		kprintf((uint8_t *)"%s", (uint8_t *)"\n");

		if (op == 1) testSetPriorityGetPriority();
		
		else if(op == 2) testEnableDisableIRQ();

		else if(op == 3) testSetPrimaskGetPrimask();

		else if(op == 4) testSetBASEPRIunsetBASEPRI();

		else if(op == 5) testEnableIRQnAndGetActive();

		else if(op == 6) testFaultMask();

		else if(op == 7) testEnableDisableFaultIRQ();

		else if(op == 8) testEnableNVICdisableNVIC();

		else if(op == 9) break;

		for(int i = 0; i < 50000000; i++);		

	}
}

void testGetTimeFunc()
{
	uint32_t prv = getTime();

	kprintf((uint8_t *)"%s", (uint8_t *)"Cur time : ");
	kprintf((uint8_t *)"%d", (uint8_t *)&prv);
	kprintf((uint8_t *)"%s", (uint8_t *)"\n");

	for (uint32_t i = 0; i < 50000000; i++)
	{
	}

	uint32_t cur = getTime();

	uint32_t passed = cur - prv;

	kprintf((uint8_t *)"%d", (uint8_t *)&passed);
	kprintf((uint8_t *)"%s", (uint8_t *)" millisecond passed.\n");

	kprintf((uint8_t *)"%s", (uint8_t *)"Cur time : ");
	kprintf((uint8_t *)"%d", (uint8_t *)&cur);
	kprintf((uint8_t *)"%s", (uint8_t *)"\n");

	kprintf((uint8_t *)"%s", (uint8_t *)"---------------------------------------------\n");
}

void testEnableDisableFaultIRQ()
{
	kprintf((uint8_t *)"%s", (uint8_t *)"*************   Test Enable Disable Fault IRQ  *************\n");

	int priority = 3;
	__NVIC_SetPriority(SysTick_IRQn, priority);

	kprintf((uint8_t *)"%s", (uint8_t *)"Setting priority for systick = ");
	kprintf((uint8_t *)"%d", (uint8_t *)&priority);
	kprintf((uint8_t *)"%s", (uint8_t *)"\n");
	kprintf((uint8_t *)"%s", (uint8_t *)"---------------------------------------------\n");

	testGetTimeFunc();

	__enable_fault_irq(); //masking

	kprintf((uint8_t *)"%s", (uint8_t *)"Enabling Faultmask\n");
	kprintf((uint8_t *)"%s", (uint8_t *)"---------------------------------------------\n");

	testGetTimeFunc();

	__disable_fault_irq(); //sets faultmask to 0 (unmasking)

	kprintf((uint8_t *)"%s", (uint8_t *)"Disabling Faultmask\n");
	kprintf((uint8_t *)"%s", (uint8_t *)"---------------------------------------------\n");

	
	testGetTimeFunc();

	/* __disable_fault_irq();

	testGetTimeFunc(); */
}

void testSetPriorityGetPriority()
{
	kprintf((uint8_t *)"%s", (uint8_t *)"*************   TestSetPriorityGetPriority  *************\n");
	
	int priority = 3;
	kprintf((uint8_t *)"%s", (uint8_t *)"Setting priority for systick = ");
	kprintf((uint8_t *)"%d", (uint8_t *)&priority);
	kprintf((uint8_t *)"%s", (uint8_t *)"\n");

	__NVIC_SetPriority(SysTick_IRQn, priority);
	uint32_t x = __NVIC_GetPriority(SysTick_IRQn);

	kprintf((uint8_t *)"%s", (uint8_t *)"Got priority for systick = ");
	kprintf((uint8_t*)"%d",(uint8_t*)&x);
	kprintf((uint8_t *)"%s", (uint8_t *)"\n\n");
}


void testEnableDisableIRQ()
{
	kprintf((uint8_t *)"%s", (uint8_t *)"*************   TestEnableDisableIRQ  *************\n");
	testGetTimeFunc();

	kprintf((uint8_t *)"%s", (uint8_t *)"-----------------Disabling IRQ---------------\n");
	kprintf((uint8_t *)"%s", (uint8_t *)"---------------------------------------------\n");

	__disable_irq(); //masking

	testGetTimeFunc();

	kprintf((uint8_t *)"%s", (uint8_t *)"-----------------Enabling  IRQ---------------\n");
	kprintf((uint8_t *)"%s", (uint8_t *)"---------------------------------------------\n");

	__enable_irq(); //unmasking

	testGetTimeFunc();
}


void testSetPrimaskGetPrimask()
{
	kprintf((uint8_t *)"%s", (uint8_t *)"*************   TestSetPrimaskGetPrimask  *************\n");

	testGetTimeFunc();

	__set_PRIMASK(1); //masking

	uint32_t primask_val = __get_PRIMASK();

	kprintf((uint8_t *)"%s", (uint8_t *)"Primask Val : ");
	kprintf((uint8_t *)"%d", (uint8_t *)&primask_val);
	kprintf((uint8_t *)"%s", (uint8_t *)"\n");

	testGetTimeFunc();

	__enable_irq(); //unmasking

	primask_val = __get_PRIMASK();

	kprintf((uint8_t *)"%s", (uint8_t *)"Primask Val : ");
	kprintf((uint8_t *)"%d", (uint8_t *)&primask_val);
	kprintf((uint8_t *)"%s", (uint8_t *)"\n");

	testGetTimeFunc();


}


void testSetBASEPRIunsetBASEPRI()
{

	kprintf((uint8_t *)"%s", (uint8_t *)"*************   TestSetBASEPRIunsetBASEPRI  *************\n");

	int priority = 4 , base_pri = 3;
	__NVIC_SetPriority(SysTick_IRQn, priority);

	testGetTimeFunc();

	kprintf((uint8_t *)"%s", (uint8_t *)"Setting priority for systick = ");
	kprintf((uint8_t *)"%d", (uint8_t *)&priority);
	kprintf((uint8_t *)"%s", (uint8_t *)"\n");
	kprintf((uint8_t *)"%s", (uint8_t *)"---------------------------------------------\n");

	__set_BASEPRI(3); //masking

	kprintf((uint8_t *)"%s", (uint8_t *)"Setting base priority = ");
	kprintf((uint8_t *)"%d", (uint8_t *)&base_pri);
	kprintf((uint8_t *)"%s", (uint8_t *)"\n");
	kprintf((uint8_t *)"%s", (uint8_t *)"---------------------------------------------\n");

	testGetTimeFunc();

	__unset_BASEPRI(3); //unmasking

	kprintf((uint8_t *)"%s", (uint8_t *)"Unsetting base priority\n");
	kprintf((uint8_t *)"%s", (uint8_t *)"---------------------------------------------\n");

	testGetTimeFunc();
}

void testEnableNVICdisableNVIC()
{
	kprintf((uint8_t *)"%s", (uint8_t *)"*************   TestEnableNVICdisableNVIC  *************\n");

	testGetTimeFunc();

	//__NVIC_DisableIRQn(SysTick_IRQn);
	sysTickInterruptDisable();

	testGetTimeFunc();

	//__NVIC_EnableIRQn(SysTick_IRQn);
	sysTickInterruptEnable();

	testGetTimeFunc();
}

void testEnableIRQnAndGetActive()
{
	kprintf((uint8_t *)"%s", (uint8_t *)"*************   TestEnableIRQAndGetActive  *************\n");
	DRV_TIMER_INIT();
	// for(int i = 0; i < 1000000; i++);
	// __NVIC_DisableIRQn(TIM7_IRQn);
}

void testFaultMask()
{
	kprintf((uint8_t *)"%s", (uint8_t *)"*************   Test Fault Mask *************\n");

	int priority = 3;
	__NVIC_SetPriority(SysTick_IRQn, priority);

	kprintf((uint8_t *)"%s", (uint8_t *)"Setting priority for systick = ");
	kprintf((uint8_t *)"%d", (uint8_t *)&priority);
	kprintf((uint8_t *)"%s", (uint8_t *)"\n");
	kprintf((uint8_t *)"%s", (uint8_t *)"---------------------------------------------\n");

	testGetTimeFunc();

	__set_FAULTMASK(1); //masking


	kprintf((uint8_t *)"%s", (uint8_t *)"Setting Faultmask\n");
	kprintf((uint8_t *)"%s", (uint8_t *)"---------------------------------------------\n");

	testGetTimeFunc();

	__set_FAULTMASK(0);//unmasking
	

	kprintf((uint8_t *)"%s", (uint8_t *)"Unsetting Faultmask\n");
	kprintf((uint8_t *)"%s", (uint8_t *)"---------------------------------------------\n");

	testGetTimeFunc();
}





	    /*kprintf((uint8_t*)"%s",(uint8_t*)"Enter an integer : ");
        kscanf((uint8_t*) "%d", (uint8_t*) &a);
		kprintf((uint8_t*)"%s", (uint8_t*) "Input : ");
		kprintf((uint8_t*)"%d", (uint8_t*) &a);
        kprintf((uint8_t*)"%s",(uint8_t*)"\n");


	    kprintf((uint8_t*)"%s",(uint8_t*)"Enter a character : ");
        kscanf((uint8_t*) "%c", (uint8_t*) &ch);
		kprintf((uint8_t*)"%s", (uint8_t*) "Input : ");
		kprintf((uint8_t*)"%c", (uint8_t*) &ch);
        kprintf((uint8_t*)"%s",(uint8_t*)"\n");

	    kprintf((uint8_t*)"%s",(uint8_t*)"Enter a string : ");
        kscanf((uint8_t*) "%s", (uint8_t*) c);
		kprintf((uint8_t*)"%s", (uint8_t*) "Input : ");
		kprintf((uint8_t*)"%s", (uint8_t*) c);
        kprintf((uint8_t*)"%s",(uint8_t*)"\n");

	    kprintf((uint8_t*)"%s",(uint8_t*)"Enter a hex : ");
        kscanf((uint8_t*) "%x", (uint8_t*) &a);
		kprintf((uint8_t*)"%s", (uint8_t*) "Input : ");
		kprintf((uint8_t*)"%x", (uint8_t*) &a);
        kprintf((uint8_t*)"%s",(uint8_t*)"\n");

	    kprintf((uint8_t*)"%s",(uint8_t*)"Enter a float : ");
        kscanf((uint8_t*) "%f", (uint8_t*) &x);
		kprintf((uint8_t*)"%s", (uint8_t*) "Input : ");
		kprintf((uint8_t*)"%f", (uint8_t*) &x);
        kprintf((uint8_t*)"%s",(uint8_t*)"\n");
		*/


		/* uint32_t t1 = getTime();
		
		kprintf((uint8_t*)"%d", (uint8_t*) &t1);
		kprintf((uint8_t*)"%s",(uint8_t*)"\n");

		func();

		uint32_t t2 = getTime();

		kprintf((uint8_t*)"%d", (uint8_t*) &t2);
		kprintf((uint8_t*)"%s",(uint8_t*)"\n");

		uint32_t x = t2 - t1;

		kprintf((uint8_t*)"%s",(uint8_t*)"Required time : ");
		kprintf((uint8_t*)"%d", (uint8_t*) &x);
		kprintf((uint8_t*)"%s",(uint8_t*)"\n");
 		

		uint32_t t3 = getTime();

		for(; getTime() - t3 < 1000 ; ){}
 */