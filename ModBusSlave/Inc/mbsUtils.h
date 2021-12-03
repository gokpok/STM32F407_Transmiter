
#ifndef __mbsUtils_H
#define __mbsUtils_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "ModbusSlave.h"
	 
// Проверка доступности серии запрашиваемых данных
FuncRes mbs_CheckQuerySeries(void);

#ifdef __cplusplus
}
#endif
#endif
