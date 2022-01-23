#pragma once
#include <QObject>
#include <QListWidget>
#include "harmoniclistitem.h"

class HarmonicList : public QObject
{
    Q_OBJECT
public:
    HarmonicList(QListWidget* list);
    void AddNewHarmonic(std::shared_ptr<HarmonicInterface> harmonic);
    void DeleteHarmonicByIndex(size_t inex);
    size_t GetSelectedharmonicIndex();
    size_t GetItemCount();

private:
    std::shared_ptr<QListWidget> m_list;
    std::vector<std::shared_ptr<HarmonicListItem>> m_listItemStorage;

    size_t m_lastItemIndex;
};
