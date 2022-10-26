#pragma once
#define BUFFSIZE 8192
#define CHNUMBER 4

#include <QtCharts>
#include <QSplineSeries>
#include <QValueAxis>

class waveform : public QChartView
{
public:
	waveform(QWidget* parent);
	~waveform();
	void plot();

private:
	QChart* waveform_chart;
	QSplineSeries* m_pSeries;
	QValueAxis* m_pAxisx;
	QValueAxis* m_pAxisy;
	qreal m_x;
	qreal m_y;
	signed short buffer[CHNUMBER * BUFFSIZE];
	signed short ch1[BUFFSIZE];

};

