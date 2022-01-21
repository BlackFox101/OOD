#include "src/view/chartdrawerview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChartDrawerView w;
    w.show();
    return a.exec();
}
