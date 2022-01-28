#pragma once
#include <QObject>
#include <QListWidget>
#include "HarmonicListItem.h"

class HarmonicList : public QObject
{
    Q_OBJECT
public:
    HarmonicList(QListWidget* list);

    void AddNewHarmonic(std::shared_ptr<IHarmonic> harmonic);
    void DeleteHarmonicByIndex(size_t inex);
    int GetSelectedharmonicIndex();
    int GetItemCount();

signals:
    void DoHarmonicChanged();

public slots:
    void HarmonicChanged();


private:
    std::shared_ptr<QListWidget> m_list;
    std::vector<std::shared_ptr<HarmonicListItem>> m_listItemStorage;

    size_t m_lastItemIndex;
};
