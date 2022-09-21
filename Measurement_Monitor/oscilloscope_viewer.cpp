#include "oscilloscope_viewer.h"

// Constructor
Oscilloscope::Oscilloscope(QWidget* parent) : QChartView(parent)
{
    // Set chart
    oscilloscope_chart = new QChart();
    oscilloscope_chart->setTitle("Oscilloscope Chart");

    // Put the chart into oscilloscope chartview
    this->setChart(oscilloscope_chart);
}

// Destructor
Oscilloscope::~Oscilloscope()
{
}
