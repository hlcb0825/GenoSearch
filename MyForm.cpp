/*
 * MyForm.cpp
 * This is the main C++/CLI entry point.
 * Its only job is to load and run your MyForm.h form.
 */

#include "MyForm.h" // Your GUI header file

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute] // Required for Windows Forms
int main(array<System::String^>^ args)
{
    // Enable visual styles
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Create the main window and run it
    // "GenoSearch" MUST match the namespace in MyForm.h
    GenoSearch::MyForm form;
    Application::Run(% form);

    return 0;
}