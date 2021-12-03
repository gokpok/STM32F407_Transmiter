
#include "main.h"
#include "dma.h"
#include "usart.h"
#include "mbsCRC.h"


extern uint8_t GetCmnd[3];
extern uint32_t* timeC;
extern uint32_t timeC_prev;
extern uint16_t TimeOut;
extern uint8_t* ReceiveBuf;
extern uint8_t Rx_Cmplt_Flag;
extern uint16_t Period;
extern uint8_t Alarm_Flag;
extern uint8_t err_counter;
extern UART_HandleTypeDef* huart_DI;

void DI_Init(UART_HandleTypeDef* huart_u, uint8_t* array, uint32_t* time, uint16_t time_out);
FuncRes DI_Handler(void);

