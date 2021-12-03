
// ------------------------------------------------------------------------------------------------
// ������ ������ ������� �� ��������� ModbusRTU � ������ master-����������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// 
// ���������, ����������� ������ � �������� ������� �������� ����� ��������� (0x10)
// ------------------------------------------------------------------------------------------------

#include "mbmFuncSetRegs.h"
#include "ModbusMaster.h"
#include "mbmSendData.h"
#include "mbmError.h"
#include "mbmUtils.h"
#include "mbmData.h"
#include "mbsCRC.h"


// �������� ������� �� ���������� �������
FuncRes QuerySetRegs(uint8_t addr, uint16_t first, uint16_t quant, uint16_t *data);

// ��������� ������
FuncRes AnswerSetRegs(uint8_t addr, uint16_t quant);

	 

// ���������� ������� � �������� ������� ����� ��������� (0x03) ---------------------------------
FuncRes mbm_FuncSetRegs(uint8_t addr, uint16_t first, uint16_t quant, uint16_t *data)
{	
	// ���� ������ �� ������� ����� - ���������� ������
	if(mbmAnsWait == 0) return QuerySetRegs(addr, first, quant, data);
	
	// ���� ���������� ������� �� ��������� - ������������ �����
	return AnswerSetRegs(addr, quant);
} // mbs_FuncSetRegs()



// �������� ������� �� ���������� ������� ---------------------------------------------------------
FuncRes QuerySetRegs(uint8_t addr, uint16_t first, uint16_t quant, uint16_t *data)
{
	// ���� ���-�� ����������� ������ ��������� ���������� - ������ � �������
	if(quant > mbmMaxLen)
		return mbm_ErrHandler(MBM_ERR_MAX_LEN);
	
	// ��������� ����� �������
	mbmTxBuf[0] = addr;               // ����� ����������
	mbmTxBuf[1] = MBM_FUNC_SET_REGS;  // ��� ������� ������ ���������
	mbmTxBuf[2] = first >> 8;         // ������ ������������� ���������
	mbmTxBuf[3] = first & 0x00FF;     // --- *** ---
	mbmTxBuf[4] = quant >> 8;         // ���-�� ������������� ���������
	mbmTxBuf[5] = quant & 0x00FF;     // --- *** ---
	mbmTxBuf[6] = quant * 2;          // --- *** ---
		
	mbmCount1 = 0;  // ���������� ������ ��������
	mbmCount2 = 7;  // ������ ������� ������ ��� ������ ������ � ������
	
	// ��������� ������������ ������ � �����
	for( ; mbmCount1 < quant; mbmCount1++, mbmCount2 += 2)
	{
		mbmTxBuf[mbmCount2]     = data[mbmCount1] >> 8;
		mbmTxBuf[mbmCount2 + 1] = data[mbmCount1] & 0x00FF;
	} // for
	
	// �������� ����������� ����� ��������������� ������� � ��������� � ����� ������
	mbmCRC = mbs_GetCrc16(mbmTxBuf, quant * 2 + 7);
	mbmTxBuf[quant * 2 + 7] = mbmCRC & 0x00ff;
	mbmTxBuf[quant * 2 + 8] = mbmCRC >> 8;	
	
	// ���������� �������� ������
	mbm_SendDataIni(quant * 2 + 9);
	
	return FRES_NONE;
} // QuerySetRegs()



// ��������� ������ -------------------------------------------------------------------------------
FuncRes AnswerSetRegs(uint8_t addr, uint16_t quant)
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
	if(mbmRxBuf[1] == (0x80 | MBM_FUNC_SET_REGS))
		return mbm_ErrHandler((MBM_ErrEnum)mbmRxBuf[2]);
	
	// ���� ����������� ������ �� ������������� ������� - ������������ � ���������� ������
	if(mbmRxBuf[1] != MBM_FUNC_SET_REGS)
		return mbm_ErrHandler(MBM_ERR_ANSWER);
	
	// ���� ���������� ������� �� ���������, ��...
	mbmAnsWait = 0;         // ���������� ���� �������� ������
	mbmErr = MBM_ERR_NONE;  // ���������� ���������� ������
	return FRES_OK;         // ���������� ������������� ���������
} // AnswerSetRegs()
