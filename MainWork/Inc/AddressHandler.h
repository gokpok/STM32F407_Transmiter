
#ifndef __AddressHandler_H
#define __AddressHandler_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"
	 

// Обработчик ошибок устройства
void AddrHandler(uint8_t *addr);

#ifdef __cplusplus
}
#endif
#endif
