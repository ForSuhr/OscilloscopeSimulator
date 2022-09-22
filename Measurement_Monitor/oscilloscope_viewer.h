#pragma once
#include <QtCharts>
#include <QTimer>
#include <QSplineSeries>
#include <QValueAxis>
#include <QRandomGenerator>


class Oscilloscope: public QChartView
{
	Q_OBJECT

public:
	Oscilloscope(QWidget* parent);
	~Oscilloscope();

public slots:
	void onStart();
	void onStop();
	void onUpdateData();
	

private:
	QChart* oscilloscope_chart;
	QTimer* timer;
	QSplineSeries* m_pSeries;
	QValueAxis* m_pAxisx;
	QValueAxis* m_pAxisy;
	qreal m_x;
	qreal m_y;

};

