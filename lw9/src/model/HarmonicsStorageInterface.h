#pragma once
#include "HarmonicInterface.h"
#include <memory>
//#include <functional>

//using Callback = std::function<void()>;

class HarmonicsStorageInterface
{
public:
    virtual size_t GetHarmonicCount() const = 0;
	virtual void AddHarmonic(std::shared_ptr<HarmonicInterface> harmonic) = 0;
    virtual std::shared_ptr<HarmonicInterface> GetHarmonicByIndex(size_t index) const = 0;
	virtual void RemoveHarmonicByIndex(size_t index) = 0;

    virtual CoordinatesVector GetSumCoordinates() const = 0;

    virtual void DoOnHarmonicChanged() = 0;
    virtual void DoOnHarmonicAdded(size_t index) = 0;
    virtual void DoOnHarmonicDeleted(size_t index) = 0;

	virtual ~HarmonicsStorageInterface() = default;
};
