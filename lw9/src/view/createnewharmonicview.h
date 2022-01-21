#ifndef CREATENEWHARMONICVIEW_H
#define CREATENEWHARMONICVIEW_H

#include <QDialog>
#include "src/common/HarmonicType.h"
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

private slots:
    void ChangeAmplitude();
    void ChangeFrequency();
    void ChangePhase();
    void ChangeType();
    void RewriteHarmonicString();
    void HideView();

private:
    Ui::CreateNewHarmonicView *ui;

    HarmonicDTO m_harmonic;

    void ResetValues();
};

#endif // CREATENEWHARMONICVIEW_H
