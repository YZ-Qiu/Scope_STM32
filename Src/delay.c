#include "delay.h"
#include "cmsis_os.h"
static __IO uint32_t sysTickCounter;

/**
 * This method needs to be called in the SysTick_Handler
 * See stm32f4xx_it.c
 */

inline void delay(uint32_t n) {
	osDelay(n);
}

