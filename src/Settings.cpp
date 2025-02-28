#include <QFile>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonDocument>

#include "ProgramConstants.hpp"
#include "Settings.hpp"

#include "Logger.hpp"

Settings::Settings()
{
    SetToDefault();
    Parse();
}

Settings::~Settings() 
{
}

void Settings::SetToDefault()
{
    allowedKeys       = PROGRAM_CONSTANTS->DEFAULT_ALLOWED_KEYS;
    enabledConsole    = false;
    enabledDiscordRPC = true;
}

void Settings::Parse()
{
    JSONFile json(PROGRAM_CONSTANTS->SETTINGS_FILE);

    enabledConsole = json.Query("$.DebugConsole").toBool();

    for (const QJsonValue& ch : json.Query("$.AllowedHotkeys").toArray())
        allowedKeys.insert(PROGRAM_CONSTANTS->KEYBOARD_KEYS.value(ch.toString()[0]));
}

void Settings::Save()
{
    JSONFile json(PROGRAM_CONSTANTS->SETTINGS_FILE);
    QJsonObject jsMainObj     = json.GetMainObject();
    jsMainObj["DebugConsole"] = enabledConsole;
    jsMainObj["DiscordRPC"]   = enabledDiscordRPC;

    QJsonDocument jsDoc;
    jsDoc.setObject(jsMainObj);

    LOGMSG("Saving changes to the \"" + PROGRAM_CONSTANTS->SETTINGS_FILE + "\"..." );
    QFile settingsJson(PROGRAM_CONSTANTS->SETTINGS_FILE);
    settingsJson.remove();
    settingsJson.open(QIODevice::WriteOnly | QIODevice::Text);
    settingsJson.write(jsDoc.toJson());
    settingsJson.close();
    LOGMSG("Setting changes has been saved.");
}

const bool Settings::IsConsoleEnabled()        const { return enabledConsole; }
const QSet<Qt::Key> Settings::GetAllowedKeys() const { return allowedKeys; }
const bool Settings::IsDiscordRPCEnabled()     const { return enabledDiscordRPC; }

void Settings::SetAllowedKeys(const QSet<Qt::Key>& keys) { allowedKeys = keys; }
void Settings::SetConsoleStatus(bool state)              { enabledConsole = state; }
void Settings::SetConsoleStatus(const Qt::CheckState& state)
{
    switch (state)
    {
        case (Qt::CheckState::Checked):
            enabledConsole = true;
            break;
        case (Qt::CheckState::Unchecked):
            enabledConsole = false;
            break;
    }
}

void Settings::SetDiscordRPCStatus(bool state) { enabledDiscordRPC = state; }
void Settings::SetDiscordRPCStatus(const Qt::CheckState& state)
{
    switch (state)
    {
        case (Qt::CheckState::Checked):
            enabledDiscordRPC = true;
            break;
        case (Qt::CheckState::Unchecked):
            enabledDiscordRPC = false;
            break;
    }
}
