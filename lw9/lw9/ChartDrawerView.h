#pragma once
#include "CreateNewHarmonicView.h"
#include "HarmonicsStorageInterface.h"
#include <memory>

namespace lw9 {

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

public ref class ChartDrawerView : public System::Windows::Forms::Form
{
public:
	ChartDrawerView(std::shared_ptr<HarmonicsStorageInterface> harmonicsStorage, std::shared_ptr<ChartDrawerControllerInterface> controller)
	{
		InitializeComponent();
	}
private:
	std::shared_ptr<HarmonicsStorageInterface> m_harmonicsStorage;

protected:
	~ChartDrawerView()
	{
		if (components)
		{
			delete components;
		}
	}
private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
private: System::Windows::Forms::GroupBox^ groupBox1;
private: System::Windows::Forms::Label^ Phase;
private: System::Windows::Forms::Label^ Frequency;
private: System::Windows::Forms::Label^ Amplitude;
private: System::Windows::Forms::TextBox^ phaseTextBox;
private: System::Windows::Forms::TextBox^ frequencyTextBox;
private: System::Windows::Forms::TextBox^ amplitudeTextBox;
private: System::Windows::Forms::RadioButton^ radioButtonSin;
private: System::Windows::Forms::RadioButton^ radioButtonCos;
private: System::Windows::Forms::Button^ addNewButton;
private: System::Windows::Forms::Button^ deleteSelectedButton;
private: System::Windows::Forms::GroupBox^ groupBox2;
private: System::Windows::Forms::Label^ Harmonics;


private:
	System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
	void InitializeComponent(void)
	{
		System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
		System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
		this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
		this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
		this->phaseTextBox = (gcnew System::Windows::Forms::TextBox());
		this->frequencyTextBox = (gcnew System::Windows::Forms::TextBox());
		this->amplitudeTextBox = (gcnew System::Windows::Forms::TextBox());
		this->radioButtonSin = (gcnew System::Windows::Forms::RadioButton());
		this->radioButtonCos = (gcnew System::Windows::Forms::RadioButton());
		this->Phase = (gcnew System::Windows::Forms::Label());
		this->Frequency = (gcnew System::Windows::Forms::Label());
		this->Amplitude = (gcnew System::Windows::Forms::Label());
		this->addNewButton = (gcnew System::Windows::Forms::Button());
		this->deleteSelectedButton = (gcnew System::Windows::Forms::Button());
		this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
		this->Harmonics = (gcnew System::Windows::Forms::Label());
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
		this->groupBox1->SuspendLayout();
		this->groupBox2->SuspendLayout();
		this->SuspendLayout();
		// 
		// chart1
		// 
		chartArea3->Name = L"ChartArea1";
		this->chart1->ChartAreas->Add(chartArea3);
		this->chart1->Location = System::Drawing::Point(12, 300);
		this->chart1->Name = L"chart1";
		series3->BorderWidth = 2;
		series3->ChartArea = L"ChartArea1";
		series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
		series3->Name = L"Series1";
		this->chart1->Series->Add(series3);
		this->chart1->Size = System::Drawing::Size(737, 300);
		this->chart1->TabIndex = 0;
		// 
		// groupBox1
		// 
		this->groupBox1->Controls->Add(this->phaseTextBox);
		this->groupBox1->Controls->Add(this->frequencyTextBox);
		this->groupBox1->Controls->Add(this->amplitudeTextBox);
		this->groupBox1->Controls->Add(this->radioButtonSin);
		this->groupBox1->Controls->Add(this->radioButtonCos);
		this->groupBox1->Controls->Add(this->Phase);
		this->groupBox1->Controls->Add(this->Frequency);
		this->groupBox1->Controls->Add(this->Amplitude);
		this->groupBox1->Location = System::Drawing::Point(455, 31);
		this->groupBox1->Name = L"groupBox1";
		this->groupBox1->Size = System::Drawing::Size(253, 193);
		this->groupBox1->TabIndex = 1;
		this->groupBox1->TabStop = false;
		// 
		// phaseTextBox
		// 
		this->phaseTextBox->Location = System::Drawing::Point(121, 147);
		this->phaseTextBox->Name = L"phaseTextBox";
		this->phaseTextBox->Size = System::Drawing::Size(111, 22);
		this->phaseTextBox->TabIndex = 7;
		// 
		// frequencyTextBox
		// 
		this->frequencyTextBox->Location = System::Drawing::Point(121, 107);
		this->frequencyTextBox->Name = L"frequencyTextBox";
		this->frequencyTextBox->Size = System::Drawing::Size(111, 22);
		this->frequencyTextBox->TabIndex = 6;
		// 
		// amplitudeTextBox
		// 
		this->amplitudeTextBox->Location = System::Drawing::Point(121, 32);
		this->amplitudeTextBox->Name = L"amplitudeTextBox";
		this->amplitudeTextBox->Size = System::Drawing::Size(111, 22);
		this->amplitudeTextBox->TabIndex = 5;
		// 
		// radioButtonSin
		// 
		this->radioButtonSin->AutoSize = true;
		this->radioButtonSin->Location = System::Drawing::Point(52, 72);
		this->radioButtonSin->Name = L"radioButtonSin";
		this->radioButtonSin->Size = System::Drawing::Size(49, 21);
		this->radioButtonSin->TabIndex = 4;
		this->radioButtonSin->TabStop = true;
		this->radioButtonSin->Text = L"Sin";
		this->radioButtonSin->UseVisualStyleBackColor = true;
		// 
		// radioButtonCos
		// 
		this->radioButtonCos->AutoSize = true;
		this->radioButtonCos->Location = System::Drawing::Point(136, 72);
		this->radioButtonCos->Name = L"radioButtonCos";
		this->radioButtonCos->Size = System::Drawing::Size(53, 21);
		this->radioButtonCos->TabIndex = 3;
		this->radioButtonCos->TabStop = true;
		this->radioButtonCos->Text = L"Cos";
		this->radioButtonCos->UseVisualStyleBackColor = true;
		// 
		// Phase
		// 
		this->Phase->AutoSize = true;
		this->Phase->Location = System::Drawing::Point(20, 150);
		this->Phase->Name = L"Phase";
		this->Phase->Size = System::Drawing::Size(48, 17);
		this->Phase->TabIndex = 2;
		this->Phase->Text = L"Phase";
		// 
		// Frequency
		// 
		this->Frequency->AutoSize = true;
		this->Frequency->Location = System::Drawing::Point(20, 107);
		this->Frequency->Name = L"Frequency";
		this->Frequency->Size = System::Drawing::Size(75, 17);
		this->Frequency->TabIndex = 1;
		this->Frequency->Text = L"Frequency";
		// 
		// Amplitude
		// 
		this->Amplitude->AutoSize = true;
		this->Amplitude->Location = System::Drawing::Point(20, 35);
		this->Amplitude->Name = L"Amplitude";
		this->Amplitude->Size = System::Drawing::Size(74, 17);
		this->Amplitude->TabIndex = 0;
		this->Amplitude->Text = L"Amplitude:";
		// 
		// addNewButton
		// 
		this->addNewButton->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->addNewButton->Location = System::Drawing::Point(31, 212);
		this->addNewButton->Name = L"addNewButton";
		this->addNewButton->Size = System::Drawing::Size(94, 30);
		this->addNewButton->TabIndex = 2;
		this->addNewButton->Text = L"Add new";
		this->addNewButton->UseVisualStyleBackColor = true;
		this->addNewButton->Click += gcnew System::EventHandler(this, &ChartDrawerView::addNewButton_Click);
		// 
		// deleteSelectedButton
		// 
		this->deleteSelectedButton->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->deleteSelectedButton->Location = System::Drawing::Point(157, 212);
		this->deleteSelectedButton->Name = L"deleteSelectedButton";
		this->deleteSelectedButton->Size = System::Drawing::Size(143, 30);
		this->deleteSelectedButton->TabIndex = 3;
		this->deleteSelectedButton->Text = L"Delete selected";
		this->deleteSelectedButton->UseVisualStyleBackColor = true;
		// 
		// groupBox2
		// 
		this->groupBox2->Controls->Add(this->Harmonics);
		this->groupBox2->Location = System::Drawing::Point(41, 31);
		this->groupBox2->Name = L"groupBox2";
		this->groupBox2->Size = System::Drawing::Size(248, 129);
		this->groupBox2->TabIndex = 4;
		this->groupBox2->TabStop = false;
		// 
		// Harmonics
		// 
		this->Harmonics->AutoSize = true;
		this->Harmonics->Location = System::Drawing::Point(6, 18);
		this->Harmonics->Name = L"Harmonics";
		this->Harmonics->Size = System::Drawing::Size(75, 17);
		this->Harmonics->TabIndex = 5;
		this->Harmonics->Text = L"Harmonics";
		// 
		// ChartDrawerView
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(761, 612);
		this->Controls->Add(this->groupBox2);
		this->Controls->Add(this->deleteSelectedButton);
		this->Controls->Add(this->addNewButton);
		this->Controls->Add(this->groupBox1);
		this->Controls->Add(this->chart1);
		this->Name = L"ChartDrawerView";
		this->Text = L"ChartDrawerView";
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
		this->groupBox1->ResumeLayout(false);
		this->groupBox1->PerformLayout();
		this->groupBox2->ResumeLayout(false);
		this->groupBox2->PerformLayout();
		this->ResumeLayout(false);

	}
#pragma endregion


private: System::Void addNewButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	CreateNewHarmonicView^ createNewHarmonicView = gcnew CreateNewHarmonicView;
	createNewHarmonicView->Show();
}

};
}
