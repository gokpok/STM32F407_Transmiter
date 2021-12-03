
// ------------------------------------------------------------------------------------------------
// Модуль опроса дискретных входов
// Разработчик ПО Сынышин Э. М. (edmahalich@yandex.ua)
// 
// Подмодуль интерфейса модуля
// Cостояние DI доступно  в массиве DI_State, где 
//   - индекс - номер DI, заданный при добавлении входа в модуль;
//   - значение элемента это состояние DI: 0 - low; 1 - hi.
// ------------------------------------------------------------------------------------------------

#include "DigitInput.h"
#include "diDefines.h"
#include "stdlib.h"


uint8_t            *DI_State;  // Указатель на массив состояний обрабатываемых DI
DI_ParamStruct      diParam;   // Параметры обработки DI
DI_DescriptStruct  *di;        // Указатель на массив описаний DI
uint8_t							test[100];

void    DI_PoolStep(uint8_t *resArr);    // Выполнение шага опроса
void    DI_AcceptResult(void);           // Применение результата опросов
uint8_t DI_CheckPollRes(uint8_t numDI);  // Проверка результата опроса


// Инициализация DI модуля ------------------------------------------------------------------------
void DI_Init(uint8_t diNum, uint8_t periodPoll, uint8_t numPoll, uint64_t *time)
{
	// Параметры функции:
	// diNum       - кол-во DI
	// periodPoll  - периодичность опроса DI (мсек)
	// numPoll     - кол-во опроса DI
	// time        - указатель на счетчик теущего времени
	
	// Задаем параметры конфигурации модуля
	diParam.diNum      = diNum;
	diParam.periodPoll = periodPoll;
	diParam.numPoll    = numPoll;
	diParam.time       = time;
	
	// Устанавливаем исходные значения оперативных параметров
	// Время последнего опроса задаем больше текущего на величину отсрочки старта опроса
	diParam.lastTime = *time + 500;
	diParam.stepPoll = 0;
	
	// Выделяем память для массива описания DI
	di = (DI_DescriptStruct*) malloc(diNum * sizeof(DI_DescriptStruct));
	
	// Выделяем память для массива результатов опросов
	diParam.resArr = (uint8_t*) malloc(diNum * numPoll * sizeof(uint8_t));
	
	// Выделяем память для массива состояний обрабатываемых DI
	DI_State = (uint8_t*) malloc(diNum * sizeof(uint8_t));
} // DI_Init()



// Добавление входа в DI модуль -------------------------------------------------------------------
void DI_AddInput(uint8_t diNum, GPIO_TypeDef *port, uint16_t pin)
{
	di[diNum].port = port;
	di[diNum].pin  = pin;
} // DI_AddInput()



// Обработчик состояния DI ------------------------------------------------------------------------
FuncRes DI_Handler(void)
{
	// Если время очередного опроса не подошло - уходим
	if(*diParam.time < (diParam.lastTime + diParam.periodPoll))
		return FRES_NONE;
	
	// Делаем шаг опроса DI и передаем в обработчик область массива
	// реультатов, соответствующую текущему шагу опроса
	DI_PoolStep(&diParam.resArr[diParam.stepPoll * diParam.diNum]);
	
	// Увеличиваем шаг опроса
	diParam.stepPoll++;
	
	// Запоминаем время опроса
	diParam.lastTime = *diParam.time;
			
	// Если не все шаги опроса выполнены - уходим
	if(diParam.stepPoll < diParam.numPoll)
		return FRES_NONE;
	
	// Сбрасываем шаг опроса
	diParam.stepPoll = 0;
	
	// Применяем результат опросов
	DI_AcceptResult();
	return FRES_OK;
} // DI_Handler



// Выполнение шага опроса -------------------------------------------------------------------------
void DI_PoolStep(uint8_t *resArr)
{
	// Перебираем и опрашиваем DI
	for(uint8_t i = 0; i < diParam.diNum; i++)
		resArr[i] = HAL_GPIO_ReadPin(di[i].port, di[i].pin);
} // DI_PoolStep()



// Применение результата опросов ------------------------------------------------------------------
void DI_AcceptResult(void)
{
	// Перебираем и сохраняем результаты опросов для портов DI
	for(uint8_t i = 0; i < diParam.diNum; i++)
	{	DI_State[i] = DI_CheckPollRes(i); test[i]=DI_State[i];}
	
} // DI_AcceptResult()



// Проверка результата опроса ---------------------------------------------------------------------
uint8_t DI_CheckPollRes(uint8_t numDI)
{
	// Перебираем результаты опроса для заданного DI
	for(uint8_t i = 0; i < diParam.numPoll; i++)
	{
		// Если в опросах есть отрицательный результат - возвращаем 0
		if(diParam.resArr[numDI + (i * diParam.diNum)] != GPIO_PIN_SET)
			return 0;
	} // for
		
	return 1;
} // DI_CheckPollRes()
