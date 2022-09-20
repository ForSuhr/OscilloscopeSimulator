#ifndef _QTXDMAAPI_H_
#define _QTXDMAAPI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

//#include "pub.h"

#define REG_SPACE_SIZE (64 * 1024) //64KB register space

#define BASE_CONTROL (0x0000)
#define BASE_DMA_ADC (0x1000)
#define BASE_ADC_CTRL (0x2000)
#define BASE_BOARD_INFO (0x3000)
#define BASE_DMA_DAC (0x4000)
#define BASE_DAC_CTRL (0x5000)
#define BASE_PCIE_INTR (0x6000)
#define BASE_TRIG_CTRL (0x7000)
#define BASE_DMA_DAC2 (0x8000)
#define BASE_DAC_CTRL2 (0x9000)

#define OFFSET_ADC_CTRL_SAMPLE_RATE 0x00

#define OFFSET_TRIG_CTRL_TRIG_MODE 0x00                       //触发模式 目前6种 实现4种, 头文件中通过TRIG_MODE_关键字进行查找触发模式列表
#define OFFSET_TRIG_CTRL_TRIG_COUNT 0x04                      //触发次数(0 表示无限次触发，直至不满足触发条件，或主动停止)   软件触发下无效
#define OFFSET_TRIG_CTRL_PULSE_PERIOD 0x08                    //秒脉冲周期  单位10ns
#define OFFSET_TRIG_CTRL_PULSE_WIDTH 0x0C                     //秒脉冲宽度  单位10ns
#define OFFSET_TRIG_CTRL_PULSE_ENABLE 0x10                    //秒脉冲使能  高电平有效
#define OFFSET_TRIG_CTRL_CHANNEL_RISING_EDGE_TRIG_LEVEL 0x14  //通道上升沿触发电平
#define OFFSET_TRIG_CTRL_CHANNEL_FALLING_EDGE_TRIG_LEVEL 0x18 //通道下降沿触发电平

#define OFFSET_ADC_CTRL_SAMPLE_RATE 0x00        //adc采样率(单位M)
#define OFFSET_ADC_CTRL_EXTERNAL_REFERENCE 0x04 //外参考,外时钟使能 bit0=外时钟使能  bit1=外参考使能  高电平有效 二者互斥
#define OFFSET_ADC_CTRL_ADC_ENABLE 0x08         //配置adc使能(上升沿有效)

#define OFFSET_BDINFO_BDINFO 0x00   //板卡信息(子板,载板) 如0x7135_7010(无子板默认为载板信息) bit[31:16]:子板信息 bit[15:0]:载板信息
#define OFFSET_BDINFO_SOFT_VER 0x04 //软件版本(年,月,日) 如0x2019_1208  bit[31:16]:年 bit[15:8]:月 bit[7:0]日
#define OFFSET_BDINFO_XDMA 0x08     //xdma信息(模式,链路通道速率,位宽) 如0x0808_0256表示x8模式 8Gb链路通道速率 256bit数据宽度
#define OFFSET_BDINFO_ADC 0x0C      //adc采样率,通道数,分辨率 如0x2000_0416 bit[31:16]:adc采样率(单位M) bit[15:8]:adc通道数 bit[7:0]adc分辨率
#define OFFSET_BDINFO_DAC 0x10      //dac采样率,通道数,分辨率 如0x2500_0816 bit[31:16]:dac采样率(单位M) bit[15:8]:dac通道数 bit[7:0]dac分辨率
#define OFFSET_BDINFO_RDTEST 0x14   //固定值32'h0000_0014 用于测试

#define OFFSET_PCIE_INTR_INTR_ENABLE 0x00 //pcie中断使能 bit0-n 表示使能第1~n+1个中断源 高电平有效
#define OFFSET_PCIE_INTR_INTR_CLEAR 0x04  //pcie中断清除 bit0-n 表示清除第1~n+1个中断源 高电平有效
#define OFFSET_PCIE_INTR_START_ADC 0x08   //启动上位机采集adc数据 上升沿有效
#define OFFSET_PCIE_INTR_START_DAC 0x0C   //启动上位机播放dac数据 上升沿有效
#define OFFSET_PCIE_INTR_STOP_ADC 0x10    //上位机停止采集adc数据 上升沿有效
#define OFFSET_PCIE_INTR_STOP_DAC 0x14    //上位机停止播放dac数据 上升沿有效

enum TRIG_MODE
{
    TRIG_MODE_SOFTWARE = 0,
    TRIG_MODE_INTERNAL_PULSE = 1,
    TRIG_MODE_EXTERNAL_PULSE = 2,
    TRIG_MODE_CHANNEL = 4
};

enum DIRECTION
{
    DIRECTION_CARD2HOST,
    DIRECTION_HOST2CARD
};

enum HFILEHANDLE_INDEX
{
	HFILEHANDLE_COUNT = 64,
	HFILEHANDLE_USER = 0,
	HFILEHANDLE_CONTROL,
	HFILEHANDLE_EVENT_0,
	HFILEHANDLE_C2H_0,
	HFILEHANDLE_H2C_0
};

typedef struct
{
	int hFileHandle[HFILEHANDLE_COUNT];
	void *RegSpace;
	uint32_t RegSpaceSize;
} STXDMA_CARDINFO;

