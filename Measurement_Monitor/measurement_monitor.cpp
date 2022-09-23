#include "measurement_monitor.h"


Measurement_Monitor::Measurement_Monitor(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    
    // Set plain text
    ui.plainTextEdit->setPlainText("Oscilloscope");

    // Set chartview
    oscilloscope_chartview = new Oscilloscope(ui.oscilloscope_widget);
    oscilloscope_chartview->resize(ui.oscilloscope_widget->size());

    // Define QueenTest_Digitizer
    queentest_digitizer = QueenTest_Digitizer();

    // Define dma struct
    dma_configuration =
    {
        2048,
        (80000 / 64) * 64,
        1
    };
    ptr_dma_configuration = &dma_configuration;

    // Set buttons
    QObject::connect(ui.start_btn, &QPushButton::clicked, this, &Measurement_Monitor::onStart);
    QObject::connect(ui.stop_btn, &QPushButton::clicked, this, &Measurement_Monitor::onStop);
    QObject::connect(ui.initialize_btn, &QPushButton::clicked, this, &Measurement_Monitor::initialize);
    QObject::connect(ui.configure_btn, &QPushButton::clicked, this, &Measurement_Monitor::configure);

}



Measurement_Monitor::~Measurement_Monitor()
{
    queentest_digitizer.digitizer_disconnect();
}


void Measurement_Monitor::onStart()
{
    oscilloscope_chartview->onStart();
}


void Measurement_Monitor::onStop()
{
    oscilloscope_chartview->onStop();
}


void Measurement_Monitor::initialize()
{
    queentest_digitizer.digitizer_connect();
    ui.plainTextEdit->appendPlainText("Connected");

    queentest_digitizer.digitizer_getinfo();
    ui.plainTextEdit->appendPlainText("Info loaded");

    queentest_digitizer.digitizer_reset();
    ui.plainTextEdit->appendPlainText("Reset success");

    queentest_digitizer.digitizer_clean_interrupt();
    ui.plainTextEdit->appendPlainText("Interrupt cleaned");

}


void Measurement_Monitor::configure()
{
    queentest_digitizer.digitizer_dma_configure(ptr_dma_configuration);
    ui.plainTextEdit->appendPlainText("Dma configured");

    queentest_digitizer.digitizer_mode_configure();
    ui.plainTextEdit->appendPlainText("Trigger mode configured");

    queentest_digitizer.digitizer_pcie_interrupt();
    ui.plainTextEdit->appendPlainText("PCIe interrupt enabled");

}


