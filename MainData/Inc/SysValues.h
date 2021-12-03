
#ifndef __SysValues_H
#define __SysValues_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "data.h"
#include "main.h"
// Cчетчик системных тиков (глобальное время от старта, мсек)	 
extern uint64_t gTick;
	 
// Состояние связи с master-устройством
extern FuncRes link;
	 
// Адрес slave-устройства
extern uint8_t sAddr;

#ifdef __cplusplus
}
#endif
#endif
