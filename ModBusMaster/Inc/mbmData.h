
#ifndef __mbmData_H
#define __mbmData_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"


// ����������� ��� ���� ���������� RS485
#define MBM_DIR_ON     HAL_GPIO_WritePin(mbmDirPort, mbmDirPin, GPIO_PIN_SET)
#define MBM_DIR_OFF    HAL_GPIO_WritePin(mbmDirPort, mbmDirPin, GPIO_PIN_RESET)
	 

// �������� ���������� ������
extern uint8_t  *mbmRxBuf;      // ����� ������
extern uint8_t  *mbmTxBuf;      // ����� ��������
extern uint8_t   mbmAnsWait;    // ���� �������� ������
extern uint8_t   mbmEndReciev;  // ���� ���������� ������
extern uint16_t  mbmDataBegin;  // ������ ������������� ������
extern uint16_t  mbmDataNum;    // ������ ������������� ������
extern uint16_t  mbmDataEnd;    // ����� ������������� ������
extern uint16_t  mbmRxLen;      // ������ ����������� ������
extern uint16_t  mbmTxLen;      // ������ ������������� ������
extern uint16_t  mbmCRC;        // ����������� �����
extern uint64_t *mbmTime;       // ������� ���������� �����
extern uint64_t  mbmQueryTime;  // ����� �������� �������
extern uint16_t  mbmCount1;     // 1� ������� ����������� ����
extern uint16_t  mbmCount2;     // 2� ������� ����������� ����


// ���������� ��������� slave-����������
extern USART_TypeDef *mbmUart;     // ����������������
extern TIM_TypeDef   *mbmTim;      // ������ ���������� ������
extern GPIO_TypeDef  *mbmDirPort;  // ���� ������ ���������� RS485
extern uint16_t       mbmDirPin;   // ��� ������ ���������� RS485

#ifdef __cplusplus
}
#endif
#endif
