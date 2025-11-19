/*
 * MyForm.h - Modern UI Design with "GenoSearch" Green Theme
 *
 * MODIFICATION:
 * - Fixed E0153 error by correctly declaring all controls.
 * - Implemented the user's new 2-column layout for the "Results" tab
 *.
 * - Added a new `resultsTableLayout` (2 columns, 2 rows).
 * - Col 0, Row 0: summaryGroup
 * - Col 0, Row 1: grammarGroup
 * - Col 1, Row 0: matchReportGroup (with RowSpan = 2)
 * - This layout is fully responsive and makes better use of wide screens.
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





		   // *** MODIFICATION: Added TableLayoutPanel for 2-column results ***
	private: System::Windows::Forms::TableLayoutPanel^ resultsTableLayout;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::Button^ resetButton;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Label^ sim3Label;
	private: System::Windows::Forms::Label^ sim2Label;
	private: System::Windows::Forms::Label^ sim1Label;
	private: System::Windows::Forms::RadioButton^ pdaRadio;
	private: System::Windows::Forms::RadioButton^ approxRadio;
	private: System::Windows::Forms::RadioButton^ regexRadio;
	private: System::Windows::Forms::Button^ showErrorButton;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ step2Label;
	private: System::Windows::Forms::Button^ runButton;
	private: System::Windows::Forms::GroupBox^ fileInputGroup;
	private: System::Windows::Forms::Label^ supportLabel;
	private: System::Windows::Forms::Button^ browseButton;
	private: System::Windows::Forms::TextBox^ fileInputBox;
	private: System::Windows::Forms::Label^ fileInputLabel;
	private: System::Windows::Forms::GroupBox^ pdaInputTypeGroup;
	private: System::Windows::Forms::Label^ sourceInputLabel;
	private: System::Windows::Forms::RadioButton^ pdaFileRadio;
	private: System::Windows::Forms::RadioButton^ pdaStringRadio;
	private: System::Windows::Forms::GroupBox^ editDistanceGroup;
	private: System::Windows::Forms::NumericUpDown^ editDistanceInput;
	private: System::Windows::Forms::Label^ distanceLabel;
	private: System::Windows::Forms::GroupBox^ patternInputGroup;
	private: System::Windows::Forms::Label^ patternLabel;
	private: System::Windows::Forms::TextBox^ patternInputBox;


	private: System::ComponentModel::IContainer^ components;

	private:


#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->headerPanel = (gcnew System::Windows::Forms::Panel());
			this->exportButton = (gcnew System::Windows::Forms::Button());
			this->subtitleLabel = (gcnew System::Windows::Forms::Label());
			this->titleLabel = (gcnew System::Windows::Forms::Label());
			this->mainContainer = (gcnew System::Windows::Forms::Panel());
			this->rightPanel = (gcnew System::Windows::Forms::Panel());
			this->outputTabControl = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->normalOutputGroup = (gcnew System::Windows::Forms::GroupBox());
			this->resultsTableLayout = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->summaryGroup = (gcnew System::Windows::Forms::GroupBox());
			this->summaryBox = (gcnew System::Windows::Forms::TextBox());
			this->grammarGroup = (gcnew System::Windows::Forms::GroupBox());
			this->grammarBox = (gcnew System::Windows::Forms::TextBox());
			this->matchReportGroup = (gcnew System::Windows::Forms::GroupBox());
			this->resultsBox = (gcnew System::Windows::Forms::TextBox());
			this->resultsLabel = (gcnew System::Windows::Forms::Label());
			this->errorGroup = (gcnew System::Windows::Forms::GroupBox());
			this->errorBox = (gcnew System::Windows::Forms::TextBox());
			this->errorLabel = (gcnew System::Windows::Forms::Label());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->pdaTraceBox = (gcnew System::Windows::Forms::TextBox());
			this->vizPictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->vizToggleGroup = (gcnew System::Windows::Forms::Panel());
			this->showDfaButton = (gcnew System::Windows::Forms::Button());
			this->showNfaButton = (gcnew System::Windows::Forms::Button());
			this->vizLabel = (gcnew System::Windows::Forms::Label());
			this->leftPanel = (gcnew System::Windows::Forms::Panel());
			this->progressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->animationTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->patternInputGroup = (gcnew System::Windows::Forms::GroupBox());
			this->patternInputBox = (gcnew System::Windows::Forms::TextBox());
			this->patternLabel = (gcnew System::Windows::Forms::Label());
			this->editDistanceGroup = (gcnew System::Windows::Forms::GroupBox());
			this->distanceLabel = (gcnew System::Windows::Forms::Label());
			this->editDistanceInput = (gcnew System::Windows::Forms::NumericUpDown());
			this->pdaInputTypeGroup = (gcnew System::Windows::Forms::GroupBox());
			this->pdaStringRadio = (gcnew System::Windows::Forms::RadioButton());
			this->pdaFileRadio = (gcnew System::Windows::Forms::RadioButton());
			this->sourceInputLabel = (gcnew System::Windows::Forms::Label());
			this->fileInputGroup = (gcnew System::Windows::Forms::GroupBox());
			this->fileInputLabel = (gcnew System::Windows::Forms::Label());
			this->fileInputBox = (gcnew System::Windows::Forms::TextBox());
			this->browseButton = (gcnew System::Windows::Forms::Button());
			this->supportLabel = (gcnew System::Windows::Forms::Label());
			this->runButton = (gcnew System::Windows::Forms::Button());
			this->step2Label = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->showErrorButton = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->regexRadio = (gcnew System::Windows::Forms::RadioButton());
			this->approxRadio = (gcnew System::Windows::Forms::RadioButton());
			this->pdaRadio = (gcnew System::Windows::Forms::RadioButton());
			this->sim1Label = (gcnew System::Windows::Forms::Label());
			this->sim2Label = (gcnew System::Windows::Forms::Label());
			this->sim3Label = (gcnew System::Windows::Forms::Label());
			this->resetButton = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->headerPanel->SuspendLayout();
			this->mainContainer->SuspendLayout();
			this->rightPanel->SuspendLayout();
			this->outputTabControl->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->normalOutputGroup->SuspendLayout();
			this->resultsTableLayout->SuspendLayout();
			this->summaryGroup->SuspendLayout();
			this->grammarGroup->SuspendLayout();
			this->matchReportGroup->SuspendLayout();
			this->errorGroup->SuspendLayout();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->vizPictureBox))->BeginInit();
			this->vizToggleGroup->SuspendLayout();
			this->leftPanel->SuspendLayout();
			this->patternInputGroup->SuspendLayout();
			this->editDistanceGroup->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->editDistanceInput))->BeginInit();
			this->pdaInputTypeGroup->SuspendLayout();
			this->fileInputGroup->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// headerPanel
			// 
			this->headerPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(42)), static_cast<System::Int32>(static_cast<System::Byte>(157)),
				static_cast<System::Int32>(static_cast<System::Byte>(143)));
			this->headerPanel->Controls->Add(this->exportButton);
			this->headerPanel->Controls->Add(this->subtitleLabel);
			this->headerPanel->Controls->Add(this->titleLabel);
			this->headerPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->headerPanel->Location = System::Drawing::Point(0, 0);
			this->headerPanel->Name = L"headerPanel";
			this->headerPanel->Size = System::Drawing::Size(1716, 100);
			this->headerPanel->TabIndex = 0;
			// 
			// exportButton
			// 
			this->exportButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->exportButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(132)), static_cast<System::Int32>(static_cast<System::Byte>(169)),
				static_cast<System::Int32>(static_cast<System::Byte>(140)));
			this->exportButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->exportButton->FlatAppearance->BorderSize = 0;
			this->exportButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->exportButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->exportButton->ForeColor = System::Drawing::Color::White;
			this->exportButton->Location = System::Drawing::Point(1483, 45);
			this->exportButton->Name = L"exportButton";
			this->exportButton->Size = System::Drawing::Size(209, 41);
			this->exportButton->TabIndex = 1;
			this->exportButton->Text = L"Export Full Report";
			this->exportButton->UseVisualStyleBackColor = false;
			this->exportButton->Click += gcnew System::EventHandler(this, &MyForm::exportButton_Click);
			this->exportButton->MouseEnter += gcnew System::EventHandler(this, &MyForm::Button_MouseEnter);
			this->exportButton->MouseLeave += gcnew System::EventHandler(this, &MyForm::Button_MouseLeave);
			// 
			// subtitleLabel
			// 
			this->subtitleLabel->AutoSize = true;
			this->subtitleLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->subtitleLabel->ForeColor = System::Drawing::SystemColors::Control;
			this->subtitleLabel->Location = System::Drawing::Point(30, 58);
			this->subtitleLabel->Name = L"subtitleLabel";
			this->subtitleLabel->Size = System::Drawing::Size(381, 28);
			this->subtitleLabel->TabIndex = 1;
			this->subtitleLabel->Text = L"A Unified Simulator for Formal Languages.";
			this->subtitleLabel->Click += gcnew System::EventHandler(this, &MyForm::subtitleLabel_Click);
			// 
			// titleLabel
			// 
			this->titleLabel->AutoSize = true;
			this->titleLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->titleLabel->ForeColor = System::Drawing::Color::White;
			this->titleLabel->Location = System::Drawing::Point(26, 9);
			this->titleLabel->Name = L"titleLabel";
			this->titleLabel->Size = System::Drawing::Size(1038, 54);
			this->titleLabel->TabIndex = 0;
			this->titleLabel->Text = L"GenoSearch | Automata-Powered Pattern Recognition";
			// 
			// mainContainer
			// 
			this->mainContainer->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(247)),
				static_cast<System::Int32>(static_cast<System::Byte>(245)));
			this->mainContainer->Controls->Add(this->rightPanel);
			this->mainContainer->Controls->Add(this->leftPanel);
			this->mainContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->mainContainer->Location = System::Drawing::Point(0, 100);
			this->mainContainer->Name = L"mainContainer";
			this->mainContainer->Padding = System::Windows::Forms::Padding(20);
			this->mainContainer->Size = System::Drawing::Size(1716, 871);
			this->mainContainer->TabIndex = 1;
			// 
			// rightPanel
			// 
			this->rightPanel->Controls->Add(this->outputTabControl);
			this->rightPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->rightPanel->Location = System::Drawing::Point(825, 20);
			this->rightPanel->Name = L"rightPanel";
			this->rightPanel->Padding = System::Windows::Forms::Padding(10, 0, 0, 0);
			this->rightPanel->Size = System::Drawing::Size(871, 831);
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
			this->outputTabControl->Size = System::Drawing::Size(861, 831);
			this->outputTabControl->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->BackColor = System::Drawing::Color::White;
			this->tabPage1->Controls->Add(this->normalOutputGroup);
			this->tabPage1->Controls->Add(this->errorGroup);
			this->tabPage1->Location = System::Drawing::Point(4, 44);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(15);
			this->tabPage1->Size = System::Drawing::Size(853, 783);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Results";
			// 
			// normalOutputGroup
			// 
			this->normalOutputGroup->Controls->Add(this->resultsTableLayout);
			this->normalOutputGroup->Controls->Add(this->resultsLabel);
			this->normalOutputGroup->Dock = System::Windows::Forms::DockStyle::Fill;
			this->normalOutputGroup->Location = System::Drawing::Point(15, 15);
			this->normalOutputGroup->Name = L"normalOutputGroup";
			this->normalOutputGroup->Padding = System::Windows::Forms::Padding(15);
			this->normalOutputGroup->Size = System::Drawing::Size(823, 753);
			this->normalOutputGroup->TabIndex = 1;
			this->normalOutputGroup->TabStop = false;
			// 
			// resultsTableLayout
			// 
			this->resultsTableLayout->ColumnCount = 2;
			this->resultsTableLayout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->resultsTableLayout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->resultsTableLayout->Controls->Add(this->summaryGroup, 0, 0);
			this->resultsTableLayout->Controls->Add(this->grammarGroup, 0, 1);
			this->resultsTableLayout->Controls->Add(this->matchReportGroup, 1, 0);
			this->resultsTableLayout->Dock = System::Windows::Forms::DockStyle::Fill;
			this->resultsTableLayout->Location = System::Drawing::Point(15, 42);
			this->resultsTableLayout->Name = L"resultsTableLayout";
			this->resultsTableLayout->RowCount = 2;
			this->resultsTableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->resultsTableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->resultsTableLayout->Size = System::Drawing::Size(793, 696);
			this->resultsTableLayout->TabIndex = 5;
			// 
			// summaryGroup
			// 
			this->summaryGroup->Controls->Add(this->summaryBox);
			this->summaryGroup->Dock = System::Windows::Forms::DockStyle::Fill;
			this->summaryGroup->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->summaryGroup->Location = System::Drawing::Point(3, 3);
			this->summaryGroup->Name = L"summaryGroup";
			this->summaryGroup->Padding = System::Windows::Forms::Padding(10, 9, 10, 9);
			this->summaryGroup->Size = System::Drawing::Size(390, 342);
			this->summaryGroup->TabIndex = 2;
			this->summaryGroup->TabStop = false;
			this->summaryGroup->Text = L"Simulation Summary";
			// 
			// summaryBox
			// 
			this->summaryBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(248)), static_cast<System::Int32>(static_cast<System::Byte>(252)),
				static_cast<System::Int32>(static_cast<System::Byte>(251)));
			this->summaryBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->summaryBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->summaryBox->Font = (gcnew System::Drawing::Font(L"Consolas", 9));
			this->summaryBox->Location = System::Drawing::Point(10, 36);
			this->summaryBox->Multiline = true;
			this->summaryBox->Name = L"summaryBox";
			this->summaryBox->ReadOnly = true;
			this->summaryBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->summaryBox->Size = System::Drawing::Size(370, 297);
			this->summaryBox->TabIndex = 0;
			// 
			// grammarGroup
			// 
			this->grammarGroup->Controls->Add(this->grammarBox);
			this->grammarGroup->Dock = System::Windows::Forms::DockStyle::Fill;
			this->grammarGroup->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->grammarGroup->Location = System::Drawing::Point(3, 351);
			this->grammarGroup->Name = L"grammarGroup";
			this->grammarGroup->Padding = System::Windows::Forms::Padding(10, 9, 10, 9);
			this->grammarGroup->Size = System::Drawing::Size(390, 342);
			this->grammarGroup->TabIndex = 3;
			this->grammarGroup->TabStop = false;
			this->grammarGroup->Text = L"Generated Grammar";
			// 
			// grammarBox
			// 
			this->grammarBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(248)), static_cast<System::Int32>(static_cast<System::Byte>(252)),
				static_cast<System::Int32>(static_cast<System::Byte>(251)));
			this->grammarBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->grammarBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->grammarBox->Font = (gcnew System::Drawing::Font(L"Consolas", 9));
			this->grammarBox->Location = System::Drawing::Point(10, 36);
			this->grammarBox->Multiline = true;
			this->grammarBox->Name = L"grammarBox";
			this->grammarBox->ReadOnly = true;
			this->grammarBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->grammarBox->Size = System::Drawing::Size(370, 297);
			this->grammarBox->TabIndex = 0;
			// 
			// matchReportGroup
			// 
			this->matchReportGroup->Controls->Add(this->resultsBox);
			this->matchReportGroup->Dock = System::Windows::Forms::DockStyle::Fill;
			this->matchReportGroup->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->matchReportGroup->Location = System::Drawing::Point(399, 3);
			this->matchReportGroup->Name = L"matchReportGroup";
			this->matchReportGroup->Padding = System::Windows::Forms::Padding(10, 9, 10, 9);
			this->resultsTableLayout->SetRowSpan(this->matchReportGroup, 2);
			this->matchReportGroup->Size = System::Drawing::Size(391, 690);
			this->matchReportGroup->TabIndex = 4;
			this->matchReportGroup->TabStop = false;
			this->matchReportGroup->Text = L"Match Report";
			// 
			// resultsBox
			// 
			this->resultsBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(248)), static_cast<System::Int32>(static_cast<System::Byte>(252)),
				static_cast<System::Int32>(static_cast<System::Byte>(251)));
			this->resultsBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->resultsBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->resultsBox->Font = (gcnew System::Drawing::Font(L"Consolas", 9));
			this->resultsBox->Location = System::Drawing::Point(10, 36);
			this->resultsBox->Multiline = true;
			this->resultsBox->Name = L"resultsBox";
			this->resultsBox->ReadOnly = true;
			this->resultsBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->resultsBox->Size = System::Drawing::Size(371, 645);
			this->resultsBox->TabIndex = 0;
			// 
			// resultsLabel
			// 
			this->resultsLabel->AutoSize = true;
			this->resultsLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
			this->resultsLabel->ForeColor = System::Drawing::Color::Green;
			this->resultsLabel->Location = System::Drawing::Point(3, 0);
			this->resultsLabel->Name = L"resultsLabel";
			this->resultsLabel->Size = System::Drawing::Size(109, 38);
			this->resultsLabel->TabIndex = 0;
			this->resultsLabel->Text = L"Results";
			this->resultsLabel->Click += gcnew System::EventHandler(this, &MyForm::resultsLabel_Click);
			// 
			// errorGroup
			// 
			this->errorGroup->Controls->Add(this->errorBox);
			this->errorGroup->Controls->Add(this->errorLabel);
			this->errorGroup->Dock = System::Windows::Forms::DockStyle::Fill;
			this->errorGroup->Location = System::Drawing::Point(15, 15);
			this->errorGroup->Name = L"errorGroup";
			this->errorGroup->Padding = System::Windows::Forms::Padding(15);
			this->errorGroup->Size = System::Drawing::Size(823, 753);
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
			this->errorBox->Size = System::Drawing::Size(793, 644);
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
			this->errorLabel->Size = System::Drawing::Size(202, 52);
			this->errorLabel->TabIndex = 0;
			this->errorLabel->Text = L"Simulation Error";
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
			this->tabPage2->Size = System::Drawing::Size(791, 712);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Visualization";
			// 
			// pdaTraceBox
			// 
			this->pdaTraceBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(248)), static_cast<System::Int32>(static_cast<System::Byte>(252)),
				static_cast<System::Int32>(static_cast<System::Byte>(251)));
			this->pdaTraceBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pdaTraceBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pdaTraceBox->Font = (gcnew System::Drawing::Font(L"Consolas", 9));
			this->pdaTraceBox->Location = System::Drawing::Point(15, 73);
			this->pdaTraceBox->Multiline = true;
			this->pdaTraceBox->Name = L"pdaTraceBox";
			this->pdaTraceBox->ReadOnly = true;
			this->pdaTraceBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->pdaTraceBox->Size = System::Drawing::Size(761, 624);
			this->pdaTraceBox->TabIndex = 3;
			// 
			// vizPictureBox
			// 
			this->vizPictureBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(248)), static_cast<System::Int32>(static_cast<System::Byte>(252)),
				static_cast<System::Int32>(static_cast<System::Byte>(251)));
			this->vizPictureBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->vizPictureBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->vizPictureBox->Location = System::Drawing::Point(15, 73);
			this->vizPictureBox->Name = L"vizPictureBox";
			this->vizPictureBox->Size = System::Drawing::Size(761, 624);
			this->vizPictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->vizPictureBox->TabIndex = 2;
			this->vizPictureBox->TabStop = false;
			// 
			// vizToggleGroup
			// 
			this->vizToggleGroup->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->vizToggleGroup->Controls->Add(this->showDfaButton);
			this->vizToggleGroup->Controls->Add(this->showNfaButton);
			this->vizToggleGroup->Location = System::Drawing::Point(490, 7);
			this->vizToggleGroup->Name = L"vizToggleGroup";
			this->vizToggleGroup->Padding = System::Windows::Forms::Padding(0, 9, 0, 9);
			this->vizToggleGroup->Size = System::Drawing::Size(283, 54);
			this->vizToggleGroup->TabIndex = 1;
			// 
			// showDfaButton
			// 
			this->showDfaButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(220)), static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(225)));
			this->showDfaButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->showDfaButton->Dock = System::Windows::Forms::DockStyle::Left;
			this->showDfaButton->FlatAppearance->BorderSize = 0;
			this->showDfaButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->showDfaButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->showDfaButton->Location = System::Drawing::Point(140, 9);
			this->showDfaButton->Name = L"showDfaButton";
			this->showDfaButton->Size = System::Drawing::Size(142, 36);
			this->showDfaButton->TabIndex = 1;
			this->showDfaButton->Text = L"Show DFA";
			this->showDfaButton->UseVisualStyleBackColor = false;
			this->showDfaButton->Click += gcnew System::EventHandler(this, &MyForm::showDfaButton_Click);
			this->showDfaButton->MouseEnter += gcnew System::EventHandler(this, &MyForm::Button_MouseEnter);
			this->showDfaButton->MouseLeave += gcnew System::EventHandler(this, &MyForm::Button_MouseLeave);
			// 
			// showNfaButton
			// 
			this->showNfaButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(42)), static_cast<System::Int32>(static_cast<System::Byte>(157)),
				static_cast<System::Int32>(static_cast<System::Byte>(143)));
			this->showNfaButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->showNfaButton->Dock = System::Windows::Forms::DockStyle::Left;
			this->showNfaButton->FlatAppearance->BorderSize = 0;
			this->showNfaButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->showNfaButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->showNfaButton->ForeColor = System::Drawing::Color::White;
			this->showNfaButton->Location = System::Drawing::Point(0, 9);
			this->showNfaButton->Name = L"showNfaButton";
			this->showNfaButton->Size = System::Drawing::Size(140, 36);
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
			this->vizLabel->ForeColor = System::Drawing::Color::Green;
			this->vizLabel->Location = System::Drawing::Point(15, 15);
			this->vizLabel->Name = L"vizLabel";
			this->vizLabel->Padding = System::Windows::Forms::Padding(0, 0, 0, 20);
			this->vizLabel->Size = System::Drawing::Size(334, 58);
			this->vizLabel->TabIndex = 0;
			this->vizLabel->Text = L"Visualization (NFA/DFA)";
			// 
			// leftPanel
			// 
			this->leftPanel->BackColor = System::Drawing::Color::White;
			this->leftPanel->Controls->Add(this->groupBox2);
			this->leftPanel->Controls->Add(this->progressBar);
			this->leftPanel->Dock = System::Windows::Forms::DockStyle::Left;
			this->leftPanel->Location = System::Drawing::Point(20, 20);
			this->leftPanel->Name = L"leftPanel";
			this->leftPanel->Padding = System::Windows::Forms::Padding(15);
			this->leftPanel->Size = System::Drawing::Size(805, 831);
			this->leftPanel->TabIndex = 0;
			// 
			// progressBar
			// 
			this->progressBar->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->progressBar->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(42)), static_cast<System::Int32>(static_cast<System::Byte>(157)),
				static_cast<System::Int32>(static_cast<System::Byte>(143)));
			this->progressBar->Location = System::Drawing::Point(15, 807);
			this->progressBar->MarqueeAnimationSpeed = 30;
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(775, 9);
			this->progressBar->Style = System::Windows::Forms::ProgressBarStyle::Marquee;
			this->progressBar->TabIndex = 2;
			this->progressBar->Visible = false;
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
			// patternInputGroup
			// 
			this->patternInputGroup->Controls->Add(this->patternLabel);
			this->patternInputGroup->Controls->Add(this->patternInputBox);
			this->patternInputGroup->Location = System::Drawing::Point(15, 188);
			this->patternInputGroup->Name = L"patternInputGroup";
			this->patternInputGroup->Padding = System::Windows::Forms::Padding(10, 9, 10, 9);
			this->patternInputGroup->Size = System::Drawing::Size(746, 112);
			this->patternInputGroup->TabIndex = 0;
			this->patternInputGroup->TabStop = false;
			// 
			// patternInputBox
			// 
			this->patternInputBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(248)), static_cast<System::Int32>(static_cast<System::Byte>(252)),
				static_cast<System::Int32>(static_cast<System::Byte>(251)));
			this->patternInputBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->patternInputBox->Font = (gcnew System::Drawing::Font(L"Consolas", 11));
			this->patternInputBox->Location = System::Drawing::Point(25, 62);
			this->patternInputBox->Name = L"patternInputBox";
			this->patternInputBox->Size = System::Drawing::Size(635, 33);
			this->patternInputBox->TabIndex = 0;
			// 
			// patternLabel
			// 
			this->patternLabel->AutoSize = true;
			this->patternLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->patternLabel->Location = System::Drawing::Point(19, 23);
			this->patternLabel->Name = L"patternLabel";
			this->patternLabel->Size = System::Drawing::Size(282, 28);
			this->patternLabel->TabIndex = 1;
			this->patternLabel->Text = L"Pattern (Regular Expression)";
			// 
			// editDistanceGroup
			// 
			this->editDistanceGroup->Controls->Add(this->editDistanceInput);
			this->editDistanceGroup->Controls->Add(this->distanceLabel);
			this->editDistanceGroup->Location = System::Drawing::Point(15, 306);
			this->editDistanceGroup->Name = L"editDistanceGroup";
			this->editDistanceGroup->Padding = System::Windows::Forms::Padding(10, 9, 10, 9);
			this->editDistanceGroup->Size = System::Drawing::Size(746, 76);
			this->editDistanceGroup->TabIndex = 1;
			this->editDistanceGroup->TabStop = false;
			// 
			// distanceLabel
			// 
			this->distanceLabel->AutoSize = true;
			this->distanceLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->distanceLabel->Location = System::Drawing::Point(20, 30);
			this->distanceLabel->Name = L"distanceLabel";
			this->distanceLabel->Size = System::Drawing::Size(173, 28);
			this->distanceLabel->TabIndex = 0;
			this->distanceLabel->Text = L"Edit Distance (k):";
			// 
			// editDistanceInput
			// 
			this->editDistanceInput->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(248)),
				static_cast<System::Int32>(static_cast<System::Byte>(252)), static_cast<System::Int32>(static_cast<System::Byte>(251)));
			this->editDistanceInput->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->editDistanceInput->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11));
			this->editDistanceInput->Location = System::Drawing::Point(211, 27);
			this->editDistanceInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->editDistanceInput->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->editDistanceInput->Name = L"editDistanceInput";
			this->editDistanceInput->Size = System::Drawing::Size(80, 37);
			this->editDistanceInput->TabIndex = 1;
			this->editDistanceInput->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// pdaInputTypeGroup
			// 
			this->pdaInputTypeGroup->Controls->Add(this->sourceInputLabel);
			this->pdaInputTypeGroup->Controls->Add(this->pdaFileRadio);
			this->pdaInputTypeGroup->Controls->Add(this->pdaStringRadio);
			this->pdaInputTypeGroup->Location = System::Drawing::Point(15, 535);
			this->pdaInputTypeGroup->Name = L"pdaInputTypeGroup";
			this->pdaInputTypeGroup->Padding = System::Windows::Forms::Padding(10, 9, 10, 9);
			this->pdaInputTypeGroup->Size = System::Drawing::Size(746, 74);
			this->pdaInputTypeGroup->TabIndex = 2;
			this->pdaInputTypeGroup->TabStop = false;
			// 
			// pdaStringRadio
			// 
			this->pdaStringRadio->AutoSize = true;
			this->pdaStringRadio->Checked = true;
			this->pdaStringRadio->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pdaStringRadio->Location = System::Drawing::Point(165, 28);
			this->pdaStringRadio->Name = L"pdaStringRadio";
			this->pdaStringRadio->Size = System::Drawing::Size(150, 29);
			this->pdaStringRadio->TabIndex = 0;
			this->pdaStringRadio->TabStop = true;
			this->pdaStringRadio->Text = L"Validate String";
			this->pdaStringRadio->UseVisualStyleBackColor = true;
			this->pdaStringRadio->CheckedChanged += gcnew System::EventHandler(this, &MyForm::pdaInputType_CheckedChanged);
			// 
			// pdaFileRadio
			// 
			this->pdaFileRadio->AutoSize = true;
			this->pdaFileRadio->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pdaFileRadio->Location = System::Drawing::Point(321, 28);
			this->pdaFileRadio->Name = L"pdaFileRadio";
			this->pdaFileRadio->Size = System::Drawing::Size(130, 29);
			this->pdaFileRadio->TabIndex = 1;
			this->pdaFileRadio->Text = L"Validate File";
			this->pdaFileRadio->UseVisualStyleBackColor = true;
			this->pdaFileRadio->CheckedChanged += gcnew System::EventHandler(this, &MyForm::pdaInputType_CheckedChanged);
			// 
			// sourceInputLabel
			// 
			this->sourceInputLabel->AutoSize = true;
			this->sourceInputLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->sourceInputLabel->Location = System::Drawing::Point(20, 27);
			this->sourceInputLabel->Name = L"sourceInputLabel";
			this->sourceInputLabel->Size = System::Drawing::Size(137, 28);
			this->sourceInputLabel->TabIndex = 2;
			this->sourceInputLabel->Text = L"Input Source:";
			this->sourceInputLabel->Click += gcnew System::EventHandler(this, &MyForm::sourceInputLabel_Click);
			// 
			// fileInputGroup
			// 
			this->fileInputGroup->Controls->Add(this->supportLabel);
			this->fileInputGroup->Controls->Add(this->browseButton);
			this->fileInputGroup->Controls->Add(this->fileInputBox);
			this->fileInputGroup->Controls->Add(this->fileInputLabel);
			this->fileInputGroup->Location = System::Drawing::Point(15, 388);
			this->fileInputGroup->Name = L"fileInputGroup";
			this->fileInputGroup->Padding = System::Windows::Forms::Padding(10, 9, 10, 9);
			this->fileInputGroup->Size = System::Drawing::Size(746, 129);
			this->fileInputGroup->TabIndex = 3;
			this->fileInputGroup->TabStop = false;
			this->fileInputGroup->Enter += gcnew System::EventHandler(this, &MyForm::fileInputGroup_Enter);
			// 
			// fileInputLabel
			// 
			this->fileInputLabel->AutoSize = true;
			this->fileInputLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->fileInputLabel->Location = System::Drawing::Point(21, 22);
			this->fileInputLabel->Name = L"fileInputLabel";
			this->fileInputLabel->Size = System::Drawing::Size(101, 28);
			this->fileInputLabel->TabIndex = 0;
			this->fileInputLabel->Text = L"Input File";
			// 
			// fileInputBox
			// 
			this->fileInputBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(248)), static_cast<System::Int32>(static_cast<System::Byte>(252)),
				static_cast<System::Int32>(static_cast<System::Byte>(251)));
			this->fileInputBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->fileInputBox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->fileInputBox->Location = System::Drawing::Point(24, 55);
			this->fileInputBox->Name = L"fileInputBox";
			this->fileInputBox->ReadOnly = true;
			this->fileInputBox->Size = System::Drawing::Size(516, 34);
			this->fileInputBox->TabIndex = 1;
			// 
			// browseButton
			// 
			this->browseButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->browseButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(132)), static_cast<System::Int32>(static_cast<System::Byte>(169)),
				static_cast<System::Int32>(static_cast<System::Byte>(140)));
			this->browseButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->browseButton->FlatAppearance->BorderSize = 0;
			this->browseButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->browseButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->browseButton->ForeColor = System::Drawing::Color::White;
			this->browseButton->Location = System::Drawing::Point(618, 55);
			this->browseButton->Name = L"browseButton";
			this->browseButton->Size = System::Drawing::Size(100, 34);
			this->browseButton->TabIndex = 2;
			this->browseButton->Text = L"Browse";
			this->browseButton->UseVisualStyleBackColor = false;
			this->browseButton->Click += gcnew System::EventHandler(this, &MyForm::browseButton_Click);
			this->browseButton->MouseEnter += gcnew System::EventHandler(this, &MyForm::Button_MouseEnter);
			this->browseButton->MouseLeave += gcnew System::EventHandler(this, &MyForm::Button_MouseLeave);
			// 
			// supportLabel
			// 
			this->supportLabel->AutoSize = true;
			this->supportLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8));
			this->supportLabel->ForeColor = System::Drawing::Color::Gray;
			this->supportLabel->Location = System::Drawing::Point(21, 92);
			this->supportLabel->Name = L"supportLabel";
			this->supportLabel->Size = System::Drawing::Size(198, 21);
			this->supportLabel->TabIndex = 3;
			this->supportLabel->Text = L"Supports: .txt, .fa, .fasta files";
			// 
			// runButton
			// 
			this->runButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->runButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(42)), static_cast<System::Int32>(static_cast<System::Byte>(157)),
				static_cast<System::Int32>(static_cast<System::Byte>(143)));
			this->runButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->runButton->FlatAppearance->BorderSize = 0;
			this->runButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->runButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
			this->runButton->ForeColor = System::Drawing::Color::White;
			this->runButton->Location = System::Drawing::Point(15, 666);
			this->runButton->Name = L"runButton";
			this->runButton->Size = System::Drawing::Size(745, 49);
			this->runButton->TabIndex = 4;
			this->runButton->Text = L"Run Simulation";
			this->runButton->UseVisualStyleBackColor = false;
			this->runButton->Click += gcnew System::EventHandler(this, &MyForm::runButton_Click);
			this->runButton->MouseEnter += gcnew System::EventHandler(this, &MyForm::Button_MouseEnter);
			this->runButton->MouseLeave += gcnew System::EventHandler(this, &MyForm::Button_MouseLeave);
			// 
			// step2Label
			// 
			this->step2Label->AutoSize = true;
			this->step2Label->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
			this->step2Label->ForeColor = System::Drawing::Color::Green;
			this->step2Label->Location = System::Drawing::Point(9, 159);
			this->step2Label->Name = L"step2Label";
			this->step2Label->Size = System::Drawing::Size(292, 32);
			this->step2Label->TabIndex = 5;
			this->step2Label->Text = L"Step 2: Configure Inputs";
			this->step2Label->Click += gcnew System::EventHandler(this, &MyForm::step2Label_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
			this->label1->ForeColor = System::Drawing::Color::Green;
			this->label1->Location = System::Drawing::Point(9, 29);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(356, 32);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Step 1: Select Simulation Type";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// showErrorButton
			// 
			this->showErrorButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->showErrorButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(233)), static_cast<System::Int32>(static_cast<System::Byte>(196)),
				static_cast<System::Int32>(static_cast<System::Byte>(106)));
			this->showErrorButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->showErrorButton->FlatAppearance->BorderSize = 0;
			this->showErrorButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->showErrorButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->showErrorButton->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(71)));
			this->showErrorButton->Location = System::Drawing::Point(591, 726);
			this->showErrorButton->Name = L"showErrorButton";
			this->showErrorButton->Size = System::Drawing::Size(170, 35);
			this->showErrorButton->TabIndex = 6;
			this->showErrorButton->Text = L"Show Error Demo";
			this->showErrorButton->UseVisualStyleBackColor = false;
			this->showErrorButton->Click += gcnew System::EventHandler(this, &MyForm::showErrorButton_Click);
			this->showErrorButton->MouseEnter += gcnew System::EventHandler(this, &MyForm::Button_MouseEnter);
			this->showErrorButton->MouseLeave += gcnew System::EventHandler(this, &MyForm::Button_MouseLeave);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->sim3Label);
			this->groupBox1->Controls->Add(this->sim2Label);
			this->groupBox1->Controls->Add(this->sim1Label);
			this->groupBox1->Controls->Add(this->pdaRadio);
			this->groupBox1->Controls->Add(this->approxRadio);
			this->groupBox1->Controls->Add(this->regexRadio);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->groupBox1->Location = System::Drawing::Point(15, 56);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(15);
			this->groupBox1->Size = System::Drawing::Size(746, 92);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Enter += gcnew System::EventHandler(this, &MyForm::groupBox1_Enter);
			// 
			// regexRadio
			// 
			this->regexRadio->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->regexRadio->AutoSize = true;
			this->regexRadio->Checked = true;
			this->regexRadio->Cursor = System::Windows::Forms::Cursors::Hand;
			this->regexRadio->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->regexRadio->Location = System::Drawing::Point(20, 26);
			this->regexRadio->Name = L"regexRadio";
			this->regexRadio->Size = System::Drawing::Size(208, 32);
			this->regexRadio->TabIndex = 0;
			this->regexRadio->TabStop = true;
			this->regexRadio->Text = L"Regular Expression";
			this->regexRadio->UseVisualStyleBackColor = true;
			this->regexRadio->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Radio_CheckedChanged);
			// 
			// approxRadio
			// 
			this->approxRadio->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->approxRadio->AutoSize = true;
			this->approxRadio->Cursor = System::Windows::Forms::Cursors::Hand;
			this->approxRadio->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->approxRadio->Location = System::Drawing::Point(248, 27);
			this->approxRadio->Name = L"approxRadio";
			this->approxRadio->Size = System::Drawing::Size(216, 32);
			this->approxRadio->TabIndex = 1;
			this->approxRadio->Text = L"Approximate Match";
			this->approxRadio->UseVisualStyleBackColor = true;
			this->approxRadio->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Radio_CheckedChanged);
			// 
			// pdaRadio
			// 
			this->pdaRadio->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->pdaRadio->AutoSize = true;
			this->pdaRadio->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pdaRadio->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->pdaRadio->Location = System::Drawing::Point(486, 26);
			this->pdaRadio->Name = L"pdaRadio";
			this->pdaRadio->Size = System::Drawing::Size(219, 32);
			this->pdaRadio->TabIndex = 2;
			this->pdaRadio->Text = L"Structural Validation";
			this->pdaRadio->UseVisualStyleBackColor = true;
			this->pdaRadio->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Radio_CheckedChanged);
			// 
			// sim1Label
			// 
			this->sim1Label->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->sim1Label->AutoSize = true;
			this->sim1Label->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->sim1Label->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->sim1Label->Location = System::Drawing::Point(32, 60);
			this->sim1Label->Name = L"sim1Label";
			this->sim1Label->Size = System::Drawing::Size(185, 21);
			this->sim1Label->TabIndex = 4;
			this->sim1Label->Text = L"Find exact patterns (DFA).";
			this->sim1Label->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
			// 
			// sim2Label
			// 
			this->sim2Label->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->sim2Label->AutoSize = true;
			this->sim2Label->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->sim2Label->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->sim2Label->Location = System::Drawing::Point(255, 61);
			this->sim2Label->Name = L"sim2Label";
			this->sim2Label->Size = System::Drawing::Size(199, 21);
			this->sim2Label->TabIndex = 5;
			this->sim2Label->Text = L"Find \"fuzzy\" patterns (NFA).";
			// 
			// sim3Label
			// 
			this->sim3Label->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->sim3Label->AutoSize = true;
			this->sim3Label->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->sim3Label->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->sim3Label->Location = System::Drawing::Point(486, 61);
			this->sim3Label->Name = L"sim3Label";
			this->sim3Label->Size = System::Drawing::Size(222, 21);
			this->sim3Label->TabIndex = 6;
			this->sim3Label->Text = L"Check nested structures (PDA).";
			// 
			// resetButton
			// 
			this->resetButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->resetButton->BackColor = System::Drawing::SystemColors::AppWorkspace;
			this->resetButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->resetButton->FlatAppearance->BorderSize = 0;
			this->resetButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->resetButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->resetButton->ForeColor = System::Drawing::Color::DarkGray;
			this->resetButton->Location = System::Drawing::Point(15, 726);
			this->resetButton->Name = L"resetButton";
			this->resetButton->Size = System::Drawing::Size(170, 35);
			this->resetButton->TabIndex = 7;
			this->resetButton->Text = L"Reset All";
			this->resetButton->UseVisualStyleBackColor = false;
			this->resetButton->Click += gcnew System::EventHandler(this, &MyForm::resetButton_Click);
			this->resetButton->MouseEnter += gcnew System::EventHandler(this, &MyForm::Button_MouseEnter);
			this->resetButton->MouseLeave += gcnew System::EventHandler(this, &MyForm::Button_MouseLeave);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->resetButton);
			this->groupBox2->Controls->Add(this->groupBox1);
			this->groupBox2->Controls->Add(this->showErrorButton);
			this->groupBox2->Controls->Add(this->label1);
			this->groupBox2->Controls->Add(this->pdaInputTypeGroup);
			this->groupBox2->Controls->Add(this->editDistanceGroup);
			this->groupBox2->Controls->Add(this->step2Label);
			this->groupBox2->Controls->Add(this->runButton);
			this->groupBox2->Controls->Add(this->fileInputGroup);
			this->groupBox2->Controls->Add(this->patternInputGroup);
			this->groupBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->groupBox2->Location = System::Drawing::Point(15, 15);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Padding = System::Windows::Forms::Padding(15);
			this->groupBox2->Size = System::Drawing::Size(775, 792);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(1716, 971);
			this->Controls->Add(this->mainContainer);
			this->Controls->Add(this->headerPanel);
			this->MinimumSize = System::Drawing::Size(1196, 661);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"GenoSearch ";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->headerPanel->ResumeLayout(false);
			this->headerPanel->PerformLayout();
			this->mainContainer->ResumeLayout(false);
			this->rightPanel->ResumeLayout(false);
			this->outputTabControl->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->normalOutputGroup->ResumeLayout(false);
			this->normalOutputGroup->PerformLayout();
			this->resultsTableLayout->ResumeLayout(false);
			this->summaryGroup->ResumeLayout(false);
			this->summaryGroup->PerformLayout();
			this->grammarGroup->ResumeLayout(false);
			this->grammarGroup->PerformLayout();
			this->matchReportGroup->ResumeLayout(false);
			this->matchReportGroup->PerformLayout();
			this->errorGroup->ResumeLayout(false);
			this->errorGroup->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->vizPictureBox))->EndInit();
			this->vizToggleGroup->ResumeLayout(false);
			this->leftPanel->ResumeLayout(false);
			this->patternInputGroup->ResumeLayout(false);
			this->patternInputGroup->PerformLayout();
			this->editDistanceGroup->ResumeLayout(false);
			this->editDistanceGroup->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->editDistanceInput))->EndInit();
			this->pdaInputTypeGroup->ResumeLayout(false);
			this->pdaInputTypeGroup->PerformLayout();
			this->fileInputGroup->ResumeLayout(false);
			this->fileInputGroup->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

		// *** MODIFICATION: Removed non-functional shadow painting ***
		void InitializeModernUI() {
			// Set modern fonts
			this->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);

			ApplyScienceTheme();
		}

		// [UPDATED] Draws a Cleaner Bio-Tech Gradient (Teal -> Lime)
		void HeaderPanel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
			// A smoother, modern science gradient
			System::Drawing::Drawing2D::LinearGradientBrush^ brush =
				gcnew System::Drawing::Drawing2D::LinearGradientBrush(
					this->headerPanel->ClientRectangle,
					System::Drawing::Color::FromArgb(15, 50, 30),   // Deep Bio-Green
					System::Drawing::Color::FromArgb(140, 190, 40), // Tech Lime
					System::Drawing::Drawing2D::LinearGradientMode::Horizontal
				);

			e->Graphics->FillRectangle(brush, this->headerPanel->ClientRectangle);
		}

		// [UPDATED] Applies theme with specific Dark Green buttons + Lime Error button
		void ApplyScienceTheme() {
			// 1. Hook up Header Gradient
			this->headerPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::HeaderPanel_Paint);

			// Text Transparency
			this->titleLabel->BackColor = System::Drawing::Color::Transparent;
			this->subtitleLabel->BackColor = System::Drawing::Color::Transparent;
			this->titleLabel->ForeColor = System::Drawing::Color::White;
			this->subtitleLabel->ForeColor = System::Drawing::Color::FromArgb(220, 255, 220);

			// 2. Main Backgrounds
			this->BackColor = System::Drawing::Color::FromArgb(250, 252, 250);
			this->mainContainer->BackColor = System::Drawing::Color::FromArgb(250, 252, 250);
			this->leftPanel->BackColor = System::Drawing::Color::White;
			this->rightPanel->BackColor = System::Drawing::Color::White;

			// 3. Standard Buttons (Dark Green #1D623A)
			System::Drawing::Color specificDarkGreen = System::Drawing::Color::FromArgb(29, 98, 58);

			this->runButton->BackColor = specificDarkGreen;
			this->runButton->ForeColor = System::Drawing::Color::White;

			this->exportButton->BackColor = specificDarkGreen;
			this->exportButton->ForeColor = System::Drawing::Color::White;

			this->browseButton->BackColor = specificDarkGreen;
			this->browseButton->ForeColor = System::Drawing::Color::White;

			this->showNfaButton->BackColor = specificDarkGreen; // Active
			this->showDfaButton->BackColor = System::Drawing::Color::FromArgb(220, 230, 220); // Inactive

			// Reset Button
			this->resetButton->BackColor = System::Drawing::Color::FromArgb(240, 240, 240);
			this->resetButton->ForeColor = System::Drawing::Color::Black;

			// *** UPDATED: Show Error Demo Button (#8CBF28) ***
			this->showErrorButton->BackColor = System::Drawing::Color::FromArgb(140, 191, 40);
			this->showErrorButton->ForeColor = System::Drawing::Color::White; // Changed to White for better contrast
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

		// [UPDATED] Restores correct colors (Dark Green & Lime Green) on mouse leave
		void Button_MouseLeave(Object^ sender, EventArgs^ e) {
			Button^ btn = safe_cast<Button^>(sender);
			System::Drawing::Color specificDarkGreen = System::Drawing::Color::FromArgb(29, 98, 58);

			if (btn == runButton || btn == exportButton || btn == browseButton) {
				btn->BackColor = specificDarkGreen;
			}
			// *** UPDATED: Restore Lime Green (#8CBF28) ***
			else if (btn == showErrorButton) {
				btn->BackColor = System::Drawing::Color::FromArgb(140, 191, 40);
			}
			else if (btn == resetButton) {
				btn->BackColor = System::Drawing::Color::FromArgb(240, 240, 240);
			}
			else if (btn == showNfaButton) {
				if (showNfaButton->ForeColor == Color::White) {
					btn->BackColor = specificDarkGreen;
				}
				else {
					btn->BackColor = System::Drawing::Color::FromArgb(220, 230, 220);
				}
			}
			else if (btn == showDfaButton) {
				if (showDfaButton->ForeColor == Color::White) {
					btn->BackColor = specificDarkGreen;
				}
				else {
					btn->BackColor = System::Drawing::Color::FromArgb(220, 230, 220);
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

			// Clear all outputs
			ResetOutputs();
		}

		// *** MODIFICATION: Updated ResetOutputs to fix visibility bug ***
		void ResetOutputs() {
			this->normalOutputGroup->Visible = true;

			// *** FIX ***
			// Ensure all components of the results layout are visible
			this->summaryGroup->Visible = true;
			this->grammarGroup->Visible = true;
			this->matchReportGroup->Visible = true;

			this->resultsLabel->Text = "Results";
			this->vizLabel->Text = "Visualization";
			this->summaryBox->Text = "";
			this->grammarBox->Text = "";
			this->resultsBox->Text = "";
			this->pdaTraceBox->Text = "";
			if (this->vizPictureBox->Image != nullptr) {
				this->vizPictureBox->Image = nullptr;
			}
			this->outputTabControl->SelectedTab = this->tabPage1;
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

		// [UPDATED] Shows error in a popup window (MessageBox) instead of the tab
		void ShowError(std::string error_message) {
			// Convert std::string to System::String^
			System::String^ msg = ToNetString(error_message);

			// Show the popup
			MessageBox::Show(msg, "Simulation Error", MessageBoxButtons::OK, MessageBoxIcon::Error);

			// We no longer need to hide/show groups or switch tabs!
			// The previous UI logic for errorGroup is removed.
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

			// Clear previous results
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
				this->resultsLabel->Text = "Results (Regex)";
				this->vizLabel->Text = "Visualization (NFA/DFA)";
				this->matchReportGroup->Text = "Match Report";
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
				this->resultsLabel->Text = "Results (Approximate)";
				this->vizLabel->Text = "Visualization (NFA)";
				this->matchReportGroup->Text = "Match Report";
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
				this->resultsLabel->Text = "Results (PDA)";
				this->vizLabel->Text = "Visualization (PDA Trace)";
				this->matchReportGroup->Text = "Validation Report";
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

				this->summaryGroup->Visible = true;
				this->grammarGroup->Visible = true;
				this->matchReportGroup->Visible = true;

				this->summaryBox->Text = ToNetString(report.summary);
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

		// *** MODIFICATION: Updated button colors for "Green Vibes" theme ***
		System::Void showNfaButton_Click(System::Object^ sender, System::EventArgs^ e) {
			this->showNfaButton->BackColor = Color::FromArgb(34, 139, 34); // Forest Green
			this->showNfaButton->ForeColor = Color::White;
			this->showDfaButton->BackColor = Color::FromArgb(240, 230, 140); // Khaki
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

		// *** MODIFICATION: Updated button colors for "Green Vibes" theme ***
		System::Void showDfaButton_Click(System::Object^ sender, System::EventArgs^ e) {
			this->showNfaButton->BackColor = Color::FromArgb(240, 230, 140); // Khaki
			this->showNfaButton->ForeColor = Color::Black;
			this->showDfaButton->BackColor = Color::FromArgb(34, 139, 34); // Forest Green
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

		// *** MODIFICATION: Added Reset Button Click Handler ***
	private: System::Void resetButton_Click(System::Object^ sender, System::EventArgs^ e) {
		// Reset all inputs to their default state
		this->regexRadio->Checked = true;
		UpdateUIMode();

		// Clear all results
		ResetOutputs();
	}

	private: System::Void vizLabel_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void subtitleLabel_Click(System::Object^ sender, System::EventArgs^ e) {
	}

private: System::Void resultsLabel_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void groupBox1_Enter(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void fileInputGroup_Enter(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void step2Label_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void sourceInputLabel_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}