#pragma once
#include <QObject>
#include "HarmonicInterface.h"

class Harmonic : public QObject, public HarmonicInterface
{
    Q_OBJECT
public:
	const double MIN_X = 0;
    const double MAX_X = 550;
    const double STEP = 0.1;

	Harmonic(HarmonicType type, double amplitude, double frequency, double phase);
	
	HarmonicType GetType() const override;
	void SetType(HarmonicType type) override;

	double GetAmplitude() const override;
	void SetAmplitude(double amplitude) override;

	double GetFrequency() const override;
	void SetFrequency(double frequency) override;

	double GetPhase() const override;
	void SetPhase(double phase) override;

	CoordinatesVector GetCoordinates() const override;
	std::string ToString() const override;

signals:
    void DoOnChange();

private:
    HarmonicType m_type;
	double m_amplitude;
	double m_frequency;
	double m_phase;
};

