
// ------------------------------------------------------------------------------------------------
// Модуль обмена данными по протоколу ModbusRTU в режиме master-устройства
// Разработчик ПО Сынышин Э. М. (edmahalich@yandex.ua)
// 
// Подмодуль, выполняющий запрос с функцией задания значений серии регистров (0x10)
// ------------------------------------------------------------------------------------------------

#include "mbmFuncSetRegs.h"
#include "ModbusMaster.h"
#include "mbmSendData.h"
#include "mbmError.h"
#include "mbmUtils.h"
#include "mbmData.h"
#include "mbsCRC.h"


// Отправка запроса на выполнение функции
FuncRes QuerySetRegs(uint8_t addr, uint16_t first, uint16_t quant, uint16_t *data);

// Обработка ответа
FuncRes AnswerSetRegs(uint8_t addr, uint16_t quant);

	 

// Выполнение запроса с функцией задания серии регистров (0x03) ---------------------------------
FuncRes mbm_FuncSetRegs(uint8_t addr, uint16_t first, uint16_t quant, uint16_t *data)
{	
	// Если модуль не ожидает ответ - отправляем запрос
	if(mbmAnsWait == 0) return QuerySetRegs(addr, first, quant, data);
	
	// Если предыдущие условия не сработали - обрабатываем ответ
	return AnswerSetRegs(addr, quant);
} // mbs_FuncSetRegs()



// Отправка запроса на выполнение функции ---------------------------------------------------------
FuncRes QuerySetRegs(uint8_t addr, uint16_t first, uint16_t quant, uint16_t *data)
{
	// Если кол-во запрошенных данных превышает допустимое - уходим с ошибкой
	if(quant > mbmMaxLen)
		return mbm_ErrHandler(MBM_ERR_MAX_LEN);
	
	// формируем пакет запроса
	mbmTxBuf[0] = addr;               // Адрес устройства
	mbmTxBuf[1] = MBM_FUNC_SET_REGS;  // Код команды чтения регистров
	mbmTxBuf[2] = first >> 8;         // Начало запрашиваемых регистров
	mbmTxBuf[3] = first & 0x00FF;     // --- *** ---
	mbmTxBuf[4] = quant >> 8;         // Кол-во запрашиваемых регистров
	mbmTxBuf[5] = quant & 0x00FF;     // --- *** ---
	mbmTxBuf[6] = quant * 2;          // --- *** ---
		
	mbmCount1 = 0;  // Сбрасываем первый счетичик
	mbmCount2 = 7;  // Второй счетчик задаем как начало данных в пакете
	
	// Добавляем отправляемые данные в пакет
	for( ; mbmCount1 < quant; mbmCount1++, mbmCount2 += 2)
	{
		mbmTxBuf[mbmCount2]     = data[mbmCount1] >> 8;
		mbmTxBuf[mbmCount2 + 1] = data[mbmCount1] & 0x00FF;
	} // for
	
	// Получаем контрольную сумму сформированного запроса и добавляем в конец пакета
	mbmCRC = mbs_GetCrc16(mbmTxBuf, quant * 2 + 7);
	mbmTxBuf[quant * 2 + 7] = mbmCRC & 0x00ff;
	mbmTxBuf[quant * 2 + 8] = mbmCRC >> 8;	
	
	// Инициируем отправку данных
	mbm_SendDataIni(quant * 2 + 9);
	
	return FRES_NONE;
} // QuerySetRegs()



// Обработка ответа -------------------------------------------------------------------------------
FuncRes AnswerSetRegs(uint8_t addr, uint16_t quant)
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
	if(mbmRxBuf[1] == (0x80 | MBM_FUNC_SET_REGS))
		return mbm_ErrHandler((MBM_ErrEnum)mbmRxBuf[2]);
	
	// Если запрошенные данные не соответствуют запросу - обрабатываем и возвращаем ошибку
	if(mbmRxBuf[1] != MBM_FUNC_SET_REGS)
		return mbm_ErrHandler(MBM_ERR_ANSWER);
	
	// Если предыдущие условия не сработали, то...
	mbmAnsWait = 0;         // Сбрасываем флаг ожидания ответа
	mbmErr = MBM_ERR_NONE;  // Сбрасываем переменную ошибки
	return FRES_OK;         // Возвращаем положительный результат
} // AnswerSetRegs()
