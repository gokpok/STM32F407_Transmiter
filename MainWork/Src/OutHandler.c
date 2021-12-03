
// ------------------------------------------------------------------------------------------------
// Модуль обработки основной логики устройства
// Разработчик ПО Сынышин Э. М. (edmahalich@yandex.ua)
// 
// Подмодуль обработки состояний рабочих выходов
// ------------------------------------------------------------------------------------------------

#include "OutHandler.h"
#include "DigitInput.h"
#include "BitFuncs.h"
#include "stdlib.h"
#include "data.h"


DO_StateStruct *DO_State;   // Указатель на массив состояний обрабатываемых DO
GPIO_PinState   state;      // Состояние порта GPIO
GPIO_PinState  *lastState;  // Указатель на массив последних состояний DO
uint8_t         doNum;      // Кол-во обрабатываемых выходов
uint8_t         count;      // Счетчик собственных нужд


// Задание состояниея выхода
void do_SetState(void);

// Контроль таймаута по связи для выхода
void do_TimeoutCtrl(void);

// Контроль включения выхода
uint8_t do_OnCtrl(void);

// Контроль отключения выхода
uint8_t do_OffCtrl(void);


// Инициализация модуля ---------------------------------------------------------------------------
void DO_Init(uint8_t num)
{	
	// Задаем параметры конфигурации модуля
	doNum = num;    // Задаем кол-во обрабатываемых выходов
	
	// Выделяем память для массива структур DO
	DO_State = (DO_StateStruct*) malloc(doNum * sizeof(DO_StateStruct));
	
	// Выделяем память для массива последних состояний DO
	lastState = (GPIO_PinState*) malloc(doNum * sizeof(GPIO_PinState));
} // DO_Init()



// Добавление выхода в модуль -------------------------------------------------------------------
void DO_Add(uint8_t num, GPIO_TypeDef *port, uint16_t pin, uint16_t *stateReg, uint16_t *onCtrlReg,
						uint16_t *offCtrlReg, uint16_t *toCtrlReg, uint16_t *onErrReg, uint16_t *offErrReg, uint8_t bit)
{
	DO_State[num].port       = port;
	DO_State[num].pin        = pin;
	DO_State[num].stateReg   = stateReg;
	DO_State[num].onCtrlReg  = onCtrlReg;
	DO_State[num].offCtrlReg = offCtrlReg;
	DO_State[num].toCtrlReg  = toCtrlReg;
	DO_State[num].onErrReg   = onErrReg;
	DO_State[num].offErrReg  = offErrReg;
	DO_State[num].bit        = bit;
} // DO_Add()



// Обработчик состояния DO ------------------------------------------------------------------------
void DO_Handler(void)
{
	// Выполняем обработку выходорв
	for(count = 1; count < doNum; count++)
	{
		do_SetState();      // Задаем состояние выхода
		do_TimeoutCtrl();   // Обрабатываем контроль таймаута по связи
		
		// Обрабатываем контроль включения
		SetBit(DO_State[count].onErrReg, DO_State[count].bit, do_OnCtrl()); 
		
		// Обрабатываем контроль отключения
		SetBit(DO_State[count].offErrReg, DO_State[count].bit, do_OffCtrl());        
		
		// Задаем состояние GPIO-порта выхода
		HAL_GPIO_WritePin(DO_State[count].port, DO_State[count].pin, state);
	} // for
} // DO_Handler



// Задание состояниея выхода ----------------------------------------------------------------------
void do_SetState(void)
{
		// Задаем состояние GPIO-порта выхода
		state = GetBit(DO_State[count].stateReg, DO_State[count].bit) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET;
	
		// Если состояние изменилось, то...
		if(state != lastState[count])
		{
			DO_State[count].changeTime = gTick;   // Запоминаем время изменения состояния
			lastState[count] = state;             // Сохраняем состояние
		} // if
} // do_SetState()



// Контроль таймаута по связи для выхода ----------------------------------------------------------
void do_TimeoutCtrl(void)
{
	// Если нет ошибки связи - уходим
	if(link != FRES_ERR) return;
	
	// Если для выхода не задан контроль таймаута - уходим
	if(GetBit(DO_State[count].toCtrlReg, DO_State[count].bit) == 0) return;
	
	// Если предыдущие условия не сработали - отключаем выход
	state = GPIO_PIN_RESET;
} // do_TimeoutCtrl()



// Контроль включения выхода ----------------------------------------------------------------------
uint8_t do_OnCtrl(void)
{
	// Если выход отключен - уходим
	if(state == GPIO_PIN_RESET) return 0;
	
	// Если для выхода не задан контроль включения - уходим
	if(GetBit(DO_State[count].onCtrlReg, DO_State[count].bit) == 0) return 0;
	
	// Если время контроля не подошло - уходим
	if(gTick < (DO_State[count].changeTime + TIME_CTRL_ON)) return 0;
	
	// Если нет сигнала от выхода - ставим флаг наличия ошибки включения
	if(DI_State[count] == 0)
		return 1;
	else
		return 0;
} // do_OnCtrl()



// Контроль отключения выхода ----------------------------------------------------------------------
uint8_t do_OffCtrl(void)
{
	// Если выход включен - уходим
	if(state == GPIO_PIN_SET) return 0;
	
	// Если для выхода не задан контроль отключения - уходим
	if(GetBit(DO_State[count].offCtrlReg, DO_State[count].bit) == 0) return 0;
	
	// Если время контроля не подошло - уходим
	if(gTick < (DO_State[count].changeTime + TIME_CTRL_OFF)) return 0;
	
	// Если нет сигнала от выхода - сбрасываем флаг наличия ошибки включения
	if(DI_State[count] == 0)
		return 0;
	else
		return 1;
} // do_OffCtrl()
