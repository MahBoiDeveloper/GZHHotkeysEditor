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

int ShowErrorMessage(const char* txt)
{
    // Log exception message
    LOGGER->LogException(txt);
    
    // And show it to user
    QMessageBox::critical(nullptr, LOGGER->EXCEPTION_HEADER, txt);

    // Also return -1 as error
    return -1;
}

int main(int argc, const char** argv)
{
    // After this all out text to console MUST be showed via std::wcout and all chars should be converted as wchar_t
    _setmode(_fileno(stdout), _O_U16TEXT);

    // Initialize main Qt application
    QApplication HotkeyEditor(argc, const_cast<char**>(argv));

    QString workingDirectory = QString::fromStdWString(filesystem::current_path().c_str());
    
    if (workingDirectory.indexOf(BINARIES_FOLDER) != -1)
    {
        LOGMSG("Program started from Resources\\Binaries folder. Redirect working directory to the ..\\..\\");
        LOGMSG("Before redirect: " + workingDirectory);
        LOGMSG("After redirect:  " + workingDirectory.replace(BINARIES_FOLDER, "", Qt::CaseSensitive));
        filesystem::current_path(workingDirectory.toStdWString());
    }

    if (!filesystem::exists(SETTINGS_PATH.toStdString().c_str()))
        return ShowErrorMessage(SETTINGS_NO_FOUND);

    if (!filesystem::exists(TECH_TREE_PATH.toStdString().c_str()))
        return ShowErrorMessage(TECH_TREE_NO_FOUND);

    if (!filesystem::exists(ICONS_FOLDER.toStdString().c_str()))
        return ShowErrorMessage(ICONS_FOLDER_NO_FOUND);

    if (!filesystem::exists(THEME_FOLDER.toStdString().c_str()))
        return ShowErrorMessage(THEME_FOLDER_NO_FOUND);

    if (!filesystem::exists(TRANSLATIONS_FOLDER.toStdString().c_str()))
        return ShowErrorMessage(TRANSLATIONS_NO_FOUND);

    // Call parsing the Settings.json
    PROGRAM_CONSTANTS = make_unique<ProgramConstants>();

    // Hides console
    if (!PROGRAM_CONSTANTS->IsConsoleEnabled()) 
        ShowWindow(GetConsoleWindow(), SW_HIDE);

    // Define logger as a singleton class, that could be used anywhere in project
    WINDOW_MANAGER = make_unique<WindowManager>();
    CSF_PARSER->Parse(RESOURCE_FOLDER + "/DataSamples/generalsRU.csf");

    try
    {
        WINDOW_MANAGER->Show();
        HotkeyEditor.exec();
    }
    catch (const exception& exception) { return ShowErrorMessage(exception.what()); }
    catch (const char* msg)            { return ShowErrorMessage(msg); }
    catch (const string& msg)          { return ShowErrorMessage(msg.c_str()); }
    catch (const QString& msg)         { return ShowErrorMessage(msg.toStdString().c_str()); }
    catch (...)                        { return ShowErrorMessage(UNKNOWN_ERROR); }

    return 0;
}
