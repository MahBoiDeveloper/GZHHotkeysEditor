#include <QFile>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonDocument>

#include "Settings.hpp"
#include "Convert.hpp"
#include "Registry.hpp"
#include "Logger.hpp"

Settings::Settings()
{
    json = JSONFile(PROGRAM_CONSTANTS->SETTINGS_FILE);
    SetToDefault();
    Parse();
}

Settings::~Settings() 
{
}

void Settings::SetToDefault()
{
    allowedKeys                 = PROGRAM_CONSTANTS->DEFAULT_ALLOWED_KEYS;
    enabledConsole              = false;
    enabledDiscordRPC           = true;
    enabledForceOSLangOnStartUp = true;
    language                    = Languages::English;
}

void Settings::Parse()
{
    enabledConsole              = json.Query("$.DebugConsole").toBool();
    enabledDiscordRPC           = json.Query("$.DiscordRPC").toBool();
    enabledForceOSLangOnStartUp = json.Query("$.ForceSystemLanguage").toBool();
    if (enabledForceOSLangOnStartUp)
        language = Convert::ToLangEnum(Registry::GetCurrentUserLanguage());
    else
        language = Convert::ToLangEnum(json.Query("$.Language").toString());

    for (const QJsonValue& ch : json.Query("$.AllowedHotkeys").toArray())
        allowedKeys.insert(PROGRAM_CONSTANTS->KEYBOARD_KEYS.value(ch.toString()[0]));
}

void Settings::Save()
{
    QJsonObject jsMainObj            = json.GetMainObject();
    jsMainObj["DebugConsole"]        = enabledConsole;
    jsMainObj["DiscordRPC"]          = enabledDiscordRPC;
    jsMainObj["ForceSystemLanguage"] = enabledForceOSLangOnStartUp;
    jsMainObj["Language"]            = Convert::ToQString(language);

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

bool Settings::FromQtCheckState(const Qt::CheckState& state)
{
    bool flag;
    switch (state)
    {
        case (Qt::CheckState::Checked):
            flag = true;
            break;
        case (Qt::CheckState::Unchecked):
            flag = false;
            break;
    }
    return flag;
}

const QSet<Qt::Key> Settings::GetAllowedKeys()                        const { return allowedKeys; }
const bool          Settings::IsConsoleEnabled()                      const { return enabledConsole; }
const bool          Settings::IsDiscordRPCEnabled()                   const { return enabledDiscordRPC; }
const bool          Settings::IsForceSystemLanguageOnStartUpEnabled() const { return enabledForceOSLangOnStartUp; }
const Languages     Settings::GetLanguage()                           const { return language; }

void Settings::SetAllowedKeys(const QSet<Qt::Key>& keys)                    { allowedKeys                 = keys; }
void Settings::SetConsoleStatus(const bool state)                           { enabledConsole              = state; }
void Settings::SetConsoleStatus(const Qt::CheckState& state)                { enabledConsole              = FromQtCheckState(state); }
void Settings::SetDiscordRPCStatus(const bool state)                        { enabledDiscordRPC           = state; }
void Settings::SetDiscordRPCStatus(const Qt::CheckState& state)             { enabledDiscordRPC           = FromQtCheckState(state); }
void Settings::SetForceSystemLanguageOnStartUp(const bool state)            { enabledForceOSLangOnStartUp = state; }
void Settings::SetForceSystemLanguageOnStartUp(const Qt::CheckState& state) { enabledForceOSLangOnStartUp = FromQtCheckState(state); }
void Settings::SetLanguage(const Languages& locale)                         { language                    = locale; }
