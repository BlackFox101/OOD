#include "chartgraphicview.h"

ChartGraphicView::ChartGraphicView(QTabWidget* tabs, QGraphicsView* graphicsView, QTableWidget* table)
    : m_tabs(tabs)
    , m_graphicsScene(new QGraphicsScene())
    , m_table(table)
{
    m_table->setColumnCount(2);

    //graphicsView->scale(2, 2);
    graphicsView->setScene(m_graphicsScene.get());


//    const auto mainRect = graphicsView->geometry();
//    m_graphicsScene->setSceneRect(mainRect);
//    graphicsView->setAlignment(Qt::AlignLeft);
//    //m_graphicsScene->s
      m_graphicsScene->addLine(0, 0, 300, 5);

//    QPen pen(Qt::gray);
//    for (int i = 1; i <= 1; ++i)
//    {
//        m_graphicsScene->addLine(0, i * 0, 600, i * 30, pen);
//    }

      // currentChanged
      connect(m_tabs.get(), SIGNAL(currentChanged(int)), this, SLOT(ChangeView(int)));
}

void ChartGraphicView::ChangeView(int)
{
    ChangeSelectedHarmonic(m_harmonic);
}

void ChartGraphicView::UpdateDate()
{
    ChangeSelectedHarmonic(m_harmonic);
}

void ChartGraphicView::ChangeSelectedHarmonic(std::shared_ptr<HarmonicInterface> harmonic)
{
    if (m_harmonic != harmonic)
    {
        disconnect(dynamic_cast<QObject*>(m_harmonic.get()), SIGNAL(DoOnChange()), this, SLOT(UpdateDate()));
        m_harmonic = harmonic;
        connect(dynamic_cast<QObject*>(m_harmonic.get()), SIGNAL(DoOnChange()), this, SLOT(UpdateDate()));
    }

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

void ChartGraphicView::InsertСoordinatesInTable()
{
    auto coordinates = m_harmonic->GetCoordinates();
    m_table->setRowCount(coordinates.size());

    for (size_t i = 0; i < coordinates.size(); ++i)
    {
         QTableWidgetItem* x = new QTableWidgetItem(QString::number(coordinates[i].x));
         QTableWidgetItem* y = new QTableWidgetItem(QString::number(coordinates[i].y));
         m_table->setItem(i, 0, x);
         m_table->setItem(i, 1, y);
    }
}

void ChartGraphicView::DrawChart()
{
    m_graphicsScene->clear();
    auto coordinates = m_harmonic->GetCoordinates();
    auto lastPoint = coordinates.front();
    for (auto& coordinate : coordinates)
    {
        m_graphicsScene->addLine(lastPoint.x, lastPoint.y, coordinate.x, coordinate.y);
    }
}
