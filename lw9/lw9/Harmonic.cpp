#include "Harmonic.h"
#include <sstream>
#include <cmath>

Harmonic::Harmonic(HarmonicType type = HarmonicType::Sin, double amplitude = 1, double frequency = 1, double phase = 0)
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
}

double Harmonic::GetAmplitude() const
{
	return m_amplitude;
}

void Harmonic::SetAmplitude(double amplitude)
{
	m_amplitude = amplitude;
}

double Harmonic::GetFrequency() const
{
	return m_frequency;
}

void Harmonic::SetFrequency(double frequency)
{
	m_frequency = frequency;
}

double Harmonic::GetPhase() const
{
	return m_phase;
}

void Harmonic::SetPhase(double phase)
{
	m_phase = phase;
}

CoordinatesVector Harmonic::GetCoordinates() const
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
