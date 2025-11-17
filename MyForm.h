/*
 * MyForm.h - Modern UI Design with Enhanced Visuals
 *
 * Improvements:
 * - Modern color scheme with gradient backgrounds
 * - Card-based layout with shadows
 * - Smooth hover effects and transitions
 * - Better spacing and typography
 * - Fullscreen optimized layout
 * - Animated progress feedback
 */
#pragma once

#include "automaton_logic.h"
#include <msclr/marshal_cppstd.h>
#include <sstream>
#include <fstream>
#include <cstdlib>

namespace GenoSearch {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	using namespace System::IO;
	using namespace msclr::interop;
	using namespace GenoSearchEngine;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			InitializeModernUI();
			UpdateUIMode();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Panel^ headerPanel;
	private: System::Windows::Forms::Label^ titleLabel;
	private: System::Windows::Forms::Label^ subtitleLabel;
	private: System::Windows::Forms::Panel^ mainContainer;
	private: System::Windows::Forms::Panel^ leftPanel;
	private: System::Windows::Forms::Panel^ rightPanel;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::RadioButton^ regexRadio;
	private: System::Windows::Forms::RadioButton^ pdaRadio;
	private: System::Windows::Forms::RadioButton^ approxRadio;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::GroupBox^ patternInputGroup;
	private: System::Windows::Forms::TextBox^ patternInputBox;
	private: System::Windows::Forms::GroupBox^ editDistanceGroup;
	private: System::Windows::Forms::Label^ patternLabel;
	private: System::Windows::Forms::Label^ distanceLabel;
	private: System::Windows::Forms::GroupBox^ pdaInputTypeGroup;
	private: System::Windows::Forms::RadioButton^ pdaStringRadio;
	private: System::Windows::Forms::NumericUpDown^ editDistanceInput;
	private: System::Windows::Forms::GroupBox^ fileInputGroup;
	private: System::Windows::Forms::RadioButton^ pdaFileRadio;
	private: System::Windows::Forms::Button^ browseButton;
	private: System::Windows::Forms::TextBox^ fileInputBox;
	private: System::Windows::Forms::Label^ fileInputLabel;
	private: System::Windows::Forms::Label^ supportLabel;
	private: System::Windows::Forms::Label^ sourceInputLabel;
	private: System::Windows::Forms::Label^ step2Label;
	private: System::Windows::Forms::Button^ runButton;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ showErrorButton;
	private: System::Windows::Forms::TabControl^ outputTabControl;
	private: System::Windows::Forms::TabPage^ tabPage1;
	private: System::Windows::Forms::GroupBox^ errorGroup;
	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::TextBox^ errorBox;
	private: System::Windows::Forms::Label^ errorLabel;
	private: System::Windows::Forms::GroupBox^ normalOutputGroup;
	private: System::Windows::Forms::Label^ resultsLabel;
	private: System::Windows::Forms::Button^ exportButton;
	private: System::Windows::Forms::GroupBox^ summaryGroup;
	private: System::Windows::Forms::TextBox^ summaryBox;
	private: System::Windows::Forms::GroupBox^ grammarGroup;
	private: System::Windows::Forms::TextBox^ grammarBox;
	private: System::Windows::Forms::GroupBox^ matchReportGroup;
	private: System::Windows::Forms::TextBox^ resultsBox;
	private: System::Windows::Forms::Panel^ vizToggleGroup;
	private: System::Windows::Forms::Button^ showNfaButton;
	private: System::Windows::Forms::Label^ vizLabel;
	private: System::Windows::Forms::PictureBox^ vizPictureBox;
	private: System::Windows::Forms::Button^ showDfaButton;
	private: System::Windows::Forms::TextBox^ pdaTraceBox;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::ProgressBar^ progressBar;
	private: System::Windows::Forms::Timer^ animationTimer;

	private: System::String^ m_nfaDot;
	private: System::String^ m_dfaDot;
	private: System::ComponentModel::IContainer^ components;

