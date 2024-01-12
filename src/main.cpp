#include <fcntl.h>   // Allows to use UTF-16 encoding as the default encoding
#include <iostream>

// Internal cute logic
#include <QApplication>
#include <QMessageBox>

// Project files
#include "GUI/stacked_launch_widget.hpp"
#include "GUI/hotkeys_main_window.hpp"
#include "Logger.hpp"
#include "Registry.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    // Hide console
    // ShowWindow(GetConsoleWindow(), SW_HIDE);
    
    // All out text MUST be showed via wcout and all chars should be converted as (wchar_t)
    _setmode(_fileno(stdout), _O_U16TEXT);

    // Define logger as a singleton class, that could be used anywhere in project
    Logger::Instance = make_unique<Logger>();

    // Initialize main cute application
    QApplication HotkeyEditor{argc, argv};

    try
    {
        // Create main window with user system language
        StackedLaunchWidget* HotkeyEditor_Window = new StackedLaunchWidget{Config::GetLangEnumByLocale(Registry::GetCurrentUserLanguage())};
        HotkeyEditor_Window->setWindowTitle("C&C: Generals Zero Hour Hotkey Editor");

        // Create HotkeysEditor with accepted configuration
        QObject::connect(HotkeyEditor_Window, &StackedLaunchWidget::acceptedConfiguration, HotkeyEditor_Window, [=](const QVariant& configuration)
        {
            LOGMSG("Loading hotkey editor window...");
            HotkeysMainWindow* pHotkeysEditor = new HotkeysMainWindow{configuration};
            pHotkeysEditor->setWindowTitle("C&C: Generals Zero Hour Hotkey Editor");
            pHotkeysEditor->show();
            LOGMSG("Hotkey editor window has been loaded");

            LOGMSG("Closing and deleting the StartWidget");
            HotkeyEditor_Window->deleteLater();
        });

        HotkeyEditor_Window->show();

        HotkeyEditor.exec();
    }
    catch (const exception& exception)
    {
        // Log exception message
        Logger::Instance->LogException();
        LOGMSG(exception.what());

        // And show it to user
        QMessageBox::critical(nullptr, "I'VE GOT A PRESENT FOR YA", exception.what());
    }

    return 0;
}
