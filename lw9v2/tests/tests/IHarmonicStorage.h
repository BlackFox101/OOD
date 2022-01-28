#pragma once
#include "IGetSumYHarmonicStorage.h"
#include <memory>
#include "IHarmonic.h"

class IHarmonicStorage : public IGetSumYHarmonicStorage
{
public:
    virtual size_t GetHarmonicCount() const = 0;
    virtual void AddHarmonic(std::shared_ptr<IHarmonic> harmonic) = 0;
    virtual std::shared_ptr<IHarmonic> GetHarmonicByIndex(size_t index) const = 0;
    virtual void RemoveHarmonicByIndex(size_t index) = 0;

    virtual ~IHarmonicStorage() = default;
};
