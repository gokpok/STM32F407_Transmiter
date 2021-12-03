
// ------------------------------------------------------------------------------------------------
// ������ ������ ������� �� ��������� ModbusRTU � ������ master-����������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// 
// ��������� ������������� ������
// ------------------------------------------------------------------------------------------------

#include "mbmInit.h"
#include "mbmData.h"
#include "ModbusMaster.h"
#include "stdlib.h"



// ������������� ���������� modbus master ---------------------------------------------------------
void mbm_Init(uint8_t maxLen, uint16_t timeout, USART_TypeDef *uart, TIM_TypeDef *tim, 
							GPIO_TypeDef *dirPort, uint16_t dirPin, uint64_t *time)
{
	// ��������� ���������� �������������
	mbmMaxLen  = maxLen;
	mbmTimeout = timeout;
	mbmTime    = time;
	
	// ���������� ������������ ����������
	mbmUart    = uart;
	mbmTim     = tim;
	mbmDirPort = dirPort;
	mbmDirPin  = dirPin;
	
	// �������� ������ ��� ������ ������
	mbmRxBuf = (uint8_t*)  malloc(mbmMaxLen * sizeof(uint8_t) * 2 + 10);
	mbmTxBuf = (uint8_t*)  malloc(mbmMaxLen * sizeof(uint8_t) * 2 + 10);
} // mbm_Init()
