#include <fcntl.h>   // Allows to use UTF-16 encoding as the default encoding
#include <exception> // Allows to use standart cpp exceptions

// Internal cute logic
#include <QApplication>
#include <QMessageBox>

// Project files
#include "gui/mainwidget.hpp"
#include "Helper.hpp"
#include "Logger.hpp"
#include "Registry.hpp"
#include "CSFParser.hpp"
#include "JSONFile.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    // All out text MUST be showed via wcout and all chars should be converted as (wchar_t)
    _setmode(_fileno(stdout), _O_U16TEXT);

    Registry::Instance = make_unique<Registry>();

    // Define logger as a singleton class, that could be used anywhere in project
    Logger::Instance   = make_unique<Logger>();

    QApplication HotkeyEditor(argc, argv);

    try
    {
        MainWidget HotkeyEditor_Window;
        HotkeyEditor_Window.setWindowTitle("C&C: Generals Zero Hour Hotkey Editor");
        HotkeyEditor_Window.show();
        HotkeyEditor.exec();
    }
    catch(const exception& e)
    {
        // Log exception message
        Logger::Instance->Log() << "I'VE GOT A PRESENT FOR YA" << endl;
        Logger::Instance->Log(string(e.what()));

        // And show it to user
        QMessageBox::critical(nullptr, "I'VE GOT A PRESENT FOR YA", e.what());
    }

    return 0;
}
