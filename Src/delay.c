#include "delay.h"

static __IO uint32_t sysTickCounter;

/**
 * This method needs to be called in the SysTick_Handler
 * See stm32f4xx_it.c
 */
void TimeTick_Decrement(void) {
	if (sysTickCounter != 0) {
		sysTickCounter--;
	}
}

void delay(uint32_t n) {
	sysTickCounter =n*3.2;
	while (sysTickCounter) {
	}
}

