#pragma once
#include <QObject>
#include <QLineEdit>
#include <QRadioButton>
#include <QGroupBox>

#include "../../src/controller/IControllerHarmonicEditor.h"
#include "../../src/common/HarmonicDTO.h"

class HarmonicEditor : public QObject
{
    Q_OBJECT
public:
    HarmonicEditor(std::shared_ptr<IControllerHarmonicEditor> controller,
                   QGroupBox* editorMenuBox,
                   QLineEdit* amplitudeInput,
                   QLineEdit* frequencyInput,
                   QLineEdit* phaseInput,
                   QRadioButton* radioButtonSin,
                   QRadioButton* radioButtonCos);

public:
    void ChangeSelectedHarmonic(const HarmonicDTO& harmonic, size_t index);

private slots:
    void ChangePhase();
    void ChangeFrequency();
    void ChangeAmplitude();
    void ChangeType();

private:
    size_t m_harmonicIndex;
    QGroupBox* m_editorMenuBox;
    QLineEdit* m_amplitudeInput;
    QLineEdit* m_frequencyInput;
    QLineEdit* m_phaseInput;
    QRadioButton* m_radioButtonSin;
    QRadioButton* m_radioButtonCos;
    std::shared_ptr<IControllerHarmonicEditor> m_controller;

    void Initialize();
};
