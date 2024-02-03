#include "Config.hpp"

const QString Config::GetLanguageShortName(Languages language)
{
    return LANGUAGES_STRINGS.value(language).first;
}

Config::Languages Config::GetLangEnumByLocale(const QString& locale)
{
    QString lowerLocale = locale.toLower();

    for(auto it = LANGUAGES_STRINGS.cbegin(); it != LANGUAGES_STRINGS.cend(); ++it)
        if (GetLanguageShortName(it.key()) == lowerLocale)
            return it.key();
    
    return Languages::English;
}

Config::Languages Config::GetLangEnumByLocale(const std::string& locale)
{
    return GetLangEnumByLocale(QString::fromStdString(locale));
}

const QString Config::GetLanguageFullName(Languages language)
{
    return LANGUAGES_STRINGS.value(language).second;
}
