#include "src/view/chartdrawerview.h"
#include "src/model/HarmonicsStorage.h"
#include "src/controller/ChartDrawerController.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::shared_ptr<HarmonicsStorageInterface> model = std::make_shared<HarmonicsStorage>();
    std::shared_ptr<ChartDrawerControllerInterface> controller = std::make_shared<ChartDrawerController>(model);
    ChartDrawerView w(model, controller);
    w.show();
    return a.exec();
}
