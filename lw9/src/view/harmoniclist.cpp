#include "harmoniclist.h"
#include "harmoniclistitem.h"

HarmonicList::HarmonicList(QListWidget* list)
    : m_list(list)
{
}

void HarmonicList::AddNewHarmonic(std::shared_ptr<HarmonicInterface> harmonic)
{
    auto newItem = std::make_shared<HarmonicListItem>(harmonic);
    m_listItemStorage.push_back(newItem);

    m_list->addItem(newItem->GetListWidgetItem().get());
    m_list->setCurrentRow(m_list->count()-1);
}

void HarmonicList::DeleteHarmonicByIndex(size_t index)
{
    auto widget = m_list->takeItem(index);
}

size_t HarmonicList::GetSelectedharmonicIndex()
{
    return (size_t)m_list->currentRow();
}

size_t HarmonicList::GetItemCount()
{
    return m_list->count();
}
