#ifndef __KSTDIO_H
#define __KSTDIO_H

#include <stdint.h>
#include "../arch/stm32f446re/include/dev/usart.h"

void kprintf(uint8_t*,uint8_t*); 
void kscanf(uint8_t*,uint8_t *);

#endif /* KSTDIO */

