#pragma once
#include <QObject>
#include "IHarmonic.h"

class Harmonic : public QObject, public IHarmonic
{
    Q_OBJECT
public:
    Harmonic(HarmonicType type, double amplitude, double frequency, double phase);

    HarmonicType GetType() const override;
    void SetType(HarmonicType type) override;
    
    double GetAmplitude() const override;
    void SetAmplitude(double amplitude) override;
    
    double GetFrequency() const override;
    void SetFrequency(double frequency) override;
    
    double GetPhase() const override;
    void SetPhase(double phase) override;

    double GetYByX(double x) const override;

signals:
    void DoOnChange();

private:
    HarmonicType m_type;
    double m_amplitude;
    double m_frequency;
    double m_phase;
};