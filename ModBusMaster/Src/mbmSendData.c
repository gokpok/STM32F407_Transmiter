
// ------------------------------------------------------------------------------------------------
// ?????? ?????? ??????? ?? ????????? ModbusRTU ? ?????? master-??????????
// ??????????? ?? ??????? ?. ?. (edmahalich@yandex.ua)
// 
// ?????????, ??????????? ????????? ???????? ?????????????? ??????
// ------------------------------------------------------------------------------------------------

#include "mbmSendData.h"
#include "mbmData.h"

	 
	 extern uint16_t mbmTxCount;
	 
// ????????? ???????? ??????
void mbm_SendDataIni(uint16_t len)
{		
	mbmTxLen = len;           // ?????? ????? ????????????? ??????
	mbmQueryTime = *mbmTime;  // ?????????? ????? ???????? ??????
	mbmAnsWait = 1;           // ?????? ???? ???????? ??????
	
	// ?????????? ?????? ???? ?????? ? UART	
	//mbmUart->DR = mbmTxBuf[0];
	//USART3->CR1 |= USART_CR1_TE; 
	
	if(mbmTxCount == 0)
	{
		MBM_DIR_ON;
		for(int i = 0; i < 8; i++) __NOP();
	} // if
	
	mbmUart->DR = mbmTxBuf[0];
	mbmTxCount++;
	
	// ?????????? ??????? ???????? ?????????????? ? ???????????
} // mbm_SendDataIni()
