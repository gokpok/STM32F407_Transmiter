
// ------------------------------------------------------------------------------------------------
// Модуль обмена данными по протоколу ModbusRTU в режиме slave-устройства
// Разработчик ПО Сынышин Э. М. (edmahalich@yandex.ua)
// 
// Подмодуль, предоставляющий вспомагательные функции модуля
// ------------------------------------------------------------------------------------------------

#include "mbsUtils.h"
#include "mbsError.h"
#include "mbsData.h"


// Проверка доступности серии запрашиваемых данных
FuncRes mbs_CheckQuerySeries(void)
{
	// Проверяем на ограничение длинны запрошенной серии	
	if(mbsVar.dataNum > MBS_MAX_TRX_DATA)
	{
		mbs_ReturnErr(MBS_ERR_BADADDR);
		return FRES_ERR;
	} // if
	
	// Проверяем на выход за пределы массива данных
	if((mbsVar.dataBegin + mbsVar.dataNum) >= mbsBufLen)
	{
		mbs_ReturnErr(MBS_ERR_BADADDR);
		return FRES_ERR;
	} // if
	
	// Если предыдущие условия не сработали - возвращаем положительный результтат
	return FRES_OK;
} // mbs_CheckQuerySeries()
