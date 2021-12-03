
// ------------------------------------------------------------------------------------------------
// ������ ������ ������� �� ��������� ModbusRTU � ������ master-����������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// 
// ��������� ���������� ������
// ------------------------------------------------------------------------------------------------

#include "ModbusMaster.h"
#include "mbmInit.h"
#include "mbmInterrupt.h"
#include "mbmFuncGetRegs.h"
#include "mbmFuncSetRegs.h"



// ������������� master-��������� ------------------------------------------------------------------
void MBM_Init(uint8_t maxLen, uint16_t timeout, USART_TypeDef *uart, TIM_TypeDef *tim, GPIO_TypeDef *dirPort, uint16_t dirPin, uint64_t *time)
{
	mbm_Init(maxLen, timeout, uart, tim, dirPort, dirPin, time);
} // MBM_Init()



// ���������� ���������� �� USATR (�����/��������) ------------------------------------------------
void MBM_UART_Interrupt(USART_TypeDef *uart)
{
	mbm_UsartInterrupt(uart);
} // MBM_UART_Interrupt()



// ���������� ���������� �� TIM (���������� ������) -----------------------------------------------
void MBM_TIM_Interrupt(TIM_TypeDef *tim)
{
	mbm_TimInterrupt(tim);
} // MBM_TIM_Interrupt()



// ������� ��������� �������� ����� ��������� �� ���������� ---------------------------------------
FuncRes MBM_GetRegs(uint8_t addr, uint16_t first, uint16_t quant, uint16_t *data)
{
	return mbm_FuncGetRegs(addr, first, quant, data);
} // MBM_GetRegs()


	 
// ������� ������� �������� ����� ��������� �� ���������� -----------------------------------------
FuncRes MBM_SetRegs(uint8_t addr, uint16_t first, uint16_t quant, uint16_t *data)
{
	return mbm_FuncSetRegs(addr, first, quant, data);
} // MBM_SetRegs()


