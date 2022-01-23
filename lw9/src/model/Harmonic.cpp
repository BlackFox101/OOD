#include "Harmonic.h"
#include <sstream>
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

HarmonicInterface::CoordinatesVector Harmonic::GetCoordinates() const
{
	CoordinatesVector coordinates;
	double x = MIN_X;
	while (x <= MAX_X)
	{
		double y;
		if (m_type == HarmonicType::Sin)
		{
			y = m_amplitude * std::sin(m_frequency * x + m_phase);
		}
		else
		{
			y = m_amplitude * std::cos(m_frequency * x + m_phase);
		}
		coordinates.push_back({ x, y });
		x += STEP;
	}

	return coordinates;
}

std::string Harmonic::ToString() const
{
	std::ostringstream function;
	function << m_amplitude << "*" << HarmonicTypeToString(m_type) << "(" << m_frequency << "*x + " << m_phase << ")";

	return function.str();
}