#ifdef QTXDMAAPI_EXPORTS
#define QTXDMAAPI_API __declspec(dllexport)
#else
#define QTXDMAAPI_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

    //函数功能: 打开板卡
    //函数参数：
    //  unCardIdx, 板卡下标, 从0开始编号, 多个板卡时需要设置不同值
    //函数返回: 成功返回0,失败返回-1并把详细错误信息写入日志文件
	QTXDMAAPI_API int QTXdmaOpenBoard(STXDMA_CARDINFO *pstCardInfo, unsigned int unCardIdx);
	QTXDMAAPI_API int QTXdmaCloseBoard(STXDMA_CARDINFO *pstCardInfo);

	QTXDMAAPI_API int QTXdmaWriteRegister(STXDMA_CARDINFO *pstCardInfo, unsigned int BaseAddr, unsigned int Offset, unsigned int Value);
	QTXDMAAPI_API int QTXdmaReadRegister(STXDMA_CARDINFO *pstCardInfo, unsigned int BaseAddr, unsigned int Offset, unsigned int *Value);

	QTXDMAAPI_API int QTXdmaStart(STXDMA_CARDINFO *pstCardInfo, unsigned int unDirection);
	QTXDMAAPI_API int QTXdmaStop(STXDMA_CARDINFO *pstCardInfo, unsigned int unDirection);

	QTXDMAAPI_API int QTXdmaGetLoopEvent(STXDMA_CARDINFO *pstCardInfo);
	QTXDMAAPI_API int QTXdmaGetOneEvent(STXDMA_CARDINFO *pstCardInfo);
	QTXDMAAPI_API int QTXdmaGetDataBuffer(unsigned int unOffsetAddr, STXDMA_CARDINFO *pstCardInfo, unsigned char *pBufDest, unsigned int unLen, unsigned int unTimeOut);
	QTXDMAAPI_API int QTXdmaGetData(unsigned int unOffsetAddr, STXDMA_CARDINFO *pstCardInfo, unsigned char *pBufDest, unsigned int unLen, unsigned int unTimeOut);
	QTXDMAAPI_API int QTXdmaSendData(unsigned int unOffsetAddr, STXDMA_CARDINFO *pstCardInfo, void *pBufsrc, unsigned int unLen, unsigned int unTimeOut);
	QTXDMAAPI_API int QTXdmaSetSoftTrigger(STXDMA_CARDINFO *pstCardInfo);
	QTXDMAAPI_API int QTXdmaSetInternalPulseTrigger(STXDMA_CARDINFO *pstCardInfo, uint32_t unPulsePeriod, uint32_t unPulseWidth, uint32_t unTrigCount);

	QTXDMAAPI_API int QTXdmaSetExternalPulseTrigger(STXDMA_CARDINFO *pstCardInfo, uint32_t unPulsePeriod, uint32_t unPulseWidth, uint32_t unTrigCount);

	QTXDMAAPI_API int QTXdmaSetChannelTrigger(STXDMA_CARDINFO *pstCardInfo, int32_t unRisingEdgeTrigLevel, int32_t unFallingEdgeTrigLevel, uint32_t unTrigCount);

	QTXDMAAPI_API int QTXdmaDataSplitChannels(char *MultiChannelFileName, int ChannelCount, int ChannelIndex, char *SingleChannelFileName);

	QTXDMAAPI_API int QTXdmaSetParameterADC(STXDMA_CARDINFO *pstCardInfo,
                          uint32_t adcSampleRate,         //adc采样率(单位M)  暂时未用
                          uint32_t enableExtRefClock,     //外参考,外时钟使能 bit0=外时钟使能  bit1=外参考使能  高电平有效 二者互斥
                          bool bEnableADC,                //配置adc使能(上升沿有效)
                          uint32_t ChannelCount,          //通道数 NUM
                          uint32_t ChannelID,             //通道ID
                          uint32_t DMA_TransmitMode,      //dam0传输模式   1:连续传输模式 0:有限次传输模式
                          uint32_t DMA_TransmitOnceBytes, //dma0 一次传输的大小(byte)  如 4096
                          uint32_t DMA_TransmitCount      //dma0 传输的次数  连续模式下,传输次数完成后,切换基地址继续传输,直到不使能连续传输模式
    );
	QTXDMAAPI_API int QTXdmaSetParameterDAC(STXDMA_CARDINFO *pstCardInfo,
                          uint32_t dacSampleRate,
                          uint32_t enableExtRefClock,
                          bool bEnableDAC,
                          uint32_t ChannelCount,
                          uint32_t ChannelID,
                          uint32_t DMA_TransmitMode,
                          uint32_t DMA_TransmitOnceBytes,
                          uint32_t DMA_TransmitCount);

	QTXDMAAPI_API int QTXdma_Buff_BIT8_TO_BIT16(uint8_t buffer_8bit, uint16_t buffer_16bit[2], bool isSignal);
	QTXDMAAPI_API int QTXdma_Buff_BIT12_TO_BIT16(uint8_t buffer_12bit[3], uint16_t buffer_16bit[2], bool isSignal);
	QTXDMAAPI_API int QTXdma_Buff_BIT10_TO_BIT16(uint8_t buffer_10bit[5], uint16_t buffer_16bit[4], bool isSignal);

	QTXDMAAPI_API int QTXdma_File_BIT8_TO_BIT16(char *src8bitFilename, char *dst16bitFilename, bool isSignal);
	QTXDMAAPI_API int QTXdma_File_BIT10_TO_BIT16(char *src10bitFilename, char *dst16bitFilename, bool isSignal);
	QTXDMAAPI_API int QTXdma_File_BIT12_TO_BIT16(char *src12bitFilename, char *dst16bitFilename, bool isSignal);
	QTXDMAAPI_API int QTXdmaShow_file_content(char *filename, uint32_t dataCount, int StartEnd, int offsetBytes, int dataType);

#ifdef __cplusplus
}
#endif //extern "C" {

#endif //_QTAPI_H_
