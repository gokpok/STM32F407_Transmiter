
#ifndef __mbmInterrupt_H
#define __mbmInterrupt_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"

void mbm_UsartInterrupt(USART_TypeDef *uart);    // ���������� ���������� �� USART
void mbm_TimInterrupt(TIM_TypeDef *tim);         // ���������� ���������� �� �������

#ifdef __cplusplus
}
#endif
#endif
