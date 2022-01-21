#pragma once
#include "src/model/HarmonicInterface.h"

class ChartDrawerControllerInterface
{
public:
	virtual void CreateNewHarmonic(HarmonicType type, double amplitude, double frequency, double phase) const = 0;
	virtual void DeleteHarmonic(size_t index) const = 0;
	virtual ~ChartDrawerControllerInterface() = default;
};

