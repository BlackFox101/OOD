#include "chartdrawerview.h"
#include "ui_chartdrawerview.h"
#include "src/common/harmonicdto.h"

#include <QLabel>
#include <QListWidget >

ChartDrawerView::ChartDrawerView(std::shared_ptr<HarmonicsStorageInterface> harmonicsStorage,
                                 std::shared_ptr<ChartDrawerControllerInterface> controller,
                                 QWidget *parent)
    : QMainWindow(parent)
    , m_harmonicsStorage(harmonicsStorage)
    , m_controller(controller)
    , ui(new Ui::ChartDrawerView)
{
    ui->setupUi(this);
    m_harmonicEditor = std::make_unique<HarmonicEditor>(controller, ui->editorMenuBox, ui->amplitudeInput, ui->frequencyInput, ui->phaseInput, ui->radioButtonSin, ui->radioButtonCos);
    m_harmonicList = std::make_unique<HarmonicList>(ui->harmonicList);
    m_chartGraphicView = std::make_unique<ChartGraphicView>(ui->tabWidget, ui->graphicsView, ui->tableWidget);

    connect(ui->addNewButton, SIGNAL(clicked()), this, SLOT(OpenAddNewHarmonicView()));
    connect(dynamic_cast<QObject*>(m_harmonicsStorage.get()), SIGNAL(DoOnHarmonicAdded(size_t)), this, SLOT(HarmonicAdded(size_t)));
    connect(dynamic_cast<QObject*>(m_harmonicsStorage.get()), SIGNAL(DoOnHarmonicDeleted(size_t)), this, SLOT(HarmonicDeleted(size_t)));
    m_createNewHarmonicView.onClickOkButton(this);
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
    for (size_t i = 0; i < m_harmonicsStorage->GetHarmonicCount(); ++i)
    {
        auto harmonic = m_harmonicsStorage->GetHarmonicByIndex(i);
        m_harmonicList->AddNewHarmonic(harmonic);
    }

    if(m_harmonicsStorage->GetHarmonicCount() == 0)
    {
        ui->deleteSelectedButton->setEnabled(false);
    }
}

void ChartDrawerView::HarmonicAdded(size_t index)
{
    auto harmonic = m_harmonicsStorage->GetHarmonicByIndex(index);
    m_harmonicList->AddNewHarmonic(harmonic);
    ui->deleteSelectedButton->setEnabled(true);
}

void ChartDrawerView::HarmonicDeleted(size_t index)
{
    if (m_harmonicsStorage->GetHarmonicCount() == 0)
    {
        ui->editorMenuBox->hide();
    }

    if(m_harmonicsStorage->GetHarmonicCount() == 0)
    {
        ui->deleteSelectedButton->setEnabled(false);
    }

    m_harmonicList->DeleteHarmonicByIndex(index);
    ChangeSelectedHarmonic();
    connect(ui->harmonicList, SIGNAL(itemSelectionChanged()), this, SLOT(ChangeSelectedHarmonic()));
}

void ChartDrawerView::OpenAddNewHarmonicView()
{
    m_createNewHarmonicView.show();
}

void ChartDrawerView::CreateNewHarmonic()
{
    m_controller->CreateNewHarmonic(m_createNewHarmonicView.GetHarmonicData());
    m_createNewHarmonicView.Close();
}

void ChartDrawerView::DeleteHarmonic()
{
    disconnect(ui->harmonicList, SIGNAL(itemSelectionChanged()), this, SLOT(ChangeSelectedHarmonic()));
    size_t deletedHarmonicIndex = m_harmonicList->GetSelectedharmonicIndex();
    m_controller->DeleteHarmonic(deletedHarmonicIndex);
}

void ChartDrawerView::ChangeSelectedHarmonic()
{
    size_t index = m_harmonicList->GetSelectedharmonicIndex();
    if (index < 0 || index >= m_harmonicList->GetItemCount())
    {
        return;
    }
    auto harmonic = m_harmonicsStorage->GetHarmonicByIndex(index);

    HarmonicDTO harmonicDTO = { harmonic->GetAmplitude(), harmonic->GetFrequency(), harmonic->GetPhase(), harmonic->GetType() };
    m_harmonicEditor->ChangeSelectedHarmonic(harmonicDTO, index);

    m_chartGraphicView->ChangeSelectedHarmonic(harmonic);
}



