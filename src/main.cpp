#include <fcntl.h>   // Allows to use UTF-16 encoding as the default encoding
#include <exception> // Allows to use standart cpp exceptions
#include <iostream>

// Internal cute logic
#include <QApplication>
#include <QMessageBox>

// Project files
#include "gui/launchWidgets/mainlaunchwidget.hpp"
#include "Logger.hpp"
#include "Registry.hpp"
#include "CSFParser.hpp"
#include "JSONFile.hpp"
#include "GINIParser.hpp"

// #include <windows.h>

using namespace std;
void Test();

int main(int argc, char *argv[])
{
    // hide console
    // ShowWindow(GetConsoleWindow(), SW_HIDE);
    
    // All out text MUST be showed via wcout and all chars should be converted as (wchar_t)
    _setmode(_fileno(stdout), _O_U16TEXT);

    // Define logger as a singleton class, that could be used anywhere in project
    Logger::Instance = make_unique<Logger>();

    // Initialize main cute application
    QApplication HotkeyEditor(argc, argv);

    try
    {
        Test();

        // Create main window with user system language
        MainLaunchWidget HotkeyEditor_Window(Config::GetLangEnumByLocale(
            QString::fromStdString(Registry::GetCurrentUserLanguage()).toLower()));

        HotkeyEditor_Window.setWindowTitle("C&C: Generals Zero Hour Hotkey Editor");
        HotkeyEditor_Window.show();
        HotkeyEditor.exec();
    }
    catch(const exception& e)
    {
        // Log exception message
        LOGSTM() << endl << endl << "\t\t\t\tI'VE GOT A PRESENT FOR YA" << endl;
        LOGMSG(string(e.what()));

        // And show it to user
        QMessageBox::critical(nullptr, "I'VE GOT A PRESENT FOR YA", e.what());
    }

    return 0;
}

void Test()
{
    return;
}
