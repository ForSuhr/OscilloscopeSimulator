

#include "waveform.h"


waveform::waveform(QWidget* parent) : QChartView(parent)
{
    // Set chart
    waveform_chart = new QChart();
    waveform_chart->setTitle("Oscilloscope");
    waveform_chart->legend()->hide();
    waveform_chart->setAnimationOptions(QChart::AllAnimations);

    // Put the chart into oscilloscope chartview
    this->setChart(waveform_chart);

    m_pAxisx = new QValueAxis(this);
    m_pAxisy = new QValueAxis(this);

    m_x = 0;
    m_y = 0;

    QPen pen(Qt::blue);
    pen.setWidth(2);

    m_pSeries = new QSplineSeries(this);
    m_pSeries->setPen(pen);
    m_pSeries->append(m_x, m_y);

    waveform_chart->addSeries(m_pSeries);

    waveform_chart->addAxis(m_pAxisx, Qt::AlignBottom);
    waveform_chart->addAxis(m_pAxisy, Qt::AlignLeft);

    m_pSeries->attachAxis(m_pAxisx);
    m_pSeries->attachAxis(m_pAxisy);
    m_pAxisx->setTickCount(1);
    m_pAxisx->setTickCount(1);

    m_pAxisx->setRange(0, 10000);
    m_pAxisy->setRange(-10000, 10000);



}


waveform::~waveform()
{
    delete waveform_chart;
}

void waveform::plot()
{
    qreal x = waveform_chart->plotArea().width() / this->m_pAxisx->tickCount();

    qreal xValue = (this->m_pAxisx->max() - this->m_pAxisx->min()) / this->m_pAxisx->tickCount();


    this->buffer[CHNUMBER * BUFFSIZE] = {};
    this->ch1[BUFFSIZE] = {};
    int count = 0;

    std::string filename = "xdma0.bin";	//binary file name
    FILE* fp = NULL;
    fp = fopen(filename.c_str(), "r");

    while (!feof(fp)) {
        count = fread(this->buffer, sizeof(signed short), BUFFSIZE * CHNUMBER, fp);
        for (int i = 0; i < 1000; i++) {
            this->ch1[i] = this->buffer[i * CHNUMBER + 0];
            //ch2[i] = buffer[i * CHNUMBER + 1];
            //ch3[i] = buffer[i * CHNUMBER + 2];
            //ch4[i] = buffer[i * CHNUMBER + 3];
                    // 0.5ns per sample

            this->m_x += 0.5;
            this->m_y = this->ch1[i];
            this->m_pSeries->append(this->m_x, this->m_y);
        }
    }

    fclose(fp);
    fp = NULL;
}
