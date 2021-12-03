
#ifndef __data_H
#define __data_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"
	 
// Подключаем дочерние модули
#include "SysBuffer.h"
#include "SysValues.h"


void MainDataInit(uint16_t mDataLen);   // Инициализация модуля основных данных системы
	 
	 
#ifdef __cplusplus
}
#endif
#endif
