#include "oscilloscope_viewer.h"

// Constructor
Oscilloscope::Oscilloscope(QWidget* parent) : QChartView(parent)
{
    // Set chart
    oscilloscope_chart = new QChart();
    oscilloscope_chart->setTitle("Oscilloscope");
	oscilloscope_chart->legend()->hide();
	oscilloscope_chart->setAnimationOptions(QChart::AllAnimations);

    // Put the chart into oscilloscope chartview
    this->setChart(oscilloscope_chart);

    // Set QTimer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Oscilloscope::onUpdateData);



    m_pAxisx = new QValueAxis(this);
    m_pAxisy = new QValueAxis(this);

    m_x = 10;
    m_y = 1;

    QPen pen(Qt::blue);
    pen.setWidth(2);

    m_pSeries = new QSplineSeries(this);
    m_pSeries->setPen(pen);
    m_pSeries->append(m_x, m_y);

    oscilloscope_chart->addSeries(m_pSeries);

    oscilloscope_chart->addAxis(m_pAxisx, Qt::AlignBottom);
    oscilloscope_chart->addAxis(m_pAxisy, Qt::AlignLeft);

    m_pSeries->attachAxis(m_pAxisx);
    m_pSeries->attachAxis(m_pAxisy);
    m_pAxisx->setTickCount(1);
    m_pAxisx->setTickCount(1);

    m_pAxisx->setRange(0, 10);
    m_pAxisy->setRange(-1.5, 1.5);
}

// Destructor
Oscilloscope::~Oscilloscope()
{
    delete oscilloscope_chart;
}

void Oscilloscope::onStart()
{
    timer->start(200);
}

void Oscilloscope::onStop()
{
    timer->stop();
}

void Oscilloscope::onUpdateData()
{
    qreal x = oscilloscope_chart->plotArea().width() / this->m_pAxisx->tickCount();

    qreal xValue = (this->m_pAxisx->max() - this->m_pAxisx->min()) / this->m_pAxisx->tickCount();
    this->m_x += xValue;

    qreal yValue = QRandomGenerator::global()->bounded(-1, 1);
    this->m_y = yValue;

    this->m_pSeries->append(this->m_x, this->m_y);

    oscilloscope_chart->scroll(x, 0);
}