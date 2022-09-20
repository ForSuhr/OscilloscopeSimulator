#pragma once
#ifndef QTXDMAAPIINTERFACE_H
#define QTXDMAAPIINTERFACE_H

#include "QTXdmaApi.h"

class QTXdmaApiInterface
{
public:
    QTXdmaApiInterface();
public:
    static int Func_QTXdmaReadRegister(STXDMA_CARDINFO* pstCardInfo, uint32_t base, uint32_t offset, uint32_t* value, bool bWrilteLog = true);
    static int Func_QTXdmaWriteRegister(STXDMA_CARDINFO* pstCardInfo, uint32_t base, uint32_t offset, uint32_t value);
};

#endif // QTXDMAAPIINTERFACE_H
