#pragma once
#include "IEditedHarmonic.h"

class IHarmonic : public IEditedHarmonic
{
public:
    virtual double GetYByX(double x) const = 0;

    virtual ~IHarmonic() = default;
};
