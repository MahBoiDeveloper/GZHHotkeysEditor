#include <QJsonValue>
#include <QJsonArray>
#include <QJsonDocument>

#include "Parsers/JSONFile.hpp"
#include "ProgramConstants.hpp"
#include "Settings.hpp"

Settings::Settings()
{
    SetToDefault();
    ParseSettings();
}

Settings::~Settings() 
{
}

void Settings::SetToDefault()
{
    allowedKeys    = PROGRAM_CONSTANTS->DEFAULT_ALLOWED_KEYS;
    enabledConsole = false;
}

void Settings::ParseSettings()
{
    JSONFile json(PROGRAM_CONSTANTS->SETTINGS_FILE);

    enabledConsole = json.Query("$.DebugConsole").toBool();

    for (const QJsonValue& ch : json.Query("$.AllowedHotkeys").toArray())
        allowedKeys.insert(PROGRAM_CONSTANTS->KEYBOARD_KEYS.value(ch.toString()[0]));
}

const bool Settings::IsConsoleEnabled()        { return enabledConsole; }
const QSet<Qt::Key> Settings::GetAllowedKeys() { return allowedKeys; }
