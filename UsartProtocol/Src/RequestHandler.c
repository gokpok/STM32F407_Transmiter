
#include "RequestHandler.h"

uint8_t ResponseBuf[6];  //Formed response

uint8_t RequestOfData(void)
{
	//Function of start making response check 
	
	
	if ((RxStart[1] == ( mbs_GetCrc16(RxStart,3) & 0x00ff)) && ( RxStart[2] == mbs_GetCrc16(RxStart,3) >> 8) && RxStart[0] == 0xFF) 
	return 1; //If start byte is 0xFF and CRC16 matches, return TRUE(1), else return FALSE(0)
	else
	{
		//If CRC16 doesnt match, return 0 and transmit error of communication
		//uint8_t
		//HAL_UART_Transmit_DMA(&huart1,"",6);
		return 0;
	}
}

void MakeResponse(uint8_t* buf, uint8_t* DI_State)
{
	
	//Valuable part of response ( FU1-18 and KM2-5 )  
	//Each bite depicts state of Digital Input. For example 0b000101 means, that DI #1 and #3 is HIGH, rest is LOW
	//---------------------------------------------------------------------------------------------------
	buf[0]=DI_State[1]<<0 | DI_State[2]<<1 | DI_State[3]<<2 | DI_State[4]<<3 |
	DI_State[5]<<4 | DI_State[6]<<5 | DI_State[7]<<6 | DI_State[8]<<7;
	
	for (uint8_t i=8;i<=24;i=i+8)
	{
		uint8_t step=0;
		step++;
		buf[i-8*step+step]=DI_State[i+1]<<0 | DI_State[i+2]<<1 | DI_State[i+3]<<2 | DI_State[i+4]<<3 |
		DI_State[i+5]<<4 | DI_State[i+6]<<5 | DI_State[i+7]<<6 | DI_State[i+8]<<7;
	}
	
	buf[3]|=0x0F;  //Supporting part of last valuable byte, that makes CRC stronger (not zero) 
	
	//---------------------------------------------------------------------------------------------------
	
	//Making CRC part
	buf[4] = mbs_GetCrc16(buf,4) & 0x0f;
	buf[5] = mbs_GetCrc16(buf,4) >> 8;
	
	
}
