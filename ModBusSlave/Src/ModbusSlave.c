
// ------------------------------------------------------------------------------------------------
// Модуль обмена данными по протоколу ModbusRTU в режиме slave-устройства
// Разработчик ПО Сынышин Э. М. (edmahalich@yandex.ua)
// 
// Подмодуль интерфейса модуля
// ------------------------------------------------------------------------------------------------

#include "ModbusSlave.h"
#include "mbsInit.h"
#include "mbsInterrupt.h"
#include "mbsHandler.h"



// Инициализация slave-усройства ------------------------------------------------------------------
void MBS_Init(MBS_InitStruct *initStruct)
{
	mbs_Init(initStruct);
} // MBS_Init()



// Обработчик slave-устройства --------------------------------------------------------------------
FuncRes MBS_Handler(void)
{
	return mbs_Handler();
} // MBS_Handler()



// Обработчик прерывания по USATR (прием/передача) ------------------------------------------------
void MBS_UART_Interrupt()
{
	mbs_UsartInterrupt();
} // MBS_UART_Interrupt()



// Обработчик прерывания по TIM (завершение приема) ------------------------------------------------
void MBS_TIM_Interrupt(void)
{
	mbs_TimInterrupt();
} // MBS_TIM_Interrupt()


