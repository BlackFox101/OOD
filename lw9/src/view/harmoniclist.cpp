#include "harmoniclist.h"
#include "harmoniclistitem.h"

HarmonicList::HarmonicList(QListWidget* list)
    : m_list(list)
{
}

void HarmonicList::AddNewHarmonic(std::shared_ptr<HarmonicInterface> harmonic)
{
    auto newItem = std::make_shared<HarmonicListItem>(harmonic);
    connect(dynamic_cast<QObject*>(newItem.get()), SIGNAL(DoOnHarmonicChanged()), this, SLOT(HarmonicChanged()));
    m_listItemStorage.push_back(newItem);

    m_list->addItem(newItem->GetListWidgetItem().get());
    m_list->setCurrentRow(m_list->count()-1);
}

void HarmonicList::DeleteHarmonicByIndex(size_t index)
{
    m_list->takeItem(index);

    auto item = m_listItemStorage.at(index);
    disconnect(dynamic_cast<QObject*>(item.get()), SIGNAL(DoOnHarmonicChanged()), this, SLOT(HarmonicChanged()));
    m_listItemStorage.erase(m_listItemStorage.begin() + index);
}

int HarmonicList::GetSelectedharmonicIndex()
{
    return m_list->currentRow();
}

int HarmonicList::GetItemCount()
{
    return m_list->count();
}


void HarmonicList::HarmonicChanged()
{
    emit DoHarmonicChanged();
}
