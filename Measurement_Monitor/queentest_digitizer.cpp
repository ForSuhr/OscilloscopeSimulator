#include "queentest_digitizer.h"


//#define PCIE_DMA_DDR 0x000000
//#define QTFM_COMMON_TRIGGER_TYPE_RISING_EDG 2
//#define QTFM_COMMON_TRIGGER_TYPE_FALLING_EDG 3
//



// Constructor
QueenTest_Digitizer::QueenTest_Digitizer() : QThread()
{
	pstCardInfo = STXDMA_CARDINFO();
	m_Board = QT_IMPORT();
	dma_total_bytes = 0;
	base_addr = 0;
	offset = 0;
	buffer_once_bytes = 0;
	buffer = 0;
	buffer_count = 0;
}

// Destructor
QueenTest_Digitizer::~QueenTest_Digitizer()
{
	;
}


int QueenTest_Digitizer::digitizer_connect()
{
	// Connect to digitizer
	QTXdmaOpenBoard(&pstCardInfo, 0);
	return 0;
}


int QueenTest_Digitizer::digitizer_getinfo()
{
	// Get digitizer info
	m_Board.getCardInfo();
	return 0;
}


int QueenTest_Digitizer::digitizer_reset()
{
	// Reset digitizer
	m_Board.QT_BoardReset();
	return 0;
}


int QueenTest_Digitizer::digitizer_clean_interrupt()
{
	// Clean interrupt
	m_Board.QT_BoardGetInterruptClear();
	return 0;
}

/**
 * @brief Configure the dma
 * @param dma_once_bytes Bytes per single transmission of dma
 * @param dma_interrupt_bytes Bytes per interrupt signal from dma to cpu. If dma finishes transmitting this byte of data, dma will send an interrupt to the cpu.
 * @param trigger_number Trigger number
 * @param dma_total_bytes Total bytes from dma to memory
 * @return 0
*/
int QueenTest_Digitizer::digitizer_dma_configure(Ptr_Dma_Configuration ptr_dma_configuration)
{

	dma_total_bytes = ptr_dma_configuration->dma_interrupt_bytes * ptr_dma_configuration->trigger_number;

	// Call dma api to configure the dma, tell the dma how to transmit data
	m_Board.QT_BoardMultiTriggerSingleDma
	(	ptr_dma_configuration->dma_once_bytes,
		ptr_dma_configuration->dma_interrupt_bytes,
		dma_total_bytes
	);
	return 0;
}


int QueenTest_Digitizer::digitizer_mode_configure()
{
	m_Board.QT_BoardSoftTriggerSet();
	return 0;
}


int QueenTest_Digitizer::digitizer_pcie_interrupt()
{
	m_Board.QT_BoardEnableInterruptSwitch();
	return 0;
}


int QueenTest_Digitizer::digitizer_buffer_set()
{
	base_addr = 0x40000000;
	offset = 0;
	buffer_once_bytes = 8 * 1024 * 1024;
	buffer = (uint8_t*)malloc(dma_total_bytes);
	if (NULL == buffer)
	{
		return -1;
	}
	return 0;
}


int QueenTest_Digitizer::digitizer_start_adc()
{
	m_Board.QT_BoardSetADCStart();
	offset = 0;
	buffer_count = 0;
	// Initialize the buffer	
	memset(buffer, 0, dma_total_bytes);
	if (dma_total_bytes > buffer_once_bytes) {
		do
		{
			// The unit part of the buffer
			if (dma_total_bytes >= buffer_once_bytes)
			{
				QTXdmaGetDataBuffer(base_addr + offset, &pstCardInfo, &buffer[buffer_count * buffer_once_bytes], buffer_once_bytes, 0);
			}
			else if (dma_total_bytes < buffer_once_bytes)
			{
				// The last part of the buffer
				QTXdmaGetDataBuffer(base_addr + offset, &pstCardInfo, &buffer[buffer_count * buffer_once_bytes], dma_total_bytes, 0);
				dma_total_bytes = 0;
				buffer_count = 0;
				break;
			}

			dma_total_bytes -= buffer_once_bytes;
			offset += buffer_once_bytes;
			buffer_count += 1;

		} while (dma_total_bytes > 0);
	}
	else
	{
		QTXdmaGetDataBuffer(base_addr, &pstCardInfo, buffer, dma_total_bytes, 0);
	}

	return 0;
}


int QueenTest_Digitizer::digitizer_oscilloscope_update()
{

	return 0;
}

int QueenTest_Digitizer::foo()
{
	return 0;
}

////////for (int i = 0; i < 1024; i++)
////////{
////////	ch1[i] = buffer[4 * i];
////////	std::this_thread::sleep_for(std::chrono::seconds(1));
//////
////////}

int QueenTest_Digitizer::digitizer_stop_adc()
{
	memset(buffer, 0, dma_total_bytes);
	m_Board.QT_BoardSetADCStop();
	free(buffer);
	buffer = NULL;
	return 0;
}


int QueenTest_Digitizer::digitizer_disconnect()
{
	// Disconnect from digitizer
	QTXdmaCloseBoard(&pstCardInfo);
	return 0;
}

void QueenTest_Digitizer::run()
{
	this->foo();
}

