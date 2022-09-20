#include "QT_IMPORT.h"
#include "QTXdmaApi.h"
#include "qtxdmaapiinterface.h"
#include "./include/pthread.h"
#include "pub.h"

//extern STXDMA_CARDINFO pstCardInfo;
STXDMA_CARDINFO pstCardInfo;
#define PCIE_DMA_DDR 0x00000000

QT_IMPORT::QT_IMPORT() {

}
void QT_IMPORT::getCardInfo()
{
	uint32_t uintValue = 0;
	QTXdmaApiInterface::Func_QTXdmaReadRegister(&pstCardInfo, BASE_BOARD_INFO, OFFSET_BDINFO_BDINFO, &uintValue);
	string hexstr = pub::DecIntToHexStr(uintValue);
	printf("板卡类型 is %s.\n", hexstr.data());
	QTXdmaApiInterface::Func_QTXdmaReadRegister(&pstCardInfo, BASE_BOARD_INFO, OFFSET_BDINFO_SOFT_VER, &uintValue);
	string vexstr = pub::DecIntToHexStr(uintValue);
	printf("逻辑版本号 is %s.\n", vexstr.data());
	QTXdmaApiInterface::Func_QTXdmaReadRegister(&pstCardInfo, BASE_BOARD_INFO, OFFSET_BDINFO_ADC, &uintValue);
	string hexAdcStr = pub::DecIntToHexStr(uintValue);//表示转换成16进制存入字符串
	int strLen = hexAdcStr.length();
	uintValue = std::stoi(hexAdcStr);
	uint32_t c1 = uintValue / 10000;//采样率
	uint32_t c2 = uintValue / 100 - (uintValue / 10000) * 100;//通道数
	uint32_t c3 = uintValue - (uintValue / 100) * 100;//分辨率
	printf("板卡采样率 is %d\n", c1);
	printf("板卡通道数 is %d\n", c2);
	printf("板卡分辨率 is %d\n\n", c3);
	uint32_t state = 0;
	QTXdmaApiInterface::Func_QTXdmaReadRegister(&pstCardInfo, BASE_BOARD_INFO, 0x20, &state);
	printf("状态值为:%#X\n\n", state);

};
int QT_IMPORT::QT_BoardReset() {//软件复位
	int ret = 0;

	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_PCIE_INTR, 0x18, 0);//	
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_PCIE_INTR, 0x18, 1);
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_PCIE_INTR, 0x18, 0);//

	return ret;

}

int QT_IMPORT::QT_BoardSetADCStart() {//启动ADC采集
	int ret = 0;

	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_PCIE_INTR, 0x08, 0);//
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_PCIE_INTR, 0x08, 1);//
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_PCIE_INTR, 0x08, 0);//

	return ret;
}
int QT_IMPORT::QT_BoardSetADCStop() {//停止ADC采集
	int ret = 0;

	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_PCIE_INTR, 0x10, 0);//
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_PCIE_INTR, 0x10, 1);//
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_PCIE_INTR, 0x10, 0);//
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_DMA_ADC, 0x20, 0);
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_DMA_ADC, 0x00, 0);//

	return ret;

}
int QT_IMPORT::QT_BoardEnableInterruptSwitch() {//使能PCIE中断
	int ret = 0;

	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_PCIE_INTR, 0x00, 1);//

	return ret;

}
int QT_IMPORT::QT_BoardGetInterruptClear() {//清除中断
	int ret = 0;

	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_PCIE_INTR, 0x04, 0);//
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_PCIE_INTR, 0x04, 1);//
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_PCIE_INTR, 0x04, 0);//

	return ret;
}


