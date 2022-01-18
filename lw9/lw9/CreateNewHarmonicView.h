#pragma once

namespace lw9 {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class CreateNewHarmonicView : public System::Windows::Forms::Form
	{
	public:
		CreateNewHarmonicView()
		{
			InitializeComponent();
		}

	protected:
		~CreateNewHarmonicView()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^ groupBox1;
	protected:
	private: System::Windows::Forms::TextBox^ phaseTextBox;
	private: System::Windows::Forms::TextBox^ frequencyTextBox;
	private: System::Windows::Forms::TextBox^ amplitudeTextBox;
	private: System::Windows::Forms::RadioButton^ radioButtonSin;
	private: System::Windows::Forms::RadioButton^ radioButtonCos;
	private: System::Windows::Forms::Label^ Phase;
	private: System::Windows::Forms::Label^ Frequency;
	private: System::Windows::Forms::Label^ Amplitude;
	private: System::Windows::Forms::Button^ cancleButton;
	private: System::Windows::Forms::Button^ okButton;
	private: System::Windows::Forms::Label^ label1;

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->cancleButton = (gcnew System::Windows::Forms::Button());
			this->phaseTextBox = (gcnew System::Windows::Forms::TextBox());
			this->okButton = (gcnew System::Windows::Forms::Button());
			this->frequencyTextBox = (gcnew System::Windows::Forms::TextBox());
			this->amplitudeTextBox = (gcnew System::Windows::Forms::TextBox());
			this->radioButtonSin = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonCos = (gcnew System::Windows::Forms::RadioButton());
			this->Phase = (gcnew System::Windows::Forms::Label());
			this->Frequency = (gcnew System::Windows::Forms::Label());
			this->Amplitude = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->cancleButton);
			this->groupBox1->Controls->Add(this->phaseTextBox);
			this->groupBox1->Controls->Add(this->okButton);
			this->groupBox1->Controls->Add(this->frequencyTextBox);
			this->groupBox1->Controls->Add(this->amplitudeTextBox);
			this->groupBox1->Controls->Add(this->radioButtonSin);
			this->groupBox1->Controls->Add(this->radioButtonCos);
			this->groupBox1->Controls->Add(this->Phase);
			this->groupBox1->Controls->Add(this->Frequency);
			this->groupBox1->Controls->Add(this->Amplitude);
			this->groupBox1->Location = System::Drawing::Point(36, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(253, 273);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(19, 193);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(112, 20);
			this->label1->TabIndex = 8;
			this->label1->Text = L"1*Sin(1*x + 0)";
			// 
			// cancleButton
			// 
			this->cancleButton->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->cancleButton->Location = System::Drawing::Point(165, 235);
			this->cancleButton->Name = L"cancleButton";
			this->cancleButton->Size = System::Drawing::Size(75, 23);
			this->cancleButton->TabIndex = 4;
			this->cancleButton->Text = L"Cancel";
			this->cancleButton->UseVisualStyleBackColor = true;
			// 
			// phaseTextBox
			// 
			this->phaseTextBox->Location = System::Drawing::Point(121, 147);
			this->phaseTextBox->Name = L"phaseTextBox";
			this->phaseTextBox->Size = System::Drawing::Size(111, 22);
			this->phaseTextBox->TabIndex = 7;
			this->phaseTextBox->Text = L"0";
			// 
			// okButton
			// 
			this->okButton->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->okButton->Location = System::Drawing::Point(84, 235);
			this->okButton->Name = L"okButton";
			this->okButton->Size = System::Drawing::Size(75, 23);
			this->okButton->TabIndex = 3;
			this->okButton->Text = L"OK";
			this->okButton->UseVisualStyleBackColor = true;
			// 
			// frequencyTextBox
			// 
			this->frequencyTextBox->Location = System::Drawing::Point(121, 107);
			this->frequencyTextBox->Name = L"frequencyTextBox";
			this->frequencyTextBox->Size = System::Drawing::Size(111, 22);
			this->frequencyTextBox->TabIndex = 6;
			this->frequencyTextBox->Text = L"1";
			// 
			// amplitudeTextBox
			// 
			this->amplitudeTextBox->Location = System::Drawing::Point(121, 32);
			this->amplitudeTextBox->Name = L"amplitudeTextBox";
			this->amplitudeTextBox->Size = System::Drawing::Size(111, 22);
			this->amplitudeTextBox->TabIndex = 5;
			this->amplitudeTextBox->Text = L"1";
			// 
			// radioButtonSin
			// 
			this->radioButtonSin->AutoSize = true;
			this->radioButtonSin->Checked = true;
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
			// CreateNewHarmonicView
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(324, 301);
			this->Controls->Add(this->groupBox1);
			this->Name = L"CreateNewHarmonicView";
			this->Text = L"CreateNewHarmonicView";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
};
}
