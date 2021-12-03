
// ------------------------------------------------------------------------------------------------
// Модуль обмена данными по протоколу ModbusRTU в режиме slave-устройства
// Разработчик ПО Сынышин Э. М. (edmahalich@yandex.ua)
// 
// Подмодуль, обрабатывающий запрос с функцией получения значений серии регистров (0x03)
// ------------------------------------------------------------------------------------------------

#include "mbsFuncGetRegs.h"
#include "mbsSendData.h"
#include "mbsError.h"
#include "mbsUtils.h"
#include "mbsCRC.h"
#include "mbsData.h"

	 

// Возврат ответа на запрос с функцией получения серии регистров (0x03) ---------------------------
FuncRes mbs_FuncGetRegs(void)
{
	// Получаем начальный адрес и длинну запрашиваемых данных
	mbsVar.dataBegin = (mbsRxBuf[2] << 8) | mbsRxBuf[3];
	mbsVar.dataNum   = (mbsRxBuf[4] << 8) | mbsRxBuf[5];
	
	// Проверяем запрошенные данные на доступность
	if(mbs_CheckQuerySeries() == FRES_ERR)
		return FRES_ERR;
	
	// Формируем заголовок ответа
	mbsTxBuf[0] = *mbsVar.addr;        // Указаваем адрес slave-устройства
	mbsTxBuf[1] = MBS_FUNC_GET_REGS;  // Указываем код выполняемой функции
	mbsTxBuf[2] = mbsVar.dataNum * 2; // Указываем кол-во данных в ответе
	
	// Получаем конечный адрес запрашиваемых данных
	mbsVar.dataEnd = mbsVar.dataBegin + mbsVar.dataNum;
	
	mbsVar.count1 = mbsVar.dataBegin;   // первый счетчик задаем как стартовый адрес запрошенных данных
	mbsVar.count2 = 3;                  // второй счетчик задаем как стартовый адрес запрошенных данных в пакете
		
	// Добавляем в пакет запрошенные данные
	for( ; mbsVar.count1 <= mbsVar.dataEnd; mbsVar.count1++, mbsVar.count2++)
	{
		mbsTxBuf[mbsVar.count2]   = mbsBuf[mbsVar.count1] >> 8;
		mbsTxBuf[++mbsVar.count2] = mbsBuf[mbsVar.count1] & 0x00FF;
	} // for	
	
	// Получаем контрольную сумму сформированнных данных и добавляем в конец пакета
	mbsVar.crc = mbs_GetCrc16(mbsTxBuf, mbsVar.count2 - 2);
	mbsTxBuf[mbsVar.count2 - 2] = mbsVar.crc & 0x00ff;
	mbsTxBuf[mbsVar.count2 - 1] = mbsVar.crc >> 8;	
	
	// Инициируем отправку данных
	mbs_SendDataIni(mbsVar.count2);
	
	return FRES_OK;
} // mbs_FuncGetRegs()
