#pragma once
#include "../../src/common/HarmonicType.h"

class IEditedHarmonic
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

    virtual ~IEditedHarmonic() = default;
};