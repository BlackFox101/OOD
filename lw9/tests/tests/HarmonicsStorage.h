#pragma once
#include <vector>
#include <memory>
#include "HarmonicsStorageInterface.h"

class HarmonicsStorage :  public HarmonicsStorageInterface
{
public:
	HarmonicsStorage();
    ~HarmonicsStorage() {};

	size_t GetHarmonicCount() const override;
	void AddHarmonic(std::shared_ptr<HarmonicInterface> harmonic) override;
	std::shared_ptr<HarmonicInterface> GetHarmonicByIndex(size_t index) const override;
    void RemoveHarmonicByIndex(size_t index) override;

    CoordinatesVector GetSumCoordinates() const override;

private:
	std::vector<std::shared_ptr<HarmonicInterface>> m_harmonics;
};

