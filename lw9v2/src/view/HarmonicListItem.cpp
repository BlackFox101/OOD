#include "HarmonicListItem.h"
#include <sstream>

HarmonicListItem::HarmonicListItem(std::shared_ptr<IHarmonic> harmonic)
    : m_harmonic(harmonic)
    , m_listWidgetItem(new QListWidgetItem)
{
    m_listWidgetItem->setText(QString::fromStdString(HarmonicToString(m_harmonic)));
    connect(dynamic_cast<QObject*>(harmonic.get()), SIGNAL(DoOnChange()), this, SLOT(ChangeListWidgetItemText()));
}

std::shared_ptr<QListWidgetItem> HarmonicListItem::GetListWidgetItem()
{
    return m_listWidgetItem;
}

void HarmonicListItem::ChangeListWidgetItemText()
{
    m_listWidgetItem->setText(QString::fromStdString(HarmonicToString(m_harmonic)));
    emit DoOnHarmonicChanged();
}

std::string HarmonicListItem::HarmonicToString(std::shared_ptr<IHarmonic> harmonic)
{

    std::ostringstream function;
    function << harmonic->GetAmplitude() << "*" << HarmonicTypeToString(harmonic->GetType()) << "(" << harmonic->GetFrequency() << "*x + " << harmonic->GetPhase() << ")";

    return function.str();
}
