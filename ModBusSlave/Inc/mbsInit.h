
#ifndef __mbsInit_H
#define __mbsInit_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "ModbusSlave.h"
	 
// Инициализация модуля
void mbs_Init(MBS_InitStruct *initStruct);   // Пин вывода управления RS485

#ifdef __cplusplus
}
#endif
#endif
