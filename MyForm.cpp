#include "MyForm.h"
#include <windows.h>
#include <iostream>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Text;

// GLOBAL UTF-8 SETUP - RUNS BEFORE ANYTHING
class UnicodeSetup {
public:
    UnicodeSetup() {
        // Set console to UTF-8 (in case you use console output)
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    }
};

// This runs before main()
UnicodeSetup unicodeSetup;

[STAThreadAttribute]
int main(array<System::String^>^ args)
{
    // Set DPI awareness for crisp text
    HMODULE user32 = LoadLibraryW(L"user32.dll");
    if (user32) {
        auto pSetProcessDPIAware = (BOOL(WINAPI*)())GetProcAddress(user32, "SetProcessDPIAware");
        if (pSetProcessDPIAware) pSetProcessDPIAware();
        FreeLibrary(user32);
    }

    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Create and run main form
    GenoSearch::MyForm form;
    Application::Run(% form);

    return 0;
}