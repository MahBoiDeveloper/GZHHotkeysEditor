#include <fcntl.h>   // Allows to use UTF-16 encoding as the default encoding
#include <exception> // Allows to use standart cpp exceptions

// Internal cute logic
#include <QApplication>
#include <QMessageBox>

// Project files
#include "gui/mainwidget.hpp"
#include "Helper.hpp"
#include "Logger.hpp"
#include "CSFParser.hpp"
#include "JSONFile.hpp"

int main(int argc, char *argv[])
{
    // All out text MUST be showed via wcout and all chars should be converted as (wchar_t)
    _setmode(_fileno(stdout), _O_U16TEXT);

    // Walk around class with collection of useful methods
    Helper::Instance = make_unique<Helper>();

    // Define logger as the global variable
    Logger::Instance = make_unique<Logger>();

    QApplication HotkeyEditor(argc, argv);

    try
    {
        JSONFile jsonTest("Resources\\Settings.json");
        Logger::Instance->Log(jsonTest.GetKeyValue("Language"));

        MainWidget HotkeyEditor_Window;
        HotkeyEditor_Window.setWindowTitle("C&C: Generals Zero Hour Hotkey Editor");
        HotkeyEditor_Window.show();
        HotkeyEditor.exec();
    }
    catch(const exception& e)
    {
        Logger::Instance->Log() << "I'VE GOT A PRESENT FOR YA" << endl;
        Logger::Instance->Log(string(e.what()));

        QMessageBox::critical(nullptr, "I'VE GOT A PRESENT FOR YA", e.what());
    }

    return 0;
}
