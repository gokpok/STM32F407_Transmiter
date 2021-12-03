
// ------------------------------------------------------------------------------------------------
// Модуль обмена данными по протоколу ModbusRTU в режиме slave-устройства
// Разработчик ПО Сынышин Э. М. (edmahalich@yandex.ua)
// 
// Подмодуль, предоставляющий вспомагательные функции модуля
// ------------------------------------------------------------------------------------------------

#include "mbmUtils.h"
#include "mbmError.h"
#include "mbmData.h"
#include "mbsCRC.h"



// Проверка таймаута ожидания ответа
FuncRes mbm_CheckTimeout(void)
{
	// Если время ожидания ответа не истекло - уходим без результата
	if(*mbmTime < (mbmQueryTime + mbmTimeout))
		return FRES_NONE;
	
	return mbm_ErrHandler(MBM_ERR_TIMEOUT);
} // mbm_CheckTimeout()


	 
// Проверка контрольной суммы ---------------------------------------------------------------------
FuncRes mbm_CheckCRC(void)
{
	// Подсчет контрольной суммы принятых данных
	mbmCRC = mbs_GetCrc16(mbmRxBuf, (mbmRxLen - 2));
	
	// Сравниваем полученную сумму с заяваленной в запросе
	if((mbmRxBuf[mbmRxLen - 2] == (mbmCRC & 0x00ff)) && (mbmRxBuf[mbmRxLen - 1] == (mbmCRC >> 8)))
		return FRES_OK;
	else
		return FRES_ERR;
} // mbm_CheckCRC()
