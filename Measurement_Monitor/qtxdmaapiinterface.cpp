#include "qtxdmaapiinterface.h"

//void printfLog(int nLevel, const char* fmt, ...);

QTXdmaApiInterface::QTXdmaApiInterface()
{

}

int QTXdmaApiInterface::Func_QTXdmaReadRegister(STXDMA_CARDINFO* pstCardInfo, uint32_t base, uint32_t offset, uint32_t* value, bool bWrilteLog)
{
	return QTXdmaReadRegister(pstCardInfo, base, offset, value);
}

int QTXdmaApiInterface::Func_QTXdmaWriteRegister(STXDMA_CARDINFO* pstCardInfo, uint32_t base, uint32_t offset, uint32_t value)
{
	if (!pstCardInfo) {

		return -1;
	}

	//printfLog(5, "[QTXdmaApiInterface::Func_QTXdmaWriteRegister], base 0x%x, offset 0x%x, value 0x%x", base, offset, value);

	for (int i = 0; i < 10; i++) {
		QTXdmaWriteRegister(pstCardInfo, base, offset, value);

	}
	return 0;
}
