#pragma once
#include <QMap>
#include <QPair>
#include <QObject>
#include <QString>

inline const QPair<Qt::Key, Qt::Key> AVAILABLE_KEYS = {Qt::Key_A, Qt::Key_Z};
inline const QString RESOURCE_FOLDER     = "Resources";
inline const QString TRANSLATIONS_FOLDER = RESOURCE_FOLDER + "/Translations";
inline const QString TECH_TREE_PATH      = RESOURCE_FOLDER + "/TechTree.json";
inline const double  START_WIDGET_SIZE_RATIO = 3./7.;

enum class GameObjectTypes
{
    Buildings,
    Infantry,
    Vehicles,
    Aircrafts
};

inline static const QMap<GameObjectTypes, QString> ENTITIES_STRINGS =
{
    {GameObjectTypes::Buildings, QObject::tr("Buildings")},
    {GameObjectTypes::Infantry,  QObject::tr("Infantry")},
    {GameObjectTypes::Vehicles,  QObject::tr("Vehicles")},
    {GameObjectTypes::Aircrafts, QObject::tr("Aircrafts")}
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
