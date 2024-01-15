#pragma once

#include <QMap>
#include <QObject>

class Config
{
public: // Data
    inline static const QString resourcesFolder  = "Resources";
    inline static const QString translationsPath = resourcesFolder + "/Translations";
    inline static const QString techTreeFile     = resourcesFolder + "/TechTree.json";
    inline static const double recomendedStartWidgetSizeRatio = 3./7.;

    enum class Entities
    {
        Buildings,
        Infantry,
        Vehicles,
        Aircraft
    };

    inline static const QMap<Entities, QString> ENTITIES_STRINGS =
    {
        {Entities::Buildings, QObject::tr("Buildings")},
        {Entities::Infantry,  QObject::tr("Infantry")},
        {Entities::Vehicles,  QObject::tr("Vehicles")},
        {Entities::Aircraft,  QObject::tr("Aircraft")}
    };

    enum class Languages
    {
        English,
        Russian,
        Count
    };

    inline static const QMap<Languages, QPair<QString, QString>> LANGUAGES_STRINGS =
    {
        {Languages::English, {"en", "English"}},
        {Languages::Russian, {"ru", "Русский"}}
    };

public: // Methods
    Config() = delete;

    static const QString GetLocaleFromLangEnum(Languages language);
    static Languages GetLangEnumByLocale(const QString& locale);
    static Languages GetLangEnumByLocale(const std::string& locale);
    static const QString GetStringFromLangEnum(Languages language);
};
