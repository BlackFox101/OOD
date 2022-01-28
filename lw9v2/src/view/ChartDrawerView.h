#ifndef CHARTDRAWERVIEW_H
#define CHARTDRAWERVIEW_H
#include <QMainWindow>

#include "../../src/model/IHarmonicStorage.h"
#include "../../src/controller/IChartDrawerController.h"

#include "CreateNewHarmonicView.h"
#include "HarmonicEditor.h"
#include "HarmonicList.h"
#include "ChartGraphicView.h"

QT_BEGIN_NAMESPACE
namespace Ui {class ChartDrawerView;}
QT_END_NAMESPACE

class ChartDrawerView : public QMainWindow
{
    Q_OBJECT
public:
    ChartDrawerView(std::shared_ptr<IHarmonicStorage> harmonicsStorage,
                    std::shared_ptr<IChartDrawerController> controller,
                    QWidget *parent = nullptr);
    ~ChartDrawerView();

public:

public slots:
    void HarmonicAdded(size_t index);
    void HarmonicDeleted(size_t index);
    void HarmonicChanged();

private slots:
    void OpenCreateNewHarmonicView();
    void ChangeSelectedHarmonic();
    void DeleteHarmonic();

private:
    std::shared_ptr<IHarmonicStorage> m_harmonicStorage;
    std::shared_ptr<IChartDrawerController> m_controller;

    Ui::ChartDrawerView* ui;

    CreateNewHarmonicView m_createNewHarmonicView;
    std::unique_ptr<HarmonicEditor> m_harmonicEditor;
    std::unique_ptr<HarmonicList> m_harmonicList;
    std::unique_ptr<ChartGraphicView> m_chartGraphicView;

    void Initialize();
};
#endif
