#include "createnewharmonicview.h"
#include "ui_createnewharmonicview.h"

#include <QDoubleValidator>
#include <string>
#include <sstream>

CreateNewHarmonicView::CreateNewHarmonicView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateNewHarmonicView)
{
    ui->setupUi(this);

    auto validator = new QDoubleValidator(0, 100, 2, this);
    QLocale locale(QLocale::English);
    validator->setLocale(locale);

    ui->amplitudeInput->setValidator(validator);
    ui->frequencyInput->setValidator(validator);
    ui->phaseInput->setValidator(validator);

    connect(ui->amplitudeInput, SIGNAL(textChanged(QString)), this, SLOT(ChangeAmplitude()));
    connect(ui->frequencyInput, SIGNAL(textChanged(QString)), this, SLOT(ChangeFrequency()));
    connect(ui->phaseInput, SIGNAL(textChanged(QString)), this, SLOT(ChangePhase()));
    connect(ui->radioButtonSin, SIGNAL(toggled(bool)), this, SLOT(ChangeType()));

    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(Close()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(Close()));
}

void CreateNewHarmonicView::onClickOkButton(QMainWindow* window)
{
    connect(ui->okButton, SIGNAL(clicked()), window, SLOT(CreateNewHarmonic()));
}

CreateNewHarmonicView::~CreateNewHarmonicView()
{
    delete ui;
}

void CreateNewHarmonicView::ChangeAmplitude()
{
    m_amplitude = ui->amplitudeInput->text().toDouble();
    RewriteHarmonicString();
}

void CreateNewHarmonicView::ChangeFrequency()
{
    m_frequency = ui->frequencyInput->text().toDouble();
    RewriteHarmonicString();
}

void CreateNewHarmonicView::ChangePhase()
{
    m_phase = ui->phaseInput->text().toDouble();
    RewriteHarmonicString();
}

void CreateNewHarmonicView::ChangeType()
{
    if (ui->radioButtonSin->isChecked())
    {
        m_type = HarmonicType::Sin;
    }
    else
    {
        m_type = HarmonicType::Cos;
    }
    RewriteHarmonicString();
}

void CreateNewHarmonicView::ResetValues()
{
    m_amplitude = 1;
    m_frequency = 1;
    m_phase = 0;
    m_type = HarmonicType::Sin;

    ui->amplitudeInput->setText(QString::number(m_amplitude));
    ui->frequencyInput->setText(QString::number(m_frequency));
    ui->phaseInput->setText(QString::number(m_phase));
    ui->radioButtonSin->setChecked(true);
}

void CreateNewHarmonicView::RewriteHarmonicString()
{
    std::ostringstream function;
    function << m_amplitude << "*" << HarmonicTypeToString(m_type) << "(" << m_frequency << "*x + " << m_phase << ")";

    ui->showResultLabel->setText(QString::fromStdString(function.str()));
}

void CreateNewHarmonicView::Close()
{
    close();
    ResetValues();
}

HarmonicDTO CreateNewHarmonicView::GetHarmonicData()
{
    return HarmonicDTO({ m_amplitude, m_frequency, m_phase, m_type });
}

void CreateNewHarmonicView::reject()
{
    QDialog::reject();
    ResetValues();
}