void QT_IMPORT::QT_BoardInterruptGatherType() {
	uint32_t inpoint = 0;
	do {
		inpoint = QTXdmaGetOneEvent(&pstCardInfo);
		printf("获取中断成功\n");
		if (inpoint == 1) {
			QT_BoardGetInterruptClear();

		}
	} while (inpoint != 1);
}
void QT_IMPORT::QT_BoardLunxunGatherType() {
	unsigned int uTriggerpoint = 0;
	do
	{
		QTXdmaApiInterface::Func_QTXdmaReadRegister(&pstCardInfo, BASE_PCIE_INTR, 0x1C, &uTriggerpoint, false);     //adc采样率(单位M)  暂时未用
		if (uTriggerpoint == 1) {
			QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_PCIE_INTR, OFFSET_PCIE_INTR_INTR_CLEAR, 0);//清除中断
			QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_PCIE_INTR, OFFSET_PCIE_INTR_INTR_CLEAR, 1);//清除中断
			QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_PCIE_INTR, OFFSET_PCIE_INTR_INTR_CLEAR, 0);//清除中断			
		}
	} while (uTriggerpoint != 1);
}
int QT_IMPORT::QT_BoardLeiJia(int leiJiaCount, int leiJiaLength) {
	int ret = 0;

	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, 0xA000, 0x24, leiJiaCount);//累加次数
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, 0xA000, 0x28, leiJiaLength);//累加长度

	return ret;

}
int QT_IMPORT::QT_BoardChannelSet(int ChannelA, int ChannelB) {
	int ret = 0;

	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, 0xA000, 0x48, ChannelA);//累加通道选择A
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, 0xA000, 0x4C, ChannelB);//累加通道选择B

	return ret;

}
int QT_IMPORT::QT_BoardMultiTrigerSingleDma(uint32_t dmaOnceBytes, uint32_t dmaTotolBytes, uint32_t  transmitBytes) {
	int ret = 0;

	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_DMA_ADC, 0x14, dmaOnceBytes);//DMA单次搬运的长度
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_DMA_ADC, 0x18, dmaTotolBytes);//每一次触发的长度 如果是触发式采集应该注意触发频率和单次采集长度的大小关系 单次采集长度<触发频率理论采集长度
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_DMA_ADC, 0x04, 0x40000000);//乒乓操作第一块地址
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_DMA_ADC, 0x10, 0);//地址范围超出32位，高位在偏移地址0x10处设置
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_DMA_ADC, 0x00, 0);
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_DMA_ADC, 0x20, 0);

	return ret;
}
/*
* @brief 软件触发
*/
int QT_IMPORT::QT_BoardSoftTriggerSet() {
	int ret = 0;

	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_TRIG_CTRL, 0x00, 0);//设置触发模式
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_TRIG_CTRL, 0x04, 1);//设置触发次数

	return ret;

}
/**
* @brief 内部秒脉冲触发
*
* @param[in] counts 	设置触发次数。
* @param[in] pulse_period 设置秒脉冲触发周期。
* @param[in] pulse_width 设置秒脉冲触发宽度。
*/
int QT_IMPORT::QT_BoardPulseTriggerSet(int counts, int pulse_Period, int pulse_Width) {
	int ret = 0;

	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_TRIG_CTRL, 0x00, 1);
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_TRIG_CTRL, 0x04, counts);
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_TRIG_CTRL, 0x08, pulse_Period);
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_TRIG_CTRL, 0x0C, pulse_Width);

	return ret;
}
/*
* @brief 外部触发
* @param[in] counts 	设置触发次数。
* @param[in] type 	设置触发为上升沿或下降沿。
*/
int QT_IMPORT::QT_BoardExtriggerSet(uint32_t counts, uint32_t type, uint32_t pulseWidth) {
	int ret = 0;

	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_TRIG_CTRL, 0x00, type);//设置触发模式
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_TRIG_CTRL, 0x04, counts);//设置触发次数
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_TRIG_CTRL, 0x0C, pulseWidth);		//设置秒脉冲宽度

	return ret;

}

/**
* @brief 通道触发
*
* @param[in] mode 设置通道触发触发模式。
* @param[in] counts 	设置触发次数。
* @param[in] channelID 设置通道触发触发通道ID号。
* @param[in] rasing_codevalue 设置通道上升沿触发电平。
* @param[in] falling_codevalue 设置通道下降沿触发电平。
*/
int QT_IMPORT::QT_BoardChannelTriggerSet(int mode, int counts, int channelID, int rasing_CodeValue, int falling_CodeValue) {
	int ret = 0;

	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_TRIG_CTRL, 0x00, mode);
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_TRIG_CTRL, 0x04, counts);
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_TRIG_CTRL, 0x24, channelID);
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_TRIG_CTRL, 0x14, rasing_CodeValue);
	ret = QTXdmaApiInterface::Func_QTXdmaWriteRegister(&pstCardInfo, BASE_TRIG_CTRL, 0x18, falling_CodeValue);

	return ret;
}

