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

    ui->amplitudeInput->setValidator( new QDoubleValidator(0, 100, 2, this) );
    ui->frequencyInput->setValidator( new QDoubleValidator(0, 100, 2, this) );
    ui->phaseInput->setValidator( new QDoubleValidator(0, 100, 2, this) );

    connect(ui->amplitudeInput, SIGNAL(textChanged(const QString &)), this, SLOT(ChangeAmplitude()));
    connect(ui->frequencyInput, SIGNAL(textChanged(const QString &)), this, SLOT(ChangeFrequency()));
    connect(ui->phaseInput, SIGNAL(textChanged(const QString &)), this, SLOT(ChangePhase()));
    connect(ui->radioButtonSin, SIGNAL(toggled(bool)), this, SLOT(ChangeType()));

    connect(ui->createButton, SIGNAL(clicked()), this, SLOT(HideView()));
}

CreateNewHarmonicView::~CreateNewHarmonicView()
{
    delete ui;
}

void CreateNewHarmonicView::ChangeAmplitude()
{
    m_harmonic.amplitude = ui->amplitudeInput->text().toDouble();
    RewriteHarmonicString();
}

void CreateNewHarmonicView::ChangeFrequency()
{
    m_harmonic.frequency = ui->frequencyInput->text().toDouble();
    RewriteHarmonicString();
}

void CreateNewHarmonicView::ChangePhase()
{
    m_harmonic.phase = ui->phaseInput->text().toDouble();
    RewriteHarmonicString();
}

void CreateNewHarmonicView::ChangeType()
{
    if (ui->radioButtonSin->isChecked())
    {
        m_harmonic.type = HarmonicType::Sin;
    }
    else
    {
        m_harmonic.type = HarmonicType::Cos;
    }
    RewriteHarmonicString();
}

void CreateNewHarmonicView::RewriteHarmonicString()
{
    std::ostringstream function;
    function << m_harmonic.amplitude << "*" << HarmonicTypeToString(m_harmonic.type) << "(" << m_harmonic.frequency << "*x + " << m_harmonic.phase << ")";

    ui->showResultLabel->setText(QString::fromStdString(function.str()));
}

void CreateNewHarmonicView::HideView()
{
    close();
    ResetValues();
}

void CreateNewHarmonicView::ResetValues()
{
    m_harmonic.amplitude = 1;
    m_harmonic.frequency = 1;
    m_harmonic.phase = 0;
    m_harmonic.type = HarmonicType::Sin;

    ui->amplitudeInput->setText(QString::number(m_harmonic.amplitude));
    ui->frequencyInput->setText(QString::number(m_harmonic.frequency));
    ui->phaseInput->setText(QString::number(m_harmonic.phase));
    ui->radioButtonSin->setChecked(true);

}
