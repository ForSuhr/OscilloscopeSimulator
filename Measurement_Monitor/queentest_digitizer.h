#pragma once
#include <iostream>
#include "QTXdmaApi.h"
#include "qtxdmaapiinterface.h"
#include "QT_IMPORT.h"
#include "./include/pthread.h"
#include "./include/LOG_DEBUG.h"
//#include <QTextStream>
#include <QThread>
#include "QMessageBox"


struct Dma_Configuration
{
	uint32_t dma_once_bytes;
	uint32_t dma_interrupt_bytes;
	uint32_t trigger_number;
};


typedef struct Dma_Configuration* Ptr_Dma_Configuration;


//uint16_t ch1[1024] = {};


class QueenTest_Digitizer : public QThread
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
	int digitizer_buffer_set();
	int digitizer_start_adc();
	int digitizer_oscilloscope_update();
	int foo();
	int digitizer_stop_adc();
	int digitizer_disconnect();

	void run() override;
	

private:
	// Handle
	STXDMA_CARDINFO pstCardInfo;
	QT_IMPORT m_Board;
	uint32_t dma_total_bytes;
	// Base address
	uint32_t base_addr;
	// Offset, offset_address = base_addr + offset
	uint16_t offset;
	uint32_t buffer_once_bytes;
	uint8_t* buffer;
	uint16_t buffer_count;
};

