#pragma once
#include <iostream>
#include "QTXdmaApi.h"
#include "qtxdmaapiinterface.h"
#include "QT_IMPORT.h"
#include "./include/pthread.h"
#include "./include/LOG_DEBUG.h"


struct Dma_Configuration
{
	uint32_t dma_once_bytes;
	uint32_t dma_interrupt_bytes;
	uint32_t trigger_number;
};


typedef struct Dma_Configuration* Ptr_Dma_Configuration;


class QueenTest_Digitizer
{
public:
	QueenTest_Digitizer();
	~QueenTest_Digitizer();
	int digitizer_connect();
	int digitizer_getinfo();
	int digitizer_reset();
	int digitizer_clean_interrupt();
	int digitizer_dma_configure(Ptr_Dma_Configuration ptr_dma_configuration);
	int digitizer_mode_configure();
	int digitizer_pcie_interrupt();
	int digitizer_disconnect();

private:
	STXDMA_CARDINFO pstCardInfo;
	QT_IMPORT m_Board;
};

