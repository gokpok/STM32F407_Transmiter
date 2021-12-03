
// ------------------------------------------------------------------------------------------------
// Модуль обмена данными по протоколу ModbusRTU в режиме master-устройства
// Разработчик ПО Сынышин Э. М. (edmahalich@yandex.ua)
// 
// Подмодуль, выполняющий запрос с функцией получения значений серии регистров (0x03)
// ------------------------------------------------------------------------------------------------

#include "mbmFuncGetRegs.h"
#include "ModbusMaster.h"
#include "mbmSendData.h"
#include "mbmError.h"
#include "mbmUtils.h"
#include "mbmData.h"
#include "mbsCRC.h"


// Отправка запроса на выполнение функции
FuncRes QueryGetRegs(uint8_t addr, uint16_t first, uint16_t quant);

// Обработка ответа
FuncRes AnswerGetRegs(uint8_t addr, uint16_t quant, uint16_t *data);

// Получение запрошенных данных
void mbm_GetRegs(uint16_t quant, uint16_t *data);

	 

// Выполнение запроса с функцией получения серии регистров (0x03) ---------------------------------
FuncRes mbm_FuncGetRegs(uint8_t addr, uint16_t first, uint16_t quant, uint16_t *data)
{	
	// Если модуль не ожидает ответ - отправляем запрос
	if(mbmAnsWait == 0) return QueryGetRegs(addr, first, quant);
	
	// Если предыдущие условия не сработали - обрабатываем ответ
	return AnswerGetRegs(addr, quant, data);
} // mbs_FuncGetRegs()



// Отправка запроса на выполнение функции ---------------------------------------------------------
FuncRes QueryGetRegs(uint8_t addr, uint16_t first, uint16_t quant)
{
	// Если кол-во запрошенных данных превышает допустимое - уходим с ошибкой
	if(quant > mbmMaxLen)
		return mbm_ErrHandler(MBM_ERR_MAX_LEN);
	
	// формируем пакет запроса
	mbmTxBuf[0] = addr;               // Адрес устройства
	mbmTxBuf[1] = MBM_FUNC_GET_REGS;  // Код команды чтения регистров
	mbmTxBuf[2] = first >> 8;         // Начало запрашиваемых регистров
	mbmTxBuf[3] = first & 0x00FF;     // --- *** ---
	mbmTxBuf[4] = quant >> 8;         // Кол-во запрашиваемых регистров
	mbmTxBuf[5] = quant & 0x00FF;     // --- *** ---
	
	// Получаем контрольную сумму сформированного запроса и добавляем в конец пакета
	mbmCRC = mbs_GetCrc16(mbmTxBuf, 6);
	mbmTxBuf[6] = mbmCRC & 0x00ff;
	mbmTxBuf[7] = mbmCRC >> 8;	
	
	// Инициируем отправку данных
	mbm_SendDataIni(8);
	
	return FRES_NONE;
} // QueryGetRegs()



// Обработка ответа -------------------------------------------------------------------------------
FuncRes AnswerGetRegs(uint8_t addr, uint16_t quant, uint16_t *data)
{
	// Если принятых данных нет - возвращаем результат проверки таймаута
	if(mbmEndReciev == 0)
		return mbm_CheckTimeout();
	
	// Сбрасываем флаг принятых данных
	mbmEndReciev = 0;
	
	// Если контрольная сумма не совпадает - уходим без результата
	if(mbm_CheckCRC() == FRES_ERR) return FRES_NONE;
	
	// Если адрес в ответе не соответствует запросу - уходим без результата
	if(mbmRxBuf[0] != addr) return FRES_NONE;
	
	// Если ответ содержит ошибку - обрабатываем и возвращаем ошибку
	if(mbmRxBuf[1] == (0x80 | MBM_FUNC_GET_REGS))
		return mbm_ErrHandler((MBM_ErrEnum)mbmRxBuf[2]);
	
	// Если запрошенные данные не соответствуют запросу - обрабатываем и возвращаем ошибку
	if((mbmRxBuf[1] != MBM_FUNC_GET_REGS) || (mbmRxBuf[2] != (quant * 2)))
		return mbm_ErrHandler(MBM_ERR_ANSWER);
	
	// Если предыдущие условия не сработали, то...
	mbm_GetRegs(quant, data);   // Получаем запрошенные данные
	mbmAnsWait = 0;         // Сбрасываем флаг ожидания ответа
	mbmErr = MBM_ERR_NONE;  // Сбрасываем переменную ошибки
	return FRES_OK;         // Возвращаем положительный результат
} // AnswerGetRegs()



// Получение запрошенных данных -------------------------------------------------------------------
void mbm_GetRegs(uint16_t quant, uint16_t *data)
{	
	mbmCount1 = 0;
	mbmCount2 = 3;
	
	// Записывеем полученные данные в целевой буфер
	for ( ; mbmCount1 < quant; mbmCount1++, mbmCount2 += 2)
		data[mbmCount1] = (mbmRxBuf[mbmCount2] << 8) | (mbmRxBuf[mbmCount2 + 1]);
} // GetRegs()
