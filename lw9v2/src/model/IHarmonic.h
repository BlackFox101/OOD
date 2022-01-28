#pragma once
#include "IEditedHarmonic.h"

class IHarmonic : public IEditedHarmonic
{
public:
    virtual double GetYByX(double x) const = 0;
    void DoOnChange();

    virtual ~IHarmonic() = default;
};
