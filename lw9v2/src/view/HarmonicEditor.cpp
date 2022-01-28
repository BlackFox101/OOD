#include "HarmonicEditor.h"
#include <QDoubleValidator>

HarmonicEditor::HarmonicEditor(std::shared_ptr<IControllerHarmonicEditor> controller,
                               QGroupBox* editorMenuBox,
                               QLineEdit* amplitudeInput,
                               QLineEdit* frequencyInput,
                               QLineEdit* phaseInput,
                               QRadioButton* radioButtonSin,
                               QRadioButton* radioButtonCos)
    : m_editorMenuBox(editorMenuBox)
    , m_amplitudeInput(amplitudeInput)
    , m_frequencyInput(frequencyInput)
    , m_phaseInput(phaseInput)
    , m_radioButtonSin(radioButtonSin)
    , m_radioButtonCos(radioButtonCos)
    , m_controller(controller)
{
    m_editorMenuBox->hide();

    Initialize();

    auto validator = new QDoubleValidator(0, 100, 2, this);
    QLocale locale(QLocale::English);
    validator->setLocale(locale);

    m_amplitudeInput->setValidator(validator);
    m_frequencyInput->setValidator(validator);
    m_phaseInput->setValidator(validator);
}

void HarmonicEditor::Initialize()
{
    connect(m_amplitudeInput, SIGNAL(textChanged(QString)), this, SLOT(ChangeAmplitude()));
    connect(m_frequencyInput, SIGNAL(textChanged(QString)), this, SLOT(ChangeFrequency()));
    connect(m_phaseInput, SIGNAL(textChanged(QString)), this, SLOT(ChangePhase()));
    connect(m_radioButtonSin, SIGNAL(toggled(bool)), this, SLOT(ChangeType()));
}

void HarmonicEditor::ChangeSelectedHarmonic(const HarmonicDTO& harmonic, size_t index)
{
    m_harmonicIndex = index;
    m_amplitudeInput->setText(QString::number(harmonic.amplitude));
    m_frequencyInput->setText(QString::number(harmonic.frequency));
    m_phaseInput->setText(QString::number(harmonic.phase));
    if (harmonic.type == HarmonicType::Sin)
    {
        m_radioButtonSin->setChecked(true);
    }
    else
    {
        m_radioButtonCos->setChecked(true);
    }

    if (m_editorMenuBox->isHidden())
    {
        m_editorMenuBox->show();
    }
}

void HarmonicEditor::ChangePhase()
{
    m_controller->ChangeHarmonicPhase(m_harmonicIndex, m_phaseInput->text().toDouble());
}

void HarmonicEditor::ChangeFrequency()
{
    m_controller->ChangeHarmonicFrequency(m_harmonicIndex, m_frequencyInput->text().toDouble());
}

void HarmonicEditor::ChangeAmplitude()
{
    m_controller->ChangeHarmonicAmplitude(m_harmonicIndex, m_amplitudeInput->text().toDouble());
}

void HarmonicEditor::ChangeType()
{
    HarmonicType type;
    if (m_radioButtonSin->isChecked())
    {
        type = HarmonicType::Sin;
    }
    else
    {
        type = HarmonicType::Cos;
    }
    m_controller->ChangeHarmonicType(m_harmonicIndex, type);
}

