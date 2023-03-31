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
	QChart* oscilloscopeChart = nullptr;
	QTimer* timer = nullptr;
	QSplineSeries* m_pSeries = nullptr;
	QValueAxis* m_pAxisx = nullptr;
	QValueAxis* m_pAxisy = nullptr;

	qreal m_x;
	qreal m_y;
};

