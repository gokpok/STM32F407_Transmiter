
#ifndef __mbmUtils_H
#define __mbmUtils_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
	 
// �������� �������� �������� ������
FuncRes mbm_CheckTimeout(void);
	 
// �������� ����������� �����
FuncRes mbm_CheckCRC(void);

#ifdef __cplusplus
}
#endif
#endif
