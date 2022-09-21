#pragma once
#include <QtCharts>
//#include <QChartView>


class Oscilloscope: public QChartView
{
	Q_OBJECT

public:
	Oscilloscope(QWidget* parent);
	~Oscilloscope();

public slots:


private:
	QChart* oscilloscope_chart;

};

