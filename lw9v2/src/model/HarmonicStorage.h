#pragma once
#include <QObject>
#include <vector>
#include <memory>
#include "IHarmonicStorage.h"

class HarmonicStorage : public QObject, public IHarmonicStorage
{
    Q_OBJECT
public:
    HarmonicStorage();

    size_t GetHarmonicCount() const override;
    void AddHarmonic(std::shared_ptr<IHarmonic> harmonic) override;
    std::shared_ptr<IHarmonic> GetHarmonicByIndex(size_t index) const override;
    void RemoveHarmonicByIndex(size_t index) override;

    double GetSumYByX(double x) const override;

signals:
    void DoOnHarmonicChanged() override;
    void DoOnHarmonicAdded(size_t index) override;
    void DoOnHarmonicDeleted(size_t index) override;

private:
    std::vector<std::shared_ptr<IHarmonic>> m_harmonics;
};
