/*
 * MyForm.h (Completely Corrected v4)
 *
 * This version fixes:
 * 1.  E0135: Corrected 'Visible.set(false)' to 'Visible = false'.
 * 2.  All layout and scrolling issues.
 */
#pragma once

 // --- 1. C++ ENGINE INCLUDES ---
#include "automaton_logic.h" // Your C++ engine "menu"
#include <msclr/marshal_cppstd.h> // For string conversion
#include <sstream>      // For std::stringstream (used in helpers)
#include <fstream>      // For std::ofstream (used in export)
#include <cstdlib>      // For system() call

// This namespace MUST match your project's name
namespace GenoSearch {

	// --- 2. C++/CLI "using" STATEMENTS ---
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO; // For file operations

	// This is our C++ string conversion helper
	using namespace msclr::interop;

	// This is your C++ engine's namespace
	using namespace GenoSearchEngine;


	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();

			// --- 3. CUSTOM CONSTRUCTOR CODE ---
			// This function runs once when the app starts.
			// We use it to set up the initial UI state.
			UpdateUIMode(); // Call this to set the initial UI state
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

		// --- 4. ALL YOUR DESIGNER COMPONENTS (NOW CORRECT) ---
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::RadioButton^ regexRadio;
	private: System::Windows::Forms::RadioButton^ pdaRadio;
	private: System::Windows::Forms::RadioButton^ approxRadio;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::GroupBox^ patternInputGroup;
	private: System::Windows::Forms::TextBox^ patternInputBox;
	private: System::Windows::Forms::GroupBox^ editDistanceGroup;
	private: System::Windows::Forms::Label^ patternLabel;
	private: System::Windows::Forms::Label^ distanceLabel; // Extra label you added
	private: System::Windows::Forms::GroupBox^ pdaInputTypeGroup;
	private: System::Windows::Forms::RadioButton^ pdaStringRadio;
	private: System::Windows::Forms::NumericUpDown^ editDistanceInput;
	private: System::Windows::Forms::GroupBox^ fileInputGroup;

	private: System::Windows::Forms::RadioButton^ pdaFileRadio;
	private: System::Windows::Forms::Button^ browseButton;

	private: System::Windows::Forms::TextBox^ fileInputBox;
	private: System::Windows::Forms::Label^ fileInputLabel;
	private: System::Windows::Forms::Label^ supportLabel; // Extra label you added
	private: System::Windows::Forms::Label^ sourceInputLabel; // Extra label you added
	private: System::Windows::Forms::Label^ step2Label; // Extra label you added

	private: System::Windows::Forms::Button^ runButton;
	private: System::Windows::Forms::Label^ label1; // Extra label you added
	private: System::Windows::Forms::Button^ showErrorButton;
	private: System::Windows::Forms::TabControl^ outputTabControl;
	private: System::Windows::Forms::TabPage^ tabPage1; // Results tab
	private: System::Windows::Forms::GroupBox^ errorGroup;
	private: System::Windows::Forms::TabPage^ tabPage2; // Viz tab


	private: System::Windows::Forms::TextBox^ errorBox;
	private: System::Windows::Forms::Label^ errorLabel; // Extra label you added
	private: System::Windows::Forms::GroupBox^ normalOutputGroup;
	private: System::Windows::Forms::Label^ resultsLabel;
	private: System::Windows::Forms::Button^ exportButton; // You fixed this name!
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


