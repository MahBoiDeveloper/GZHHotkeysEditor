#include "config.hpp"

QString Config::langEnumToString(const Languages& lang)
{
    QString fileBaseName = "Gui_";
    switch (lang) {
    case Languages::English:
        return fileBaseName + "en";
        break;
    case Languages::Russian:
        return fileBaseName + "ru";
        break;
    default:
        return langEnumToString(Languages::English);
        break;
    }
}
