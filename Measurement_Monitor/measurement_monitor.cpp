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
    queentest_digitizer = new QueenTest_Digitizer();

    // Define dma struct
    dma_configuration =
    {
        100 * 1024, // dma_once_bytes
        100 * 1024, // dma_interrupt_bytes
        10 // trigger_number
    };
    ptr_dma_configuration = &dma_configuration;

    // Set buttons
    QObject::connect(ui.btnStart, &QPushButton::clicked, this, &Measurement_Monitor::on_btnStart_clicked);
    QObject::connect(ui.btnStop, &QPushButton::clicked, this, &Measurement_Monitor::on_btnStop_clicked);
    QObject::connect(ui.btnInitialize, &QPushButton::clicked, this, &Measurement_Monitor::on_btnInitialize_clicked);
    QObject::connect(ui.btnConfigure, &QPushButton::clicked, this, &Measurement_Monitor::on_btnConfigure_clicked);

}



Measurement_Monitor::~Measurement_Monitor()
{
    queentest_digitizer->digitizer_disconnect();
    delete oscilloscope_chartview;
    delete queentest_digitizer;
}


void Measurement_Monitor::on_btnStart_clicked()
{
    queentest_digitizer->foo();
    queentest_digitizer->start();
    //oscilloscope_chartview->onStart();
    
    //this->start();

    
    //queentest_digitizer->digitizer_buffer_set();
    //ui.plainTextEdit->appendPlainText("Memory allocated");

    //std::thread t1(&QueenTest_Digitizer::digitizer_start_adc, queentest_digitizer);
    //ui.plainTextEdit->appendPlainText("Acquisition started");




    //for (auto i : ch1)
    //{
    //    ui.plainTextEdit->appendPlainText(QString::number(ch1[i]));
    //}
}


void Measurement_Monitor::on_btnStop_clicked()
{
    oscilloscope_chartview->onStop();
    queentest_digitizer->digitizer_stop_adc();
    ui.plainTextEdit->appendPlainText("Acquisition stopped");
}


void Measurement_Monitor::on_btnInitialize_clicked()
{
    queentest_digitizer->digitizer_connect();
    ui.plainTextEdit->appendPlainText("Connected");

    queentest_digitizer->digitizer_getinfo();
    ui.plainTextEdit->appendPlainText("Info loaded");

    queentest_digitizer->digitizer_reset();
    ui.plainTextEdit->appendPlainText("Reset success");

    queentest_digitizer->digitizer_clean_interrupt();
    ui.plainTextEdit->appendPlainText("Interrupt cleaned");

}


void Measurement_Monitor::on_btnConfigure_clicked()
{
    queentest_digitizer->digitizer_dma_configure(ptr_dma_configuration);
    ui.plainTextEdit->appendPlainText("DMA configured");

    queentest_digitizer->digitizer_mode_configure();
    ui.plainTextEdit->appendPlainText("Trigger mode configured");

    queentest_digitizer->digitizer_pcie_interrupt();
    ui.plainTextEdit->appendPlainText("PCIe interrupt enabled");
}
