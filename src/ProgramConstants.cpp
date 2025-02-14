#include <QJsonArray>
#include "Parsers/JSONFile.hpp"
#include "Logger.hpp"

#include "ProgramConstants.hpp"

ProgramConstants::ProgramConstants()
{
}

const QSet<Qt::Key>& ProgramConstants::GetAllowedKeys() { return keys; }
bool ProgramConstants::IsConsoleEnabled()               { return console; }
void ProgramConstants::InitializeSettingsJSON()
{
    JSONFile settings(SETTINGS_FILE);
    console = settings.Query("$.DebugConsole").toBool();

    for (const QJsonValue& ch : settings.Query("$.AllowedHotkeys").toArray())
        keys.insert(KEYBOARD_KEYS.value(ch.toString()[0]));
}
