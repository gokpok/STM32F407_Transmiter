
#ifndef __mbsError_H
#define __mbsError_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"
	 
	 
// Перечисление ошибок в запросах
typedef enum
{
	MBS_ERR_BADFUNC   = 0x01,   // Недопустимая функция запроса
	MBS_ERR_BADADDR   = 0x02,   // Адрес данных, указанный в запросе, недоступен
} MBS_ErrEnum;
	 

// Возврат ответа на запрос с ошибкой
void mbs_ReturnErr(MBS_ErrEnum err);

#ifdef __cplusplus
}
#endif
#endif