	private:


#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->headerPanel = (gcnew System::Windows::Forms::Panel());
			this->subtitleLabel = (gcnew System::Windows::Forms::Label());
			this->titleLabel = (gcnew System::Windows::Forms::Label());
			this->mainContainer = (gcnew System::Windows::Forms::Panel());
			this->rightPanel = (gcnew System::Windows::Forms::Panel());
			this->outputTabControl = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->errorGroup = (gcnew System::Windows::Forms::GroupBox());
			this->errorBox = (gcnew System::Windows::Forms::TextBox());
			this->errorLabel = (gcnew System::Windows::Forms::Label());
			this->normalOutputGroup = (gcnew System::Windows::Forms::GroupBox());
			this->matchReportGroup = (gcnew System::Windows::Forms::GroupBox());
			this->resultsBox = (gcnew System::Windows::Forms::TextBox());
			this->grammarGroup = (gcnew System::Windows::Forms::GroupBox());
			this->grammarBox = (gcnew System::Windows::Forms::TextBox());
			this->summaryGroup = (gcnew System::Windows::Forms::GroupBox());
			this->summaryBox = (gcnew System::Windows::Forms::TextBox());
			this->exportButton = (gcnew System::Windows::Forms::Button());
			this->resultsLabel = (gcnew System::Windows::Forms::Label());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->pdaTraceBox = (gcnew System::Windows::Forms::TextBox());
			this->vizPictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->vizToggleGroup = (gcnew System::Windows::Forms::Panel());
			this->showDfaButton = (gcnew System::Windows::Forms::Button());
			this->showNfaButton = (gcnew System::Windows::Forms::Button());
			this->vizLabel = (gcnew System::Windows::Forms::Label());
			this->leftPanel = (gcnew System::Windows::Forms::Panel());
			this->progressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->showErrorButton = (gcnew System::Windows::Forms::Button());
			this->step2Label = (gcnew System::Windows::Forms::Label());
			this->runButton = (gcnew System::Windows::Forms::Button());
			this->fileInputGroup = (gcnew System::Windows::Forms::GroupBox());
			this->supportLabel = (gcnew System::Windows::Forms::Label());
			this->browseButton = (gcnew System::Windows::Forms::Button());
			this->fileInputBox = (gcnew System::Windows::Forms::TextBox());
			this->fileInputLabel = (gcnew System::Windows::Forms::Label());
			this->pdaInputTypeGroup = (gcnew System::Windows::Forms::GroupBox());
			this->sourceInputLabel = (gcnew System::Windows::Forms::Label());
			this->pdaFileRadio = (gcnew System::Windows::Forms::RadioButton());
			this->pdaStringRadio = (gcnew System::Windows::Forms::RadioButton());
			this->editDistanceGroup = (gcnew System::Windows::Forms::GroupBox());
			this->editDistanceInput = (gcnew System::Windows::Forms::NumericUpDown());
			this->distanceLabel = (gcnew System::Windows::Forms::Label());
			this->patternInputGroup = (gcnew System::Windows::Forms::GroupBox());
			this->patternLabel = (gcnew System::Windows::Forms::Label());
			this->patternInputBox = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pdaRadio = (gcnew System::Windows::Forms::RadioButton());
			this->approxRadio = (gcnew System::Windows::Forms::RadioButton());
			this->regexRadio = (gcnew System::Windows::Forms::RadioButton());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->animationTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->headerPanel->SuspendLayout();
			this->mainContainer->SuspendLayout();
			this->rightPanel->SuspendLayout();
			this->outputTabControl->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->errorGroup->SuspendLayout();
			this->normalOutputGroup->SuspendLayout();
			this->matchReportGroup->SuspendLayout();
			this->grammarGroup->SuspendLayout();
			this->summaryGroup->SuspendLayout();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->vizPictureBox))->BeginInit();
			this->vizToggleGroup->SuspendLayout();
			this->leftPanel->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->fileInputGroup->SuspendLayout();
			this->pdaInputTypeGroup->SuspendLayout();
			this->editDistanceGroup->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->editDistanceInput))->BeginInit();
			this->patternInputGroup->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// headerPanel
			// 
			this->headerPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(71)));
			this->headerPanel->Controls->Add(this->subtitleLabel);
			this->headerPanel->Controls->Add(this->titleLabel);
			this->headerPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->headerPanel->Location = System::Drawing::Point(0, 0);
			this->headerPanel->Name = L"headerPanel";
			this->headerPanel->Size = System::Drawing::Size(1400, 100);
			this->headerPanel->TabIndex = 0;
			// 
			// subtitleLabel
			// 
			this->subtitleLabel->AutoSize = true;
			this->subtitleLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->subtitleLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(189)), static_cast<System::Int32>(static_cast<System::Byte>(206)),
				static_cast<System::Int32>(static_cast<System::Byte>(242)));
			this->subtitleLabel->Location = System::Drawing::Point(30, 60);
			this->subtitleLabel->Name = L"subtitleLabel";
			this->subtitleLabel->Size = System::Drawing::Size(343, 28);
			this->subtitleLabel->TabIndex = 1;
			this->subtitleLabel->Text = L"Advanced Pattern Recognition System";
			// 
			// titleLabel
			// 
			this->titleLabel->AutoSize = true;
			this->titleLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->titleLabel->ForeColor = System::Drawing::Color::White;
			this->titleLabel->Location = System::Drawing::Point(25, 15);
			this->titleLabel->Name = L"titleLabel";
			this->titleLabel->Size = System::Drawing::Size(246, 54);
			this->titleLabel->TabIndex = 0;
			this->titleLabel->Text = L"GenoSearch";
			// 
			// mainContainer
			// 
			this->mainContainer->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(236)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
				static_cast<System::Int32>(static_cast<System::Byte>(245)));
			this->mainContainer->Controls->Add(this->rightPanel);
			this->mainContainer->Controls->Add(this->leftPanel);
			this->mainContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->mainContainer->Location = System::Drawing::Point(0, 100);
			this->mainContainer->Name = L"mainContainer";
			this->mainContainer->Padding = System::Windows::Forms::Padding(20);
			this->mainContainer->Size = System::Drawing::Size(1400, 750);
			this->mainContainer->TabIndex = 1;
			// 
			// rightPanel
			// 
			this->rightPanel->Controls->Add(this->outputTabControl);
			this->rightPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->rightPanel->Location = System::Drawing::Point(620, 20);
			this->rightPanel->Name = L"rightPanel";
			this->rightPanel->Padding = System::Windows::Forms::Padding(10, 0, 0, 0);
			this->rightPanel->Size = System::Drawing::Size(760, 710);
			this->rightPanel->TabIndex = 1;
			// 
			// outputTabControl
			// 
			this->outputTabControl->Controls->Add(this->tabPage1);
			this->outputTabControl->Controls->Add(this->tabPage2);
			this->outputTabControl->Dock = System::Windows::Forms::DockStyle::Fill;
			this->outputTabControl->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->outputTabControl->ItemSize = System::Drawing::Size(120, 40);
			this->outputTabControl->Location = System::Drawing::Point(10, 0);
			this->outputTabControl->Name = L"outputTabControl";
			this->outputTabControl->SelectedIndex = 0;
			this->outputTabControl->Size = System::Drawing::Size(750, 710);
			this->outputTabControl->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->AutoScroll = true;
			this->tabPage1->BackColor = System::Drawing::Color::White;
			this->tabPage1->Controls->Add(this->errorGroup);
			this->tabPage1->Controls->Add(this->normalOutputGroup);
			this->tabPage1->Location = System::Drawing::Point(4, 44);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(15);
			this->tabPage1->Size = System::Drawing::Size(742, 662);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Results";
			// 
			// errorGroup
			// 
			this->errorGroup->Controls->Add(this->errorBox);
			this->errorGroup->Controls->Add(this->errorLabel);
			this->errorGroup->Dock = System::Windows::Forms::DockStyle::Fill;
			this->errorGroup->Location = System::Drawing::Point(15, 15);
			this->errorGroup->Name = L"errorGroup";
			this->errorGroup->Padding = System::Windows::Forms::Padding(15);
			this->errorGroup->Size = System::Drawing::Size(712, 632);
			this->errorGroup->TabIndex = 0;
			this->errorGroup->TabStop = false;
			// 
			// errorBox
			// 
			this->errorBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(245)),
				static_cast<System::Int32>(static_cast<System::Byte>(245)));
			this->errorBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->errorBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->errorBox->Font = (gcnew System::Drawing::Font(L"Consolas", 10));
			this->errorBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(50)));
			this->errorBox->Location = System::Drawing::Point(15, 94);
			this->errorBox->Multiline = true;
			this->errorBox->Name = L"errorBox";
			this->errorBox->ReadOnly = true;
			this->errorBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->errorBox->Size = System::Drawing::Size(682, 523);
			this->errorBox->TabIndex = 1;
			// 
			// errorLabel
			// 
			this->errorLabel->AutoSize = true;
			this->errorLabel->Dock = System::Windows::Forms::DockStyle::Top;
			this->errorLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
			this->errorLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(220)), static_cast<System::Int32>(static_cast<System::Byte>(53)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->errorLabel->Location = System::Drawing::Point(15, 42);
			this->errorLabel->Name = L"errorLabel";
			this->errorLabel->Padding = System::Windows::Forms::Padding(0, 0, 0, 20);
			this->errorLabel->Size = System::Drawing::Size(243, 52);
			this->errorLabel->TabIndex = 0;
			this->errorLabel->Text = L"⚠ Simulation Error";
			// 
			// normalOutputGroup
			// 
			this->normalOutputGroup->Controls->Add(this->matchReportGroup);
			this->normalOutputGroup->Controls->Add(this->grammarGroup);
			this->normalOutputGroup->Controls->Add(this->summaryGroup);
			this->normalOutputGroup->Controls->Add(this->exportButton);
			this->normalOutputGroup->Controls->Add(this->resultsLabel);
			this->normalOutputGroup->Dock = System::Windows::Forms::DockStyle::Fill;
			this->normalOutputGroup->Location = System::Drawing::Point(15, 15);
			this->normalOutputGroup->Name = L"normalOutputGroup";
			this->normalOutputGroup->Padding = System::Windows::Forms::Padding(15);
			this->normalOutputGroup->Size = System::Drawing::Size(712, 632);
			this->normalOutputGroup->TabIndex = 1;
			this->normalOutputGroup->TabStop = false;
			// 
			// matchReportGroup
			// 
			this->matchReportGroup->Controls->Add(this->resultsBox);
			this->matchReportGroup->Dock = System::Windows::Forms::DockStyle::Top;
			this->matchReportGroup->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->matchReportGroup->Location = System::Drawing::Point(15, 520);
			this->matchReportGroup->Name = L"matchReportGroup";
			this->matchReportGroup->Padding = System::Windows::Forms::Padding(10);
			this->matchReportGroup->Size = System::Drawing::Size(682, 160);
			this->matchReportGroup->TabIndex = 4;
			this->matchReportGroup->TabStop = false;
			this->matchReportGroup->Text = L"📊 Match Report";
			// 
			// resultsBox
			// 
			this->resultsBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(250)), static_cast<System::Int32>(static_cast<System::Byte>(252)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->resultsBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->resultsBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->resultsBox->Font = (gcnew System::Drawing::Font(L"Consolas", 9));
			this->resultsBox->Location = System::Drawing::Point(10, 37);
			this->resultsBox->Multiline = true;
			this->resultsBox->Name = L"resultsBox";
			this->resultsBox->ReadOnly = true;
			this->resultsBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->resultsBox->Size = System::Drawing::Size(662, 113);
			this->resultsBox->TabIndex = 0;
			// 
			// grammarGroup
			// 
			this->grammarGroup->Controls->Add(this->grammarBox);
			this->grammarGroup->Dock = System::Windows::Forms::DockStyle::Top;
			this->grammarGroup->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->grammarGroup->Location = System::Drawing::Point(15, 360);
			this->grammarGroup->Name = L"grammarGroup";
			this->grammarGroup->Padding = System::Windows::Forms::Padding(10);
			this->grammarGroup->Size = System::Drawing::Size(682, 160);
			this->grammarGroup->TabIndex = 3;
			this->grammarGroup->TabStop = false;
			this->grammarGroup->Text = L"📝 Generated Grammar";
			// 
			// grammarBox
			// 
			this->grammarBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(250)), static_cast<System::Int32>(static_cast<System::Byte>(252)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->grammarBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->grammarBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->grammarBox->Font = (gcnew System::Drawing::Font(L"Consolas", 9));
			this->grammarBox->Location = System::Drawing::Point(10, 37);
			this->grammarBox->Multiline = true;
			this->grammarBox->Name = L"grammarBox";
			this->grammarBox->ReadOnly = true;
			this->grammarBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->grammarBox->Size = System::Drawing::Size(662, 113);
			this->grammarBox->TabIndex = 0;
			// 
			// summaryGroup
			// 
			this->summaryGroup->Controls->Add(this->summaryBox);
			this->summaryGroup->Dock = System::Windows::Forms::DockStyle::Top;
			this->summaryGroup->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->summaryGroup->Location = System::Drawing::Point(15, 150);
			this->summaryGroup->Name = L"summaryGroup";
			this->summaryGroup->Padding = System::Windows::Forms::Padding(10);
			this->summaryGroup->Size = System::Drawing::Size(682, 210);
			this->summaryGroup->TabIndex = 2;
			this->summaryGroup->TabStop = false;
			this->summaryGroup->Text = L"✨ Simulation Summary";
			// 
			// summaryBox
			// 
			this->summaryBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(250)), static_cast<System::Int32>(static_cast<System::Byte>(252)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->summaryBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->summaryBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->summaryBox->Font = (gcnew System::Drawing::Font(L"Consolas", 9));
			this->summaryBox->Location = System::Drawing::Point(10, 37);
			this->summaryBox->Multiline = true;
			this->summaryBox->Name = L"summaryBox";
			this->summaryBox->ReadOnly = true;
			this->summaryBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->summaryBox->Size = System::Drawing::Size(662, 163);
			this->summaryBox->TabIndex = 0;
			// 
			// exportButton
			// 
			this->exportButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(76)), static_cast<System::Int32>(static_cast<System::Byte>(175)),
				static_cast<System::Int32>(static_cast<System::Byte>(80)));
			this->exportButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->exportButton->Dock = System::Windows::Forms::DockStyle::Top;
			this->exportButton->FlatAppearance->BorderSize = 0;
			this->exportButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->exportButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->exportButton->ForeColor = System::Drawing::Color::White;
			this->exportButton->Location = System::Drawing::Point(15, 100);
			this->exportButton->Name = L"exportButton";
			this->exportButton->Size = System::Drawing::Size(682, 50);
			this->exportButton->TabIndex = 1;
			this->exportButton->Text = L"📥 Export Full Report (.txt)";
			this->exportButton->UseVisualStyleBackColor = false;
			this->exportButton->Click += gcnew System::EventHandler(this, &MyForm::exportButton_Click);
			this->exportButton->MouseEnter += gcnew System::EventHandler(this, &MyForm::Button_MouseEnter);
			this->exportButton->MouseLeave += gcnew System::EventHandler(this, &MyForm::Button_MouseLeave);
			// 
			// resultsLabel
			// 
			this->resultsLabel->AutoSize = true;
			this->resultsLabel->Dock = System::Windows::Forms::DockStyle::Top;
			this->resultsLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
			this->resultsLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(71)));
			this->resultsLabel->Location = System::Drawing::Point(15, 42);
			this->resultsLabel->Name = L"resultsLabel";
			this->resultsLabel->Padding = System::Windows::Forms::Padding(0, 0, 0, 20);
			this->resultsLabel->Size = System::Drawing::Size(109, 58);
			this->resultsLabel->TabIndex = 0;
			this->resultsLabel->Text = L"Results";
			// 
			// tabPage2
			// 
			this->tabPage2->BackColor = System::Drawing::Color::White;
			this->tabPage2->Controls->Add(this->pdaTraceBox);
			this->tabPage2->Controls->Add(this->vizPictureBox);
			this->tabPage2->Controls->Add(this->vizToggleGroup);
			this->tabPage2->Controls->Add(this->vizLabel);
			this->tabPage2->Location = System::Drawing::Point(4, 44);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(15);
			this->tabPage2->Size = System::Drawing::Size(742, 662);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Visualization";
			// 
			// pdaTraceBox
			// 
			this->pdaTraceBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(250)), static_cast<System::Int32>(static_cast<System::Byte>(252)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->pdaTraceBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pdaTraceBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pdaTraceBox->Font = (gcnew System::Drawing::Font(L"Consolas", 9));
			this->pdaTraceBox->Location = System::Drawing::Point(15, 133);
			this->pdaTraceBox->Multiline = true;
			this->pdaTraceBox->Name = L"pdaTraceBox";
			this->pdaTraceBox->ReadOnly = true;
			this->pdaTraceBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->pdaTraceBox->Size = System::Drawing::Size(712, 514);
			this->pdaTraceBox->TabIndex = 3;
			// 
			// vizPictureBox
			// 
			this->vizPictureBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(250)), static_cast<System::Int32>(static_cast<System::Byte>(252)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->vizPictureBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->vizPictureBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->vizPictureBox->Location = System::Drawing::Point(15, 133);
			this->vizPictureBox->Name = L"vizPictureBox";
			this->vizPictureBox->Size = System::Drawing::Size(712, 514);
			this->vizPictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->vizPictureBox->TabIndex = 2;
			this->vizPictureBox->TabStop = false;
			// 
			// vizToggleGroup
			// 
			this->vizToggleGroup->Controls->Add(this->showDfaButton);
			this->vizToggleGroup->Controls->Add(this->showNfaButton);
			this->vizToggleGroup->Dock = System::Windows::Forms::DockStyle::Top;
			this->vizToggleGroup->Location = System::Drawing::Point(15, 73);
			this->vizToggleGroup->Name = L"vizToggleGroup";
			this->vizToggleGroup->Padding = System::Windows::Forms::Padding(0, 10, 0, 10);
			this->vizToggleGroup->Size = System::Drawing::Size(712, 60);
			this->vizToggleGroup->TabIndex = 1;
			// 
			// showDfaButton
			// 
			this->showDfaButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(220)), static_cast<System::Int32>(static_cast<System::Byte>(225)),
				static_cast<System::Int32>(static_cast<System::Byte>(235)));
			this->showDfaButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->showDfaButton->Dock = System::Windows::Forms::DockStyle::Left;
			this->showDfaButton->FlatAppearance->BorderSize = 0;
			this->showDfaButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->showDfaButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->showDfaButton->Location = System::Drawing::Point(180, 10);
			this->showDfaButton->Name = L"showDfaButton";
			this->showDfaButton->Size = System::Drawing::Size(180, 40);
			this->showDfaButton->TabIndex = 1;
			this->showDfaButton->Text = L"Show DFA";
			this->showDfaButton->UseVisualStyleBackColor = false;
			this->showDfaButton->Click += gcnew System::EventHandler(this, &MyForm::showDfaButton_Click);
			this->showDfaButton->MouseEnter += gcnew System::EventHandler(this, &MyForm::Button_MouseEnter);
			this->showDfaButton->MouseLeave += gcnew System::EventHandler(this, &MyForm::Button_MouseLeave);
			// 
			// showNfaButton
			// 
			this->showNfaButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(63)), static_cast<System::Int32>(static_cast<System::Byte>(81)),
				static_cast<System::Int32>(static_cast<System::Byte>(181)));
			this->showNfaButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->showNfaButton->Dock = System::Windows::Forms::DockStyle::Left;
			this->showNfaButton->FlatAppearance->BorderSize = 0;
			this->showNfaButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->showNfaButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->showNfaButton->ForeColor = System::Drawing::Color::White;
			this->showNfaButton->Location = System::Drawing::Point(0, 10);
			this->showNfaButton->Name = L"showNfaButton";
			this->showNfaButton->Size = System::Drawing::Size(180, 40);
			this->showNfaButton->TabIndex = 0;
			this->showNfaButton->Text = L"Show NFA";
			this->showNfaButton->UseVisualStyleBackColor = false;
			this->showNfaButton->Click += gcnew System::EventHandler(this, &MyForm::showNfaButton_Click);
			this->showNfaButton->MouseEnter += gcnew System::EventHandler(this, &MyForm::Button_MouseEnter);
			this->showNfaButton->MouseLeave += gcnew System::EventHandler(this, &MyForm::Button_MouseLeave);
			// 
			// vizLabel
			// 
			this->vizLabel->AutoSize = true;
			this->vizLabel->Dock = System::Windows::Forms::DockStyle::Top;
			this->vizLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
			this->vizLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(71)));
			this->vizLabel->Location = System::Drawing::Point(15, 15);
			this->vizLabel->Name = L"vizLabel";
			this->vizLabel->Padding = System::Windows::Forms::Padding(0, 0, 0, 20);
			this->vizLabel->Size = System::Drawing::Size(381, 58);
			this->vizLabel->TabIndex = 0;
			this->vizLabel->Text = L"🎨 Visualization (NFA/DFA)";
			this->vizLabel->Click += gcnew System::EventHandler(this, &MyForm::vizLabel_Click);
			// 
			// leftPanel
			// 
			this->leftPanel->BackColor = System::Drawing::Color::White;
			this->leftPanel->Controls->Add(this->progressBar);
			this->leftPanel->Controls->Add(this->groupBox2);
			this->leftPanel->Controls->Add(this->groupBox1);
			this->leftPanel->Dock = System::Windows::Forms::DockStyle::Left;
			this->leftPanel->Location = System::Drawing::Point(20, 20);
			this->leftPanel->Name = L"leftPanel";
			this->leftPanel->Padding = System::Windows::Forms::Padding(15);
			this->leftPanel->Size = System::Drawing::Size(600, 710);
			this->leftPanel->TabIndex = 0;
			// 
			// progressBar
			// 
			this->progressBar->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->progressBar->Location = System::Drawing::Point(15, 685);
			this->progressBar->MarqueeAnimationSpeed = 30;
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(570, 10);
			this->progressBar->Style = System::Windows::Forms::ProgressBarStyle::Marquee;
			this->progressBar->TabIndex = 2;
			this->progressBar->Visible = false;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->showErrorButton);
			this->groupBox2->Controls->Add(this->step2Label);
			this->groupBox2->Controls->Add(this->runButton);
			this->groupBox2->Controls->Add(this->fileInputGroup);
			this->groupBox2->Controls->Add(this->pdaInputTypeGroup);
			this->groupBox2->Controls->Add(this->editDistanceGroup);
			this->groupBox2->Controls->Add(this->patternInputGroup);
			this->groupBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->groupBox2->Location = System::Drawing::Point(15, 135);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Padding = System::Windows::Forms::Padding(15);
			this->groupBox2->Size = System::Drawing::Size(570, 560);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			// 
			// showErrorButton
			// 
			this->showErrorButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->showErrorButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(152)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->showErrorButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->showErrorButton->FlatAppearance->BorderSize = 0;
			this->showErrorButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->showErrorButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->showErrorButton->ForeColor = System::Drawing::Color::White;
			this->showErrorButton->Location = System::Drawing::Point(385, 510);
			this->showErrorButton->Name = L"showErrorButton";
			this->showErrorButton->Size = System::Drawing::Size(170, 35);
			this->showErrorButton->TabIndex = 6;
			this->showErrorButton->Text = L"⚠ Show Error Demo";
			this->showErrorButton->UseVisualStyleBackColor = false;
			this->showErrorButton->Click += gcnew System::EventHandler(this, &MyForm::showErrorButton_Click);
			this->showErrorButton->MouseEnter += gcnew System::EventHandler(this, &MyForm::Button_MouseEnter);
			this->showErrorButton->MouseLeave += gcnew System::EventHandler(this, &MyForm::Button_MouseLeave);
			// 
			// step2Label
			// 
			this->step2Label->AutoSize = true;
			this->step2Label->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
			this->step2Label->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(71)));
			this->step2Label->Location = System::Drawing::Point(15, 15);
			this->step2Label->Name = L"step2Label";
			this->step2Label->Size = System::Drawing::Size(292, 32);
			this->step2Label->TabIndex = 5;
			this->step2Label->Text = L"Step 2: Configure Inputs";
			// 
			// runButton
			// 
			this->runButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->runButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(33)), static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(243)));
			this->runButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->runButton->FlatAppearance->BorderSize = 0;
			this->runButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->runButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
			this->runButton->ForeColor = System::Drawing::Color::White;
			this->runButton->Location = System::Drawing::Point(20, 450);
			this->runButton->Name = L"runButton";
			this->runButton->Size = System::Drawing::Size(530, 50);
			this->runButton->TabIndex = 4;
			this->runButton->Text = L"▶ Run Simulation";
			this->runButton->UseVisualStyleBackColor = false;
			this->runButton->Click += gcnew System::EventHandler(this, &MyForm::runButton_Click);
			this->runButton->MouseEnter += gcnew System::EventHandler(this, &MyForm::Button_MouseEnter);
			this->runButton->MouseLeave += gcnew System::EventHandler(this, &MyForm::Button_MouseLeave);
			// 
			// fileInputGroup
			// 
			this->fileInputGroup->Controls->Add(this->supportLabel);
			this->fileInputGroup->Controls->Add(this->browseButton);
			this->fileInputGroup->Controls->Add(this->fileInputBox);
			this->fileInputGroup->Controls->Add(this->fileInputLabel);
			this->fileInputGroup->Dock = System::Windows::Forms::DockStyle::Top;
			this->fileInputGroup->Location = System::Drawing::Point(15, 289);
			this->fileInputGroup->Name = L"fileInputGroup";
			this->fileInputGroup->Padding = System::Windows::Forms::Padding(10);
			this->fileInputGroup->Size = System::Drawing::Size(540, 120);
			this->fileInputGroup->TabIndex = 3;
			this->fileInputGroup->TabStop = false;
			// 
			// supportLabel
			// 
			this->supportLabel->AutoSize = true;
			this->supportLabel->Dock = System::Windows::Forms::DockStyle::Top;
			this->supportLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8));
			this->supportLabel->ForeColor = System::Drawing::Color::Gray;
			this->supportLabel->Location = System::Drawing::Point(10, 96);
			this->supportLabel->Name = L"supportLabel";
			this->supportLabel->Size = System::Drawing::Size(198, 21);
			this->supportLabel->TabIndex = 3;
			this->supportLabel->Text = L"Supports: .txt, .fa, .fasta files";
			// 
			// browseButton
			// 
			this->browseButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->browseButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(96)), static_cast<System::Int32>(static_cast<System::Byte>(125)),
				static_cast<System::Int32>(static_cast<System::Byte>(139)));
			this->browseButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->browseButton->FlatAppearance->BorderSize = 0;
			this->browseButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->browseButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->browseButton->ForeColor = System::Drawing::Color::White;
			this->browseButton->Location = System::Drawing::Point(430, 46);
			this->browseButton->Name = L"browseButton";
			this->browseButton->Size = System::Drawing::Size(100, 35);
			this->browseButton->TabIndex = 2;
			this->browseButton->Text = L"📁 Browse";
			this->browseButton->UseVisualStyleBackColor = false;
			this->browseButton->Click += gcnew System::EventHandler(this, &MyForm::browseButton_Click);
			this->browseButton->MouseEnter += gcnew System::EventHandler(this, &MyForm::Button_MouseEnter);
			this->browseButton->MouseLeave += gcnew System::EventHandler(this, &MyForm::Button_MouseLeave);
			// 
			// fileInputBox
			// 
			this->fileInputBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(250)), static_cast<System::Int32>(static_cast<System::Byte>(252)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->fileInputBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->fileInputBox->Dock = System::Windows::Forms::DockStyle::Top;
			this->fileInputBox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->fileInputBox->Location = System::Drawing::Point(10, 62);
			this->fileInputBox->Name = L"fileInputBox";
			this->fileInputBox->ReadOnly = true;
			this->fileInputBox->Size = System::Drawing::Size(520, 34);
			this->fileInputBox->TabIndex = 1;
			// 
			// fileInputLabel
			// 
			this->fileInputLabel->AutoSize = true;
			this->fileInputLabel->Dock = System::Windows::Forms::DockStyle::Top;
			this->fileInputLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->fileInputLabel->Location = System::Drawing::Point(10, 34);
			this->fileInputLabel->Name = L"fileInputLabel";
			this->fileInputLabel->Size = System::Drawing::Size(101, 28);
			this->fileInputLabel->TabIndex = 0;
			this->fileInputLabel->Text = L"Input File";
			// 
			// pdaInputTypeGroup
			// 
			this->pdaInputTypeGroup->Controls->Add(this->sourceInputLabel);
			this->pdaInputTypeGroup->Controls->Add(this->pdaFileRadio);
			this->pdaInputTypeGroup->Controls->Add(this->pdaStringRadio);
			this->pdaInputTypeGroup->Dock = System::Windows::Forms::DockStyle::Top;
			this->pdaInputTypeGroup->Location = System::Drawing::Point(15, 209);
			this->pdaInputTypeGroup->Name = L"pdaInputTypeGroup";
			this->pdaInputTypeGroup->Padding = System::Windows::Forms::Padding(10);
			this->pdaInputTypeGroup->Size = System::Drawing::Size(540, 80);
			this->pdaInputTypeGroup->TabIndex = 2;
			this->pdaInputTypeGroup->TabStop = false;
			// 
			// sourceInputLabel
			// 
			this->sourceInputLabel->AutoSize = true;
			this->sourceInputLabel->Dock = System::Windows::Forms::DockStyle::Top;
			this->sourceInputLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->sourceInputLabel->Location = System::Drawing::Point(10, 34);
			this->sourceInputLabel->Name = L"sourceInputLabel";
			this->sourceInputLabel->Size = System::Drawing::Size(137, 28);
			this->sourceInputLabel->TabIndex = 2;
			this->sourceInputLabel->Text = L"Input Source:";
			// 
			// pdaFileRadio
			// 
			this->pdaFileRadio->AutoSize = true;
			this->pdaFileRadio->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pdaFileRadio->Location = System::Drawing::Point(280, 35);
			this->pdaFileRadio->Name = L"pdaFileRadio";
			this->pdaFileRadio->Size = System::Drawing::Size(130, 29);
			this->pdaFileRadio->TabIndex = 1;
			this->pdaFileRadio->Text = L"Validate File";
			this->pdaFileRadio->UseVisualStyleBackColor = true;
			this->pdaFileRadio->CheckedChanged += gcnew System::EventHandler(this, &MyForm::pdaInputType_CheckedChanged);
			// 
			// pdaStringRadio
			// 
			this->pdaStringRadio->AutoSize = true;
			this->pdaStringRadio->Checked = true;
			this->pdaStringRadio->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pdaStringRadio->Location = System::Drawing::Point(120, 35);
			this->pdaStringRadio->Name = L"pdaStringRadio";
			this->pdaStringRadio->Size = System::Drawing::Size(150, 29);
			this->pdaStringRadio->TabIndex = 0;
			this->pdaStringRadio->TabStop = true;
			this->pdaStringRadio->Text = L"Validate String";
			this->pdaStringRadio->UseVisualStyleBackColor = true;
			this->pdaStringRadio->CheckedChanged += gcnew System::EventHandler(this, &MyForm::pdaInputType_CheckedChanged);
			// 
			// editDistanceGroup
			// 
			this->editDistanceGroup->Controls->Add(this->editDistanceInput);
			this->editDistanceGroup->Controls->Add(this->distanceLabel);
			this->editDistanceGroup->Dock = System::Windows::Forms::DockStyle::Top;
			this->editDistanceGroup->Location = System::Drawing::Point(15, 139);
			this->editDistanceGroup->Name = L"editDistanceGroup";
			this->editDistanceGroup->Padding = System::Windows::Forms::Padding(10);
			this->editDistanceGroup->Size = System::Drawing::Size(540, 70);
			this->editDistanceGroup->TabIndex = 1;
			this->editDistanceGroup->TabStop = false;
			// 
			// editDistanceInput
			// 
			this->editDistanceInput->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(250)),
				static_cast<System::Int32>(static_cast<System::Byte>(252)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->editDistanceInput->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->editDistanceInput->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11));
			this->editDistanceInput->Location = System::Drawing::Point(220, 25);
			this->editDistanceInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->editDistanceInput->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->editDistanceInput->Name = L"editDistanceInput";
			this->editDistanceInput->Size = System::Drawing::Size(80, 37);
			this->editDistanceInput->TabIndex = 1;
			this->editDistanceInput->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// distanceLabel
			// 
			this->distanceLabel->AutoSize = true;
			this->distanceLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->distanceLabel->Location = System::Drawing::Point(15, 30);
			this->distanceLabel->Name = L"distanceLabel";
			this->distanceLabel->Size = System::Drawing::Size(173, 28);
			this->distanceLabel->TabIndex = 0;
			this->distanceLabel->Text = L"Edit Distance (k):";
			// 
			// patternInputGroup
			// 
			this->patternInputGroup->Controls->Add(this->patternLabel);
			this->patternInputGroup->Controls->Add(this->patternInputBox);
			this->patternInputGroup->Dock = System::Windows::Forms::DockStyle::Top;
			this->patternInputGroup->Location = System::Drawing::Point(15, 39);
			this->patternInputGroup->Name = L"patternInputGroup";
			this->patternInputGroup->Padding = System::Windows::Forms::Padding(10);
			this->patternInputGroup->Size = System::Drawing::Size(540, 100);
			this->patternInputGroup->TabIndex = 0;
			this->patternInputGroup->TabStop = false;
			// 
			// patternLabel
			// 
			this->patternLabel->AutoSize = true;
			this->patternLabel->Dock = System::Windows::Forms::DockStyle::Top;
			this->patternLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->patternLabel->Location = System::Drawing::Point(10, 67);
			this->patternLabel->Name = L"patternLabel";
			this->patternLabel->Size = System::Drawing::Size(282, 28);
			this->patternLabel->TabIndex = 1;
			this->patternLabel->Text = L"Pattern (Regular Expression)";
			// 
			// patternInputBox
			// 
			this->patternInputBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(250)), static_cast<System::Int32>(static_cast<System::Byte>(252)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->patternInputBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->patternInputBox->Dock = System::Windows::Forms::DockStyle::Top;
			this->patternInputBox->Font = (gcnew System::Drawing::Font(L"Consolas", 11));
			this->patternInputBox->Location = System::Drawing::Point(10, 34);
			this->patternInputBox->Name = L"patternInputBox";
			this->patternInputBox->Size = System::Drawing::Size(520, 33);
			this->patternInputBox->TabIndex = 0;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->pdaRadio);
			this->groupBox1->Controls->Add(this->approxRadio);
			this->groupBox1->Controls->Add(this->regexRadio);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Top;
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->groupBox1->Location = System::Drawing::Point(15, 15);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(15);
			this->groupBox1->Size = System::Drawing::Size(570, 120);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
			this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(71)));
			this->label1->Location = System::Drawing::Point(15, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(356, 32);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Step 1: Select Simulation Type";
			// 
			// pdaRadio
			// 
			this->pdaRadio->AutoSize = true;
			this->pdaRadio->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pdaRadio->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->pdaRadio->Location = System::Drawing::Point(360, 65);
			this->pdaRadio->Name = L"pdaRadio";
			this->pdaRadio->Size = System::Drawing::Size(214, 32);
			this->pdaRadio->TabIndex = 2;
			this->pdaRadio->Text = L"Structural Validation";
			this->pdaRadio->UseVisualStyleBackColor = true;
			this->pdaRadio->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Radio_CheckedChanged);
			// 
			// approxRadio
			// 
			this->approxRadio->AutoSize = true;
			this->approxRadio->Cursor = System::Windows::Forms::Cursors::Hand;
			this->approxRadio->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->approxRadio->Location = System::Drawing::Point(185, 65);
			this->approxRadio->Name = L"approxRadio";
			this->approxRadio->Size = System::Drawing::Size(211, 32);
			this->approxRadio->TabIndex = 1;
			this->approxRadio->Text = L"Approximate Match";
			this->approxRadio->UseVisualStyleBackColor = true;
			this->approxRadio->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Radio_CheckedChanged);
			// 
			// regexRadio
			// 
			this->regexRadio->AutoSize = true;
			this->regexRadio->Checked = true;
			this->regexRadio->Cursor = System::Windows::Forms::Cursors::Hand;
			this->regexRadio->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->regexRadio->Location = System::Drawing::Point(20, 65);
			this->regexRadio->Name = L"regexRadio";
			this->regexRadio->Size = System::Drawing::Size(200, 32);
			this->regexRadio->TabIndex = 0;
			this->regexRadio->TabStop = true;
			this->regexRadio->Text = L"Regular Expression";
			this->regexRadio->UseVisualStyleBackColor = true;
			this->regexRadio->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Radio_CheckedChanged);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->Filter = L"Text Files (*.txt)|*.txt|FASTA Files (*.fa;*.fasta)|*.fa;*.fasta|All Files (*.*)|"
				L"*.*";
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->Filter = L"Text File (*.txt)|*.txt";
			// 
			// animationTimer
			// 
			this->animationTimer->Interval = 50;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(1400, 850);
			this->Controls->Add(this->mainContainer);
			this->Controls->Add(this->headerPanel);
			this->MinimumSize = System::Drawing::Size(1200, 800);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"GenoSearch | Automata-Powered Pattern Recognition";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->headerPanel->ResumeLayout(false);
			this->headerPanel->PerformLayout();
			this->mainContainer->ResumeLayout(false);
			this->rightPanel->ResumeLayout(false);
			this->outputTabControl->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->errorGroup->ResumeLayout(false);
			this->errorGroup->PerformLayout();
			this->normalOutputGroup->ResumeLayout(false);
			this->normalOutputGroup->PerformLayout();
			this->matchReportGroup->ResumeLayout(false);
			this->matchReportGroup->PerformLayout();
			this->grammarGroup->ResumeLayout(false);
			this->grammarGroup->PerformLayout();
			this->summaryGroup->ResumeLayout(false);
			this->summaryGroup->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->vizPictureBox))->EndInit();
			this->vizToggleGroup->ResumeLayout(false);
			this->leftPanel->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->fileInputGroup->ResumeLayout(false);
			this->fileInputGroup->PerformLayout();
			this->pdaInputTypeGroup->ResumeLayout(false);
			this->pdaInputTypeGroup->PerformLayout();
			this->editDistanceGroup->ResumeLayout(false);
			this->editDistanceGroup->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->editDistanceInput))->EndInit();
			this->patternInputGroup->ResumeLayout(false);
			this->patternInputGroup->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

		// Modern UI Initialization
		void InitializeModernUI() {
			// Set modern fonts
			this->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);

			// Add shadow effect to panels
			this->leftPanel->Paint += gcnew PaintEventHandler(this, &MyForm::Panel_Paint);
		}

		// Panel shadow painting
		void Panel_Paint(Object^ sender, PaintEventArgs^ e) {
			Panel^ panel = safe_cast<Panel^>(sender);

			// Create shadow effect
			System::Drawing::Drawing2D::GraphicsPath^ path = gcnew System::Drawing::Drawing2D::GraphicsPath();
			path->AddRectangle(panel->ClientRectangle);

			e->Graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
		}

		// Button hover effects
		void Button_MouseEnter(Object^ sender, EventArgs^ e) {
			Button^ btn = safe_cast<Button^>(sender);
			Color currentColor = btn->BackColor;

			// Brighten the button color
			int r = Math::Min(255, currentColor.R + 20);
			int g = Math::Min(255, currentColor.G + 20);
			int b = Math::Min(255, currentColor.B + 20);

			btn->BackColor = Color::FromArgb(r, g, b);
		}

		void Button_MouseLeave(Object^ sender, EventArgs^ e) {
			Button^ btn = safe_cast<Button^>(sender);

			// Restore original colors based on button
			if (btn == runButton) {
				btn->BackColor = Color::FromArgb(33, 150, 243);
			}
			else if (btn == exportButton) {
				btn->BackColor = Color::FromArgb(76, 175, 80);
			}
			else if (btn == browseButton) {
				btn->BackColor = Color::FromArgb(96, 125, 139);
			}
			else if (btn == showErrorButton) {
				btn->BackColor = Color::FromArgb(255, 152, 0);
			}
			else if (btn == showNfaButton) {
				if (showNfaButton->ForeColor == Color::White) {
					btn->BackColor = Color::FromArgb(63, 81, 181);
				}
				else {
					btn->BackColor = Color::FromArgb(220, 225, 235);
				}
			}
			else if (btn == showDfaButton) {
				if (showDfaButton->ForeColor == Color::White) {
					btn->BackColor = Color::FromArgb(63, 81, 181);
				}
				else {
					btn->BackColor = Color::FromArgb(220, 225, 235);
				}
			}
		}

		// Helper functions
		std::string ToStdString(System::String^ netString) {
			if (netString == nullptr) {
				return std::string();
			}
			return msclr::interop::marshal_as<std::string>(netString);
		}

		System::String^ ToNetString(const std::string& stdString) {
			return gcnew System::String(stdString.c_str());
		}

		void OpenFile(TextBox^ textBox) {
			this->openFileDialog1->Filter = "Text Files (*.txt)|*.txt|FASTA Files (*.fa;*.fasta)|*.fa;*.fasta|All Files (*.*)|*.*";
			this->openFileDialog1->Title = "Select an input file";
			if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				textBox->Text = this->openFileDialog1->FileName;
			}
		}

		void SaveFile(System::String^ content) {
			this->saveFileDialog1->Filter = "Text File (*.txt)|*.txt";
			this->saveFileDialog1->Title = "Save Report";
			if (this->saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				try {
					StreamWriter^ sw = gcnew StreamWriter(this->saveFileDialog1->FileName);
					sw->Write(content);
					sw->Close();
					MessageBox::Show("Report exported successfully!", "Success",
						MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				catch (Exception^ e) {
					MessageBox::Show(e->Message, "Error Saving File",
						MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
		}

		void UpdateUIMode() {
			std::string mode = "regex";
			if (this->approxRadio->Checked) {
				mode = "approx";
			}
			else if (this->pdaRadio->Checked) {
				mode = "pda";
			}

			if (mode == "regex") {
				this->patternInputGroup->Visible = true;
				this->editDistanceGroup->Visible = false;
				this->pdaInputTypeGroup->Visible = false;
				this->fileInputGroup->Visible = true;
				this->patternLabel->Text = "Pattern (Regular Expression)";
				this->fileInputLabel->Text = "Input File";
				this->patternInputBox->Text = "(a|b)*c";
			}
			else if (mode == "approx") {
				this->patternInputGroup->Visible = true;
				this->editDistanceGroup->Visible = true;
				this->pdaInputTypeGroup->Visible = false;
				this->fileInputGroup->Visible = true;
				this->patternLabel->Text = "Pattern (e.g., AGTC)";
				this->fileInputLabel->Text = "Input File";
				this->patternInputBox->Text = "AGTC";
			}
			else if (mode == "pda") {
				this->editDistanceGroup->Visible = false;
				this->pdaInputTypeGroup->Visible = true;
				UpdatePdaInput();
			}

			this->normalOutputGroup->Visible = true;
			this->errorGroup->Visible = false;
			this->resultsLabel->Text = "Results";
			this->vizLabel->Text = "Visualization";
			this->summaryBox->Text = "";
			this->grammarBox->Text = "";
			this->resultsBox->Text = "";
			this->vizPictureBox->Image = nullptr;
			this->pdaTraceBox->Text = "";
		}

		void UpdatePdaInput() {
			if (this->pdaStringRadio->Checked) {
				this->patternInputGroup->Visible = true;
				this->fileInputGroup->Visible = false;
				this->patternLabel->Text = "String to Validate (e.g., ((())) )";
				this->patternInputBox->Text = "((G)(CA))";
			}
			else {
				this->patternInputGroup->Visible = false;
				this->fileInputGroup->Visible = true;
				this->fileInputLabel->Text = "File to Validate (e.g., rna.xml)";
			}
		}

		void ShowError(std::string error_message) {
			this->normalOutputGroup->Visible = false;
			this->errorGroup->Visible = true;
			this->errorBox->Text = ToNetString(error_message);
			this->outputTabControl->SelectedTab = this->tabPage1;
		}

		void LoadImage(PictureBox^ pb, std::string image_path) {
			try {
				if (pb->Image != nullptr) {
					pb->Image = nullptr;
				}
				System::IO::MemoryStream^ ms = gcnew System::IO::MemoryStream(
					File::ReadAllBytes(ToNetString(image_path)));
				pb->Image = Image::FromStream(ms);
			}
			catch (Exception^ e) {
				ShowError("C++ Error: Could not load image file '" + image_path +
					"'.\n" + ToStdString(e->Message));
			}
		}

		// Event Handlers
	private:
		System::Void Radio_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			UpdateUIMode();
		}

		System::Void pdaInputType_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			UpdatePdaInput();
		}

		System::Void browseButton_Click(System::Object^ sender, System::EventArgs^ e) {
			OpenFile(this->fileInputBox);
		}

		System::Void runButton_Click(System::Object^ sender, System::EventArgs^ e) {
			this->Cursor = Cursors::WaitCursor;
			this->progressBar->Visible = true;

			std::string pattern = ToStdString(this->patternInputBox->Text);
			std::string filepath = ToStdString(this->fileInputBox->Text);
			int k = (int)this->editDistanceInput->Value;

			this->errorGroup->Visible = false;
			this->normalOutputGroup->Visible = true;
			this->resultsBox->Text = "";
			this->summaryBox->Text = "";
			this->grammarBox->Text = "";
			this->pdaTraceBox->Text = "";
			if (this->vizPictureBox->Image != nullptr) {
				this->vizPictureBox->Image = nullptr;
			}

			m_nfaDot = nullptr;
			m_dfaDot = nullptr;

			GenoSearchEngine::SimulationReport report;
			GenoSearchEngine::VisualizationData viz;
			std::string out_error_msg;

			if (this->regexRadio->Checked) {
				this->resultsLabel->Text = "🔍 Results (Regex)";
				this->vizLabel->Text = "🎨 Visualization (NFA/DFA)";
				this->matchReportGroup->Text = "📊 Match Report";
				this->matchReportGroup->Visible = true;

				runBranch1_logic(pattern, filepath, report, viz, out_error_msg);

				if (!out_error_msg.empty()) {
					ShowError(out_error_msg);
					this->Cursor = Cursors::Default;
					this->progressBar->Visible = false;
					return;
				}

				this->summaryGroup->Visible = true;
				this->grammarGroup->Visible = true;
				this->matchReportGroup->Visible = true;
				this->summaryBox->Text = ToNetString(report.summary);
				this->grammarBox->Text = ToNetString(report.grammar);
				this->resultsBox->Text = ToNetString(report.matches);

				m_nfaDot = ToNetString(viz.nfaDot);
				m_dfaDot = ToNetString(viz.dfaDot);

				this->vizPictureBox->Visible = true;
				this->pdaTraceBox->Visible = false;
				this->vizToggleGroup->Visible = true;

				showNfaButton_Click(sender, e);
			}
			else if (this->approxRadio->Checked) {
				this->resultsLabel->Text = "🔍 Results (Approximate)";
				this->vizLabel->Text = "🎨 Visualization (NFA)";
				this->matchReportGroup->Text = "📊 Match Report";
				this->matchReportGroup->Visible = true;

				runBranch2A_logic(pattern, k, filepath, report, viz, out_error_msg);

				if (!out_error_msg.empty()) {
					ShowError(out_error_msg);
					this->Cursor = Cursors::Default;
					this->progressBar->Visible = false;
					return;
				}

				this->summaryGroup->Visible = true;
				this->grammarGroup->Visible = true;
				this->matchReportGroup->Visible = true;
				this->summaryBox->Text = ToNetString(report.summary);
				this->grammarBox->Text = ToNetString(report.grammar);
				this->resultsBox->Text = ToNetString(report.matches);

				m_nfaDot = ToNetString(viz.nfaDot);
				m_dfaDot = nullptr;

				this->vizPictureBox->Visible = true;
				this->pdaTraceBox->Visible = false;
				this->vizToggleGroup->Visible = false;

				std::string error_msg, fallback_str;
				bool success = GenoSearchEngine::GenerateGraphvizImage(
					ToStdString(m_nfaDot), "approx_viz.png", error_msg, fallback_str);

				if (success) {
					LoadImage(this->vizPictureBox, "approx_viz.png");
				}
				else {
					ShowError(error_msg + "\n" + fallback_str);
				}
			}
			else if (this->pdaRadio->Checked) {
				this->resultsLabel->Text = "✅ Results (PDA)";
				this->vizLabel->Text = "🎨 Visualization (PDA Trace)";
				this->matchReportGroup->Text = "📋 Validation Report";
				this->matchReportGroup->Visible = true;

				std::string pda_input = "";
				bool isFile = this->pdaFileRadio->Checked;

				if (isFile) {
					pda_input = filepath;
				}
				else {
					pda_input = pattern;
				}

				runBranch2B_logic(pda_input, isFile, report, viz, out_error_msg);

				if (!out_error_msg.empty()) {
					ShowError(out_error_msg);
					this->Cursor = Cursors::Default;
					this->progressBar->Visible = false;
					return;
				}

				this->summaryGroup->Visible = false;
				this->grammarGroup->Visible = true;
				this->matchReportGroup->Visible = true;

				this->grammarBox->Text = ToNetString(report.grammar);
				this->resultsBox->Text = ToNetString(report.matches);

				this->vizPictureBox->Visible = false;
				this->pdaTraceBox->Visible = true;
				this->vizToggleGroup->Visible = false;

				this->pdaTraceBox->Text = ToNetString(viz.pdaTrace);
			}

			this->Cursor = Cursors::Default;
			this->progressBar->Visible = false;
		}

		System::Void exportButton_Click(System::Object^ sender, System::EventArgs^ e) {
			System::String^ fullReport = "";
			fullReport += "==============================================\n";
			fullReport += "  " + this->resultsLabel->Text + "\n";
			fullReport += "==============================================\n\n";

			if (this->summaryGroup->Visible) {
				fullReport += "--- SIMULATION SUMMARY ---\n";
				fullReport += this->summaryBox->Text + "\n\n";
			}
			if (this->grammarGroup->Visible) {
				fullReport += "--- GENERATED GRAMMAR ---\n";
				fullReport += this->grammarBox->Text + "\n\n";
			}
			if (this->matchReportGroup->Visible) {
				fullReport += "--- " + this->matchReportGroup->Text + " ---\n";
				fullReport += this->resultsBox->Text + "\n\n";
			}

			SaveFile(fullReport);
		}

		System::Void showNfaButton_Click(System::Object^ sender, System::EventArgs^ e) {
			this->showNfaButton->BackColor = Color::FromArgb(63, 81, 181);
			this->showNfaButton->ForeColor = Color::White;
			this->showDfaButton->BackColor = Color::FromArgb(220, 225, 235);
			this->showDfaButton->ForeColor = Color::Black;

			std::string error_msg, fallback_str;
			bool success = GenoSearchEngine::GenerateGraphvizImage(
				ToStdString(m_nfaDot), "nfa_viz.png", error_msg, fallback_str);
			if (success) {
				LoadImage(this->vizPictureBox, "nfa_viz.png");
			}
			else {
				ShowError(error_msg + "\n" + fallback_str);
			}
		}

		System::Void showDfaButton_Click(System::Object^ sender, System::EventArgs^ e) {
			this->showNfaButton->BackColor = Color::FromArgb(220, 225, 235);
			this->showNfaButton->ForeColor = Color::Black;
			this->showDfaButton->BackColor = Color::FromArgb(63, 81, 181);
			this->showDfaButton->ForeColor = Color::White;

			std::string error_msg, fallback_str;
			bool success = GenoSearchEngine::GenerateGraphvizImage(
				ToStdString(m_dfaDot), "dfa_viz.png", error_msg, fallback_str);
			if (success) {
				LoadImage(this->vizPictureBox, "dfa_viz.png");
			}
			else {
				ShowError(error_msg + "\n" + fallback_str);
			}
		}

		System::Void showErrorButton_Click(System::Object^ sender, System::EventArgs^ e) {
			ShowError("--- THIS IS A DEMO ERROR ---\n"
				"Error: Graphviz 'dot' command not found.\n"
				"Please install Graphviz from graphviz.org\n"
				"and ensure it is in your system's PATH.\n\n"
				"--- FALLBACK VISUALIZATION ---\n"
				"(q0) --'a'--> (q1)\n"
				"(q1) --'b'--> (q1)\n"
				"(q1) --'c'--> (q2)\n");
		}

		System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
			UpdateUIMode();
		}
	private: System::Void vizLabel_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}