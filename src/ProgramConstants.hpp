#pragma once
#include <memory>
#include <QMap>
#include <QSet>
#include <QPair>
#include <QSize>
#include <QObject>

#define PROGRAM_CONSTANTS ProgramConstants::Instance

inline const static QString RESOURCE_FOLDER         = "Resources";
inline const static QString BINARIES_FOLDER         = RESOURCE_FOLDER + "\\Binaries";
inline const static QString TRANSLATIONS_FOLDER     = RESOURCE_FOLDER + "/Translations";
inline const static QString TECH_TREE_PATH          = RESOURCE_FOLDER + "/TechTree.json";
inline const static QString SETTINGS_PATH           = RESOURCE_FOLDER + "/Settings.json";
inline const static double  START_WIDGET_SIZE_RATIO = 3./7.;
inline const static QSize   START_BUTTON_SIZE       = QSize(230, 110);
inline const static QSize   LANGUAGE_CHANGE_SIZE    = QSize(250, 100);
inline const static int     ICON_MIN_HEIGHT         = 80;
inline const static int     ICON_SCALING_HEIGHT     = 25;
inline const static int     KEYBOARD_KEY_WIDTH      = 50;
inline const static int     EMPTY_KEY_WIDTH         = 25;
inline const static QString ICONS_FOLDER            = RESOURCE_FOLDER + "/Icons";
inline const static QString STYLES_SHEET            = RESOURCE_FOLDER + "/Theme/Styles.css";
inline const static QString QT_ICONS_FOLDER         = ":/icons";
inline const static QString MISSING_ICON_PATH       = QT_ICONS_FOLDER + "/NoImageSmall.webp";
inline const static QString EDITOR_ICON_PATH        = QT_ICONS_FOLDER + "/EditorIconSmall.webp";
inline const static QString EDITOR_BIG_ICON_PATH    = QT_ICONS_FOLDER + "/EditorIconBig.webp";

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

class ProgramConstants
{
private: // Data
    QSet<Qt::Key> keys = {};
    bool console       = false;
public:
    inline static std::unique_ptr<ProgramConstants> Instance;

public: // Methods
    ProgramConstants();
    /// @brief Returns QSet of available keys from QWEWRTY keyboard to choice by user.
    const QSet<Qt::Key>& GetAllowedKeys();
    /// @brief Returns field status for console from settings file.
    bool IsConsoleEnabled();
};
