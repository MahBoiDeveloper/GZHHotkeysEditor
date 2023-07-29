#pragma once
#include <QString>
#include <QMap>
#include <QSize>

class Config
{
public:
    enum class Languages
    {
        English = 0,
        Russian,
        Count
    };

    inline static const QString translationsPath = "Resources/Translations";
    inline static const QString iconsPath        = "Resources/Icons";

    inline static const QSize startButtonsSize = QSize(230, 110);

public:
    Config() = delete;

    inline static const QMap<Languages, QPair<QString, QString>> LANGUAGES_STRINGS =
    {
        {Languages::English, {"en", "English"}},
        {Languages::Russian, {"ru", "Русский"}}
    };

    static QString GetLocaleFromLangEnum(Languages language)
    {
        return LANGUAGES_STRINGS.find(language)->first;
    };
    static Languages GetLangEnumByLocale(QString locale)
    {
        for(auto it = LANGUAGES_STRINGS.constBegin(); it != LANGUAGES_STRINGS.constEnd(); ++it)
        {
            if (GetLocaleFromLangEnum(it.key()) == locale)
                return it.key();
        }
        return Languages::English;
    };
    static QString GetStringFromLangEnum(Languages language)
    {
        return LANGUAGES_STRINGS.find(language)->second;
    };
};
