#pragma once
#include "ChartDrawerControllerInterface.h"
#include "src/model/HarmonicsStorageInterface.h"
#include "src/common/harmonictype.h"
#include <memory>

class ChartDrawerController : public ChartDrawerControllerInterface
{
public:
	ChartDrawerController(std::shared_ptr<HarmonicsStorageInterface> harmonicsStorage);

	void CreateNewHarmonic(HarmonicType type, double amplitude, double frequency, double phase) const override;
	void DeleteHarmonic(size_t index) const override;
private:
	std::shared_ptr<HarmonicsStorageInterface> m_harmonicsStorage;
};

