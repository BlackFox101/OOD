#ifndef CREATENEWHARMONICVIEW_H
#define CREATENEWHARMONICVIEW_H

#include <QDialog>
#include <QMainWindow>
#include "src/common/harmonictype.h"
#include "src/common/harmonicdto.h"

namespace Ui {
class CreateNewHarmonicView;
}

class CreateNewHarmonicView : public QDialog
{
    Q_OBJECT

public:
    explicit CreateNewHarmonicView(QWidget *parent = nullptr);
    ~CreateNewHarmonicView();

    void onClickOkButton(QMainWindow* window);
    HarmonicDTO GetHarmonicData();

public slots:
    void Close();
private slots:
    void ChangeAmplitude();
    void ChangeFrequency();
    void ChangePhase();
    void ChangeType();
    void RewriteHarmonicString();

    void reject() override;

private:
    Ui::CreateNewHarmonicView *ui;

    double m_amplitude = 1;
    double m_frequency = 1;
    double m_phase = 0;
    HarmonicType m_type = HarmonicType::Sin;

    void ResetValues();
};

#endif // CREATENEWHARMONICVIEW_H
