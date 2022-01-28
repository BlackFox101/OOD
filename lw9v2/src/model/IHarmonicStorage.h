#pragma once
#include "IGetSumYHarmonicStorage.h"
#include "IHarmonic.h"
#include <memory>

class IHarmonicStorage : public IGetSumYHarmonicStorage
{
public:
    virtual size_t GetHarmonicCount() const = 0;
    virtual void AddHarmonic(std::shared_ptr<IHarmonic> harmonic) = 0;
    virtual void RemoveHarmonicByIndex(size_t index) = 0;
    virtual std::shared_ptr<IHarmonic> GetHarmonicByIndex(size_t index) const = 0;

    virtual void DoOnHarmonicChanged() = 0;
    virtual void DoOnHarmonicAdded(size_t index) = 0;
    virtual void DoOnHarmonicDeleted(size_t index) = 0;

    virtual ~IHarmonicStorage() = default;
};
