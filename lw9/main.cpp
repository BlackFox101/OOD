#include "src/view/chartdrawerview.h"
#include "src/model/HarmonicsStorage.h"
#include "src/controller/ChartDrawerController.h"
#include <QApplication>

#include "src/model/Harmonic.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::shared_ptr<HarmonicsStorageInterface> model = std::make_shared<HarmonicsStorage>();

    for (int i = 0; i < 6; ++i)
    {
        std::shared_ptr<HarmonicInterface> harmonic = std::make_shared<Harmonic>(HarmonicType::Sin, i, i, i);
        model->AddHarmonic(harmonic);
    }


    std::shared_ptr<ChartDrawerControllerInterface> controller = std::make_shared<ChartDrawerController>(model);
    ChartDrawerView w(model, controller);
    w.show();
    return a.exec();
}
