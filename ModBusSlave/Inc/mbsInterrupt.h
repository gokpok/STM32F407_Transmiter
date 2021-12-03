
#ifndef __mbsInterrupt_H
#define __mbsInterrupt_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"

void mbs_UsartInterrupt(void);    // Обработчик прерывыний от USART slave
void mbs_TimInterrupt(void);      // Обработчик прерываний от таймера slave

#ifdef __cplusplus
}
#endif
#endif
