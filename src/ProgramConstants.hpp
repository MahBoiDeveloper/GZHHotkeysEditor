#pragma once
#include <QMap>
#include <QPair>
#include <QObject>
#include <QSize>

inline static const QPair<Qt::Key, Qt::Key> AVAILABLE_KEYS = {Qt::Key_A, Qt::Key_Z}; // To Do: make parse from Setting.json
inline static const QString RESOURCE_FOLDER                = "Resources";
inline static const QString TRANSLATIONS_FOLDER            = RESOURCE_FOLDER + "/Translations";
inline static const QString TECH_TREE_PATH                 = RESOURCE_FOLDER + "/TechTree.json";
inline static const QString SETTINGS_PATH                  = RESOURCE_FOLDER + "/Settings.json";
inline static const double  START_WIDGET_SIZE_RATIO        = 3./7.;
inline static const QSize   START_BUTTON_SIZE              = QSize(230, 110);
inline static const int     ICON_MIN_HEIGHT                = 80;
inline static const int     ICON_SCALING_HEIGHT            = 25;
inline static const int     KEYBOARD_KEY_WIDTH             = 50;
inline static const int     EMPTY_KEY_WIDTH                = 25;
inline static const QString ICONS_FOLDER                   = RESOURCE_FOLDER + "/Icons";
inline static const QString STYLES_SHEET                   = RESOURCE_FOLDER + "/Theme/Styles.css";
inline static const QString QT_ICONS_FOLDER                = ":/icons";
inline static const QString MISSING_ICON_PATH              = QT_ICONS_FOLDER + "/NoImageSmall.webp";
inline static const QString EDITOR_ICON_PATH               = QT_ICONS_FOLDER + "/EditorIconSmall.webp";
inline static const QString EDITOR_BIG_ICON_PATH           = QT_ICONS_FOLDER + "/EditorIconBig.webp";

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

inline static const QMap<QChar, Qt::Key> KEYBOARD_KEYS = 
{
    {'Q', Qt::Key_Q}, {'W', Qt::Key_W}, {'E', Qt::Key_E}, {'R', Qt::Key_R}, {'T', Qt::Key_T}, {'Y', Qt::Key_Y}, {'U', Qt::Key_U}, {'I', Qt::Key_I}, {'O', Qt::Key_O}, {'P', Qt::Key_P},
    {'A', Qt::Key_A}, {'S', Qt::Key_S}, {'D', Qt::Key_D}, {'F', Qt::Key_F}, {'G', Qt::Key_G}, {'H', Qt::Key_H}, {'J', Qt::Key_J}, {'K', Qt::Key_K}, {'L', Qt::Key_L}, 
    {'Z', Qt::Key_Z}, {'X', Qt::Key_X}, {'C', Qt::Key_C}, {'V', Qt::Key_V}, {'B', Qt::Key_B}, {'N', Qt::Key_N}, {'M', Qt::Key_M}
};
