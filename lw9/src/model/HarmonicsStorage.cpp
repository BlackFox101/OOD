#include "HarmonicsStorage.h"
#include <stdexcept>

HarmonicsStorage::HarmonicsStorage()
{}

size_t HarmonicsStorage::GetHarmonicCount() const
{
	return m_harmonics.size();
}

void HarmonicsStorage::AddHarmonic(std::shared_ptr<HarmonicInterface> harmonic)
{
	m_harmonics.push_back(harmonic);
}

std::shared_ptr<HarmonicInterface> HarmonicsStorage::GetHarmonicByIndex(size_t index) const
{
	return m_harmonics.at(index);
}

void HarmonicsStorage::RemoveHarmonicByIndex(size_t index)
{
	if (index >= m_harmonics.size())
	{
		throw std::invalid_argument("There is no element for this index");
	}
	m_harmonics.erase(m_harmonics.begin() + index);
}
