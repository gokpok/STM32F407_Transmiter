
#ifndef __mbmFuncSetRegs_H
#define __mbmFuncSetRegs_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
	 

// Выполнение запроса с функцией получения серии регистров (0x03)
FuncRes mbm_FuncSetRegs(uint8_t addr, uint16_t first, uint16_t quant, uint16_t *data);

#ifdef __cplusplus
}
#endif
#endif
