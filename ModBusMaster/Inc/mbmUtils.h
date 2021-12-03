
#ifndef __mbmUtils_H
#define __mbmUtils_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
	 
// Проверка таймаута ожидания ответа
FuncRes mbm_CheckTimeout(void);
	 
// Проверка контрольной суммы
FuncRes mbm_CheckCRC(void);

#ifdef __cplusplus
}
#endif
#endif
