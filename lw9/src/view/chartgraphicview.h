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
    void UpdateCoornates(CoordinatesVector coordinates);

private slots:
    void ChangeView(int index);
    void UpdateView();

private:
    std::unique_ptr<QTabWidget> m_tabs;
    std::unique_ptr<QGraphicsScene> m_graphicsScene;
    std::shared_ptr<QTableWidget> m_table;
    CoordinatesVector m_coordinates;

    void Initialize();

    void DrawChart();
    void InsertСoordinatesInTable();
};
