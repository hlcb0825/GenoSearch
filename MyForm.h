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

	private: System::Windows::Forms::TabControl^ outputTabControl;
	private: System::Windows::Forms::TabPage^ tabPage1;

	private: System::Windows::Forms::TabPage^ tabPage2;



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
	private: System::Windows::Forms::Button^ resetButton;


	private: System::String^ m_nfaDot;
	private: System::String^ m_dfaDot;
	private: System::Windows::Forms::Label^ sim1Label;
	private: System::Windows::Forms::Label^ sim3Label;

	private: System::Windows::Forms::Label^ sim2Label;

		   // *** MODIFICATION: Added TableLayoutPanel for 2-column results ***
	private: System::Windows::Forms::TableLayoutPanel^ resultsTableLayout;
	private: System::Windows::Forms::PictureBox^ logoPictureBox;



	private: System::ComponentModel::IContainer^ components;

	private:


#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->headerPanel = (gcnew System::Windows::Forms::Panel());
			this->logoPictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->subtitleLabel = (gcnew System::Windows::Forms::Label());
			this->titleLabel = (gcnew System::Windows::Forms::Label());
			this->exportButton = (gcnew System::Windows::Forms::Button());
			this->mainContainer = (gcnew System::Windows::Forms::Panel());
			this->rightPanel = (gcnew System::Windows::Forms::Panel());
			this->outputTabControl = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->resultsTableLayout = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->summaryGroup = (gcnew System::Windows::Forms::GroupBox());
			this->summaryBox = (gcnew System::Windows::Forms::TextBox());
			this->grammarGroup = (gcnew System::Windows::Forms::GroupBox());
			this->grammarBox = (gcnew System::Windows::Forms::TextBox());
			this->matchReportGroup = (gcnew System::Windows::Forms::GroupBox());
			this->resultsBox = (gcnew System::Windows::Forms::TextBox());
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
			this->resetButton = (gcnew System::Windows::Forms::Button());
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
			this->sim3Label = (gcnew System::Windows::Forms::Label());
			this->sim2Label = (gcnew System::Windows::Forms::Label());
			this->sim1Label = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pdaRadio = (gcnew System::Windows::Forms::RadioButton());
			this->approxRadio = (gcnew System::Windows::Forms::RadioButton());
			this->regexRadio = (gcnew System::Windows::Forms::RadioButton());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->animationTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->headerPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->logoPictureBox))->BeginInit();
			this->mainContainer->SuspendLayout();
			this->rightPanel->SuspendLayout();
			this->outputTabControl->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->resultsTableLayout->SuspendLayout();
			this->summaryGroup->SuspendLayout();
			this->grammarGroup->SuspendLayout();
			this->matchReportGroup->SuspendLayout();
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
			this->headerPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(42)), static_cast<System::Int32>(static_cast<System::Byte>(157)),
				static_cast<System::Int32>(static_cast<System::Byte>(143)));
			this->headerPanel->Controls->Add(this->logoPictureBox);
			this->headerPanel->Controls->Add(this->subtitleLabel);
			this->headerPanel->Controls->Add(this->titleLabel);
			this->headerPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->headerPanel->Location = System::Drawing::Point(0, 0);
			this->headerPanel->Name = L"headerPanel";
			this->headerPanel->Size = System::Drawing::Size(1603, 105);
			this->headerPanel->TabIndex = 0;
			this->headerPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::headerPanel_Paint_1);
			// 
			// logoPictureBox
			// 
			this->logoPictureBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->logoPictureBox->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"logoPictureBox.Image")));
			this->logoPictureBox->Location = System::Drawing::Point(14, 19);
			this->logoPictureBox->Name = L"logoPictureBox";
			this->logoPictureBox->Size = System::Drawing::Size(91, 68);
			this->logoPictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->logoPictureBox->TabIndex = 2;
			this->logoPictureBox->TabStop = false;
			this->logoPictureBox->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
			// 
			// subtitleLabel
			// 
			this->subtitleLabel->AutoSize = true;
			this->subtitleLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->subtitleLabel->ForeColor = System::Drawing::SystemColors::Control;
			this->subtitleLabel->Location = System::Drawing::Point(111, 61);
			this->subtitleLabel->Name = L"subtitleLabel";
			this->subtitleLabel->Size = System::Drawing::Size(381, 28);
			this->subtitleLabel->TabIndex = 1;
			this->subtitleLabel->Text = L"A Unified Simulator for Formal Languages.";
			this->subtitleLabel->Click += gcnew System::EventHandler(this, &MyForm::subtitleLabel_Click);
			// 
			// titleLabel
			// 
			this->titleLabel->AutoSize = true;
			this->titleLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 22, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->titleLabel->ForeColor = System::Drawing::Color::White;
			this->titleLabel->Location = System::Drawing::Point(103, 9);
			this->titleLabel->Name = L"titleLabel";
			this->titleLabel->Size = System::Drawing::Size(1144, 60);
			this->titleLabel->TabIndex = 0;
			this->titleLabel->Text = L"GenoSearch | Automata-Powered Pattern Recognition";
			this->titleLabel->Click += gcnew System::EventHandler(this, &MyForm::titleLabel_Click);
			// 
			// exportButton
			// 
			this->exportButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->exportButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(132)), static_cast<System::Int32>(static_cast<System::Byte>(169)),
				static_cast<System::Int32>(static_cast<System::Byte>(140)));
			this->exportButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->exportButton->FlatAppearance->BorderSize = 0;
			this->exportButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->exportButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->exportButton->ForeColor = System::Drawing::Color::White;
			this->exportButton->Location = System::Drawing::Point(465, 567);
			this->exportButton->Name = L"exportButton";
			this->exportButton->Size = System::Drawing::Size(219, 37);
			this->exportButton->TabIndex = 1;
			this->exportButton->Text = L"💾 Export Full Report";
			this->exportButton->UseVisualStyleBackColor = false;
			this->exportButton->Click += gcnew System::EventHandler(this, &MyForm::exportButton_Click);
			this->exportButton->MouseEnter += gcnew System::EventHandler(this, &MyForm::Button_MouseEnter);
			this->exportButton->MouseLeave += gcnew System::EventHandler(this, &MyForm::Button_MouseLeave);
			// 
			// mainContainer
			// 
			this->mainContainer->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(247)),
				static_cast<System::Int32>(static_cast<System::Byte>(245)));
			this->mainContainer->Controls->Add(this->rightPanel);
			this->mainContainer->Controls->Add(this->leftPanel);
			this->mainContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->mainContainer->Location = System::Drawing::Point(0, 105);
			this->mainContainer->Name = L"mainContainer";
			this->mainContainer->Padding = System::Windows::Forms::Padding(20, 21, 20, 21);
			this->mainContainer->Size = System::Drawing::Size(1603, 840);
			this->mainContainer->TabIndex = 1;
			this->mainContainer->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::mainContainer_Paint);
			// 
			// rightPanel
			// 
			this->rightPanel->Controls->Add(this->outputTabControl);
			this->rightPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->rightPanel->Location = System::Drawing::Point(749, 21);
			this->rightPanel->Name = L"rightPanel";
			this->rightPanel->Padding = System::Windows::Forms::Padding(10, 0, 0, 0);
			this->rightPanel->Size = System::Drawing::Size(834, 798);
			this->rightPanel->TabIndex = 1;
			this->rightPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::rightPanel_Paint);
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
			this->outputTabControl->Size = System::Drawing::Size(824, 798);
			this->outputTabControl->TabIndex = 0;
			this->outputTabControl->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::outputTabControl_SelectedIndexChanged);
			// 
			// tabPage1
			// 
			this->tabPage1->BackColor = System::Drawing::Color::White;
			this->tabPage1->Controls->Add(this->resultsTableLayout);
			this->tabPage1->Controls->Add(this->resultsLabel);
			this->tabPage1->Location = System::Drawing::Point(4, 44);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(15, 16, 15, 16);
			this->tabPage1->Size = System::Drawing::Size(816, 750);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Results";
			this->tabPage1->Click += gcnew System::EventHandler(this, &MyForm::tabPage1_Click);
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
			this->resultsTableLayout->Location = System::Drawing::Point(15, 59);
			this->resultsTableLayout->Name = L"resultsTableLayout";
			this->resultsTableLayout->RowCount = 2;
			this->resultsTableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->resultsTableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->resultsTableLayout->Size = System::Drawing::Size(786, 675);
			this->resultsTableLayout->TabIndex = 5;
			this->resultsTableLayout->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::resultsTableLayout_Paint);
			// 
			// summaryGroup
			// 
			this->summaryGroup->Controls->Add(this->summaryBox);
			this->summaryGroup->Dock = System::Windows::Forms::DockStyle::Fill;
			this->summaryGroup->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->summaryGroup->Location = System::Drawing::Point(3, 3);
			this->summaryGroup->Name = L"summaryGroup";
			this->summaryGroup->Padding = System::Windows::Forms::Padding(10, 9, 10, 9);
			this->summaryGroup->Size = System::Drawing::Size(387, 331);
			this->summaryGroup->TabIndex = 2;
			this->summaryGroup->TabStop = false;
			this->summaryGroup->Text = L"Simulation Summary";
			this->summaryGroup->Enter += gcnew System::EventHandler(this, &MyForm::summaryGroup_Enter);
			// 
			// summaryBox
			// 
			this->summaryBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(248)), static_cast<System::Int32>(static_cast<System::Byte>(252)),
				static_cast<System::Int32>(static_cast<System::Byte>(251)));
			this->summaryBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->summaryBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->summaryBox->Font = (gcnew System::Drawing::Font(L"Consolas", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->summaryBox->Location = System::Drawing::Point(10, 36);
			this->summaryBox->Multiline = true;
			this->summaryBox->Name = L"summaryBox";
			this->summaryBox->ReadOnly = true;
			this->summaryBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->summaryBox->Size = System::Drawing::Size(367, 286);
			this->summaryBox->TabIndex = 0;
			this->summaryBox->TextChanged += gcnew System::EventHandler(this, &MyForm::summaryBox_TextChanged);
			// 
			// grammarGroup
			// 
			this->grammarGroup->Controls->Add(this->grammarBox);
			this->grammarGroup->Dock = System::Windows::Forms::DockStyle::Fill;
			this->grammarGroup->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->grammarGroup->Location = System::Drawing::Point(3, 340);
			this->grammarGroup->Name = L"grammarGroup";
			this->grammarGroup->Padding = System::Windows::Forms::Padding(10, 9, 10, 9);
			this->grammarGroup->Size = System::Drawing::Size(387, 332);
			this->grammarGroup->TabIndex = 3;
			this->grammarGroup->TabStop = false;
			this->grammarGroup->Text = L"Generated Grammar";
			this->grammarGroup->Enter += gcnew System::EventHandler(this, &MyForm::grammarGroup_Enter);
			// 
			// grammarBox
			// 
			this->grammarBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(248)), static_cast<System::Int32>(static_cast<System::Byte>(252)),
				static_cast<System::Int32>(static_cast<System::Byte>(251)));
			this->grammarBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->grammarBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->grammarBox->Font = (gcnew System::Drawing::Font(L"Consolas", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->grammarBox->Location = System::Drawing::Point(10, 36);
			this->grammarBox->Multiline = true;
			this->grammarBox->Name = L"grammarBox";
			this->grammarBox->ReadOnly = true;
			this->grammarBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->grammarBox->Size = System::Drawing::Size(367, 287);
			this->grammarBox->TabIndex = 0;
			this->grammarBox->TextChanged += gcnew System::EventHandler(this, &MyForm::grammarBox_TextChanged);
			// 
			// matchReportGroup
			// 
			this->matchReportGroup->Controls->Add(this->resultsBox);
			this->matchReportGroup->Dock = System::Windows::Forms::DockStyle::Fill;
			this->matchReportGroup->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->matchReportGroup->Location = System::Drawing::Point(396, 3);
			this->matchReportGroup->Name = L"matchReportGroup";
			this->matchReportGroup->Padding = System::Windows::Forms::Padding(10, 9, 10, 9);
			this->resultsTableLayout->SetRowSpan(this->matchReportGroup, 2);
			this->matchReportGroup->Size = System::Drawing::Size(387, 669);
			this->matchReportGroup->TabIndex = 4;
			this->matchReportGroup->TabStop = false;
			this->matchReportGroup->Text = L"Match Report";
			this->matchReportGroup->Enter += gcnew System::EventHandler(this, &MyForm::matchReportGroup_Enter);
			// 
			// resultsBox
			// 
			this->resultsBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(248)), static_cast<System::Int32>(static_cast<System::Byte>(252)),
				static_cast<System::Int32>(static_cast<System::Byte>(251)));
			this->resultsBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->resultsBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->resultsBox->Font = (gcnew System::Drawing::Font(L"Consolas", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->resultsBox->Location = System::Drawing::Point(10, 36);
			this->resultsBox->Multiline = true;
			this->resultsBox->Name = L"resultsBox";
			this->resultsBox->ReadOnly = true;
			this->resultsBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->resultsBox->Size = System::Drawing::Size(367, 624);
			this->resultsBox->TabIndex = 0;
			this->resultsBox->TextChanged += gcnew System::EventHandler(this, &MyForm::resultsBox_TextChanged);
			// 
			// resultsLabel
			// 
			this->resultsLabel->AutoSize = true;
			this->resultsLabel->Dock = System::Windows::Forms::DockStyle::Top;
			this->resultsLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
			this->resultsLabel->ForeColor = System::Drawing::Color::Green;
			this->resultsLabel->Location = System::Drawing::Point(15, 16);
			this->resultsLabel->Name = L"resultsLabel";
			this->resultsLabel->Padding = System::Windows::Forms::Padding(0, 0, 0, 5);
			this->resultsLabel->Size = System::Drawing::Size(109, 43);
			this->resultsLabel->TabIndex = 0;
			this->resultsLabel->Text = L"Results";
			this->resultsLabel->Click += gcnew System::EventHandler(this, &MyForm::resultsLabel_Click);
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
			this->tabPage2->Padding = System::Windows::Forms::Padding(15, 16, 15, 16);
			this->tabPage2->Size = System::Drawing::Size(816, 750);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Visualization";
			this->tabPage2->Click += gcnew System::EventHandler(this, &MyForm::tabPage2_Click);
			// 
			// pdaTraceBox
			// 
			this->pdaTraceBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(248)), static_cast<System::Int32>(static_cast<System::Byte>(252)),
				static_cast<System::Int32>(static_cast<System::Byte>(251)));
			this->pdaTraceBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pdaTraceBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pdaTraceBox->Font = (gcnew System::Drawing::Font(L"Consolas", 9));
			this->pdaTraceBox->Location = System::Drawing::Point(15, 66);
			this->pdaTraceBox->Multiline = true;
			this->pdaTraceBox->Name = L"pdaTraceBox";
			this->pdaTraceBox->ReadOnly = true;
			this->pdaTraceBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->pdaTraceBox->Size = System::Drawing::Size(786, 666);
			this->pdaTraceBox->TabIndex = 3;
			this->pdaTraceBox->TextChanged += gcnew System::EventHandler(this, &MyForm::pdaTraceBox_TextChanged);
			// 
			// vizPictureBox
			// 
			this->vizPictureBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(248)), static_cast<System::Int32>(static_cast<System::Byte>(252)),
				static_cast<System::Int32>(static_cast<System::Byte>(251)));
			this->vizPictureBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->vizPictureBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->vizPictureBox->Location = System::Drawing::Point(15, 66);
			this->vizPictureBox->Name = L"vizPictureBox";
			this->vizPictureBox->Size = System::Drawing::Size(786, 666);
			this->vizPictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->vizPictureBox->TabIndex = 2;
			this->vizPictureBox->TabStop = false;
			this->vizPictureBox->Click += gcnew System::EventHandler(this, &MyForm::vizPictureBox_Click);
			// 
			// vizToggleGroup
			// 
			this->vizToggleGroup->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->vizToggleGroup->Controls->Add(this->showDfaButton);
			this->vizToggleGroup->Controls->Add(this->showNfaButton);
			this->vizToggleGroup->Location = System::Drawing::Point(460, 3);
			this->vizToggleGroup->Name = L"vizToggleGroup";
			this->vizToggleGroup->Padding = System::Windows::Forms::Padding(0, 9, 0, 9);
			this->vizToggleGroup->Size = System::Drawing::Size(316, 57);
			this->vizToggleGroup->TabIndex = 1;
			this->vizToggleGroup->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::vizToggleGroup_Paint);
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
			this->showDfaButton->Location = System::Drawing::Point(155, 9);
			this->showDfaButton->Name = L"showDfaButton";
			this->showDfaButton->Size = System::Drawing::Size(158, 38);
			this->showDfaButton->TabIndex = 1;
			this->showDfaButton->Text = L"🗺️ Show DFA";
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
			this->showNfaButton->Size = System::Drawing::Size(155, 38);
			this->showNfaButton->TabIndex = 0;
			this->showNfaButton->Text = L"🕸️ Show NFA";
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
			this->vizLabel->Location = System::Drawing::Point(15, 16);
			this->vizLabel->Name = L"vizLabel";
			this->vizLabel->Padding = System::Windows::Forms::Padding(0, 0, 0, 10);
			this->vizLabel->Size = System::Drawing::Size(185, 48);
			this->vizLabel->TabIndex = 0;
			this->vizLabel->Text = L"Visualization";
			this->vizLabel->Click += gcnew System::EventHandler(this, &MyForm::vizLabel_Click_1);
			// 
			// leftPanel
			// 
			this->leftPanel->BackColor = System::Drawing::Color::White;
			this->leftPanel->Controls->Add(this->progressBar);
			this->leftPanel->Controls->Add(this->groupBox2);
			this->leftPanel->Controls->Add(this->groupBox1);
			this->leftPanel->Dock = System::Windows::Forms::DockStyle::Left;
			this->leftPanel->Location = System::Drawing::Point(20, 21);
			this->leftPanel->Name = L"leftPanel";
			this->leftPanel->Padding = System::Windows::Forms::Padding(15, 16, 15, 16);
			this->leftPanel->Size = System::Drawing::Size(729, 798);
			this->leftPanel->TabIndex = 0;
			this->leftPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::leftPanel_Paint);
			// 
			// progressBar
			// 
			this->progressBar->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->progressBar->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(42)), static_cast<System::Int32>(static_cast<System::Byte>(157)),
				static_cast<System::Int32>(static_cast<System::Byte>(143)));
			this->progressBar->Location = System::Drawing::Point(15, 773);
			this->progressBar->MarqueeAnimationSpeed = 30;
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(699, 9);
			this->progressBar->Style = System::Windows::Forms::ProgressBarStyle::Marquee;
			this->progressBar->TabIndex = 2;
			this->progressBar->Visible = false;
			this->progressBar->Click += gcnew System::EventHandler(this, &MyForm::progressBar_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->resetButton);
			this->groupBox2->Controls->Add(this->step2Label);
			this->groupBox2->Controls->Add(this->exportButton);
			this->groupBox2->Controls->Add(this->runButton);
			this->groupBox2->Controls->Add(this->fileInputGroup);
			this->groupBox2->Controls->Add(this->pdaInputTypeGroup);
			this->groupBox2->Controls->Add(this->editDistanceGroup);
			this->groupBox2->Controls->Add(this->patternInputGroup);
			this->groupBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->groupBox2->Location = System::Drawing::Point(15, 155);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Padding = System::Windows::Forms::Padding(15, 16, 15, 16);
			this->groupBox2->Size = System::Drawing::Size(699, 627);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Enter += gcnew System::EventHandler(this, &MyForm::groupBox2_Enter);
			// 
			// resetButton
			// 
			this->resetButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->resetButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->resetButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->resetButton->FlatAppearance->BorderSize = 0;
			this->resetButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->resetButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->resetButton->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(71)));
			this->resetButton->Location = System::Drawing::Point(15, 567);
			this->resetButton->Name = L"resetButton";
			this->resetButton->Size = System::Drawing::Size(170, 37);
			this->resetButton->TabIndex = 7;
			this->resetButton->Text = L"❌ Reset All";
			this->resetButton->UseVisualStyleBackColor = false;
			this->resetButton->Click += gcnew System::EventHandler(this, &MyForm::resetButton_Click);
			this->resetButton->MouseEnter += gcnew System::EventHandler(this, &MyForm::Button_MouseEnter);
			this->resetButton->MouseLeave += gcnew System::EventHandler(this, &MyForm::Button_MouseLeave);
			// 
			// step2Label
			// 
			this->step2Label->AutoSize = true;
			this->step2Label->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
			this->step2Label->ForeColor = System::Drawing::Color::Green;
			this->step2Label->Location = System::Drawing::Point(15, 16);
			this->step2Label->Name = L"step2Label";
			this->step2Label->Size = System::Drawing::Size(292, 32);
			this->step2Label->TabIndex = 5;
			this->step2Label->Text = L"Step 2: Configure Inputs";
			this->step2Label->Click += gcnew System::EventHandler(this, &MyForm::step2Label_Click);
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
			this->runButton->Location = System::Drawing::Point(15, 504);
			this->runButton->Name = L"runButton";
			this->runButton->Size = System::Drawing::Size(669, 51);
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
			this->fileInputGroup->Location = System::Drawing::Point(15, 311);
			this->fileInputGroup->Name = L"fileInputGroup";
			this->fileInputGroup->Padding = System::Windows::Forms::Padding(10, 9, 10, 9);
			this->fileInputGroup->Size = System::Drawing::Size(669, 135);
			this->fileInputGroup->TabIndex = 3;
			this->fileInputGroup->TabStop = false;
			this->fileInputGroup->Enter += gcnew System::EventHandler(this, &MyForm::fileInputGroup_Enter);
			// 
			// supportLabel
			// 
			this->supportLabel->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->supportLabel->AutoSize = true;
			this->supportLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8));
			this->supportLabel->ForeColor = System::Drawing::Color::Gray;
			this->supportLabel->Location = System::Drawing::Point(13, 97);
			this->supportLabel->Name = L"supportLabel";
			this->supportLabel->Size = System::Drawing::Size(198, 21);
			this->supportLabel->TabIndex = 3;
			this->supportLabel->Text = L"Supports: .txt, .fa, .fasta files";
			this->supportLabel->Click += gcnew System::EventHandler(this, &MyForm::supportLabel_Click);
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
			this->browseButton->Location = System::Drawing::Point(536, 56);
			this->browseButton->Name = L"browseButton";
			this->browseButton->Size = System::Drawing::Size(115, 36);
			this->browseButton->TabIndex = 2;
			this->browseButton->Text = L"📂 Browse";
			this->browseButton->UseVisualStyleBackColor = false;
			this->browseButton->Click += gcnew System::EventHandler(this, &MyForm::browseButton_Click);
			this->browseButton->MouseEnter += gcnew System::EventHandler(this, &MyForm::Button_MouseEnter);
			this->browseButton->MouseLeave += gcnew System::EventHandler(this, &MyForm::Button_MouseLeave);
			// 
			// fileInputBox
			// 
			this->fileInputBox->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->fileInputBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(248)), static_cast<System::Int32>(static_cast<System::Byte>(252)),
				static_cast<System::Int32>(static_cast<System::Byte>(251)));
			this->fileInputBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->fileInputBox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->fileInputBox->Location = System::Drawing::Point(15, 58);
			this->fileInputBox->Name = L"fileInputBox";
			this->fileInputBox->ReadOnly = true;
			this->fileInputBox->Size = System::Drawing::Size(516, 34);
			this->fileInputBox->TabIndex = 1;
			this->fileInputBox->TextChanged += gcnew System::EventHandler(this, &MyForm::fileInputBox_TextChanged);
			// 
			// fileInputLabel
			// 
			this->fileInputLabel->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->fileInputLabel->AutoSize = true;
			this->fileInputLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->fileInputLabel->Location = System::Drawing::Point(13, 23);
			this->fileInputLabel->Name = L"fileInputLabel";
			this->fileInputLabel->Size = System::Drawing::Size(101, 28);
			this->fileInputLabel->TabIndex = 0;
			this->fileInputLabel->Text = L"Input File";
			this->fileInputLabel->Click += gcnew System::EventHandler(this, &MyForm::fileInputLabel_Click);
			// 
			// pdaInputTypeGroup
			// 
			this->pdaInputTypeGroup->Controls->Add(this->sourceInputLabel);
			this->pdaInputTypeGroup->Controls->Add(this->pdaFileRadio);
			this->pdaInputTypeGroup->Controls->Add(this->pdaStringRadio);
			this->pdaInputTypeGroup->Dock = System::Windows::Forms::DockStyle::Top;
			this->pdaInputTypeGroup->Location = System::Drawing::Point(15, 233);
			this->pdaInputTypeGroup->Name = L"pdaInputTypeGroup";
			this->pdaInputTypeGroup->Padding = System::Windows::Forms::Padding(10, 9, 10, 9);
			this->pdaInputTypeGroup->Size = System::Drawing::Size(669, 78);
			this->pdaInputTypeGroup->TabIndex = 2;
			this->pdaInputTypeGroup->TabStop = false;
			this->pdaInputTypeGroup->Enter += gcnew System::EventHandler(this, &MyForm::pdaInputTypeGroup_Enter);
			// 
			// sourceInputLabel
			// 
			this->sourceInputLabel->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->sourceInputLabel->AutoSize = true;
			this->sourceInputLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->sourceInputLabel->Location = System::Drawing::Point(11, 29);
			this->sourceInputLabel->Name = L"sourceInputLabel";
			this->sourceInputLabel->Size = System::Drawing::Size(137, 28);
			this->sourceInputLabel->TabIndex = 2;
			this->sourceInputLabel->Text = L"Input Source:";
			this->sourceInputLabel->Click += gcnew System::EventHandler(this, &MyForm::sourceInputLabel_Click);
			// 
			// pdaFileRadio
			// 
			this->pdaFileRadio->AutoSize = true;
			this->pdaFileRadio->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pdaFileRadio->Location = System::Drawing::Point(322, 30);
			this->pdaFileRadio->Name = L"pdaFileRadio";
			this->pdaFileRadio->Size = System::Drawing::Size(130, 30);
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
			this->pdaStringRadio->Location = System::Drawing::Point(166, 30);
			this->pdaStringRadio->Name = L"pdaStringRadio";
			this->pdaStringRadio->Size = System::Drawing::Size(150, 30);
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
			this->editDistanceGroup->Location = System::Drawing::Point(15, 158);
			this->editDistanceGroup->Name = L"editDistanceGroup";
			this->editDistanceGroup->Padding = System::Windows::Forms::Padding(10, 9, 10, 9);
			this->editDistanceGroup->Size = System::Drawing::Size(669, 75);
			this->editDistanceGroup->TabIndex = 1;
			this->editDistanceGroup->TabStop = false;
			this->editDistanceGroup->Enter += gcnew System::EventHandler(this, &MyForm::editDistanceGroup_Enter);
			// 
			// editDistanceInput
			// 
			this->editDistanceInput->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(248)),
				static_cast<System::Int32>(static_cast<System::Byte>(252)), static_cast<System::Int32>(static_cast<System::Byte>(251)));
			this->editDistanceInput->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->editDistanceInput->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11));
			this->editDistanceInput->Location = System::Drawing::Point(232, 26);
			this->editDistanceInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->editDistanceInput->Name = L"editDistanceInput";
			this->editDistanceInput->Size = System::Drawing::Size(80, 37);
			this->editDistanceInput->TabIndex = 1;
			this->editDistanceInput->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->editDistanceInput->ValueChanged += gcnew System::EventHandler(this, &MyForm::editDistanceInput_ValueChanged);
			// 
			// distanceLabel
			// 
			this->distanceLabel->AutoSize = true;
			this->distanceLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->distanceLabel->Location = System::Drawing::Point(26, 29);
			this->distanceLabel->Name = L"distanceLabel";
			this->distanceLabel->Size = System::Drawing::Size(173, 28);
			this->distanceLabel->TabIndex = 0;
			this->distanceLabel->Text = L"Edit Distance (k):";
			this->distanceLabel->Click += gcnew System::EventHandler(this, &MyForm::distanceLabel_Click);
			// 
			// patternInputGroup
			// 
			this->patternInputGroup->Controls->Add(this->patternLabel);
			this->patternInputGroup->Controls->Add(this->patternInputBox);
			this->patternInputGroup->Dock = System::Windows::Forms::DockStyle::Top;
			this->patternInputGroup->Location = System::Drawing::Point(15, 40);
			this->patternInputGroup->Name = L"patternInputGroup";
			this->patternInputGroup->Padding = System::Windows::Forms::Padding(10, 9, 10, 9);
			this->patternInputGroup->Size = System::Drawing::Size(669, 118);
			this->patternInputGroup->TabIndex = 0;
			this->patternInputGroup->TabStop = false;
			this->patternInputGroup->Enter += gcnew System::EventHandler(this, &MyForm::patternInputGroup_Enter);
			// 
			// patternLabel
			// 
			this->patternLabel->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->patternLabel->AutoSize = true;
			this->patternLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->patternLabel->Location = System::Drawing::Point(11, 24);
			this->patternLabel->Name = L"patternLabel";
			this->patternLabel->Size = System::Drawing::Size(282, 28);
			this->patternLabel->TabIndex = 1;
			this->patternLabel->Text = L"Pattern (Regular Expression)";
			this->patternLabel->Click += gcnew System::EventHandler(this, &MyForm::patternLabel_Click);
			// 
			// patternInputBox
			// 
			this->patternInputBox->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->patternInputBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(248)), static_cast<System::Int32>(static_cast<System::Byte>(252)),
				static_cast<System::Int32>(static_cast<System::Byte>(251)));
			this->patternInputBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->patternInputBox->Font = (gcnew System::Drawing::Font(L"Consolas", 11));
			this->patternInputBox->Location = System::Drawing::Point(17, 65);
			this->patternInputBox->Name = L"patternInputBox";
			this->patternInputBox->Size = System::Drawing::Size(635, 33);
			this->patternInputBox->TabIndex = 0;
			this->patternInputBox->TextChanged += gcnew System::EventHandler(this, &MyForm::patternInputBox_TextChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->sim3Label);
			this->groupBox1->Controls->Add(this->sim2Label);
			this->groupBox1->Controls->Add(this->sim1Label);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->pdaRadio);
			this->groupBox1->Controls->Add(this->approxRadio);
			this->groupBox1->Controls->Add(this->regexRadio);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Top;
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->groupBox1->Location = System::Drawing::Point(15, 16);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(15, 16, 15, 16);
			this->groupBox1->Size = System::Drawing::Size(699, 139);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Enter += gcnew System::EventHandler(this, &MyForm::groupBox1_Enter);
			// 
			// sim3Label
			// 
			this->sim3Label->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->sim3Label->AutoSize = true;
			this->sim3Label->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->sim3Label->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->sim3Label->Location = System::Drawing::Point(477, 97);
			this->sim3Label->Name = L"sim3Label";
			this->sim3Label->Size = System::Drawing::Size(222, 21);
			this->sim3Label->TabIndex = 6;
			this->sim3Label->Text = L"Check nested structures (PDA).";
			this->sim3Label->Click += gcnew System::EventHandler(this, &MyForm::sim3Label_Click);
			// 
			// sim2Label
			// 
			this->sim2Label->AutoSize = true;
			this->sim2Label->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->sim2Label->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->sim2Label->Location = System::Drawing::Point(249, 97);
			this->sim2Label->Name = L"sim2Label";
			this->sim2Label->Size = System::Drawing::Size(199, 21);
			this->sim2Label->TabIndex = 5;
			this->sim2Label->Text = L"Find \"fuzzy\" patterns (NFA).";
			this->sim2Label->Click += gcnew System::EventHandler(this, &MyForm::sim2Label_Click);
			// 
			// sim1Label
			// 
			this->sim1Label->AutoSize = true;
			this->sim1Label->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->sim1Label->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->sim1Label->Location = System::Drawing::Point(32, 96);
			this->sim1Label->Name = L"sim1Label";
			this->sim1Label->Size = System::Drawing::Size(185, 21);
			this->sim1Label->TabIndex = 4;
			this->sim1Label->Text = L"Find exact patterns (DFA).";
			this->sim1Label->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
			this->label1->ForeColor = System::Drawing::Color::Green;
			this->label1->Location = System::Drawing::Point(15, 16);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(356, 32);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Step 1: Select Simulation Type";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// pdaRadio
			// 
			this->pdaRadio->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->pdaRadio->AutoSize = true;
			this->pdaRadio->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pdaRadio->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->pdaRadio->Location = System::Drawing::Point(476, 60);
			this->pdaRadio->Name = L"pdaRadio";
			this->pdaRadio->Size = System::Drawing::Size(219, 34);
			this->pdaRadio->TabIndex = 2;
			this->pdaRadio->Text = L"Structural Validation";
			this->pdaRadio->UseVisualStyleBackColor = true;
			this->pdaRadio->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Radio_CheckedChanged);
			// 
			// approxRadio
			// 
			this->approxRadio->AutoSize = true;
			this->approxRadio->Cursor = System::Windows::Forms::Cursors::Hand;
			this->approxRadio->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->approxRadio->Location = System::Drawing::Point(238, 61);
			this->approxRadio->Name = L"approxRadio";
			this->approxRadio->Size = System::Drawing::Size(216, 34);
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
			this->regexRadio->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->regexRadio->Location = System::Drawing::Point(20, 60);
			this->regexRadio->Name = L"regexRadio";
			this->regexRadio->Size = System::Drawing::Size(208, 34);
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
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->Filter = L"Text File (*.txt)|*.txt";
			this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::saveFileDialog1_FileOk);
			// 
			// animationTimer
			// 
			this->animationTimer->Interval = 50;
			this->animationTimer->Tick += gcnew System::EventHandler(this, &MyForm::animationTimer_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 21);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(1603, 945);
			this->Controls->Add(this->mainContainer);
			this->Controls->Add(this->headerPanel);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MinimumSize = System::Drawing::Size(1196, 691);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"TOPIC 3: TEXT SEARCH ENGINE AND BIOINFORMATICS - Babuyo, Bao, Gamalo, Noval, Suel"
				L"o (CS3B) ";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->headerPanel->ResumeLayout(false);
			this->headerPanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->logoPictureBox))->EndInit();
			this->mainContainer->ResumeLayout(false);
			this->rightPanel->ResumeLayout(false);
			this->outputTabControl->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->resultsTableLayout->ResumeLayout(false);
			this->summaryGroup->ResumeLayout(false);
			this->summaryGroup->PerformLayout();
			this->grammarGroup->ResumeLayout(false);
			this->grammarGroup->PerformLayout();
			this->matchReportGroup->ResumeLayout(false);
			this->matchReportGroup->PerformLayout();
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

		// [UPDATED] Applies theme: Green (Run), Neon Yellow (Export), Orange (Error)
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

			// 3. COLOR VARIABLES
			System::Drawing::Color deepScienceGreen = System::Drawing::Color::FromArgb(29, 98, 58);   // #1D623A
			System::Drawing::Color neonYellow = System::Drawing::Color::FromArgb(246, 255, 1);        // #F6FF01
			System::Drawing::Color alertLime = System::Drawing::Color::FromArgb(140, 190, 40);       // Lime
			System::Drawing::Color resetDarkGray = System::Drawing::Color::FromArgb(80, 80, 80);        // Dark Gray

			// 4. Apply Colors

			// Run Simulation & Browse (Green)
			this->runButton->BackColor = deepScienceGreen;
			this->runButton->ForeColor = System::Drawing::Color::White;
			this->browseButton->BackColor = deepScienceGreen;
			this->browseButton->ForeColor = System::Drawing::Color::White;

			// Export Full Report 
			this->exportButton->BackColor = alertLime;
			this->exportButton->ForeColor = System::Drawing::Color::White;

			// Visualization Toggles (Green)
			this->showNfaButton->BackColor = deepScienceGreen;
			this->showDfaButton->BackColor = System::Drawing::Color::FromArgb(220, 230, 220);
			this->showNfaButton->ForeColor = System::Drawing::Color::White;
			this->showDfaButton->ForeColor = System::Drawing::Color::Black;

			// Reset Button (Dark Gray)
			this->resetButton->BackColor = resetDarkGray;
			this->resetButton->ForeColor = System::Drawing::Color::White;
		}

		void Button_MouseEnter(Object^ sender, EventArgs^ e) {
			Button^ btn = safe_cast<Button^>(sender);
			Color currentColor = btn->BackColor;

			if (btn == exportButton) {
				// Darken instead of brighten for better visibility
				btn->BackColor = Color::FromArgb(120, 170, 20);
			}
			else {
				// Original brightening logic for other buttons
				int r = Math::Min(255, currentColor.R + 20);
				int g = Math::Min(255, currentColor.G + 20);
				int b = Math::Min(255, currentColor.B + 20);
				btn->BackColor = Color::FromArgb(r, g, b);
			}
		}

		// [UPDATED] Restores specific colors correctly on mouse leave
		void Button_MouseLeave(Object^ sender, EventArgs^ e) {
			Button^ btn = safe_cast<Button^>(sender);

			System::Drawing::Color deepScienceGreen = System::Drawing::Color::FromArgb(29, 98, 58);
			System::Drawing::Color neonYellow = System::Drawing::Color::FromArgb(246, 255, 1);
			System::Drawing::Color alertLime = System::Drawing::Color::FromArgb(140, 190, 40); 
			System::Drawing::Color resetDarkGray = System::Drawing::Color::FromArgb(80, 80, 80);

			if (btn == runButton || btn == browseButton) {
				btn->BackColor = deepScienceGreen;
			}
			else if (btn == exportButton) {
				btn->BackColor = alertLime;
			}
			else if (btn == resetButton) {
				btn->BackColor = resetDarkGray;
			}
			else if (btn == showNfaButton) {
				if (showNfaButton->ForeColor == Color::White) {
					btn->BackColor = deepScienceGreen;
				}
				else {
					btn->BackColor = System::Drawing::Color::FromArgb(220, 230, 220);
				}
			}
			else if (btn == showDfaButton) {
				if (showDfaButton->ForeColor == Color::White) {
					btn->BackColor = deepScienceGreen;
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

		// *** THIS IS THE CORRECT, UNIQUE DEFINITION ***
		System::String^ ToNetString(const std::string& utf8String) {
			// FIX: Correctly marshal UTF-8 std::string to System::String (Unicode/UTF-16).
			if (utf8String.empty()) {
				return String::Empty;
			}
			// 1. Get the UTF-8 bytes from the std::string
			array<unsigned char>^ bytes = gcnew array<unsigned char>((int)utf8String.length());
			for (int i = 0; i < utf8String.length(); i++)
				bytes[i] = (unsigned char)utf8String[i];

			// 2. Decode the bytes explicitly using UTF8 encoding
			return System::Text::Encoding::UTF8->GetString(bytes);
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
				this->patternInputBox->Text = "AGTC";
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
			System::String^ msg = ToNetString(error_message);
			MessageBox::Show(msg, "Simulation Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
				this->resultsLabel->Text = "Results";
				this->vizLabel->Text = "Visualization (NFA/DFA)";
				this->summaryGroup->Text = "Regex Search Paramaters";
				this->summaryGroup->Visible = true;
				this->matchReportGroup->Text = "Exact Match Results";
				this->matchReportGroup->Visible = true;
				this->grammarGroup->Text = "DFA Construction";
				this->grammarGroup->Visible = true;

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
				this->resultsLabel->Text = "Results";
				this->vizLabel->Text = "Visualization (NFA)";
				this->summaryGroup->Text = "Fuzzy Search Parameters";
				this->summaryGroup->Visible = true;
				this->grammarGroup->Text = "Levenshtein Automaton";
				this->grammarGroup->Visible = true;
				this->matchReportGroup->Text = "Approximate Match Results";
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
				this->resultsLabel->Text = "Results";
				this->vizLabel->Text = "Visualization (PDA Trace)";
				this->summaryGroup->Text = "Structure Validation Parameters";
				this->matchReportGroup->Text = "Validation Results";
				this->matchReportGroup->Visible = true;
				this->grammarGroup->Text = "PDA Configuration";
				this->grammarGroup->Visible = true;

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

		// [UPDATED - PERFECT GUI MATCH LAYOUT] Exports HTML with dynamic section names matching the GUI
		System::Void exportButton_Click(System::Object^ sender, System::EventArgs^ e) {
			// 1. Simple check: Don't export if nothing has run.
			bool hasResults =
				!String::IsNullOrWhiteSpace(this->summaryBox->Text) ||
				!String::IsNullOrWhiteSpace(this->grammarBox->Text) ||
				!String::IsNullOrWhiteSpace(this->resultsBox->Text) ||
				!String::IsNullOrWhiteSpace(this->pdaTraceBox->Text) ||
				this->vizPictureBox->Image != nullptr;

			if (!hasResults) {
				MessageBox::Show("Please run a simulation before exporting.", "Nothing to Export", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			System::String^ timestamp = System::DateTime::Now.ToString("yyyy-MM-dd HH:mm:ss");

			// 2. Start building the HTML string
			System::Text::StringBuilder^ html = gcnew System::Text::StringBuilder();

			// --- HTML HEAD & CSS STYLING ---
			html->Append("<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><title>GenoSearch Report</title>");
			// Use Segoe UI font to match the application
			html->Append("<link href='https://fonts.googleapis.com/css2?family=Segoe+UI:wght@300;400;600;700&display=swap' rel='stylesheet'>");
			html->Append("<style>");
			html->Append("body { font-family: 'Segoe UI', Roboto, Helvetica, Arial, sans-serif; line-height: 1.6; color: #333; background-color: #FAFCFA; margin: 0; padding: 0; }");
			html->Append(".container { max-width: 950px; margin: 30px auto; background: #fff; box-shadow: 0 4px 15px rgba(0,0,0,0.1); border-radius: 8px; overflow: hidden; }");

			// --- ACCURATE HEADER CSS ---
			// Use flexbox to separate left (logo+titles) and right (report info) sections.
			html->Append(".header { background: linear-gradient(to right, #0F321E, #8CBE28); color: white; padding: 25px 30px; display: flex; align-items: center; justify-content: space-between; }");

			// --- Left Section: Logo & Title Block ---
			html->Append(".header-left { display: flex; align-items: center; }");
			html->Append(".logo-img { height: 50px; width: auto; margin-right: 15px; }");
			// Fallback CSS logo
			html->Append(".logo-icon-css { width: 42px; height: 42px; background: #F6FF01; border-radius: 8px; display: flex; align-items: center; justify-content: center; margin-right: 15px; box-shadow: 0 2px 5px rgba(0,0,0,0.2); }");
			html->Append(".logo-text-g { color: #0F321E; font-size: 28px; font-weight: 900; font-family: sans-serif; }");

			// NEW: Block to stack title and subtitle vertically
			html->Append(".title-block { display: flex; flex-direction: column; justify-content: center; }");
			// Main Title styling
			html->Append(".logo-title { font-size: 24px; font-weight: 700; letter-spacing: 0.5px; margin: 0; line-height: 1.1; color: #ffffff; }");
			// Subtitle styling - placed directly below
			html->Append(".app-subtitle { font-size: 14px; font-weight: 400; margin: 3px 0 0 0; color: rgba(255,255,255,0.85); }");

			// --- Right Section: Report Info ---
			// text-align: right. white-space: nowrap prevents wrapping.
			html->Append(".header-right { text-align: right; white-space: nowrap; margin-left: 20px; }");
			html->Append(".report-title { font-size: 14px; font-weight: 600; margin: 0; text-transform: uppercase; letter-spacing: 1px; opacity: 0.9; }");
			html->Append(".timestamp { font-size: 13px; opacity: 0.8; font-weight: 400; margin: 3px 0 0 0; }");


			// --- Content Styling (Rest remains same) ---
			html->Append(".content { padding: 40px; }");
			html->Append("h2 { color: #0F321E; border-bottom: 3px solid #F6FF01; padding-bottom: 10px; margin-top: 40px; font-size: 1.6em; }");
			html->Append("h2:first-child { margin-top: 0; }");

			// Data boxes
			html->Append(".data-box { background: #f8f9fa; border: 1px solid #e9ecef; border-left: 5px solid #0F321E; padding: 15px 20px; border-radius: 4px; font-family: 'Consolas', 'Courier New', monospace; white-space: pre-wrap; word-wrap: break-word; overflow-x: auto; font-size: 0.95em;}");
			html->Append("ul.inputs-list { list-style-type: none; padding: 0; }");
			html->Append("ul.inputs-list li { margin-bottom: 12px; padding-left: 25px; position: relative; font-size: 1.05em; }");
			html->Append("ul.inputs-list li::before { content: '•'; color: #F6FF01; font-weight: bold; font-size: 1.2em; position: absolute; left: 0; top: 1px; text-shadow: 1px 1px 1px rgba(0,0,0,0.2); }");
			html->Append("strong { color: #0F321E; }");

			// Visualization Image container
			html->Append(".viz-container { text-align: center; margin-top: 25px; padding: 30px; background: #ffffff; border: 2px solid #eee; border-radius: 8px; box-shadow: inset 0 0 20px rgba(0,0,0,0.05); }");
			html->Append(".viz-img { max-width: 100%; height: auto; box-shadow: 0 4px 12px rgba(0,0,0,0.15); border-radius: 4px; }");
			html->Append("</style></head><body>");

			// --- HTML BODY CONTENT ---
			html->Append("<div class='container'>");

			// --- ACCURATE HEADER STRUCTURE ---
			html->Append("<div class='header'>");

			// --- LOGO LOADING LOGIC ---
			String^ logoBase64 = "";
			try {
				// Look for "GenoSearch Logo White.png" in the same folder as your application .exe
				String^ logoPath = System::IO::Path::Combine(System::Windows::Forms::Application::StartupPath, "GenoSearch Logo White.png");
				if (System::IO::File::Exists(logoPath)) {
					System::Drawing::Image^ logoImg = System::Drawing::Image::FromFile(logoPath);
					// Use our helper function to convert it to base64 string
					logoBase64 = ImageToBase64(logoImg);
					delete logoImg; // Clean up memory
				}
			}
			catch (Exception^ ex) {
				// If loading fails, we'll just use the fallback CSS logo.
			}
			// --------------------------

			// 1. Left Section: Logo and Title Block
			html->Append("<div class='header-left'>");
			if (!String::IsNullOrEmpty(logoBase64)) {
				// Embed YOUR logo image
				html->Append("<img class='logo-img' src='data:image/png;base64," + logoBase64 + "' alt='GenoSearch Logo' />");
			}
			else {
				// Fallback to the CSS "G" icon if logo is missing
				html->Append("<div class='logo-icon-css'><span class='logo-text-g'>G</span></div>");
			}

			// NEW: Title Block for stacking
			html->Append("<div class='title-block'>");
			html->Append("<div class='logo-title'>GenoSearch | Automata-Powered Pattern Recognition</div>");
			html->Append("<p class='app-subtitle'>A Unified Simulator for Formal Languages.</p>");
			html->Append("</div>"); // end title-block

			html->Append("</div>"); // end header-left

			// 2. Right Section: Report Info
			html->Append("<div class='header-right'>");
			html->Append("<p class='report-title'>Full Report</p>");
			html->Append("<p class='timestamp'>" + timestamp + "</p>");
			html->Append("</div>"); // end header-right

			html->Append("</div>"); // end header

			html->Append("<div class='content'>");

			// 2. Input Configuration Section
			html->Append("<h2>Input Configuration</h2><ul class='inputs-list'>");
			html->Append("<li><strong>Simulation Mode:</strong> " + this->resultsLabel->Text + "</li>");
			if (this->regexRadio->Checked || this->approxRadio->Checked || (this->pdaRadio->Checked && this->pdaStringRadio->Checked)) {
				html->Append("<li><strong>Pattern/String:</strong> " + System::Web::HttpUtility::HtmlEncode(this->patternInputBox->Text) + "</li>");
			}
			if (this->fileInputGroup->Visible) {
				html->Append("<li><strong>Input File path:</strong> " + System::Web::HttpUtility::HtmlEncode(this->fileInputBox->Text) + "</li>");
			}
			if (this->editDistanceGroup->Visible) {
				html->Append("<li><strong>Edit Distance (k):</strong> " + this->editDistanceInput->Value.ToString() + "</li>");
			}
			html->Append("</ul>");

			// 3. Results Text Sections - USING DYNAMIC NAMES FROM GROUP BOXES
			if (!String::IsNullOrWhiteSpace(this->summaryBox->Text)) {
				html->Append("<h2>" + System::Web::HttpUtility::HtmlEncode(this->summaryGroup->Text) + "</h2>");
				html->Append("<div class='data-box'>" + System::Web::HttpUtility::HtmlEncode(this->summaryBox->Text) + "</div>");
			}
			if (!String::IsNullOrWhiteSpace(this->grammarBox->Text)) {
				html->Append("<h2>" + System::Web::HttpUtility::HtmlEncode(this->grammarGroup->Text) + "</h2>");
				html->Append("<div class='data-box'>" + System::Web::HttpUtility::HtmlEncode(this->grammarBox->Text) + "</div>");
			}

			// Decide whether to show PDA Trace or standard Match Report
			if (!String::IsNullOrWhiteSpace(this->pdaTraceBox->Text) && this->pdaTraceBox->Visible) {
				html->Append("<h2>PDA Validation Trace</h2>");
				html->Append("<div class='data-box'>" + System::Web::HttpUtility::HtmlEncode(this->pdaTraceBox->Text) + "</div>");
			}
			else if (!String::IsNullOrWhiteSpace(this->resultsBox->Text)) {
				html->Append("<h2>" + System::Web::HttpUtility::HtmlEncode(this->matchReportGroup->Text) + "</h2>");
				html->Append("<div class='data-box'>" + System::Web::HttpUtility::HtmlEncode(this->resultsBox->Text) + "</div>");
			}

			// 4. Visualization Image Section
			if (this->regexRadio->Checked) {
				html->Append("<h2>Visualizations</h2>");

				// --- BLOCK 1: Export NFA ---
				if (!String::IsNullOrEmpty(this->m_nfaDot)) {
					std::string error_msg, fallback_str;
					std::string tempFileName = "temp_export_nfa.png";
					// Generate PNG from NFA DOT data
					if (GenoSearchEngine::GenerateGraphvizImage(ToStdString(this->m_nfaDot), tempFileName, error_msg, fallback_str)) {
						try {
							// Load the temp image
							System::Drawing::Image^ img = System::Drawing::Image::FromFile(ToNetString(tempFileName));
							// Convert to Base64
							String^ imgBase64 = ImageToBase64(img);
							delete img; // Unlock file
							if (!String::IsNullOrEmpty(imgBase64)) {
								// Add HTML
								html->Append("<h3>NFA (Non-deterministic Finite Automaton)</h3>");
								html->Append("<div class='viz-container'>");
								html->Append("<img class='viz-img' src='data:image/png;base64," + imgBase64 + "' alt='NFA Visualization' />");
								html->Append("</div>");
							}
							// Delete temp file
							System::IO::File::Delete(ToNetString(tempFileName));
						}
						catch (...) { /* Silently fail if image loading messed up */ }
					}
				}

				// --- BLOCK 2: Export DFA ---
				if (!String::IsNullOrEmpty(this->m_dfaDot)) {
					std::string error_msg, fallback_str;
					std::string tempFileName = "temp_export_dfa.png";
					// Generate PNG from DFA DOT data
					if (GenoSearchEngine::GenerateGraphvizImage(ToStdString(this->m_dfaDot), tempFileName, error_msg, fallback_str)) {
						try {
							// Load the temp image
							System::Drawing::Image^ img = System::Drawing::Image::FromFile(ToNetString(tempFileName));
							// Convert to Base64
							String^ imgBase64 = ImageToBase64(img);
							delete img; // Unlock file
							if (!String::IsNullOrEmpty(imgBase64)) {
								// Add HTML
								html->Append("<h3>DFA (Deterministic Finite Automaton)</h3>");
								html->Append("<div class='viz-container'>");
								html->Append("<img class='viz-img' src='data:image/png;base64," + imgBase64 + "' alt='DFA Visualization' />");
								html->Append("</div>");
							}
							// Delete temp file
							System::IO::File::Delete(ToNetString(tempFileName));
						}
						catch (...) { /* Silently fail if image loading messed up */ }
					}
				}
			}
			// --- APPROXIMATE MATCH MODE: Export the single displayed NFA ---
			else if (this->approxRadio->Checked) {
				html->Append("<h2>Visualization (Levenshtein NFA)</h2>");

				// Try to export the current NFA visualization
				if (!String::IsNullOrEmpty(this->m_nfaDot)) {
					std::string error_msg, fallback_str;
					std::string tempFileName = "temp_export_approx_nfa.png";

					// Generate PNG from NFA DOT data
					if (GenoSearchEngine::GenerateGraphvizImage(ToStdString(this->m_nfaDot), tempFileName, error_msg, fallback_str)) {
						try {
							// Load the temp image
							System::Drawing::Image^ img = System::Drawing::Image::FromFile(ToNetString(tempFileName));
							// Convert to Base64
							String^ imgBase64 = ImageToBase64(img);
							delete img; // Unlock file

							if (!String::IsNullOrEmpty(imgBase64)) {
								html->Append("<div class='viz-container'>");
								html->Append("<img class='viz-img' src='data:image/png;base64," + imgBase64 + "' alt='Levenshtein NFA Visualization' />");
								html->Append("</div>");

								// Add explanation
								html->Append("<div style='margin-top: 15px; padding: 15px; background: #f8f9fa; border-radius: 5px;'>");
								html->Append("<h4>Levenshtein NFA Symbols:</h4>");
								html->Append("<ul style='margin: 0;'>");
								html->Append("<li><strong>Exact match</strong>: Correct character → same error count</li>");
								html->Append("<li><strong>sub(*)</strong>: Substitution → errors + 1</li>");
								html->Append("<li><strong>ins(+)</strong>: Insertion → errors + 1</li>");
								html->Append("<li><strong>ε</strong>: Deletion → errors + 1</li>");
								html->Append("</ul></div>");
							}
							// Delete temp file
							System::IO::File::Delete(ToNetString(tempFileName));
						}
						catch (...) {
							// Fallback if image generation fails
							html->Append("<div class='data-box'>NFA visualization generation failed. DOT content:<br/>" +
								System::Web::HttpUtility::HtmlEncode(this->m_nfaDot) + "</div>");
						}
					}
					else {
						// Fallback: Show DOT content as text
						html->Append("<div class='data-box'>NFA visualization generation failed. DOT content:<br/>" +
							System::Web::HttpUtility::HtmlEncode(this->m_nfaDot) + "</div>");
					}
				}
				else {
					html->Append("<div class='data-box'>No NFA visualization data available.</div>");
				}
			}

			html->Append("</div>"); // end content
			html->Append("</div>"); // end container
			html->Append("</body></html>");

			// 3. Save the final HTML string to a file
			SaveHTMLFile(html->ToString());
		}

		// *** MODIFICATION: Updated active color to Deep Green ***
		System::Void showNfaButton_Click(System::Object^ sender, System::EventArgs^ e) {
			System::Drawing::Color deepScienceGreen = System::Drawing::Color::FromArgb(29, 98, 58);

			this->showNfaButton->BackColor = deepScienceGreen; // Active
			this->showNfaButton->ForeColor = Color::White;
			this->showDfaButton->BackColor = Color::FromArgb(220, 230, 220); // Inactive
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

		// *** MODIFICATION: Updated active color to Deep Green ***
		System::Void showDfaButton_Click(System::Object^ sender, System::EventArgs^ e) {
			System::Drawing::Color deepScienceGreen = System::Drawing::Color::FromArgb(29, 98, 58);

			this->showNfaButton->BackColor = Color::FromArgb(220, 230, 220); // Inactive
			this->showNfaButton->ForeColor = Color::Black;
			this->showDfaButton->BackColor = deepScienceGreen; // Active
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
	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void titleLabel_Click(System::Object^ sender, System::EventArgs^ e) {
}
	   // [UPDATED HELPER] Safer version that clones the image to avoid GDI+ locking issues
	   System::String^ ImageToBase64(System::Drawing::Image^ image) {
		   if (image == nullptr) return "";
		   try {
			   // Create a temporary clone of the image to avoid GDI+ locking conflicts
			   // when saving an image that is currently displayed on screen.
			   System::Drawing::Image^ tempImage = (System::Drawing::Image^)image->Clone();
			   System::IO::MemoryStream^ ms = gcnew System::IO::MemoryStream();
			   // Save the clone to memory stream as PNG
			   tempImage->Save(ms, System::Drawing::Imaging::ImageFormat::Png);
			   delete tempImage; // Clean up the clone immediately

			   array<Byte>^ imageBytes = ms->ToArray();
			   System::String^ base64String = Convert::ToBase64String(imageBytes);
			   delete ms;
			   return base64String;
		   }
		   catch (Exception^ e) {
			   // If image encoding fails, return empty string so HTML doesn't break
			   MessageBox::Show("Warning: Could not encode visualization image for export.\n" + e->Message);
			   return "";
		   }
	   }

	   // [NEW HELPER] Saves the final HTML string to a file
	   void SaveHTMLFile(System::String^ content) {
		   SaveFileDialog^ sfd = gcnew SaveFileDialog();
		   sfd->Filter = "HTML Web Page (*.html)|*.html";
		   sfd->Title = "Export Full Report as HTML";
		   sfd->FileName = "GenoSearch_Report";

		   if (sfd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			   try {
				   // Use UTF8 encoding so special characters work
				   StreamWriter^ sw = gcnew StreamWriter(sfd->FileName, false, System::Text::Encoding::UTF8);
				   sw->Write(content);
				   sw->Close();
				   MessageBox::Show("Full report exported successfully!\n\nYou can open this file in any web browser.", "Success",
					   MessageBoxButtons::OK, MessageBoxIcon::Information);
			   }
			   catch (Exception^ e) {
				   MessageBox::Show("Error saving HTML report:\n" + e->Message, "Export Error",
					   MessageBoxButtons::OK, MessageBoxIcon::Error);
			   }
		   }
		   delete sfd;
	   }
private: System::Void matchReportGroup_Enter(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void headerPanel_Paint_1(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
}
private: System::Void mainContainer_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
}
private: System::Void rightPanel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
}
private: System::Void outputTabControl_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void tabPage1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void resultsTableLayout_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
}
private: System::Void summaryGroup_Enter(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void grammarGroup_Enter(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void grammarBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void resultsBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void summaryBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void resultsLabel_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void tabPage2_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void pdaTraceBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void vizPictureBox_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void vizToggleGroup_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
}
private: System::Void vizLabel_Click_1(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void leftPanel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
}
private: System::Void progressBar_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void groupBox2_Enter(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void step2Label_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void fileInputGroup_Enter(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void supportLabel_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void fileInputBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void fileInputLabel_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void pdaInputTypeGroup_Enter(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void sourceInputLabel_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void editDistanceGroup_Enter(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void editDistanceInput_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void distanceLabel_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void patternInputGroup_Enter(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void patternLabel_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void patternInputBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void groupBox1_Enter(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void sim3Label_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void sim2Label_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void openFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
}
private: System::Void saveFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
}
private: System::Void animationTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
}
};
}