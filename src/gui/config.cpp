#include "config.hpp"

QString Config::LangEnumToString(const Languages& lang)
{
    QString fileBaseName = "Gui_";
    
    switch (lang)
    {
        case Languages::English:
            return fileBaseName + "en";

        case Languages::Russian:
            return fileBaseName + "ru";

        default: // English is a default language of all editor
            return LangEnumToString(Languages::English);
    }
}
