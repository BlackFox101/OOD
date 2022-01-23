#ifndef HARMONICDTO_H
#define HARMONICDTO_H

#include "src/common/harmonictype.h"

struct HarmonicDTO
{
    double amplitude = 1;
    double frequency = 1;
    double phase = 0;
    HarmonicType type = HarmonicType::Sin;
};

#endif // HARMONICDTO_H
