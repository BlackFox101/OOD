#pragma once
#include <string>
#include <QObject>
#include <QListWidgetItem>
#include "../../src/model/IHarmonic.h"

class HarmonicListItem : public QObject
{
    Q_OBJECT
public:
    HarmonicListItem(std::shared_ptr<IHarmonic> harmonic);
    std::shared_ptr<QListWidgetItem> GetListWidgetItem();

signals:
    void DoOnHarmonicChanged();

private slots:
    void ChangeListWidgetItemText();

private:
    std::shared_ptr<IHarmonic> m_harmonic;
    std::shared_ptr<QListWidgetItem> m_listWidgetItem;

    size_t m_lastItemIndex;

    static std::string HarmonicToString(std::shared_ptr<IHarmonic> harmonic);
};

