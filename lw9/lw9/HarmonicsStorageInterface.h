#pragma once
#include "HarmonicInterface.h"

ref class HarmonicsStorageInterface
{
public:
	virtual size_t GetHarmonicCount() = 0;
	virtual void AddHarmonic(std::shared_ptr<HarmonicInterface> harmonic) = 0;
	virtual std::shared_ptr<HarmonicInterface> GetHarmonicByIndex(size_t index) = 0;
	virtual void RemoveHarmonicByIndex(size_t index) = 0;

	virtual ~HarmonicsStorageInterface() = default;
};

