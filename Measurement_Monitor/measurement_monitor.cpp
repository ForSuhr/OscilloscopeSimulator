#include "measurement_monitor.h"

// Constructor
Measurement_Monitor::Measurement_Monitor(QWidget *parent) : QMainWindow(parent)
{
    ui->setupUi(this);

    // Set plain text
    ui->plainTextEdit->setPlainText("Oscilloscope");

    // Set chartview
    oscilloscope_chartview = new Oscilloscope(ui->oscilloscope_widget);
    oscilloscope_chartview->resize(ui->oscilloscope_widget->size());
}

// Destructor
Measurement_Monitor::~Measurement_Monitor()
{}
