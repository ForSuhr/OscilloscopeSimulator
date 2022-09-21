#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_measurement_monitor.h"
#include "oscilloscope_viewer.h"



class Measurement_Monitor : public QMainWindow
{
    Q_OBJECT

public:
    Measurement_Monitor(QWidget* parent = nullptr);
    ~Measurement_Monitor();

private:
    Ui::Measurement_MonitorClass* ui;
    Oscilloscope* oscilloscope_chartview;

    
};
