#include <QObject>
#include <QGraphicsView>
#include <QTabWidget>
#include <QTableWidget>

#include "../../src/model/IHarmonicStorage.h"

class ChartGraphicView : public QObject
{
     Q_OBJECT
public:
    const double MIN_X = 0;
    const double MAX_X = 600;
    const double STEP = 0.1;
    const double CORRECTION_FACTOR = 10;

    ChartGraphicView(QTabWidget* tabs, QGraphicsView* graphicsView, QTableWidget* table, std::shared_ptr<IHarmonicStorage> harmonicStorage);
    void Update();

private slots:
    void ChangeView(int index);
    void UpdateView();

private:
    struct Point
    {
        double x;
        double y;
    };

    typedef std::vector<Point> CoordinatesVector;

    std::unique_ptr<QTabWidget> m_tabs;
    std::unique_ptr<QGraphicsScene> m_graphicsScene;
    std::shared_ptr<QTableWidget> m_table;
    std::shared_ptr<IHarmonicStorage> m_harmonicStorage;

    CoordinatesVector m_coordinates;
    CoordinatesVector GetCoordinates();

    void Initialize();

    void DrawChart();
    void InsertСoordinatesInTable();
};
