#include "ChartDrawerView.h"
#include "ui_ChartDrawerView.h"

ChartDrawerView::ChartDrawerView(std::shared_ptr<IHarmonicStorage> harmonicStorage,
                                 std::shared_ptr<IChartDrawerController> controller,
                                 QWidget *parent)
    : QMainWindow(parent)
    , m_harmonicStorage(harmonicStorage)
    , m_controller(controller)
    , ui(new Ui::ChartDrawerView)
    , m_createNewHarmonicView(m_controller)
{
    ui->setupUi(this);

    m_harmonicEditor = std::make_unique<HarmonicEditor>(controller, ui->editorMenuBox, ui->amplitudeInput, ui->frequencyInput, ui->phaseInput, ui->radioButtonSin, ui->radioButtonCos);
    m_harmonicList = std::make_unique<HarmonicList>(ui->harmonicList);
    m_chartGraphicView = std::make_unique<ChartGraphicView>(ui->tabWidget, ui->graphicsView, ui->tableWidget, m_harmonicStorage);

    connect(ui->addNewButton, SIGNAL(clicked()), this, SLOT(OpenCreateNewHarmonicView()));
    connect(dynamic_cast<QObject*>(m_harmonicStorage.get()), SIGNAL(DoOnHarmonicAdded(size_t)), this, SLOT(HarmonicAdded(size_t)));
    connect(dynamic_cast<QObject*>(m_harmonicStorage.get()), SIGNAL(DoOnHarmonicDeleted(size_t)), this, SLOT(HarmonicDeleted(size_t)));
    connect(dynamic_cast<QObject*>(m_harmonicList.get()), SIGNAL(DoHarmonicChanged()), this, SLOT(HarmonicChanged()));

    connect(ui->harmonicList, SIGNAL(itemSelectionChanged()), this, SLOT(ChangeSelectedHarmonic()));
    connect(ui->deleteSelectedButton, SIGNAL(clicked()), this, SLOT(DeleteHarmonic()));

    Initialize();
}

ChartDrawerView::~ChartDrawerView()
{
    delete ui;
}

void ChartDrawerView::Initialize()
{
    for (size_t i = 0; i < m_harmonicStorage->GetHarmonicCount(); ++i)
    {
        auto harmonic = m_harmonicStorage->GetHarmonicByIndex(i);
        m_harmonicList->AddNewHarmonic(harmonic);
    }

    if(m_harmonicStorage->GetHarmonicCount() == 0)
    {
        ui->deleteSelectedButton->setEnabled(false);
    }
    else
    {
        m_chartGraphicView->Update();
    }
}

void ChartDrawerView::HarmonicChanged()
{
    m_chartGraphicView->Update();
}

void ChartDrawerView::OpenCreateNewHarmonicView()
{
    m_createNewHarmonicView.show();
}

void ChartDrawerView::HarmonicAdded(size_t index)
{
    auto harmonic = m_harmonicStorage->GetHarmonicByIndex(index);

    m_harmonicList->AddNewHarmonic(harmonic);
    ui->deleteSelectedButton->setEnabled(true);
    m_chartGraphicView->Update();
}

void ChartDrawerView::HarmonicDeleted(size_t index)
{
    if (m_harmonicStorage->GetHarmonicCount() == 0)
    {
        ui->editorMenuBox->hide();
    }

    if(m_harmonicStorage->GetHarmonicCount() == 0)
    {
        ui->deleteSelectedButton->setEnabled(false);
    }

    m_harmonicList->DeleteHarmonicByIndex(index);
    ChangeSelectedHarmonic();
    connect(ui->harmonicList, SIGNAL(itemSelectionChanged()), this, SLOT(ChangeSelectedHarmonic()));

    m_chartGraphicView->Update();
}

void ChartDrawerView::DeleteHarmonic()
{
    disconnect(ui->harmonicList, SIGNAL(itemSelectionChanged()), this, SLOT(ChangeSelectedHarmonic()));
    size_t deletedHarmonicIndex = m_harmonicList->GetSelectedharmonicIndex();
    m_controller->DeleteHarmonic(deletedHarmonicIndex);
}


void ChartDrawerView::ChangeSelectedHarmonic()
{
    int index = m_harmonicList->GetSelectedharmonicIndex();
    if (index < 0 || index >= m_harmonicList->GetItemCount())
    {
        return;
    }
    auto harmonic = m_harmonicStorage->GetHarmonicByIndex(index);

    HarmonicDTO harmonicDTO = { harmonic->GetAmplitude(), harmonic->GetFrequency(), harmonic->GetPhase(), harmonic->GetType() };
    m_harmonicEditor->ChangeSelectedHarmonic(harmonicDTO, index);
}
