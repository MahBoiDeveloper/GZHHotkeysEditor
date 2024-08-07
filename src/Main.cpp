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
    // TODO:
    //   Make it toggable via .json config

    // Hides console
    // ShowWindow(GetConsoleWindow(), SW_HIDE);
    
    // After this all out text to console MUST be showed via std::wcout and all chars should be converted as wchar_t
    _setmode(_fileno(stdout), _O_U16TEXT);

    // Initialize main qt application
    QApplication HotkeyEditor(argc, argv);

    // Define logger as a singleton class, that could be used anywhere in project
    WINDOW_MANAGER = make_unique<WindowManager>();
    CSF_PARSER->Parse(Config::RESOURCE_FOLDER + "/DataSamples/generalsRU.csf");

    try
    {
        WindowManager::Instance->Show();
        HotkeyEditor.exec();
    }
    catch (const exception& exception)
    {
        // Log exception message
        LOGGER->LogException(exception.what());

        // And show it to user
        QMessageBox::critical(nullptr, "I'VE GOT A PRESENT FOR YA", exception.what());
    }
    catch (const char* msg)
    {
        LOGGER->LogException(msg);
        QMessageBox::critical(nullptr, "I'VE GOT A PRESENT FOR YA", msg);
    }
    catch (const string& msg)
    {
        LOGGER->LogException(msg.c_str());
        QMessageBox::critical(nullptr, "I'VE GOT A PRESENT FOR YA", msg.c_str());
    }
    catch (const QString& msg)
    {
        LOGGER->LogException(msg.toStdString().c_str());
        QMessageBox::critical(nullptr, "I'VE GOT A PRESENT FOR YA", msg.toStdString().c_str());
    }
    catch (...)
    {
        const char* tmp = "Unknown error has been occured.";
        LOGGER->LogException(tmp);
        QMessageBox::critical(nullptr, "I'VE GOT A PRESENT FOR YA", tmp);
    }

    return 0;
}
