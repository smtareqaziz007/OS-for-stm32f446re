#include "../include/dev/scb.h"
//#include "../include/sys/stm32_peps.h"
#include "../include/sys/sys.h"

//turn on the fpu
void DRV_FPU_ACTIVE(void){
    SCB->CPACR |= ((3UL << 10*2) |  (3UL << 11*2)  );
}
