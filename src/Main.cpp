// std headers
#include <fcntl.h>   // Allows to use UTF-16 encoding as the default encoding
#include <windows.h> // Allows disable console
#include <iostream>
#include <filesystem>

// Qt headers
#include <QApplication>
#include <QMessageBox>
#include <QDebug>

// Project headers
#include "GUI/WindowManager.hpp"
#include "Parsers/CSFParser.hpp"
#include "Parsers/JSONFile.hpp"
#include "ProgramConstants.hpp"
#include "Logger.hpp"

using namespace std;

int main(int argc, const char** argv)
{
    // After this all out text to console MUST be showed via std::wcout and all chars should be converted as wchar_t
    _setmode(_fileno(stdout), _O_U16TEXT);

    QString workingDirectory = QString::fromStdWString(filesystem::current_path().c_str());
    
    if (workingDirectory.indexOf(BINARIES_FOLDER) != -1)
    {
        LOGMSG("Program started from Resources\\Binaries folder. Redirect working directory to the ..\\..\\");
        LOGMSG("Before redirect: " + workingDirectory);
        LOGMSG("After redirect:  " + workingDirectory.replace(BINARIES_FOLDER, "", Qt::CaseSensitive));
        filesystem::current_path(workingDirectory.toStdWString());
    }

    // Calls parsing from Settings.json
    PROGRAM_CONSTANTS = make_unique<ProgramConstants>();

    // Hides console
    if (!PROGRAM_CONSTANTS->IsConsoleEnabled()) 
        ShowWindow(GetConsoleWindow(), SW_HIDE);

    // Initialize main qt application
    QApplication HotkeyEditor(argc, const_cast<char**>(argv));

    // Define logger as a singleton class, that could be used anywhere in project
    WINDOW_MANAGER = make_unique<WindowManager>();
    CSF_PARSER->Parse(RESOURCE_FOLDER + "/DataSamples/generalsRU.csf");

    try
    {
        WINDOW_MANAGER->Show();
        HotkeyEditor.exec();
    }
    catch (const exception& exception)
    {
        // Log exception message
        LOGGER->LogException(exception.what());

        // And show it to user
        QMessageBox::critical(nullptr, LOGGER->EXCEPTION_HEADER, exception.what());
    }
    catch (const char* msg)
    {
        LOGGER->LogException(msg);
        QMessageBox::critical(nullptr, LOGGER->EXCEPTION_HEADER, msg);
    }
    catch (const string& msg)
    {
        LOGGER->LogException(msg.c_str());
        QMessageBox::critical(nullptr, LOGGER->EXCEPTION_HEADER, msg.c_str());
    }
    catch (const QString& msg)
    {
        LOGGER->LogException(msg.toStdString().c_str());
        QMessageBox::critical(nullptr, LOGGER->EXCEPTION_HEADER, msg.toStdString().c_str());
    }
    catch (...)
    {
        const char* tmp = "Unknown error has been occured.";
        LOGGER->LogException(tmp);
        QMessageBox::critical(nullptr, LOGGER->EXCEPTION_HEADER, tmp);
    }

    return 0;
}
