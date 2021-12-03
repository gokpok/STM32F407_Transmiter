
#include "DI_Handler.h"

uint8_t GetCmnd[3] = {0};
uint8_t Rx_Cmplt_Flag = 0;
uint32_t* timeC = 0;
uint32_t timeC_prev = 0;
uint16_t TimeOut;
uint8_t* ReceiveBuf;
uint16_t Period = 0;
uint8_t Alarm_Flag = 0;
uint8_t err_counter = 0;
UART_HandleTypeDef* huart_DI;


void DI_Init(UART_HandleTypeDef* huart_u, uint8_t* array, uint32_t* time, uint16_t time_out)
{
	// huart_u  - pointer on user's USART
	// array    - pointer on user's receive buffer
	// time     - pointer on time counter
	// time_out - period of polling (timeout)
	
	//Init pointer to user's USART
	huart_DI = huart_u;
	
	//Init pointer to user's buffer
	ReceiveBuf = array;
	
	//Init Start command and calculate CRC
	GetCmnd[0] = 0xFF;
	GetCmnd[1] = mbs_GetCrc16(GetCmnd, 1)&0x0F;
	GetCmnd[2] = mbs_GetCrc16(GetCmnd, 1)>>8;
	
	//Start Receiving reply
	HAL_UART_Receive_DMA(huart_DI,ReceiveBuf,6);
	
	//Transmit start command
	HAL_UART_Transmit_DMA(huart_DI,GetCmnd,3);
	
	//Addres of current time counter
	timeC = time;
	
	// Время последнего опроса задаем больше текущего на величину отсрочки старта опроса
	timeC_prev = *timeC+100;
	
	//Init TimeOut
	TimeOut  =  time_out;
	
	//Period of polling
//	Period = time_period;
}

FuncRes DI_Handler(void)
{

	FuncRes res = FRES_NONE;

	if ((*timeC) >= (timeC_prev+TimeOut))																//If timeout elapsed and
	{
		if (Rx_Cmplt_Flag)																					    	//If received complete and
		{
			if (ReceiveBuf[4]  ==  (mbs_GetCrc16(ReceiveBuf, 4) & 0x0F) &&  //If CRC match return ok, else return err
					ReceiveBuf[5]  ==  (mbs_GetCrc16(ReceiveBuf, 4)>>8))
			
			{res = FRES_OK;}
			
			else
			{res = FRES_ERR;}

			Rx_Cmplt_Flag  =  0;																				//RESET Rx complete flag
			 
			HAL_UART_Receive_DMA(huart_DI,ReceiveBuf,6);										//Start Receiving reply
			HAL_UART_Transmit_DMA(huart_DI,GetCmnd,3);											//Transmit start command
			
			timeC_prev  =  *timeC;																			//Remember last time
			
			err_counter = 0;																						//RESET error counter
	 
			return res;																		   						//Function return result
		}
		
		else 																													//If USART buffer empty, increase error counter
		{
			err_counter++;
			
			HAL_UART_Receive_DMA(huart_DI,ReceiveBuf,6);										//Start Receiving reply
			HAL_UART_Transmit_DMA(huart_DI,GetCmnd,3);											//Transmit start command
			
			timeC_prev  =  *timeC;
			
			if (err_counter >= 5)																				//If there are critical amount of error in a row -
																																	// set alarm flag
			{Alarm_Flag = 1;}
				
			res = FRES_ERR;																							//Return error
			
			return res;																									//If timeout elapsed and CRC doesnt match 
																																	//return NULL																							
		}
	}
	return res;

}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == huart_DI)
	Rx_Cmplt_Flag  =  1;
}
