

#include "MainInit.h"
#include "clock.h"
//#include "iwdg.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "data.h"

#include "DigitInput.h"
#include "OutHandler.h"

#define MDATA_LEN 23        //Number of processed pins


uint8_t RxStart[3]={0};          //Command of start making data packet


// Функция инициализации и настройки перефирии и програмных модулей системы -----------------------
void InitSystem(void)
{
	
	// Инициализируем модуль основных данных системы
	MainDataInit(MDATA_LEN);
	
	
	// Инициализируем модуль дискретных входов
	// (кол-во DI задаем на 1 больше, т.к. DI-0 не используем)
	DI_Init(24, 10, 1, &gTick);
	DI_AddInput(1, GPIOB, GPIO_PIN_9);    // Добавление DI обратной связи выхода 1
	DI_AddInput(2, GPIOB, GPIO_PIN_8);    // Добавление DI обратной связи выхода 2
	DI_AddInput(3, GPIOB, GPIO_PIN_7);    // Добавление DI обратной связи выхода 3
	DI_AddInput(4, GPIOB, GPIO_PIN_6);    // Добавление DI обратной связи выхода 4
	DI_AddInput(5, GPIOB, GPIO_PIN_0);    // Добавление DI обратной связи выхода 5
	DI_AddInput(6, GPIOA, GPIO_PIN_11);    // Добавление DI обратной связи выхода 6
	DI_AddInput(7, GPIOA, GPIO_PIN_8);    // Добавление DI обратной связи выхода 7
	DI_AddInput(8, GPIOA, GPIO_PIN_7);    // Добавление DI обратной связи выхода 8
	DI_AddInput(9, GPIOA, GPIO_PIN_6);   // Добавление DI обратной связи выхода 9
	DI_AddInput(10, GPIOA, GPIO_PIN_5);  // Добавление DI обратной связи выхода 10
	DI_AddInput(11, GPIOA, GPIO_PIN_4);  // Добавление DI обратной связи выхода 11
	DI_AddInput(12, GPIOA, GPIO_PIN_3);   // Добавление DI обратной связи выхода 12
	DI_AddInput(13, GPIOA, GPIO_PIN_2);   // Добавление DI обратной связи выхода 13
	DI_AddInput(14, GPIOA, GPIO_PIN_1);   // Добавление DI обратной связи выхода 14
	DI_AddInput(15, GPIOA, GPIO_PIN_0);  // Добавление DI обратной связи выхода 15
	DI_AddInput(16, GPIOB, GPIO_PIN_15);  // Добавление DI обратной связи выхода 16
	DI_AddInput(17, GPIOB, GPIO_PIN_14);  // Добавление DI обратной связи выхода 17
	DI_AddInput(18, GPIOB, GPIO_PIN_13);   // Добавление DI обратной связи выхода 18
	DI_AddInput(19, GPIOB, GPIO_PIN_12);   // Добавление DI обратной связи выхода 19
	DI_AddInput(20, GPIOB, GPIO_PIN_11);   // Добавление DI обратной связи выхода 20
	DI_AddInput(21, GPIOB, GPIO_PIN_10);   // Добавление DI обратной связи выхода 21
	DI_AddInput(22, GPIOB, GPIO_PIN_2);   // Добавление DI обратной связи выхода 22
	DI_AddInput(23, GPIOB, GPIO_PIN_1);   // Добавление DI обратной связи выхода 23
	//DI_AddInput(24, GPIOA, GPIO_PIN_4);   // Добавление DI бита 5 аддреса устройства
	
	// Start UART recieve with DMA
	HAL_UART_Receive_DMA(&huart1,RxStart,3);
	
//  MX_IWDG_Init();           // Инициализируем сторожевой таймер
} // InitSystem()
