
// ------------------------------------------------------------------------------------------------
// ������ ������ ������� �� ��������� ModbusRTU � ������ slave-����������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// 
// ���������, �������������� ������ � �������� ���������� �������� (0x64)
// ------------------------------------------------------------------------------------------------

#include "mbsFuncCmd.h"
#include "mbsSendData.h"
#include "mbsError.h"
#include "mbsUtils.h"
#include "mbsData.h"
//#include "Interface.h"
#include "mbsCRC.h"

	 

// ��������� ������� ���������� ������� (0x64) ----------------------------------------------------
//FuncRes mbs_FuncCmd(void)
//{
//	// ��������� ��������� ������� � ���������� ������ �������� ������
//	mbsDataNum = InterfaceCmdHandler(mbsRxBuf[2] << 8 | mbsRxBuf[3], mbsRxBuf[4] << 8 | mbsRxBuf[5], mbsRxBuf[6] << 8 | mbsRxBuf[7]);
//	
//	// ��������� ��������� ������
//	mbsTxBuf[0] = mbsAddr;        // ��������� ����� slave-����������
//	mbsTxBuf[1] = MBS_FUNC_CMD;   // ��������� ��� ����������� �������
//	mbsTxBuf[2] = mbsDataNum;     // ��������� ���-�� ������ � ������
//	
//	mbsCount1 = 0;   // ������ ������� �����������
//	mbsCount2 = 3;   // ������ ������� ������ ��� ��������� ����� ����������� ������ � ������
//		
//	// ��������� � ����� ����������� ������
//	for( ; mbsCount1 <= mbsDataNum; mbsCount1++, mbsCount2++)
//	{
//		mbsTxBuf[mbsCount2]   = intfData[mbsCount1] >> 8;
//		mbsTxBuf[++mbsCount2] = intfData[mbsCount1] & 0x00FF;
//	} // for	
//	
//	// �������� ����������� ����� ��������������� ������ � ��������� � ����� ������
//	mbsCRC =  mbs_GetCrc16(mbsTxBuf, mbsCount2 - 2);
//	mbsTxBuf[mbsCount2 - 2] = mbsCRC & 0x00ff;
//	mbsTxBuf[mbsCount2 - 1] = mbsCRC >> 8;
//	
//	// ���������� �������� ������
//	mbs_SendDataIni(mbsCount2);
//	
//	return FRES_OK;
//} // mbs_FuncCmd()
