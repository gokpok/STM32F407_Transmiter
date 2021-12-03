
// ------------------------------------------------------------------------------------------------
// ������ ������ ������� �� ��������� ModbusRTU � ������ master-����������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// 
// ���������, ����������� ������ � �������� ��������� �������� ����� ��������� (0x03)
// ------------------------------------------------------------------------------------------------

#include "mbmFuncGetRegs.h"
#include "ModbusMaster.h"
#include "mbmSendData.h"
#include "mbmError.h"
#include "mbmUtils.h"
#include "mbmData.h"
#include "mbsCRC.h"


// �������� ������� �� ���������� �������
FuncRes QueryGetRegs(uint8_t addr, uint16_t first, uint16_t quant);

// ��������� ������
FuncRes AnswerGetRegs(uint8_t addr, uint16_t quant, uint16_t *data);

// ��������� ����������� ������
void mbm_GetRegs(uint16_t quant, uint16_t *data);

	 

// ���������� ������� � �������� ��������� ����� ��������� (0x03) ---------------------------------
FuncRes mbm_FuncGetRegs(uint8_t addr, uint16_t first, uint16_t quant, uint16_t *data)
{	
	// ���� ������ �� ������� ����� - ���������� ������
	if(mbmAnsWait == 0) return QueryGetRegs(addr, first, quant);
	
	// ���� ���������� ������� �� ��������� - ������������ �����
	return AnswerGetRegs(addr, quant, data);
} // mbs_FuncGetRegs()



// �������� ������� �� ���������� ������� ---------------------------------------------------------
FuncRes QueryGetRegs(uint8_t addr, uint16_t first, uint16_t quant)
{
	// ���� ���-�� ����������� ������ ��������� ���������� - ������ � �������
	if(quant > mbmMaxLen)
		return mbm_ErrHandler(MBM_ERR_MAX_LEN);
	
	// ��������� ����� �������
	mbmTxBuf[0] = addr;               // ����� ����������
	mbmTxBuf[1] = MBM_FUNC_GET_REGS;  // ��� ������� ������ ���������
	mbmTxBuf[2] = first >> 8;         // ������ ������������� ���������
	mbmTxBuf[3] = first & 0x00FF;     // --- *** ---
	mbmTxBuf[4] = quant >> 8;         // ���-�� ������������� ���������
	mbmTxBuf[5] = quant & 0x00FF;     // --- *** ---
	
	// �������� ����������� ����� ��������������� ������� � ��������� � ����� ������
	mbmCRC = mbs_GetCrc16(mbmTxBuf, 6);
	mbmTxBuf[6] = mbmCRC & 0x00ff;
	mbmTxBuf[7] = mbmCRC >> 8;	
	
	// ���������� �������� ������
	mbm_SendDataIni(8);
	
	return FRES_NONE;
} // QueryGetRegs()



// ��������� ������ -------------------------------------------------------------------------------
FuncRes AnswerGetRegs(uint8_t addr, uint16_t quant, uint16_t *data)
{
	// ���� �������� ������ ��� - ���������� ��������� �������� ��������
	if(mbmEndReciev == 0)
		return mbm_CheckTimeout();
	
	// ���������� ���� �������� ������
	mbmEndReciev = 0;
	
	// ���� ����������� ����� �� ��������� - ������ ��� ����������
	if(mbm_CheckCRC() == FRES_ERR) return FRES_NONE;
	
	// ���� ����� � ������ �� ������������� ������� - ������ ��� ����������
	if(mbmRxBuf[0] != addr) return FRES_NONE;
	
	// ���� ����� �������� ������ - ������������ � ���������� ������
	if(mbmRxBuf[1] == (0x80 | MBM_FUNC_GET_REGS))
		return mbm_ErrHandler((MBM_ErrEnum)mbmRxBuf[2]);
	
	// ���� ����������� ������ �� ������������� ������� - ������������ � ���������� ������
	if((mbmRxBuf[1] != MBM_FUNC_GET_REGS) || (mbmRxBuf[2] != (quant * 2)))
		return mbm_ErrHandler(MBM_ERR_ANSWER);
	
	// ���� ���������� ������� �� ���������, ��...
	mbm_GetRegs(quant, data);   // �������� ����������� ������
	mbmAnsWait = 0;         // ���������� ���� �������� ������
	mbmErr = MBM_ERR_NONE;  // ���������� ���������� ������
	return FRES_OK;         // ���������� ������������� ���������
} // AnswerGetRegs()



// ��������� ����������� ������ -------------------------------------------------------------------
void mbm_GetRegs(uint16_t quant, uint16_t *data)
{	
	mbmCount1 = 0;
	mbmCount2 = 3;
	
	// ���������� ���������� ������ � ������� �����
	for ( ; mbmCount1 < quant; mbmCount1++, mbmCount2 += 2)
		data[mbmCount1] = (mbmRxBuf[mbmCount2] << 8) | (mbmRxBuf[mbmCount2 + 1]);
} // GetRegs()
