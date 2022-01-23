#pragma once
#include <QObject>
#include <QListWidgetItem>
#include "src/model/HarmonicInterface.h"

class HarmonicListItem : public QObject
{
    Q_OBJECT
public:
    HarmonicListItem(std::shared_ptr<HarmonicInterface> harmonic);
    std::shared_ptr<QListWidgetItem> GetListWidgetItem();

private slots:
    void ChangeListWidgetItemText();

private:
    std::shared_ptr<HarmonicInterface> m_harmonic;
    std::shared_ptr<QListWidgetItem> m_listWidgetItem;

    size_t m_lastItemIndex;
};

