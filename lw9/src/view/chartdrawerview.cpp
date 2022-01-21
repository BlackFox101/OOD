#include "chartdrawerview.h"
#include "ui_chartdrawerview.h"

ChartDrawerView::ChartDrawerView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChartDrawerView)
{
    ui->setupUi(this);

    connect(ui->addNewButton, SIGNAL(clicked()), this, SLOT(OpenAddNewHarmonicView()));
}

ChartDrawerView::~ChartDrawerView()
{
    delete ui;
}

void ChartDrawerView::OpenAddNewHarmonicView()
{
    m_createNewHarmonicView.show();
}
