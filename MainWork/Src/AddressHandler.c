
// ------------------------------------------------------------------------------------------------
// Модуль обработки основной логики устройства
// Разработчик ПО Сынышин Э. М. (edmahalich@yandex.ua)
// 
// Подмодуль получения адреса slave-устройства
// ------------------------------------------------------------------------------------------------

#include "AddressHandler.h"
#include "DigitInput.h"
#include "data.h"

// Период обновления адреса
#define PERIOD_ADDR_UPDATE   500
	 	 
// Определение состояний битов адреса
#define ADDR_BIT_0   DI_State[19]
#define ADDR_BIT_1   DI_State[20]
#define ADDR_BIT_2   DI_State[21]
#define ADDR_BIT_3   DI_State[22]
#define ADDR_BIT_4   DI_State[23]
#define ADDR_BIT_5   DI_State[24]

// Время последнего обновления
uint64_t lastAddrUpdate = 0;

// Временное значение аддреса
uint8_t tempAddr;


// Обработчик ошибок устройства -------------------------------------------------------------------
void AddrHandler(uint8_t *addr)
{
	// Если время обработки адреса не подошло - уходим
	if(gTick < (lastAddrUpdate + PERIOD_ADDR_UPDATE)) return;
	
	// Сбрасываем временную переменную
	tempAddr = 0;
	
	if(ADDR_BIT_5 != 0) tempAddr &= 0xffdf; else tempAddr |= 0x0020;
	if(ADDR_BIT_4 != 0) tempAddr &= 0xffef; else tempAddr |= 0x0010;
	if(ADDR_BIT_3 != 0) tempAddr &= 0xfff7; else tempAddr |= 0x0008;
	if(ADDR_BIT_2 != 0) tempAddr &= 0xfffb; else tempAddr |= 0x0004;
	if(ADDR_BIT_1 != 0) tempAddr &= 0xfffd; else tempAddr |= 0x0002;
	if(ADDR_BIT_0 != 0) tempAddr &= 0xfffe; else tempAddr |= 0x0001;
	
	// Увеличиваем значение заданного адреса и запоминаем адрес
	sAddr = tempAddr;
	
	lastAddrUpdate = gTick;
} // AddrHandler()
