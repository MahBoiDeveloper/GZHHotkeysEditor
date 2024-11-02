#include "Unsorted.hpp"
using namespace std;

namespace Unsorted
{
    QStringList STDStringListToQStringList(const list<string>& srcList)
    {
        QStringList retList;

        for (const auto& elem : srcList)
            retList.push_back(QString::fromStdString(elem));

        return retList;
    }

    list<string> QStringListToSTDStringList(const QStringList& srcList)
    {
        list<string> retList;
    
        for (const auto& elem : srcList)
            retList.push_back(elem.toStdString());
    
        return retList;
    }
    const QString GetLanguageShortName(Languages language)
{
    return LANGUAGES_STRINGS.value(language).first;
}

    Languages GetLangEnumByLocale(const QString& locale)
    {
        QString lowerLocale = locale.toLower();

        for(auto it = LANGUAGES_STRINGS.cbegin(); it != LANGUAGES_STRINGS.cend(); ++it)
            if (GetLanguageShortName(it.key()) == lowerLocale)
                return it.key();
    
        return Languages::English;
    }

    Languages GetLangEnumByLocale(const std::string& locale)
    {
        return GetLangEnumByLocale(QString::fromStdString(locale));
    }

    const QString GetLanguageFullName(Languages language)
    {
        return LANGUAGES_STRINGS.value(language).second;
    }

    Qt::Key ToQtKey(const QChar& ch)
    {
        return static_cast<Qt::Key>(QChar(ch).unicode());
    }
}
