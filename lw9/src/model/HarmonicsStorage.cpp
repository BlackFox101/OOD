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
    emit DoOnHarmonicAdded(m_harmonics.size() - 1);
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
    emit DoOnHarmonicDeleted(index);
}

CoordinatesVector HarmonicsStorage::GetSumCoordinates() const
{
    CoordinatesVector coordinates;
    for(auto& harmonic : m_harmonics)
    {
        auto curCoordinates = harmonic->GetCoordinates();
        for (size_t i = 0; i < curCoordinates.size(); ++i)
        {
            try
            {
                coordinates.at(i);
            }
            catch (...) {
                coordinates.push_back({(double)i, 0});
            }
            coordinates.at(i).y += curCoordinates[i].y;
        }
    }

    return coordinates;
}
