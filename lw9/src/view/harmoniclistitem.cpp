#include "harmoniclistitem.h"

HarmonicListItem::HarmonicListItem(std::shared_ptr<HarmonicInterface> harmonic)
    : m_harmonic(harmonic)
    , m_listWidgetItem(new QListWidgetItem)
{
    m_listWidgetItem->setText(QString::fromStdString(m_harmonic->ToString()));
    connect(dynamic_cast<QObject*>(harmonic.get()), SIGNAL(DoOnChange()), this, SLOT(ChangeListWidgetItemText()));
}

std::shared_ptr<QListWidgetItem> HarmonicListItem::GetListWidgetItem()
{
    return m_listWidgetItem;
}

void HarmonicListItem::ChangeListWidgetItemText()
{
    m_listWidgetItem->setText(QString::fromStdString(m_harmonic->ToString()));
}
