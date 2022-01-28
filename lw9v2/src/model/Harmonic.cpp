#include "Harmonic.h"
#include <cmath>

Harmonic::Harmonic(HarmonicType type, double amplitude, double frequency, double phase)
    : m_type(type)
    , m_amplitude(amplitude)
    , m_frequency(frequency)
    , m_phase(phase)
{
}

HarmonicType Harmonic::GetType() const
{
    return m_type;
}

void Harmonic::SetType(HarmonicType type)
{
    m_type = type;
    emit DoOnChange();
}

double Harmonic::GetAmplitude() const
{
    return m_amplitude;
}

void Harmonic::SetAmplitude(double amplitude)
{
    m_amplitude = amplitude;
    emit DoOnChange();
}

double Harmonic::GetFrequency() const
{
    return m_frequency;
}

void Harmonic::SetFrequency(double frequency)
{
    m_frequency = frequency;
    emit DoOnChange();
}

double Harmonic::GetPhase() const
{
    return m_phase;
}

void Harmonic::SetPhase(double phase)
{
    m_phase = phase;
    emit DoOnChange();
}

double Harmonic::GetYByX(double x) const
{
    if (m_type == HarmonicType::Sin)
    {
        return  m_amplitude * std::sin(m_frequency * x + m_phase);
    }

    return m_amplitude * std::cos(m_frequency * x + m_phase);
}
