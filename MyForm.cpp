/*
 * MyForm.cpp
 * This is the main C++/CLI entry point.
 * Its only job is to load and run your MyForm.h form.
 */

#include "MyForm.h" // Your GUI header file

// Use Win32 API for DPI awareness when targeting .NET Framework
#include <windows.h>

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute] // Required for Windows Forms
int main(array<System::String^>^ args)
{
    // *** THIS IS THE FIX for blurry text ***
    // Application::SetHighDpiMode(...) is available on .NET Core / .NET 5+ only.
    // For projects targeting .NET Framework, call the Win32 DPI API instead.
    typedef BOOL(WINAPI* SetProcessDPIAware_t)();
    HMODULE user32 = LoadLibraryW(L"user32.dll");
    if (user32)
    {
        SetProcessDPIAware_t pSetProcessDPIAware = (SetProcessDPIAware_t)GetProcAddress(user32, "SetProcessDPIAware");
        if (pSetProcessDPIAware)
        {
            // Sets the process to system-DPI aware (closest equivalent to SystemAware)
            pSetProcessDPIAware();
        }
        FreeLibrary(user32);
    }

    // Enable visual styles
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Create the main window and run it
    // "GenoSearch" MUST match the namespace in MyForm.h
    GenoSearch::MyForm form;
    Application::Run(% form);

    return 0;
}