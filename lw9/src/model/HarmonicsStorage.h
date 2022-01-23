#pragma once
#include <QObject>
#include <vector>
#include <memory>
#include "HarmonicsStorageInterface.h"

class HarmonicsStorage : public QObject, public HarmonicsStorageInterface
{
    Q_OBJECT
public:
	HarmonicsStorage();

	size_t GetHarmonicCount() const override;
	void AddHarmonic(std::shared_ptr<HarmonicInterface> harmonic) override;
	std::shared_ptr<HarmonicInterface> GetHarmonicByIndex(size_t index) const override;
    void RemoveHarmonicByIndex(size_t index) override;

signals:
    void DoOnHarmonicAdded(size_t index) override;
    void DoOnHarmonicDeleted(size_t index) override;


private:
	std::vector<std::shared_ptr<HarmonicInterface>> m_harmonics;
};

