#include "measurement_monitor.h"
#include <QtWidgets/QApplication>
#include "queentest_digitizer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Measurement_Monitor w;
    w.show();
    return a.exec();
}
