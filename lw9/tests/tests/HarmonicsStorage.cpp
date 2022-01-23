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
                coordinates.push_back({0, 0});
            }
            coordinates.at(i).x += curCoordinates[i].x;
            coordinates.at(i).y += curCoordinates[i].y;
        }
    }

    return coordinates;
}
