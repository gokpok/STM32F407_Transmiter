
// ------------------------------------------------------------------------------------------------
// ?????? ?????? ??????? ?? ????????? ModbusRTU ? ?????? master-??????????
// ??????????? ?? ??????? ?. ?. (edmahalich@yandex.ua)
// 
// ?????????, ?????????????? ?????? ??????
// ------------------------------------------------------------------------------------------------

#include "mbmError.h"
#include "mbmData.h"


// ????????? ?????? ?????? ------------------------------------------------------------------------
FuncRes mbm_ErrHandler(MBM_ErrEnum err)
{
	mbmErr = err;         // ?????????? ??????
	mbmAnsWait = 0;       // ?????????? ???? ???????? ??????
	return FRES_ERR;
} // mbs_ErrHandler
