#pragma once
#include "../../src/common/HarmonicType.h"

class IControllerHarmonicEditor
{
public:
    virtual void ChangeHarmonicPhase(size_t index, double value) = 0;
    virtual void ChangeHarmonicFrequency(size_t index, double value) = 0;
    virtual void ChangeHarmonicAmplitude(size_t index, double value) = 0;
    virtual void ChangeHarmonicType(size_t index, HarmonicType value) = 0;

    virtual ~IControllerHarmonicEditor() = default;
};