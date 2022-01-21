#ifndef CHARTDRAWERVIEW_H
#define CHARTDRAWERVIEW_H
#include <QMainWindow>

#include "src/view/createnewharmonicview.h"

#include "src/model/HarmonicsStorage.h"
#include "src/controller/ChartDrawerController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ChartDrawerView; }
QT_END_NAMESPACE

class ChartDrawerView : public QMainWindow
{
    Q_OBJECT

public:
    ChartDrawerView(std::shared_ptr<HarmonicsStorageInterface> harmonicsStorage,
                    std::shared_ptr<ChartDrawerControllerInterface> controller,
                    QWidget *parent = nullptr);
    ~ChartDrawerView();

private slots:
    void OpenAddNewHarmonicView();

private:
    std::shared_ptr<HarmonicsStorageInterface> m_harmonicsStorage;
    std::shared_ptr<ChartDrawerControllerInterface> m_controller;

    Ui::ChartDrawerView *ui;
    CreateNewHarmonicView m_createNewHarmonicView;

    void Initialize();
};
#endif // CHARTDRAWERVIEW_H
