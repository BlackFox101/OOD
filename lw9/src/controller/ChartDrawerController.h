#pragma once
#include "ChartDrawerControllerInterface.h"
#include "src/model/HarmonicsStorageInterface.h"
#include "src/common/harmonictype.h"
#include <memory>

class ChartDrawerController : public ChartDrawerControllerInterface
{
public:
	ChartDrawerController(std::shared_ptr<HarmonicsStorageInterface> harmonicsStorage);

    void CreateNewHarmonic(HarmonicDTO harmonic) override;
    void DeleteHarmonic(size_t index) override;

    void ChangeHarmonicPhase(size_t index, double value) override;
    void ChangeHarmonicFrequency(size_t index, double value) override;
    void ChangeHarmonicAmplitude(size_t index, double value) override;
    void ChangeHarmonicType(size_t index, HarmonicType value) override;

private:
	std::shared_ptr<HarmonicsStorageInterface> m_harmonicsStorage;
};
