
#ifndef __ModbusMaster_H
#define __ModbusMaster_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
	 
	 
	 
// ������������ �������������� ������ ������
typedef enum
{
	MBM_FUNC_GET_REGS = 0x03,   // ��������� �������� ����� ���������
	MBM_FUNC_SET_REGS = 0x10,	  // ������� �������� ����� ���������
} MBM_FuncsEnum;


	 
// ������������ ������ ������
typedef enum
{
	MBM_ERR_NONE      = 0,   // ���������� ������
	
	MBM_ERR_BADFUNC   = 1,   // ������������ ������� �������
	MBM_ERR_BADADDR   = 2,   // ����� ������, ��������� � �������, ����������
	
	MBM_ERR_TIMEOUT   = 100,   // ������� �������� ������
	MBM_ERR_MAX_LEN   = 101,   // ���������� ���������� ������ ������
	MBM_ERR_ANSWER    = 102,   // ��������� �����
} MBM_ErrEnum;


	 
extern uint8_t     mbmMaxLen;     // ������������ ������ ������
extern uint16_t    mbmTimeout;    // �������� �������� ������ slave-����������
extern MBM_ErrEnum mbmErr;        // ������ ����������
	 
	 
// ������������� master-���������
void MBM_Init(uint8_t maxLen, uint16_t timeout, USART_TypeDef *uart, TIM_TypeDef *tim, GPIO_TypeDef *dirPort, uint16_t dirPin, uint64_t *time);
	 
// ���������� ���������� �� USATR (�����/��������)
void MBM_UART_Interrupt(USART_TypeDef *uart);
	 
// ���������� ���������� �� TIM (���������� ������)
void MBM_TIM_Interrupt(TIM_TypeDef *tim);
	 
// ������� ��������� �������� ����� ��������� �� ����������
FuncRes MBM_GetRegs(uint8_t addr, uint16_t first, uint16_t quant, uint16_t *data);
	 
// ������� ������� �������� ����� ��������� �� ����������
FuncRes MBM_SetRegs(uint8_t addr, uint16_t first, uint16_t quant, uint16_t *data);
	 

#ifdef __cplusplus
}
#endif
#endif
