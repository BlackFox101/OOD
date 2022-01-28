#pragma once
#include "../../src/common/HarmonicDTO.h"

class IChartDrawerControllerCreator
{
public:
    virtual void CreateNewHarmonic(HarmonicDTO harmonic) = 0;
    virtual ~IChartDrawerControllerCreator() = default;
};