
// ------------------------------------------------------------------------------------------------
// Модуль обмена данными по протоколу ModbusRTU в режиме slave-устройства
// Разработчик ПО Сынышин Э. М. (edmahalich@yandex.ua)
// 
// Подмодуль, обрабатывающий запрос с функцией выполнения комманды (0x64)
// ------------------------------------------------------------------------------------------------

#include "mbsFuncCmd.h"
#include "mbsSendData.h"
#include "mbsError.h"
#include "mbsUtils.h"
#include "mbsData.h"
//#include "Interface.h"
#include "mbsCRC.h"

	 

// Обработка функции выполнения команды (0x64) ----------------------------------------------------
//FuncRes mbs_FuncCmd(void)
//{
//	// Выполняем обработку команды с получением длинны ответных данных
//	mbsDataNum = InterfaceCmdHandler(mbsRxBuf[2] << 8 | mbsRxBuf[3], mbsRxBuf[4] << 8 | mbsRxBuf[5], mbsRxBuf[6] << 8 | mbsRxBuf[7]);
//	
//	// Формируем заголовок ответа
//	mbsTxBuf[0] = mbsAddr;        // Указаваем адрес slave-устройства
//	mbsTxBuf[1] = MBS_FUNC_CMD;   // Указываем код выполняемой функции
//	mbsTxBuf[2] = mbsDataNum;     // Указываем кол-во данных в ответе
//	
//	mbsCount1 = 0;   // первый счетчик сбрасывыаем
//	mbsCount2 = 3;   // второй счетчик задаем как стартовый адрес запрошенных данных в пакете
//		
//	// Добавляем в пакет запрошенные данные
//	for( ; mbsCount1 <= mbsDataNum; mbsCount1++, mbsCount2++)
//	{
//		mbsTxBuf[mbsCount2]   = intfData[mbsCount1] >> 8;
//		mbsTxBuf[++mbsCount2] = intfData[mbsCount1] & 0x00FF;
//	} // for	
//	
//	// Получаем контрольную сумму сформированнных данных и добавляем в конец пакета
//	mbsCRC =  mbs_GetCrc16(mbsTxBuf, mbsCount2 - 2);
//	mbsTxBuf[mbsCount2 - 2] = mbsCRC & 0x00ff;
//	mbsTxBuf[mbsCount2 - 1] = mbsCRC >> 8;
//	
//	// Инициируем отправку данных
//	mbs_SendDataIni(mbsCount2);
//	
//	return FRES_OK;
//} // mbs_FuncCmd()
