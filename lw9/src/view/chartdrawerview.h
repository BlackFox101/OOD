#ifndef CHARTDRAWERVIEW_H
#define CHARTDRAWERVIEW_H

#include <QMainWindow>

#include "src/view/createnewharmonicview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ChartDrawerView; }
QT_END_NAMESPACE

class ChartDrawerView : public QMainWindow
{
    Q_OBJECT

public:
    ChartDrawerView(QWidget *parent = nullptr);
    ~ChartDrawerView();

private slots:
    void OpenAddNewHarmonicView();

private:
    Ui::ChartDrawerView *ui;
    CreateNewHarmonicView m_createNewHarmonicView;
};
#endif // CHARTDRAWERVIEW_H
