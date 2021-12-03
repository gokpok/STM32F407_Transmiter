
// ------------------------------------------------------------------------------------------------
// ������ ������ ������� �� ��������� ModbusRTU � ������ slave-����������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// 
// ���������, ��������������� ��������������� ������� ������
// ------------------------------------------------------------------------------------------------

#include "mbmUtils.h"
#include "mbmError.h"
#include "mbmData.h"
#include "mbsCRC.h"



// �������� �������� �������� ������
FuncRes mbm_CheckTimeout(void)
{
	// ���� ����� �������� ������ �� ������� - ������ ��� ����������
	if(*mbmTime < (mbmQueryTime + mbmTimeout))
		return FRES_NONE;
	
	return mbm_ErrHandler(MBM_ERR_TIMEOUT);
} // mbm_CheckTimeout()


	 
// �������� ����������� ����� ---------------------------------------------------------------------
FuncRes mbm_CheckCRC(void)
{
	// ������� ����������� ����� �������� ������
	mbmCRC = mbs_GetCrc16(mbmRxBuf, (mbmRxLen - 2));
	
	// ���������� ���������� ����� � ����������� � �������
	if((mbmRxBuf[mbmRxLen - 2] == (mbmCRC & 0x00ff)) && (mbmRxBuf[mbmRxLen - 1] == (mbmCRC >> 8)))
		return FRES_OK;
	else
		return FRES_ERR;
} // mbm_CheckCRC()
