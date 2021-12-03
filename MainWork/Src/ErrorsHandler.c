
// ------------------------------------------------------------------------------------------------
// Модуль обработки основной логики устройства
// Разработчик ПО Сынышин Э. М. (edmahalich@yandex.ua)
// 
// Подмодуль обработки ошибок устройства
// ------------------------------------------------------------------------------------------------

#include "ErrorsHandler.h"
#include "DigitInput.h"
#include "BitFuncs.h"
#include "data.h"


uint8_t onErr;
uint8_t offErr;


// Обработчик ошибок устройства -------------------------------------------------------------------
void ErrHandler(void)
{
	// Если есть ошибка в флагах ошибок включения, то
	// выводим номер первого выхода с ошибкой
	if(ON_ERR_1 > 0 || ON_ERR_2 > 0)
	{
		     if(ON_ERR_DO1)  onErr = 1;
		else if(ON_ERR_DO2)  onErr = 2;
		else if(ON_ERR_DO3)  onErr = 3;
		else if(ON_ERR_DO4)  onErr = 4;
		else if(ON_ERR_DO5)  onErr = 5;
		else if(ON_ERR_DO6)  onErr = 6;
		else if(ON_ERR_DO7)  onErr = 7;
		else if(ON_ERR_DO8)  onErr = 8;
		else if(ON_ERR_DO9)  onErr = 9;
		else if(ON_ERR_DO10) onErr = 10;
		else if(ON_ERR_DO11) onErr = 11;
		else if(ON_ERR_DO12) onErr = 12;
		else if(ON_ERR_DO13) onErr = 13;
		else if(ON_ERR_DO14) onErr = 14;
		else if(ON_ERR_DO15) onErr = 15;
		else if(ON_ERR_DO16) onErr = 16;
		else if(ON_ERR_DO17) onErr = 17;
		else if(ON_ERR_DO18) onErr = 18;
	} else onErr = 0;
	
	// Если есть ошибка в флагах ошибок отключения, то
	// выводим номер первого выхода с ошибкой
	if(OFF_ERR_1 > 0 || OFF_ERR_2 > 0)
	{
		     if(OFF_ERR_DO1)  offErr = 1;
		else if(OFF_ERR_DO2)  offErr = 2;
		else if(OFF_ERR_DO3)  offErr = 3;
		else if(OFF_ERR_DO4)  offErr = 4;
		else if(OFF_ERR_DO5)  offErr = 5;
		else if(OFF_ERR_DO6)  offErr = 6;
		else if(OFF_ERR_DO7)  offErr = 7;
		else if(OFF_ERR_DO8)  offErr = 8;
		else if(OFF_ERR_DO9)  offErr = 9;
		else if(OFF_ERR_DO10) offErr = 10;
		else if(OFF_ERR_DO11) offErr = 11;
		else if(OFF_ERR_DO12) offErr = 12;
		else if(OFF_ERR_DO13) offErr = 13;
		else if(OFF_ERR_DO14) offErr = 14;
		else if(OFF_ERR_DO15) offErr = 15;
		else if(OFF_ERR_DO16) offErr = 16;
		else if(OFF_ERR_DO17) offErr = 17;
		else if(OFF_ERR_DO18) offErr = 18;
	} else offErr = 0;
	
	// Задаем состояние регистра вывода номера DO с ошибкой включения/отключения
	ON_OFF_ERR_DO = (onErr << 8) | offErr;
} // ErrHandler()
