#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f4xx.h"

void SysTick_Init(void);
void TimeTick_Decrement(void);
void delay(uint32_t n);

#endif
