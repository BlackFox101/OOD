#pragma once
#include "IChartDrawerController.h"
#include "../../src/model/IHarmonicStorage.h"
#include <memory>

class ChartDrawerController : public IChartDrawerController
{
public:
    ChartDrawerController(std::shared_ptr<IHarmonicStorage> harmonicsStorage);

    void CreateNewHarmonic(HarmonicDTO harmonic) override;
    void DeleteHarmonic(size_t index) override;

    void ChangeHarmonicPhase(size_t index, double value) override;
    void ChangeHarmonicFrequency(size_t index, double value) override;
    void ChangeHarmonicAmplitude(size_t index, double value) override;
    void ChangeHarmonicType(size_t index, HarmonicType value) override;

private:
    std::shared_ptr<IHarmonicStorage> m_harmonicsStorage;
};
