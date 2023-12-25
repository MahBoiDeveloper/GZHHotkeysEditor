#pragma once

#include <map>

class Config
{
public:
    inline static const std::string resourcesFolder  = "Resources";
    inline static const std::string translationsPath = "Resources/Translations";
    inline static const std::string iconsPath        = "Resources/Icons";
    inline static const std::string defaultIconFile  = iconsPath + "/NoImageSmall.webp";
    inline static const double recomendedStartWidgetSizeRatio = 3./7.;

    enum class Languages
    {
        English,
        Russian,
        Count
    };

    inline static const std::map<Languages, std::pair<std::string, std::string>> LANGUAGES_STRINGS =
    {
        {Languages::English, {"en", "English"}},
        {Languages::Russian, {"ru", "Русский"}}
    };

public:
    Config() = delete;

    static const std::string GetLocaleFromLangEnum(Languages language);
    static Languages GetLangEnumByLocale(const std::string& locale);
    static const std::string GetStringFromLangEnum(Languages language);
};
