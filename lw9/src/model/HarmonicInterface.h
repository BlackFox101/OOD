#pragma once
#include <vector>
#include <string>
#include <functional>
#include "src/common/harmonictype.h"

typedef std::vector<std::pair<double, double>> CoordinatesVector;
typedef std::function<void()> OutlineStyleCallback;

class HarmonicInterface
{
public:
	virtual HarmonicType GetType() const = 0;
	virtual void SetType(HarmonicType type) = 0;

	virtual double GetAmplitude() const = 0;
	virtual void SetAmplitude(double amplitude) = 0;

	virtual double GetFrequency() const = 0;
	virtual void SetFrequency(double frequency) = 0;

	virtual double GetPhase() const = 0;
	virtual void SetPhase(double phase) = 0;

	virtual CoordinatesVector GetCoordinates() const = 0;
	virtual std::string ToString() const = 0;

	virtual ~HarmonicInterface() = default;
};

