#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_measurement_monitor.h"
#include "oscilloscope_viewer.h"
#include "queentest_digitizer.h"
#include "waveform.h"

class Measurement_Monitor : public QMainWindow
{
    Q_OBJECT

public:
    Measurement_Monitor(QWidget* parent = nullptr);
    ~Measurement_Monitor();

public slots:
    void on_btnStart_clicked();
    void on_btnStop_clicked();
    void on_btnWaveform_clicked();
    void on_btnInitialize_clicked();
    void on_btnConfigure_clicked();

private:
    Ui::Measurement_MonitorClass ui;
    Oscilloscope* oscilloscope_chartview = nullptr;
    waveform* waveform_chartview = nullptr;
    QueenTest_Digitizer* queentest_digitizer = nullptr;

    struct Dma_Configuration dma_configuration;
    Ptr_Dma_Configuration ptr_dma_configuration;
};
