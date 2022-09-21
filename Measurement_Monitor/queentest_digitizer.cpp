﻿#include "queentest_digitizer.h"

#include <iostream>
#include "QTXdmaApi.h"
#include "qtxdmaapiinterface.h"
#include "QT_IMPORT.h"
//#include "TraceLog.h"
#include "./include/pthread.h"
#include "./include/LOG_DEBUG.h"


extern STXDMA_CARDINFO pstCardInfo;
QT_IMPORT m_Board;

#define PCIE_DMA_DDR 0x000000
#define SYMBOL2ASCII(symbol) #symbol
#define QTFM_COMMON_TRIGGER_TYPE_RISING_EDG 2
#define QTFM_COMMON_TRIGGER_TYPE_FALLING_EDG 3

//Log_TraceLog g_Log(std::string("./logs/KunchiUpperMonitor.log"));
//Log_TraceLog* pLog = &g_Log;

/*
void printfLog(int nLevel, const char* fmt, ...)
{
	if (pLog == NULL)
		return;

	char buf[1024];
	va_list list;
	va_start(list, fmt);
	vsprintf(buf, fmt, list);
	va_end(list);

	pLog->Trace(nLevel, buf);
}
*/

void measurement()
{

	printf("here");


	/*

	int iRet = QTXdmaOpenBoard(&pstCardInfo, 0);//打开板卡
	m_Board.getCardInfo();

	//软件复位
	CHECK_COP_RET(m_Board.QT_BoardReset(), < , 0, -1, -1, "");					//板卡复位
	printf("Execute %s successfully!\r\n", SYMBOL2ASCII(QT_BoardReset));

	CHECK_COP_RET(m_Board.QT_BoardGetInterruptClear(), < , 0, -1, -1, "");			//中断清除
	printf("Execute %s successfully!\r\n", SYMBOL2ASCII(QT_BoardGetInterruptClear));



	uint32_t triggercouts = 1;
	uint32_t dmaTotolBytes = (80000 / 64) * 64;//单次采集产生中断数据量
	uint32_t dmaOnceBytes = 2048;//单位：字节
	uint32_t transmitBytes = dmaTotolBytes;//一般为载板DDR内存的一半  变量 单位：字节
	uint32_t allBytes = transmitBytes;


	CHECK_COP_RET(m_Board.QT_BoardMultiTrigerSingleDma(dmaOnceBytes, dmaTotolBytes, transmitBytes), < , 0, -1, -1, "");
	printf("Execute %s successfully!\r\n", SYMBOL2ASCII(QT_BoardMultiTrigerSingleDma));




	//软件触发
	CHECK_COP_RET(m_Board.QT_BoardSoftTriggerSet(), < , 0, -1, -1, "");//设置触发模式和触发次数
	printf("Execute %s successfully!\r\n", SYMBOL2ASCII(QT_BoardSoftTrigger));
	//内部秒脉冲触发
	//CHECK_COP_RET(m_Board.QT_BoardPulseTrigger(leijiacount,1000000,20), < , 0, -1, -1, "");
	//printf("Execute %s successfully!\r\n", SYMBOL2ASCII(QT_BoardPulseTrigger));
	////外部下降沿触发
	//CHECK_COP_RET(m_Board.QT_BoardExtrigger_falling(triggercount), < , 0, -1, -1, "");
	//printf("Execute falling %s successfully!\r\n", SYMBOL2ASCII(QT_BoardExtrigger_falling));
	//外部上升沿触发
	//CHECK_COP_RET(m_Board.QT_BoardExtriggerSet(triggercouts, QTFM_COMMON_TRIGGER_TYPE_RISING_EDG, 20), < , 0, -1, -1, "");				//设置为外部脉冲上升沿触发，触发次数为累加次数
	//printf("Execute rising %s successfully!\r\n", SYMBOL2ASCII(QT_BoardExtriggerSet));
	////通道上升沿触发
	//CHECK_COP_RET(m_Board.QT_BoardChannelTrigger(4, triggercount,1,1000,0), < , 0, -1, -1, "");
	//printf("Execute rising %s successfully!\r\n", SYMBOL2ASCII(QT_BoardChannelTrigger));
	////通道下降沿触发
	//CHECK_COP_RET(m_Board.QT_BoardChannelTrigger(5, triggercount, 1, 0, 1000), < , 0, -1, -1, "");
	//printf("Execute falling %s successfully!\r\n", SYMBOL2ASCII(QT_BoardChannelTrigger));



	CHECK_COP_RET(m_Board.QT_BoardEnableInterruptSwitch(), < , 0, -1, -1, "");//使能PCIE中断
	printf("Execute %s successfully!\r\n", SYMBOL2ASCII(QT_BoardEnableInterruptSwitch));

	uint32_t ADDR = 0x40000000;
	uint32_t iReadbytes = 8 * 1024 * 1024;
	uint8_t* buffer = (uint8_t*)malloc(transmitBytes);
	if (NULL == buffer)
	{
		return 0;
	}
	for (int i = 0; i < 20; i++)
	{

		CHECK_COP_RET(m_Board.QT_BoardSetADCStart(), < , 0, -1, -1, "");//启动ADC采集
		printf("Execute %s successfully!\r\n", SYMBOL2ASCII(QT_BoardSetADCStart));

		uint16_t offsetCount = 0;


		memset(buffer, 0, transmitBytes);
		printf("申请内存成功 内存大小为: %d bytes\n", transmitBytes);
		QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_TRIG_CTRL, 0x10, 1);//设置秒脉冲使能
		m_Board.QT_BoardInterruptGatherType();
		printf("清除中断成功|\n");
		uint32_t offset = 0;
		if (transmitBytes > iReadbytes) {
			do
			{

				if (transmitBytes >= iReadbytes)
				{
					QTXdmaGetDataBuffer(ADDR + offset, &pstCardInfo, &buffer[offsetCount * iReadbytes], iReadbytes, 0);//获取数据到缓存
					//printf("这是大于8MB中的8MB%s的第%d次搬运数据，搬运地址为%d,搬运剩余数据量大小为%d\n", cc.c_str(), aa, ADDR + offset, pingpongonebytes);

				}
				else if (transmitBytes < iReadbytes)
				{
					QTXdmaGetDataBuffer(ADDR + offset, &pstCardInfo, &buffer[offsetCount * iReadbytes], transmitBytes, 0);//获取数据到缓存

					//printf("这是大于8MB中的小于8MB%s的第%d次搬运数据，搬运地址为%d,数据量大小为%d\n", cc.c_str(), aa, ADDR + offset, pingpongonebytes);
					transmitBytes = 0;
					offsetCount = 0;
					break;
				}

				transmitBytes -= iReadbytes;
				offset += iReadbytes;
				offsetCount += 1;

			} while (transmitBytes > 0);
		}
		else
		{
			QTXdmaGetDataBuffer(ADDR, &pstCardInfo, buffer, transmitBytes, 0);//获取数据到缓存

		}
		memset(buffer, 0, transmitBytes);

		char allFileName[32] = { 0 };
		sprintf(allFileName, "%sxdma%d.bin", "E:/1/7131DC+/", i);
		FILE* fpall = fopen(allFileName, "wb+");
		if (NULL == fpall)
		{
			return 0;
		}
		fwrite(buffer, 1, allBytes, fpall);
		fclose(fpall);
		fpall = NULL;
		printf("采集完成第%d次\n", i);
		CHECK_COP_RET(m_Board.QT_BoardSetADCStop(), < , 0, -1, -1, "");//多次触发来一次中断  停止采集
		printf("Execute %s successfully!\r\n", SYMBOL2ASCII(QT_BoardSetADCStop));

	}
	free(buffer);
	buffer = NULL;
	QTXdmaCloseBoard(&pstCardInfo);
	Sleep(3000);
	printf("停止采集\n");
	system("pause");

	return 0;

	*/
}