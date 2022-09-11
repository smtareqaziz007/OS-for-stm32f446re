#include "../include/sys_init.h"
#include "../include/kmain.h"
#include "../include/kstdio.h"
#include "../arch/stm32f446re/include/sys/sys.h"
#include <stdint.h>

void func(){

	uint32_t a = 2 , b = 3;
	a = a + b;
	for(uint32_t i = 0 ; i < 700000 ; i++){}
}

void kmain(void)
{
	__sys_init();
	sysTick_init(1800000);

	uint32_t cases = 10;
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

		uint32_t t1 = getTime();
		
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

	}
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
