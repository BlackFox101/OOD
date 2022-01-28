#include "HarmonicStorage.h"
#include <stdexcept>

HarmonicStorage::HarmonicStorage()
{}

size_t HarmonicStorage::GetHarmonicCount() const
{
    return m_harmonics.size();
}

void HarmonicStorage::AddHarmonic(std::shared_ptr<IHarmonic> harmonic)
{
    m_harmonics.push_back(harmonic);
    emit DoOnHarmonicAdded(m_harmonics.size() - 1);
}

std::shared_ptr<IHarmonic> HarmonicStorage::GetHarmonicByIndex(size_t index) const
{
    return m_harmonics.at(index);
}

void HarmonicStorage::RemoveHarmonicByIndex(size_t index)
{
    if (index >= m_harmonics.size())
    {
        throw std::invalid_argument("There is no element for this index");
    }
    m_harmonics.erase(m_harmonics.begin() + index);
    emit DoOnHarmonicDeleted(index);
}

double HarmonicStorage::GetSumYByX(double x) const
{
    double sumY = 0;
    for(auto& harmonic : m_harmonics)
    {
        auto curY = harmonic->GetYByX(x);
        sumY += curY;
    }

    return sumY;
}
