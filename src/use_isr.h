#ifndef __USE_ISR_H__
#define __USE_ISR_H__

#include "config.h"

INTERRUPT(UART1_ISR_Handler, UART1_VECTOR);
INTERRUPT(Timer0_ISR_Handler, TMR0_VECTOR);

#endif