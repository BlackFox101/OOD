#pragma once
#include <vector>
#include <memory>
#include "IHarmonicStorage.h"

class HarmonicStorage : public IHarmonicStorage
{
public:
    HarmonicStorage();

    size_t GetHarmonicCount() const override;
    void AddHarmonic(std::shared_ptr<IHarmonic> harmonic) override;
    std::shared_ptr<IHarmonic> GetHarmonicByIndex(size_t index) const override;
    void RemoveHarmonicByIndex(size_t index) override;

    double GetSumYByX(double x) const override;

private:
    std::vector<std::shared_ptr<IHarmonic>> m_harmonics;
};
