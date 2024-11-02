#include "Unsorted.hpp"
using namespace std;

namespace Unsorted
{
    Languages LangEnumFromLocale(const QString& locale)
    {
        QString lowerLocale = locale.toLower();

        for(auto it = LANGUAGES_STRINGS.cbegin(); it != LANGUAGES_STRINGS.cend(); ++it)
            if (GetLanguageShortName(it.key()) == lowerLocale)
                return it.key();
    
        return Languages::English;
    }

    const QString GetLanguageShortName(Languages language) { return LANGUAGES_STRINGS.value(language).first; }
    const QString GetLanguageFullName(Languages language)  { return LANGUAGES_STRINGS.value(language).second; }
}
