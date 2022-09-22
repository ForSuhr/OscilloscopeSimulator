#include "measurement_monitor.h"


// Constructor
Measurement_Monitor::Measurement_Monitor(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    
    // Set plain text
    ui.plainTextEdit->setPlainText("Oscilloscope");

    // Set chartview
    oscilloscope_chartview = new Oscilloscope(ui.oscilloscope_widget);
    oscilloscope_chartview->resize(ui.oscilloscope_widget->size());

    // Set buttons
    connect(ui.start_btn, &QPushButton::clicked, this, &Measurement_Monitor::onStart);
    connect(ui.stop_btn, &QPushButton::clicked, this, &Measurement_Monitor::onStop);
}


// Destructor
Measurement_Monitor::~Measurement_Monitor()
{}


void Measurement_Monitor::onStart()
{
    oscilloscope_chartview->onStart();
}

void Measurement_Monitor::onStop()
{
    oscilloscope_chartview->onStop();
}


