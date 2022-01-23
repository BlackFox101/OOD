#include <QObject>
#include <QGraphicsView>
#include <QTabWidget>
#include <QTableWidget>
#include "src/model/HarmonicInterface.h"

class ChartGraphicView : public QObject
{
     Q_OBJECT
public:
    ChartGraphicView(QTabWidget* tabs, QGraphicsView* graphicsView, QTableWidget* table);
    void ChangeSelectedHarmonic(std::shared_ptr<HarmonicInterface> harmonic);

private slots:
    void ChangeView(int index);
    void UpdateDate();

private:
    std::unique_ptr<QTabWidget> m_tabs;
    std::unique_ptr<QGraphicsScene> m_graphicsScene;
    std::shared_ptr<QTableWidget> m_table;
    std::shared_ptr<HarmonicInterface> m_harmonic;

    void DrawChart();
    void InsertСoordinatesInTable();
};
