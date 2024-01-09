#pragma once

#include <QMap>

class Config
{
public:
    inline static const QString resourcesFolder  = "Resources";
    inline static const QString translationsPath = resourcesFolder + "/Translations";
    inline static const QString iconsPath        = resourcesFolder + "/Icons";
    inline static const QString defaultIconFile  = iconsPath + "/NoImageSmall.webp";
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
        {Entities::Buildings, "Buildings"},
        {Entities::Infantry, "Infantry"},
        {Entities::Vehicles, "Vehicles"},
        {Entities::Aircraft, "Aircraft"}
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

public:
    Config() = delete;

    static const QString GetLocaleFromLangEnum(Languages language);
    static Languages GetLangEnumByLocale(const QString& locale);
    static Languages GetLangEnumByLocale(const std::string& locale);
    static const QString GetStringFromLangEnum(Languages language);
};
