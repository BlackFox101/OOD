#include "ChartGraphicView.h"
#include "QGraphicsItem"

ChartGraphicView::ChartGraphicView(QTabWidget* tabs, QGraphicsView* graphicsView, QTableWidget* table, std::shared_ptr<IHarmonicStorage> harmonicStorage)
    : m_tabs(tabs)
    , m_graphicsScene(new QGraphicsScene())
    , m_table(table)
    , m_harmonicStorage(harmonicStorage)
{
    m_table->setColumnCount(2);

    graphicsView->setScene(m_graphicsScene.get());

    connect(m_tabs.get(), SIGNAL(currentChanged(int)), this, SLOT(ChangeView(int)));
}

void ChartGraphicView::Initialize()
{
    QPen pen(Qt::gray);
    m_graphicsScene->addLine(0, 0, 600, 0, pen);

    for (int i = 0; i < MAX_X + 50; i += 50)
    {
        auto text = m_graphicsScene->addText(QString::number(i));
        text->setPos(i, 0);
    }
}

void ChartGraphicView::ChangeView(int)
{
    UpdateView();
}

void ChartGraphicView::UpdateView()
{
    m_tabs->currentIndex();
    if (m_tabs->currentIndex() == 0)
    {
        DrawChart();
    }
    else
    {
        InsertСoordinatesInTable();
    }
}

void ChartGraphicView::Update()
{
    m_coordinates = GetCoordinates();
    UpdateView();
}

ChartGraphicView::CoordinatesVector ChartGraphicView::GetCoordinates()
{
    CoordinatesVector coordinates;
    double x = MIN_X;
    while (x <= MAX_X)
    {
        double y = m_harmonicStorage->GetSumYByX(x);
        coordinates.push_back({ x, y });
        x += STEP;
    }

    return coordinates;
}

void ChartGraphicView::InsertСoordinatesInTable()
{
    m_table->setRowCount(m_coordinates.size());

    for (size_t i = 0; i < m_coordinates.size(); ++i)
    {
         QTableWidgetItem* x = new QTableWidgetItem(QString::number(m_coordinates[i].x));
         QTableWidgetItem* y = new QTableWidgetItem(QString::number(m_coordinates[i].y));
         m_table->setItem(i, 0, x);
         m_table->setItem(i, 1, y);
    }
}

void ChartGraphicView::DrawChart()
{
    m_graphicsScene->clear();
    Initialize();
    auto lastPoint = m_coordinates.front();
    for (auto& coordinate : m_coordinates)
    {
        m_graphicsScene->addLine(lastPoint.x * CORRECTION_FACTOR, lastPoint.y, coordinate.x * 10, coordinate.y);
        lastPoint = coordinate;

        if (coordinate.x * CORRECTION_FACTOR > MAX_X)
        {
            break;
        }
    }
}
