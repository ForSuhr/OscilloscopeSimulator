#include "oscilloscope_viewer.h"

Oscilloscope::Oscilloscope(QWidget* parent) 
    : QChartView(parent),
    oscilloscopeChart(new QChart)
{
    // Set chart
    oscilloscopeChart->setTitle("Oscilloscope");
    oscilloscopeChart->legend()->hide();
    oscilloscopeChart->setAnimationOptions(QChart::AllAnimations);

    // set chartview
    this->setChart(oscilloscopeChart);

    // Set QTimer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Oscilloscope::onUpdateData);

    m_pAxisx = new QValueAxis(this);
    m_pAxisy = new QValueAxis(this);

    m_x = 5;
    m_y = 0;

    QPen pen(Qt::blue);
    pen.setWidth(2);

    m_pSeries = new QSplineSeries(this);
    m_pSeries->setPen(pen);
    m_pSeries->append(m_x, m_y);

    oscilloscopeChart->addSeries(m_pSeries);

    oscilloscopeChart->addAxis(m_pAxisx, Qt::AlignBottom);
    oscilloscopeChart->addAxis(m_pAxisy, Qt::AlignLeft);

    m_pSeries->attachAxis(m_pAxisx);
    m_pSeries->attachAxis(m_pAxisy);
    m_pAxisx->setTickCount(1);
    m_pAxisx->setTickCount(1);

    m_pAxisx->setRange(0, m_x*2);
    m_pAxisy->setRange(-12, 12);
}

Oscilloscope::~Oscilloscope()
{
    delete oscilloscopeChart;
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
    qreal x = oscilloscopeChart->plotArea().width() / this->m_pAxisx->tickCount();

    qreal xValue = (this->m_pAxisx->max() - this->m_pAxisx->min()) / this->m_pAxisx->tickCount();
    this->m_x += xValue;

    qreal yValue = QRandomGenerator::global()->bounded(-10, 10);
    this->m_y = yValue;

    this->m_pSeries->append(this->m_x, this->m_y);

    oscilloscopeChart->scroll(x, 0);
}