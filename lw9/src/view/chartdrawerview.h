#ifndef CHARTDRAWERVIEW_H
#define CHARTDRAWERVIEW_H
#include <QMainWindow>
#include <QScrollArea>

#include "src/view/createnewharmonicview.h"
#include "harmoniceditor.h"
#include "harmoniclist.h"
#include "chartgraphicview.h"

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

public slots:
    void HarmonicAdded(size_t index);
    void HarmonicDeleted(size_t index);

private slots:
    void OpenAddNewHarmonicView();
    void CreateNewHarmonic();
    void DeleteHarmonic();
    void ChangeSelectedHarmonic();

    //void ShowCartView();
    //void ShowTableView();

private:
    std::shared_ptr<HarmonicsStorageInterface> m_harmonicsStorage;
    std::shared_ptr<ChartDrawerControllerInterface> m_controller;

    Ui::ChartDrawerView* ui;
    CreateNewHarmonicView m_createNewHarmonicView;
    std::unique_ptr<HarmonicEditor> m_harmonicEditor;
    std::unique_ptr<HarmonicList> m_harmonicList;
    std::unique_ptr<ChartGraphicView> m_chartGraphicView;

    void Initialize();
};
#endif
