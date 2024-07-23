// std headers
#include <fcntl.h>   // Allows to use UTF-16 encoding as the default encoding
#include <iostream>

// Qt headers
#include <QApplication>
#include <QMessageBox>
#include <QDebug>

// Project headers
#include "GUI/WindowManager.hpp"
#include "Parsers/CSFParser.hpp"
#include "Logger.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    // Hide console
    // ShowWindow(GetConsoleWindow(), SW_HIDE);
    
    // After this all out text to console MUST be showed via std::wcout and all chars should be converted as wchar_t
    _setmode(_fileno(stdout), _O_U16TEXT);

    // Initialize main qt application
    QApplication HotkeyEditor(argc, argv);

    // Define logger as a singleton class, that could be used anywhere in project
    CSFParser::Instance = make_unique<CSFParser>(Config::RESOURCE_FOLDER + "/DataSamples/generalsRU.csf");

    try
    {
        WindowManager::Instance->Show();
        HotkeyEditor.exec();
    }
    catch (const exception& exception)
    {
        // Log exception message
        Logger::Instance->LogException(exception.what());

        // And show it to user
        QMessageBox::critical(nullptr, "I'VE GOT A PRESENT FOR YA", exception.what());
    }
    catch (const char* msg)
    {
        Logger::Instance->LogException(msg);
        QMessageBox::critical(nullptr, "I'VE GOT A PRESENT FOR YA", msg);
    }
    catch (const string& msg)
    {
        Logger::Instance->LogException(msg.c_str());
        QMessageBox::critical(nullptr, "I'VE GOT A PRESENT FOR YA", msg.c_str());
    }
    catch (const QString& msg)
    {
        Logger::Instance->LogException(msg.toStdString().c_str());
        QMessageBox::critical(nullptr, "I'VE GOT A PRESENT FOR YA", msg.toStdString().c_str());
    }
    catch (...)
    {
        string tmp = "Unknown error has been occured.";
        Logger::Instance->LogException(tmp.c_str());
        QMessageBox::critical(nullptr, "I'VE GOT A PRESENT FOR YA", tmp.c_str());
    }

    return 0;
}
