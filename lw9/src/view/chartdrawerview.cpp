#include "chartdrawerview.h"
#include "ui_chartdrawerview.h"



ChartDrawerView::ChartDrawerView(std::shared_ptr<HarmonicsStorageInterface> harmonicsStorage,
                                 std::shared_ptr<ChartDrawerControllerInterface> controller,
                                 QWidget *parent)
    : QMainWindow(parent)
    , m_harmonicsStorage(harmonicsStorage)
    , m_controller(controller)
    , ui(new Ui::ChartDrawerView)
{
    ui->setupUi(this);
    Initialize();
}

ChartDrawerView::~ChartDrawerView()
{
    delete ui;
}

void ChartDrawerView::Initialize()
{
    connect(ui->addNewButton, SIGNAL(clicked()), this, SLOT(OpenAddNewHarmonicView()));
}

void ChartDrawerView::OpenAddNewHarmonicView()
{
    //itemListScrollArea
    m_createNewHarmonicView.show();
}

void AddNewItemToItemList()
{
    //ui->itemListScrollArea->
}

void CreateNewHarmonicsItemLabel()
{

}
