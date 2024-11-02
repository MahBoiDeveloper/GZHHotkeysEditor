#include <QJsonArray>
#include "Parsers/JSONFile.hpp"
#include "Logger.hpp"

#include "ProgramConstants.hpp"

ProgramConstants::ProgramConstants()
{
    JSONFile settings(SETTINGS_PATH);
    console = settings.Query("$.DebugConsole").toBool();

    for (const QJsonValue& ch : settings.Query("$.AllowedHotkeys").toArray())
        keys.insert(KEYBOARD_KEYS.value(ch.toString()[0]));
}

const QSet<Qt::Key>& ProgramConstants::GetAllowedKeys() { return keys; }
bool ProgramConstants::IsConsoleEnabled()               { return console; }
