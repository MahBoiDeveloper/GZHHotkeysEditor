#include <fcntl.h>   // Allows to use UTF-16 encoding as the default encoding
#include <exception> // Allows to use standart cpp exceptions

// Internal cute logic
#include <QApplication>
// #include <QFile>
// #include <QDebug>

// Project files
#include "gui/mainwidget.hpp"
#include "Logger.hpp"
#include "Helper.hpp"
#include "CSFParser.hpp"

int main(int argc, char *argv[])
{
    // All out text MUST be showed via wcout and all chars should be converted as (wchar_t)
    _setmode(_fileno(stdout), _O_U16TEXT);

    // Walk around class with collection of useful methods
    Helper::Instance = make_unique<Helper>();

    // Define logger as the global variable
    Logger::Instance = make_unique<Logger>("Log.log");

    try
    {
        CSFParser::Instance = make_unique<CSFParser>("..\\..\\src\\csfSamples\\generalsRU.csf");

        string strTmp("CONTROLBAR:LaserMissileAttack");
        // string strTmp("GUI:BuddyAddReq");
        wcout << L"Found hotkey for [" << strTmp.c_str() << "] is a [" << CSFParser::Instance->GetHotkey(strTmp) << L']' << endl;
        
        CSFParser::Instance->SetHotkey(strTmp, L'T');
        wcout << L'{' << CSFParser::Instance->GetStringValue(strTmp) << L'}' << endl;

        CSFParser::Instance->Save("LTMP.csf");

        QApplication HotkeyEditor(argc, argv);
        MainWidget HotkeyEditor_Window;
        HotkeyEditor_Window.show();
        HotkeyEditor.exec();
    }
    catch(const exception& e)
    {
        Logger::Instance->Log() << "I'VE GOT A PRESENT FOR YA" << endl;
        Logger::Instance->Log(string(e.what()));
    }

    return 0;
}
