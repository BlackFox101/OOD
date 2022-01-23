#pragma once
#include "HarmonicEditorControllerInterface.h"
#include "src/common/harmonicdto.h"

class ChartDrawerControllerInterface : public HarmonicEditorControllerInterface
{
public:
    virtual void CreateNewHarmonic(HarmonicDTO harmonic) = 0;
    virtual void DeleteHarmonic(size_t index) = 0;
	virtual ~ChartDrawerControllerInterface() = default;
};

