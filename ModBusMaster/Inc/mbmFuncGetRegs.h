
#ifndef __mbmFuncGetRegs_H
#define __mbmFuncGetRegs_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
	 

// ���������� ������� � �������� ��������� ����� ��������� (0x03)
FuncRes mbm_FuncGetRegs(uint8_t addr, uint16_t first, uint16_t quant, uint16_t *data);

#ifdef __cplusplus
}
#endif
#endif
