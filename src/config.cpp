#include "config.hpp"

#include <algorithm>

const std::string Config::GetLocaleFromLangEnum(Languages language)
{
    return LANGUAGES_STRINGS.find(language)->second.first;
}

Config::Languages Config::GetLangEnumByLocale(const std::string& locale)
{
    std::string lowerLocale = locale;
    // Make lowercase locale
    std::transform(lowerLocale.begin(), lowerLocale.end(), lowerLocale.begin(), ::tolower);

    for(auto it = LANGUAGES_STRINGS.cbegin(); it != LANGUAGES_STRINGS.cend(); ++it)
    {
        if (GetLocaleFromLangEnum(it->first) == lowerLocale)
        {
            return it->first;
        }
    }
    return Languages::English;
}

const std::string Config::GetStringFromLangEnum(Languages language)
{
    return LANGUAGES_STRINGS.find(language)->second.second;
}
