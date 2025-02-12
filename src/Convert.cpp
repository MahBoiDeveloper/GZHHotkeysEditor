#include "Unsorted.hpp"
#include "Convert.hpp"
using namespace std;

namespace Convert
{
    QStringList ToQStringList(const list<string>& srcList)
    {
        QStringList retList;

        for (const auto& elem : srcList)
            retList.push_back(QString::fromStdString(elem));

        return retList;
    }

    list<string> ToStdStringList(const QStringList& srcList)
    {
        list<string> retList;
    
        for (const auto& elem : srcList)
            retList.push_back(elem.toStdString());
    
        return retList;
    }

    Languages LangEnumFromLocale(const QString& locale)
    {
        QString lowerLocale = locale.toLower();

        for(auto it = PROGRAM_CONSTANTS->LANGUAGES_STRINGS.cbegin(); it != PROGRAM_CONSTANTS->LANGUAGES_STRINGS.cend(); ++it)
            if (Unsorted::GetLanguageShortName(it.key()) == lowerLocale)
                return it.key();
    
        return Languages::English;
    }

    Languages ToLangEnum(const std::string& locale) { return LangEnumFromLocale(QString::fromStdString(locale)); }
    Qt::Key ToQtKey(const QChar& ch)                { return static_cast<Qt::Key>(QChar(ch).unicode()); }
}
