#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_measurement_monitor.h"

class Measurement_Monitor : public QMainWindow
{
    Q_OBJECT

public:
    Measurement_Monitor(QWidget *parent = nullptr);
    ~Measurement_Monitor();

private:
    Ui::Measurement_MonitorClass ui;
};
