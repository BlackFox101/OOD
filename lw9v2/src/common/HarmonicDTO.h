#pragma once
#include "HarmonicType.h"

struct HarmonicDTO
{
    double amplitude = 1;
    double frequency = 1;
    double phase = 0;
    HarmonicType type = HarmonicType::Sin;
};
