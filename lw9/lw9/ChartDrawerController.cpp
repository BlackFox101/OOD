#include "ChartDrawerController.h"
#include "Harmonic.h"

ChartDrawerController::ChartDrawerController(std::shared_ptr<HarmonicsStorageInterface> harmonicsStorage)
	: m_harmonicsStorage(harmonicsStorage)
{
}

void ChartDrawerController::CreateNewHarmonic(HarmonicType type, double amplitude, double frequency, double phase) const
{
	auto harmonic = std::make_shared<Harmonic>(type, amplitude, frequency, phase);
	m_harmonicsStorage->AddHarmonic(harmonic);
}

void ChartDrawerController::DeleteHarmonic(size_t index) const
{
	m_harmonicsStorage->RemoveHarmonicByIndex(index);
}
