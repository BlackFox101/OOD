#ifndef CREATENEWHARMONICVIEW_H
#define CREATENEWHARMONICVIEW_H

#include <QDialog>
#include <QMainWindow>
#include "../../src/common/HarmonicType.h"
#include "../../src/common/HarmonicDTO.h"
#include "../../src/controller/IChartDrawerControllerCreator.h"

namespace Ui {
class CreateNewHarmonicView;
}

class CreateNewHarmonicView : public QDialog
{
    Q_OBJECT

public:
    explicit CreateNewHarmonicView(std::shared_ptr<IChartDrawerControllerCreator> controller, QWidget *parent = nullptr);
    ~CreateNewHarmonicView();

public slots:
    void Close();

private slots:
    void RewriteHarmonicString();
    void CreateNewHarmonic();
    void reject() override;

private:
    Ui::CreateNewHarmonicView *ui;

    std::shared_ptr<IChartDrawerControllerCreator> m_controller;

    void ResetValues();
    HarmonicDTO GetHarmonicDTO();
};

#endif // CREATENEWHARMONICVIEW_H