		   // --- C++ MEMBER VARIABLES (CORRECTED) ---
		   // We use the managed .NET String type here
	private: System::String^ m_nfaDot;
	private: System::String^ m_dfaDot;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pdaRadio = (gcnew System::Windows::Forms::RadioButton());
			this->approxRadio = (gcnew System::Windows::Forms::RadioButton());
			this->regexRadio = (gcnew System::Windows::Forms::RadioButton());
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
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->fileInputGroup->SuspendLayout();
			this->pdaInputTypeGroup->SuspendLayout();
			this->editDistanceGroup->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->editDistanceInput))->BeginInit();
			this->patternInputGroup->SuspendLayout();
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
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->pdaRadio);
			this->groupBox1->Controls->Add(this->approxRadio);
			this->groupBox1->Controls->Add(this->regexRadio);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox1->Location = System::Drawing::Point(21, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(618, 89);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(13, 12);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(255, 20);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Step 1: Select Simulation Type";
			// 
			// pdaRadio
			// 
			this->pdaRadio->AutoSize = true;
			this->pdaRadio->Location = System::Drawing::Point(413, 41);
			this->pdaRadio->Name = L"pdaRadio";
			this->pdaRadio->Size = System::Drawing::Size(177, 24);
			this->pdaRadio->TabIndex = 2;
			this->pdaRadio->Text = L"Structural Validation";
			this->pdaRadio->UseMnemonic = false;
			this->pdaRadio->UseVisualStyleBackColor = true;
			this->pdaRadio->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Radio_CheckedChanged);
			// 
			// approxRadio
			// 
			this->approxRadio->AutoSize = true;
			this->approxRadio->Location = System::Drawing::Point(215, 41);
			this->approxRadio->Name = L"approxRadio";
			this->approxRadio->Size = System::Drawing::Size(171, 24);
			this->approxRadio->TabIndex = 1;
			this->approxRadio->Text = L"Approximate Match";
			this->approxRadio->UseMnemonic = false;
			this->approxRadio->UseVisualStyleBackColor = true;
			this->approxRadio->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Radio_CheckedChanged);
			// 
			// regexRadio
			// 
			this->regexRadio->AutoSize = true;
			this->regexRadio->Checked = true;
			this->regexRadio->Location = System::Drawing::Point(26, 41);
			this->regexRadio->Name = L"regexRadio";
			this->regexRadio->Size = System::Drawing::Size(172, 24);
			this->regexRadio->TabIndex = 0;
			this->regexRadio->TabStop = true;
			this->regexRadio->Text = L"Regular Expression";
			this->regexRadio->UseVisualStyleBackColor = true;
			this->regexRadio->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Radio_CheckedChanged);
			// 
			// groupBox2
			// 
			this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox2->Controls->Add(this->showErrorButton);
			this->groupBox2->Controls->Add(this->step2Label);
			this->groupBox2->Controls->Add(this->runButton);
			this->groupBox2->Controls->Add(this->fileInputGroup);
			this->groupBox2->Controls->Add(this->pdaInputTypeGroup);
			this->groupBox2->Controls->Add(this->editDistanceGroup);
			this->groupBox2->Controls->Add(this->patternInputGroup);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox2->Location = System::Drawing::Point(21, 107);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(618, 318);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			// 
			// showErrorButton
			// 
			this->showErrorButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->showErrorButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->showErrorButton->Location = System::Drawing::Point(448, 272);
			this->showErrorButton->Name = L"showErrorButton";
			this->showErrorButton->Size = System::Drawing::Size(154, 30);
			this->showErrorButton->TabIndex = 6;
			this->showErrorButton->Text = L"Show Error (Demo)";
			this->showErrorButton->UseVisualStyleBackColor = true;
			this->showErrorButton->Click += gcnew System::EventHandler(this, &MyForm::showErrorButton_Click);
			// 
			// step2Label
			// 
			this->step2Label->AutoSize = true;
			this->step2Label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->step2Label->Location = System::Drawing::Point(13, 2);
			this->step2Label->Name = L"step2Label";
			this->step2Label->Size = System::Drawing::Size(206, 20);
			this->step2Label->TabIndex = 5;
			this->step2Label->Text = L"Step 2: Configure Inputs";
			// 
			// runButton
			// 
			this->runButton->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->runButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->runButton->Location = System::Drawing::Point(224, 268);
			this->runButton->Name = L"runButton";
			this->runButton->Size = System::Drawing::Size(182, 38);
			this->runButton->TabIndex = 4;
			this->runButton->Text = L"Run Simulation";
			this->runButton->UseVisualStyleBackColor = true;
			this->runButton->Click += gcnew System::EventHandler(this, &MyForm::runButton_Click);
			// 
			// fileInputGroup
			// 
			this->fileInputGroup->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->fileInputGroup->Controls->Add(this->supportLabel);
			this->fileInputGroup->Controls->Add(this->browseButton);
			this->fileInputGroup->Controls->Add(this->fileInputBox);
			this->fileInputGroup->Controls->Add(this->fileInputLabel);
			this->fileInputGroup->Location = System::Drawing::Point(6, 182);
			this->fileInputGroup->Name = L"fileInputGroup";
			this->fileInputGroup->Size = System::Drawing::Size(606, 88);
			this->fileInputGroup->TabIndex = 3;
			this->fileInputGroup->TabStop = false;
			// 
			// supportLabel
			// 
			this->supportLabel->AutoSize = true;
			this->supportLabel->Location = System::Drawing::Point(7, 61);
			this->supportLabel->Name = L"supportLabel";
			this->supportLabel->Size = System::Drawing::Size(187, 20);
			this->supportLabel->TabIndex = 3;
			this->supportLabel->Text = L"(Supports: .txt, .fa, .fasta)";
			// 
			// browseButton
			// 
			this->browseButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->browseButton->Location = System::Drawing::Point(508, 25);
			this->browseButton->Name = L"browseButton";
			this->browseButton->Size = System::Drawing::Size(92, 31);
			this->browseButton->TabIndex = 2;
			this->browseButton->Text = L"Browse...";
			this->browseButton->UseVisualStyleBackColor = true;
			this->browseButton->Click += gcnew System::EventHandler(this, &MyForm::browseButton_Click);
			// 
			// fileInputBox
			// 
			this->fileInputBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->fileInputBox->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->fileInputBox->Location = System::Drawing::Point(11, 26);
			this->fileInputBox->Name = L"fileInputBox";
			this->fileInputBox->ReadOnly = true;
			this->fileInputBox->Size = System::Drawing::Size(491, 26);
			this->fileInputBox->TabIndex = 1;
			// 
			// fileInputLabel
			// 
			this->fileInputLabel->AutoSize = true;
			this->fileInputLabel->Location = System::Drawing::Point(7, 0);
			this->fileInputLabel->Name = L"fileInputLabel";
			this->fileInputLabel->Size = System::Drawing::Size(75, 20);
			this->fileInputLabel->TabIndex = 0;
			this->fileInputLabel->Text = L"Input File";
			// 
			// pdaInputTypeGroup
			// 
			this->pdaInputTypeGroup->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->pdaInputTypeGroup->Controls->Add(this->sourceInputLabel);
			this->pdaInputTypeGroup->Controls->Add(this->pdaFileRadio);
			this->pdaInputTypeGroup->Controls->Add(this->pdaStringRadio);
			this->pdaInputTypeGroup->Location = System::Drawing::Point(6, 128);
			this->pdaInputTypeGroup->Name = L"pdaInputTypeGroup";
			this->pdaInputTypeGroup->Size = System::Drawing::Size(606, 56);
			this->pdaInputTypeGroup->TabIndex = 2;
			this->pdaInputTypeGroup->TabStop = false;
			// 
			// sourceInputLabel
			// 
			this->sourceInputLabel->AutoSize = true;
			this->sourceInputLabel->Location = System::Drawing::Point(7, 2);
			this->sourceInputLabel->Name = L"sourceInputLabel";
			this->sourceInputLabel->Size = System::Drawing::Size(105, 20);
			this->sourceInputLabel->TabIndex = 2;
			this->sourceInputLabel->Text = L"Input Source:";
			// 
			// pdaFileRadio
			// 
			this->pdaFileRadio->AutoSize = true;
			this->pdaFileRadio->Location = System::Drawing::Point(259, 21);
			this->pdaFileRadio->Name = L"pdaFileRadio";
			this->pdaFileRadio->Size = System::Drawing::Size(121, 24);
			this->pdaFileRadio->TabIndex = 1;
			this->pdaFileRadio->Text = L"Validate File";
			this->pdaFileRadio->UseVisualStyleBackColor = true;
			this->pdaFileRadio->CheckedChanged += gcnew System::EventHandler(this, &MyForm::pdaInputType_CheckedChanged);
			// 
			// pdaStringRadio
			// 
			this->pdaStringRadio->AutoSize = true;
			this->pdaStringRadio->Checked = true;
			this->pdaStringRadio->Location = System::Drawing::Point(117, 21);
			this->pdaStringRadio->Name = L"pdaStringRadio";
			this->pdaStringRadio->Size = System::Drawing::Size(138, 24);
			this->pdaStringRadio->TabIndex = 0;
			this->pdaStringRadio->TabStop = true;
			this->pdaStringRadio->Text = L"Validate String";
			this->pdaStringRadio->UseVisualStyleBackColor = true;
			this->pdaStringRadio->CheckedChanged += gcnew System::EventHandler(this, &MyForm::pdaInputType_CheckedChanged);
			// 
			// editDistanceGroup
			// 
			this->editDistanceGroup->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->editDistanceGroup->Controls->Add(this->editDistanceInput);
			this->editDistanceGroup->Controls->Add(this->distanceLabel);
			this->editDistanceGroup->Location = System::Drawing::Point(6, 92);
			this->editDistanceGroup->Name = L"editDistanceGroup";
			this->editDistanceGroup->Size = System::Drawing::Size(606, 36);
			this->editDistanceGroup->TabIndex = 1;
			this->editDistanceGroup->TabStop = false;
			// 
			// editDistanceInput
			// 
			this->editDistanceInput->Location = System::Drawing::Point(144, 0);
			this->editDistanceInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->editDistanceInput->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->editDistanceInput->Name = L"editDistanceInput";
			this->editDistanceInput->Size = System::Drawing::Size(61, 26);
			this->editDistanceInput->TabIndex = 1;
			this->editDistanceInput->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// distanceLabel
			// 
			this->distanceLabel->AutoSize = true;
			this->distanceLabel->Location = System::Drawing::Point(8, 0);
			this->distanceLabel->Name = L"distanceLabel";
			this->distanceLabel->Size = System::Drawing::Size(130, 20);
			this->distanceLabel->TabIndex = 0;
			this->distanceLabel->Text = L"Edit Distance (k):";
			// 
			// patternInputGroup
			// 
			this->patternInputGroup->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->patternInputGroup->Controls->Add(this->patternLabel);
			this->patternInputGroup->Controls->Add(this->patternInputBox);
			this->patternInputGroup->Location = System::Drawing::Point(6, 25);
			this->patternInputGroup->Name = L"patternInputGroup";
			this->patternInputGroup->Size = System::Drawing::Size(606, 61);
			this->patternInputGroup->TabIndex = 0;
			this->patternInputGroup->TabStop = false;
			// 
			// patternLabel
			// 
			this->patternLabel->AutoSize = true;
			this->patternLabel->Location = System::Drawing::Point(7, 11);
			this->patternLabel->Name = L"patternLabel";
			this->patternLabel->Size = System::Drawing::Size(213, 20);
			this->patternLabel->TabIndex = 0;
			this->patternLabel->Text = L"Pattern (Regular Expression)";
			// 
			// patternInputBox
			// 
			this->patternInputBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->patternInputBox->Font = (gcnew System::Drawing::Font(L"Consolas", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->patternInputBox->Location = System::Drawing::Point(11, 35);
			this->patternInputBox->Name = L"patternInputBox";
			this->patternInputBox->Size = System::Drawing::Size(589, 26);
			this->patternInputBox->TabIndex = 0;
			// 
			// outputTabControl
			// 
			this->outputTabControl->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->outputTabControl->Controls->Add(this->tabPage1);
			this->outputTabControl->Controls->Add(this->tabPage2);
			this->outputTabControl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->outputTabControl->Location = System::Drawing::Point(21, 431);
			this->outputTabControl->Name = L"outputTabControl";
			this->outputTabControl->SelectedIndex = 0;
			this->outputTabControl->Size = System::Drawing::Size(618, 299);
			this->outputTabControl->TabIndex = 2;
			// 
			// tabPage1
			// 
			this->tabPage1->AutoScroll = true;
			this->tabPage1->Controls->Add(this->errorGroup);
			this->tabPage1->Controls->Add(this->normalOutputGroup);
			this->tabPage1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tabPage1->Location = System::Drawing::Point(4, 29);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(610, 266);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Results";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// errorGroup
			// 
			this->errorGroup->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->errorGroup->Controls->Add(this->errorBox);
			this->errorGroup->Controls->Add(this->errorLabel);
			this->errorGroup->Location = System::Drawing::Point(6, 6);
			this->errorGroup->Name = L"errorGroup";
			this->errorGroup->Size = System::Drawing::Size(572, 494);
			this->errorGroup->TabIndex = 0;
			this->errorGroup->TabStop = false;
			// 
			// errorBox
			// 
			this->errorBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->errorBox->Font = (gcnew System::Drawing::Font(L"Consolas", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->errorBox->Location = System::Drawing::Point(16, 25);
			this->errorBox->Multiline = true;
			this->errorBox->Name = L"errorBox";
			this->errorBox->ReadOnly = true;
			this->errorBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->errorBox->Size = System::Drawing::Size(538, 463);
			this->errorBox->TabIndex = 1;
			// 
			// errorLabel
			// 
			this->errorLabel->AutoSize = true;
			this->errorLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->errorLabel->Location = System::Drawing::Point(3, 0);
			this->errorLabel->Name = L"errorLabel";
			this->errorLabel->Size = System::Drawing::Size(138, 20);
			this->errorLabel->TabIndex = 0;
			this->errorLabel->Text = L"Simulation Error";
			// 
			// normalOutputGroup
			// 
			this->normalOutputGroup->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->normalOutputGroup->Controls->Add(this->matchReportGroup);
			this->normalOutputGroup->Controls->Add(this->grammarGroup);
			this->normalOutputGroup->Controls->Add(this->summaryGroup);
			this->normalOutputGroup->Controls->Add(this->exportButton);
			this->normalOutputGroup->Controls->Add(this->resultsLabel);
			this->normalOutputGroup->Location = System::Drawing::Point(6, 6);
			this->normalOutputGroup->Name = L"normalOutputGroup";
			this->normalOutputGroup->Size = System::Drawing::Size(569, 500);
			this->normalOutputGroup->TabIndex = 1;
			this->normalOutputGroup->TabStop = false;
			// 
			// matchReportGroup
			// 
			this->matchReportGroup->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->matchReportGroup->Controls->Add(this->resultsBox);
			this->matchReportGroup->Location = System::Drawing::Point(8, 350);
			this->matchReportGroup->Name = L"matchReportGroup";
			this->matchReportGroup->Size = System::Drawing::Size(555, 138);
			this->matchReportGroup->TabIndex = 5;
			this->matchReportGroup->TabStop = false;
			this->matchReportGroup->Text = L"Match Report";
			// 
			// resultsBox
			// 
			this->resultsBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->resultsBox->Font = (gcnew System::Drawing::Font(L"Consolas", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->resultsBox->Location = System::Drawing::Point(8, 25);
			this->resultsBox->Multiline = true;
			this->resultsBox->Name = L"resultsBox";
			this->resultsBox->ReadOnly = true;
			this->resultsBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->resultsBox->Size = System::Drawing::Size(538, 107);
			this->resultsBox->TabIndex = 0;
			// 
			// grammarGroup
			// 
			this->grammarGroup->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->grammarGroup->Controls->Add(this->grammarBox);
			this->grammarGroup->Location = System::Drawing::Point(10, 205);
			this->grammarGroup->Name = L"grammarGroup";
			this->grammarGroup->Size = System::Drawing::Size(553, 139);
			this->grammarGroup->TabIndex = 4;
			this->grammarGroup->TabStop = false;
			this->grammarGroup->Text = L"Generated Grammar";
			// 
			// grammarBox
			// 
			this->grammarBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->grammarBox->Font = (gcnew System::Drawing::Font(L"Consolas", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->grammarBox->Location = System::Drawing::Point(6, 26);
			this->grammarBox->Multiline = true;
			this->grammarBox->Name = L"grammarBox";
			this->grammarBox->ReadOnly = true;
			this->grammarBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->grammarBox->Size = System::Drawing::Size(538, 100);
			this->grammarBox->TabIndex = 0;
			// 
			// summaryGroup
			// 
			this->summaryGroup->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->summaryGroup->Controls->Add(this->summaryBox);
			this->summaryGroup->Location = System::Drawing::Point(8, 36);
			this->summaryGroup->Name = L"summaryGroup";
			this->summaryGroup->Size = System::Drawing::Size(555, 162);
			this->summaryGroup->TabIndex = 3;
			this->summaryGroup->TabStop = false;
			this->summaryGroup->Text = L"Simulation Summary";
			// 
			// summaryBox
			// 
			this->summaryBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->summaryBox->Font = (gcnew System::Drawing::Font(L"Consolas", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->summaryBox->Location = System::Drawing::Point(8, 25);
			this->summaryBox->Multiline = true;
			this->summaryBox->Name = L"summaryBox";
			this->summaryBox->ReadOnly = true;
			this->summaryBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->summaryBox->Size = System::Drawing::Size(541, 120);
			this->summaryBox->TabIndex = 0;
			// 
			// exportButton
			// 
			this->exportButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->exportButton->Location = System::Drawing::Point(377, 0);
			this->exportButton->Name = L"exportButton";
			this->exportButton->Size = System::Drawing::Size(188, 30);
			this->exportButton->TabIndex = 2;
			this->exportButton->Text = L"Export Full Report (.txt)";
			this->exportButton->UseVisualStyleBackColor = true;
			this->exportButton->Click += gcnew System::EventHandler(this, &MyForm::exportButton_Click);
			// 
			// resultsLabel
			// 
			this->resultsLabel->AutoSize = true;
			this->resultsLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->resultsLabel->Location = System::Drawing::Point(6, 2);
			this->resultsLabel->Name = L"resultsLabel";
			this->resultsLabel->Size = System::Drawing::Size(126, 20);
			this->resultsLabel->TabIndex = 1;
			this->resultsLabel->Text = L"Regex Results";
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->pdaTraceBox);
			this->tabPage2->Controls->Add(this->vizPictureBox);
			this->tabPage2->Controls->Add(this->vizToggleGroup);
			this->tabPage2->Controls->Add(this->vizLabel);
			this->tabPage2->Location = System::Drawing::Point(4, 29);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(610, 266);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Visualization";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// pdaTraceBox
			// 
			this->pdaTraceBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->pdaTraceBox->Font = (gcnew System::Drawing::Font(L"Consolas", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->pdaTraceBox->Location = System::Drawing::Point(13, 60);
			this->pdaTraceBox->Multiline = true;
			this->pdaTraceBox->Name = L"pdaTraceBox";
			this->pdaTraceBox->ReadOnly = true;
			this->pdaTraceBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->pdaTraceBox->Size = System::Drawing::Size(585, 200);
			this->pdaTraceBox->TabIndex = 3;
			// 
			// vizPictureBox
			// 
			this->vizPictureBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->vizPictureBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->vizPictureBox->Location = System::Drawing::Point(14, 60);
			this->vizPictureBox->Name = L"vizPictureBox";
			this->vizPictureBox->Size = System::Drawing::Size(584, 200);
			this->vizPictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->vizPictureBox->TabIndex = 2;
			this->vizPictureBox->TabStop = false;
			// 
			// vizToggleGroup
			// 
			this->vizToggleGroup->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->vizToggleGroup->Controls->Add(this->showDfaButton);
			this->vizToggleGroup->Controls->Add(this->showNfaButton);
			this->vizToggleGroup->Location = System::Drawing::Point(220, 6);
			this->vizToggleGroup->Name = L"vizToggleGroup";
			this->vizToggleGroup->Size = System::Drawing::Size(378, 42);
			this->vizToggleGroup->TabIndex = 1;
			// 
			// showDfaButton
			// 
			this->showDfaButton->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->showDfaButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->showDfaButton->Location = System::Drawing::Point(223, 3);
			this->showDfaButton->Name = L"showDfaButton";
			this->showDfaButton->Size = System::Drawing::Size(122, 33);
			this->showDfaButton->TabIndex = 1;
			this->showDfaButton->Text = L"Show DFA";
			this->showDfaButton->UseVisualStyleBackColor = false;
			this->showDfaButton->Click += gcnew System::EventHandler(this, &MyForm::showDfaButton_Click);
			// 
			// showNfaButton
			// 
			this->showNfaButton->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->showNfaButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->showNfaButton->Location = System::Drawing::Point(28, 3);
			this->showNfaButton->Name = L"showNfaButton";
			this->showNfaButton->Size = System::Drawing::Size(122, 33);
			this->showNfaButton->TabIndex = 0;
			this->showNfaButton->Text = L"Show NFA\r\n";
			this->showNfaButton->UseVisualStyleBackColor = false;
			this->showNfaButton->Click += gcnew System::EventHandler(this, &MyForm::showNfaButton_Click);
			// 
			// vizLabel
			// 
			this->vizLabel->AutoSize = true;
			this->vizLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->vizLabel->Location = System::Drawing::Point(11, 15);
			this->vizLabel->Name = L"vizLabel";
			this->vizLabel->Size = System::Drawing::Size(204, 20);
			this->vizLabel->TabIndex = 0;
			this->vizLabel->Text = L"Visualization (NFA/DFA)";
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
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->BackColor = System::Drawing::SystemColors::ControlLight;
			this->ClientSize = System::Drawing::Size(659, 742);
			this->Controls->Add(this->outputTabControl);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->MinimumSize = System::Drawing::Size(680, 700);
			this->Name = L"MyForm";
			this->Text = L"GenoSearch | Automata-Powered Pattern Recognition";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
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
			this->ResumeLayout(false);

		}
#pragma endregion

		// --- 5. C++ "GLUE CODE" AND HELPER FUNCTIONS ---

		// --- STRING CONVERSION HELPERS ---
	private:
		std::string ToStdString(System::String^ netString) {
			if (netString == nullptr) {
				return std::string();
			}
			return msclr::interop::marshal_as<std::string>(netString);
		}

		System::String^ ToNetString(const std::string& stdString) {
			return gcnew System::String(stdString.c_str());
		}

		// --- FILE DIALOG HELPERS ---
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
				}
				catch (Exception^ e) {
					MessageBox::Show(e->Message, "Error Saving File", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
		}

		// --- SMART UI LOGIC ---
		void UpdateUIMode() {

			std::string mode = "regex";
			if (this->approxRadio->Checked) {
				mode = "approx";
			}
			else if (this->pdaRadio->Checked) {
				mode = "pda";
			}

			// --- 1. CONFIGURE INPUTS ---
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

			// --- 2. CONFIGURE OUTPUTS (Clear old results) ---
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
			else { // pdaFileRadio is checked
				this->patternInputGroup->Visible = false;
				this->fileInputGroup->Visible = true;
				this->fileInputLabel->Text = "File to Validate (e.g., rna.xml)";
			}
		}

		// --- ERROR HANDLING ---
		void ShowError(std::string error_message) {
			this->normalOutputGroup->Visible = false;
			this->errorGroup->Visible = true;
			this->errorBox->Text = ToNetString(error_message);
			this->outputTabControl->SelectedTab = this->tabPage1;
		}


		// --- VISUALIZATION HELPER ---
		void LoadImage(PictureBox^ pb, std::string image_path) {
			try {
				if (pb->Image != nullptr) {
					pb->Image = nullptr;
				}
				System::IO::MemoryStream^ ms = gcnew System::IO::MemoryStream(File::ReadAllBytes(ToNetString(image_path)));
				pb->Image = Image::FromStream(ms);
			}
			catch (Exception^ e) {
				ShowError("C++ Error: Could not load image file '" + image_path + "'.\n" + ToStdString(e->Message));
			}
		}


		// --- 6. ALL THE BUTTON CLICK HANDLERS ---

	private: System::Void Radio_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		UpdateUIMode();
	}
	private: System::Void pdaInputType_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		UpdatePdaInput();
	}

	private: System::Void browseButton_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFile(this->fileInputBox);
	}

		   // --- Run Button ---
	private: System::Void runButton_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Cursor = Cursors::WaitCursor;

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
			this->resultsLabel->Text = "Results (Regex)";
			this->vizLabel->Text = "Visualization (NFA/DFA)";
			this->matchReportGroup->Text = "Match Report";
			this->matchReportGroup->Visible = true;

			runBranch1_logic(pattern, filepath, report, viz, out_error_msg);

			if (!out_error_msg.empty()) {
				ShowError(out_error_msg);
				this->Cursor = Cursors::Default;
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
			bool success = GenoSearchEngine::GenerateGraphvizImage(ToStdString(m_nfaDot), "approx_viz.png", error_msg, fallback_str);

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
				return;
			}

			this->summaryGroup->Visible = false;
			this->grammarGroup->Visible = true;
			this->matchReportGroup->Visible = true;

			this->grammarBox->Text = ToNetString(report.grammar);
			this->resultsBox->Text = ToNetString(report.matches);

			this->vizPictureBox->Visible = false;
			this->pdaTraceBox->Visible = true;
			// *** THIS IS THE FIX (Line 1087) ***
			this->vizToggleGroup->Visible = false;

			this->pdaTraceBox->Text = ToNetString(viz.pdaTrace);
		}

		this->Cursor = Cursors::Default; // Stop loading
	}


		   // --- Output Panel ---
	private: System::Void exportButton_Click(System::Object^ sender, System::EventArgs^ e) {
		System::String^ fullReport = "";
		fullReport += "--- " + this->resultsLabel->Text + " ---\r\n\r\n";

		if (this->summaryGroup->Visible) {
			fullReport += "--- SIMULATION SUMMARY ---\r\n";
			fullReport += this->summaryBox->Text + "\r\n\r\n";
		}
		if (this->grammarGroup->Visible) {
			fullReport += "--- GENERATED GRAMMAR ---\r\n";
			fullReport += this->grammarBox->Text + "\r\n\r\n";
		}
		if (this->matchReportGroup->Visible) {
			fullReport += "--- " + this->matchReportGroup->Text + " ---\r\n";
			fullReport += this->resultsBox->Text + "\r\n\r\n";
		}

		SaveFile(fullReport);
	}

	private: System::Void showNfaButton_Click(System::Object^ sender, System::EventArgs^ e) {
		this->showNfaButton->BackColor = System::Drawing::SystemColors::ActiveCaption;
		this->showDfaButton->BackColor = System::Drawing::SystemColors::Control;

		std::string error_msg, fallback_str;
		bool success = GenoSearchEngine::GenerateGraphvizImage(ToStdString(m_nfaDot), "nfa_viz.png", error_msg, fallback_str);
		if (success) {
			LoadImage(this->vizPictureBox, "nfa_viz.png");
		}
		else {
			ShowError(error_msg + "\n" + fallback_str);
		}
	}
	private: System::Void showDfaButton_Click(System::Object^ sender, System::EventArgs^ e) {
		this->showNfaButton->BackColor = System::Drawing::SystemColors::Control;
		this->showDfaButton->BackColor = System::Drawing::SystemColors::ActiveCaption;

		std::string error_msg, fallback_str;
		bool success = GenoSearchEngine::GenerateGraphvizImage(ToStdString(m_dfaDot), "dfa_viz.png", error_msg, fallback_str);
		if (success) {
			LoadImage(this->vizPictureBox, "dfa_viz.png");
		}
		else {
			ShowError(error_msg + "\n" + fallback_str);
		}
	}

	private: System::Void showErrorButton_Click(System::Object^ sender, System::EventArgs^ e) {
		ShowError("--- THIS IS A DEMO ERROR ---\n"
			"Error: Graphviz 'dot' command not found.\n"
			"Please install Graphviz from graphviz.org\n"
			"and ensure it is in your system's PATH.\n\n"
			"--- FALLBACK VISUALIZATION ---\n"
			"(q0) --'a'--> (q1)\n"
			"(q1) --'b'--> (q1)\n"
			"(q1) --'c'--> (q2)\n");
	}

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		UpdateUIMode();
	}

	};
}