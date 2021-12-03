
#ifndef __mbsFuncCmd_H
#define __mbsFuncCmd_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
	 

// Возврат ответа на запрос с функцией получения серии регистров (0x03)
FuncRes mbs_FuncCmd(void);

#ifdef __cplusplus
}
#endif
#endif
