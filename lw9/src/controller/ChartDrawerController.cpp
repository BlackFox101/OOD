#include "ChartDrawerController.h"
#include "src/model/Harmonic.h"

ChartDrawerController::ChartDrawerController(std::shared_ptr<HarmonicsStorageInterface> harmonicsStorage)
	: m_harmonicsStorage(harmonicsStorage)
{
}

void ChartDrawerController::CreateNewHarmonic(HarmonicDTO harmonic)
{
    auto newHarmonic = std::make_shared<Harmonic>(harmonic.type, harmonic.amplitude, harmonic.frequency, harmonic.phase);
    m_harmonicsStorage->AddHarmonic(newHarmonic);
}

void ChartDrawerController::DeleteHarmonic(size_t index)
{
	m_harmonicsStorage->RemoveHarmonicByIndex(index);
}

void ChartDrawerController::ChangeHarmonicPhase(size_t index, double value)
{
    auto harmonic = m_harmonicsStorage->GetHarmonicByIndex(index);
    harmonic->SetPhase(value);
}

void ChartDrawerController::ChangeHarmonicFrequency(size_t index, double value)
{
    auto harmonic = m_harmonicsStorage->GetHarmonicByIndex(index);
    harmonic->SetFrequency(value);
}

void ChartDrawerController::ChangeHarmonicAmplitude(size_t index, double value)
{
    auto harmonic = m_harmonicsStorage->GetHarmonicByIndex(index);
    harmonic->SetAmplitude(value);
}

void ChartDrawerController::ChangeHarmonicType(size_t index, HarmonicType value)
{
    auto harmonic = m_harmonicsStorage->GetHarmonicByIndex(index);
    harmonic->SetType(value);
}
