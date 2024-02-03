#pragma once
#include <QMap>
#include <QObject>

class Config
{
public: // Data
    inline static const QPair<Qt::Key, Qt::Key> AVAILABLE_KEYS = {Qt::Key_A, Qt::Key_Z};

    inline static const QString RESOURCE_FOLDER     = "Resources";
    inline static const QString TRANSLATIONS_FOLDER = RESOURCE_FOLDER + "/Translations";
    inline static const QString TECH_TREE_PATH      = RESOURCE_FOLDER + "/TechTreeTmp.json";
    inline static const double  START_WIDGET_SIZE_RATIO = 3./7.;

    enum class EntitiesTypes
    {
        Buildings,
        Infantry,
        Vehicles,
        Aircraft
    };

    inline static const QMap<EntitiesTypes, QString> ENTITIES_STRINGS =
    {
        {EntitiesTypes::Buildings, QObject::tr("Buildings")},
        {EntitiesTypes::Infantry,  QObject::tr("Infantry")},
        {EntitiesTypes::Vehicles,  QObject::tr("Vehicles")},
        {EntitiesTypes::Aircraft,  QObject::tr("Aircraft")}
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

    /// @brief Return short language name text equivalent of the enum Languages value.
    static const QString GetLanguageShortName(Languages language);
    /// @brief Return full language name text equivalent of the enum Languages value.
    static const QString GetLanguageFullName(Languages language);
    /// @brief Return enum Languages value that equivalent to the text value.
    static Languages     GetLangEnumByLocale(const QString& locale);
    /// @brief Return enum Languages value that equivalent to the text value.
    static Languages     GetLangEnumByLocale(const std::string& locale);
};
