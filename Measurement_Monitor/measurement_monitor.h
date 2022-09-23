#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_measurement_monitor.h"
#include "oscilloscope_viewer.h"
#include "queentest_digitizer.h"


class Measurement_Monitor : public QMainWindow
{
    Q_OBJECT

public:
    Measurement_Monitor(QWidget* parent = nullptr);
    ~Measurement_Monitor();

public slots:
    void onStart();
    void onStop();
    void initialize();
    void configure();


private:
    Ui::Measurement_MonitorClass ui;
    Oscilloscope* oscilloscope_chartview;
    QueenTest_Digitizer queentest_digitizer;
    struct Dma_Configuration dma_configuration;
    Ptr_Dma_Configuration ptr_dma_configuration;
};
