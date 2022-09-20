#pragma once
#ifndef QTIMPORT_H
#define QTIMPORT_H
#include <string>

using namespace std;

class QT_IMPORT
{
public:
	QT_IMPORT();
public:
	void getCardInfo();
	int QT_BoardReset();
	int QT_BoardEnableInterruptSwitch();
	int QT_BoardSetADCStart();
	int QT_BoardSetADCStop();
	int QT_BoardGetInterruptClear();
	void QT_BoardInterruptGatherType();
	void QT_BoardLunxunGatherType();
	int QT_BoardLeiJia(int leiJiaCount, int leiJiaLength);
	int QT_BoardChannelSet(int ChannelA, int ChannelB);
	int QT_BoardMultiTrigerSingleDma(uint32_t dmaOnceBytes, uint32_t dmaTotolBytes, uint32_t  transmitBytes);
	int QT_BoardSoftTriggerSet();
	int QT_BoardPulseTriggerSet(int counts, int pulse_Period, int pulse_Width);
	int QT_BoardChannelTriggerSet(int mode, int counts, int channelID, int rasing_CodeValue, int falling_CodeValue);
	int QT_BoardExtriggerSet(uint32_t counts, uint32_t type, uint32_t pulseWidth);


private:


};
#endif // QTIMPORT_H
