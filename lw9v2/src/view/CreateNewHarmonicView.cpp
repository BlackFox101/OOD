#include "CreateNewHarmonicView.h"
#include "ui_CreateNewHarmonicView.h"

#include <QDoubleValidator>
#include <string>
#include <sstream>

CreateNewHarmonicView::CreateNewHarmonicView(std::shared_ptr<IChartDrawerControllerCreator> controller, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateNewHarmonicView)
    , m_controller(controller)
{
    ui->setupUi(this);

    auto validator = new QDoubleValidator(0, 100, 2, this);
    QLocale locale(QLocale::English);
    validator->setLocale(locale);

    ui->amplitudeInput->setValidator(validator);
    ui->frequencyInput->setValidator(validator);
    ui->phaseInput->setValidator(validator);

    connect(ui->amplitudeInput, SIGNAL(textChanged(QString)), this, SLOT(RewriteHarmonicString()));
    connect(ui->frequencyInput, SIGNAL(textChanged(QString)), this, SLOT(RewriteHarmonicString()));
    connect(ui->phaseInput, SIGNAL(textChanged(QString)), this, SLOT(RewriteHarmonicString()));
    connect(ui->radioButtonSin, SIGNAL(toggled(bool)), this, SLOT(RewriteHarmonicString()));

    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(Close()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(CreateNewHarmonic()));
}

void CreateNewHarmonicView::CreateNewHarmonic()
{
    m_controller->CreateNewHarmonic(GetHarmonicDTO());
    Close();
}

CreateNewHarmonicView::~CreateNewHarmonicView()
{
    delete ui;
}

void CreateNewHarmonicView::ResetValues()
{
    ui->amplitudeInput->setText(QString::number(1));
    ui->frequencyInput->setText(QString::number(1));
    ui->phaseInput->setText(QString::number(0));
    ui->radioButtonSin->setChecked(true);
}

void CreateNewHarmonicView::RewriteHarmonicString()
{
    auto harmonic = GetHarmonicDTO();

    std::ostringstream function;
    function << harmonic.amplitude << "*" << HarmonicTypeToString(harmonic.type) << "(" << harmonic.frequency << "*x + " << harmonic.phase << ")";

    ui->showResultLabel->setText(QString::fromStdString(function.str()));
}

void CreateNewHarmonicView::Close()
{
    close();
    ResetValues();
}


void CreateNewHarmonicView::reject()
{
    QDialog::reject();
    ResetValues();
}

HarmonicDTO CreateNewHarmonicView::GetHarmonicDTO()
{
    double amplitude = ui->amplitudeInput->text().toDouble();;
    double frequency = ui->frequencyInput->text().toDouble();
    double phase = ui->phaseInput->text().toDouble();
    HarmonicType type = HarmonicType::Cos;
    if (ui->radioButtonSin->isChecked())
    {
        type = HarmonicType::Sin;
    }

    return HarmonicDTO({ amplitude, frequency, phase, type });
}
