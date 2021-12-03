
#ifndef __mbsFuncSetRegs_H
#define __mbsFuncSetRegs_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "ModbusSlave.h"
	 

// Возврат ответа на запрос с функцией получения серии регистров (0x03)
FuncRes mbs_FuncSetRegs(void);

#ifdef __cplusplus
}
#endif
#endif
