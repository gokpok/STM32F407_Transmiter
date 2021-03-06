
// ------------------------------------------------------------------------------------------------
// ?????? ?????? ??????? ?? ????????? ModbusRTU ? ?????? master-??????????
// ??????????? ?? ??????? ?. ?. (edmahalich@yandex.ua)
// 
// ????????? ????????? ??????????
// ------------------------------------------------------------------------------------------------

#include "mbmInterrupt.h"
#include "mbmData.h"

uint16_t  mbmRxCount = 0;     // ??????? ???????? ??????
uint16_t  mbmTxCount = 0;     // ??????? ????????? ??????

void mbm_RxInterrupt(void);      // ????? ?????? ?? USART
void mbm_TxInterrupt(void);      // ???????? ?????? ?? USART



// ????????? ?????????? ?? USART ------------------------------------------------------------------
void mbm_UsartInterrupt(USART_TypeDef *uart)
{	
	// ????????? ????????? ?????????????? ???? ??????????
	if(uart->SR & USART_SR_TC)
		// ???????????? ????????
		mbm_TxInterrupt();                  
	else if(uart->SR & USART_SR_RXNE)
		// ???????????? ?????
		mbm_RxInterrupt(); 

	// ?????????? ??????????
	uart->SR = 0;	
} // mbm_UsartInterrupt



// ????????? ?????????? ?? TIM --------------------------------------------------------------------
void mbm_TimInterrupt(TIM_TypeDef *tim)
{
	// ????????????? ??????
	tim->CR1 &=~ TIM_CR1_CEN;	
	
	// ?????????? ??????????
	tim->SR = 0;
	
	// ?????????? ???????? ?????????? ???????? ?????? ?????? (????? ??????):
	mbmRxLen = mbmRxCount;   // ?????????? ?????? ??????
	mbmRxCount = 0;	         // ?????????? ??????? ?????????? ??????
	mbmEndReciev = 1;        // ?????? ???? ????????? ??????
} // mbm_TimInterrupt()



// ????? ?????? ?? USART --------------------------------------------------------------------------
void mbm_RxInterrupt(void)
{
	// ????????? ?????????? ????? ?? ?????? USART
	mbmRxBuf[mbmRxCount] = mbmUart->DR;

	mbmRxCount++;				// ??????????? ??????? ?????????? ??????

	// ????????????? ?????? ?????????? ?????? (????? ????????????)
	mbmTim->CNT = 0;             // ?????????? ??????? ???????
	mbmTim->CR1 |= TIM_CR1_CEN;  // ????????? ??????
} // mbm_RxInterrupt()



// ???????? ?????? ?? USART -----------------------------------------------------------------------
void mbm_TxInterrupt(void)
{	
	// ???? ???????? ?????? ????, ??
	// ???????? ??? ?????????? ? ???????? ????? (?????????:)
//	if(mbmTxCount == 0)
//	{
//		MBM_DIR_ON;
//		for(int i = 0; i < 8; i++) __NOP();
//	} // if
	
	// ????????? ????? ?????? ?????? ? USART
	if (mbmTxCount >= mbmTxLen)
	{
		// ???? ???????? ????????:		
		MBM_DIR_OFF;  // ????????? ??? ??????????
		mbmTxCount = 0;  // ?????????? ??????? ???????????? ??????
	} else
	{
		// ???? ???????? ?? ????????, ??...				
		mbmUart->DR = mbmTxBuf[mbmTxCount];  // ?????????? ????????? ????? ? ????? USART
		mbmTxCount++;                         // ??????????? ??????? ???????????? ??????
	} // if-else
} // mbm_TxInterrupt()
