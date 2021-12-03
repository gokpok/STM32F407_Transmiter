
// ------------------------------------------------------------------------------------------------
// Модуль вспомагательных функций
// Разработчик ПО Сынышин Э. М. (edmahalich@yandex.ua)
// 
// Подмодуль битовых операций
// ------------------------------------------------------------------------------------------------

#include "BitFuncs.h"

uint16_t mask;   // Битовая маска


// Получение значения бита ------------------------------------------------------------------------
uint8_t GetBit(uint16_t *reg, uint8_t bit)
{
	// По номеру бита задаем маску
	switch(bit)
	{
		case 15:
			mask = 0x8000;
			break;
		case 14:
			mask = 0x4000;
			break;
		case 13:
			mask = 0x2000;
			break;
		case 12:
			mask = 0x1000;
			break;
		case 11:
			mask = 0x0800;
			break;
		case 10:
			mask = 0x0400;
			break;
		case 9:
			mask = 0x0200;
			break;
		case 8:
			mask = 0x0100;
			break;
		case 7:
			mask = 0x0080;
			break;
		case 6:
			mask = 0x0040;
			break;
		case 5:
			mask = 0x0020;
			break;
		case 4:
			mask = 0x0010;
			break;
		case 3:
			mask = 0x0008;
			break;
		case 2:
			mask = 0x0004;
			break;
		case 1:
			mask = 0x0002;
			break;
		case 0:
			mask = 0x0001;
			break;
	} // switch
	
	// Возвращаем результат применения маски
	if(*reg & mask)
		return 1;
	else
		return 0;
} // GetBit()



// Задание значения бита --------------------------------------------------------------------------
void SetBit(uint16_t *reg, uint8_t bit, uint8_t state)
{
	if(state == 0)
		SetBitFalse(reg, bit);
	else
		SetBitTrue(reg, bit);
} // SetBit()


		
// Задание бита как "истина" ----------------------------------------------------------------------
void SetBitTrue(uint16_t *reg, uint8_t bit)
{
	switch(bit)
	{
		case 15:
			mask = 0x8000;
			break;
		case 14:
			mask = 0x4000;
			break;
		case 13:
			mask = 0x2000;
			break;
		case 12:
			mask = 0x1000;
			break;
		case 11:
			mask = 0x0800;
			break;
		case 10:
			mask = 0x0400;
			break;
		case 9:
			mask = 0x0200;
			break;
		case 8:
			mask = 0x0100;
			break;
		case 7:
			mask = 0x0080;
			break;
		case 6:
			mask = 0x0040;
			break;
		case 5:
			mask = 0x0020;
			break;
		case 4:
			mask = 0x0010;
			break;
		case 3:
			mask = 0x0008;
			break;
		case 2:
			mask = 0x0004;
			break;
		case 1:
			mask = 0x0002;
			break;
		case 0:
			mask = 0x0001;
			break;
	} // switch
	
	// Применяем маску к заданному регистру
	*reg |= mask;
} // SetBitTrue()



// Задание бита как "лож" -------------------------------------------------------------------------
void SetBitFalse(uint16_t *reg, uint8_t bit)
{		
	switch(bit)
	{
		case 15:
			mask = 0x7fff;
			break;
		case 14:
			mask = 0xbfff;
			break;
		case 13:
			mask = 0xdfff;
			break;
		case 12:
			mask = 0xefff;
			break;
		case 11:
			mask = 0xf7ff;
			break;
		case 10:
			mask = 0xfbff;
			break;
		case 9:
			mask = 0xfdff;
			break;
		case 8:
			mask = 0xfeff;
			break;
		case 7:
			mask = 0xff7f;
			break;
		case 6:
			mask = 0xffbf;
			break;
		case 5:
			mask = 0xffdf;
			break;
		case 4:
			mask = 0xffef;
			break;
		case 3:
			mask = 0xfff7;
			break;
		case 2:
			mask = 0xfffb;
			break;
		case 1:
			mask = 0xfffd;
			break;
		case 0:
			mask = 0xfffe;
			break;
	} // switch
	
	// Применяем маску к заданному регистру
	*reg &= mask;
} // SetBitFalse()
