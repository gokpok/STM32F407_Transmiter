
// ------------------------------------------------------------------------------------------------
// ПО 18-ти канального модуля вывода дискретных сигналов МВДС-18Т
// Разработчик ПО Сынышин Э. М. (edmahalich@yandex.ua)
// ------------------------------------------------------------------------------------------------
// Модуль точки входа кода исполнения
// ------------------------------------------------------------------------------------------------

#include "main.h"
#include "stm32f4xx_hal.h"
#include "MainInit.h"
#include "AddressHandler.h"
#include "ModbusSlave.h"
#include "DigitInput.h"
#include "OutHandler.h"
#include "ErrorsHandler.h"
#include "iwdg.h"
#include "data.h"


#define DEV_CODE      11    // Код устройства
#define PROG_VERS      0    // Версия ПО
#define PROG_CHANGE    0    // Изменение ПО


uint64_t blink1, blink2;


// Точка входа кода исполнения --------------------------------------------------------------------
int main(void)
{
	InitSystem();
	
	// Задаем состояния и параметры по умолчанию
	DEVICE_CODE       = DEV_CODE;
	PROG_INFO         = PROG_VERS >> 8 | PROG_CHANGE;
	CONTROL_REG       = 0x0000;
	ON_OFF_ERR_DO     = 0x0000;
	ON_ERR_1          = 0x0000;
	ON_ERR_2          = 0x0000;
	TIMEOUT_CTRL_1    = 0xffff;
	TIMEOUT_CTRL_2    = 0xffff;
	ON_CTRL_1         = 0xffff;
	ON_CTRL_2         = 0xffff;
	OFF_CTRL_1        = 0xffff;
	OFF_CTRL_2        = 0xffff;
	LINK_TIMEOUT      = 2000;
	TIME_CTRL_ON      = 150;
	TIME_CTRL_OFF     = 150;
	
  while (1)
  {
		// Обрабатываем получение адреса для slave-устройства
		AddrHandler(&sAddr);
		
		// Обрабатываем обмен данными
		link = MBS_Handler(); 
		
		DI_Handler();   // Обрабатываем состояния DI
		DO_Handler();   // Обрабатываем состояния DO
		ErrHandler();   // Обрабатываем ошибки
		
		HAL_IWDG_Refresh(&hiwdg);   // Сбрасываем собаку
		
  } // while
} // main()




/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
