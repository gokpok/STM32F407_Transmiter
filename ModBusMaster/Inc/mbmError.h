
#ifndef __mbmError_H
#define __mbmError_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "ModbusMaster.h"
	 

// Обработка ошибки модуля
FuncRes mbm_ErrHandler(MBM_ErrEnum err);

#ifdef __cplusplus
}
#endif
#endif
