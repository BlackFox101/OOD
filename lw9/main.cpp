#include "src/view/chartdrawerview.h"
#include "src/model/HarmonicsStorage.h"
#include "src/controller/ChartDrawerController.h"
#include <QApplication>

#include "src/model/Harmonic.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::shared_ptr<HarmonicsStorageInterface> model = std::make_shared<HarmonicsStorage>();

    std::shared_ptr<HarmonicInterface> harmonic = std::make_shared<Harmonic>(HarmonicType::Sin, 3, -3, 0.3);
    model->AddHarmonic(harmonic);

    harmonic = std::make_shared<Harmonic>(HarmonicType::Sin, 4.38, 2.25, 1.5);
    model->AddHarmonic(harmonic);

    harmonic = std::make_shared<Harmonic>(HarmonicType::Cos, 1, 1, 5);
    model->AddHarmonic(harmonic);

    std::shared_ptr<ChartDrawerControllerInterface> controller = std::make_shared<ChartDrawerController>(model);
    ChartDrawerView w(model, controller);
    w.show();
    return a.exec();
}
