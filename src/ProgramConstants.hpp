#pragma once
#include <memory>
#include <QMap>
#include <QSet>
#include <QPair>
#include <QSize>
#include <QObject>

#include "StringExt.hpp"
#include "Settings.hpp"

#define PROGRAM_CONSTANTS ProgramConstants::Instance

enum class GameObjectTypes
{
    Buildings,
    Infantry,
    Vehicles,
    Aircrafts
};

enum class Languages
{
    English,
    Russian,
    Count
};

class ProgramConstants
{
private: // Data
    std::unique_ptr<Settings>                       SettingsFile = nullptr;
public:
    inline static std::unique_ptr<ProgramConstants> Instance     = nullptr;

    // Folders
    const QString          RESOURCE_FOLDER         = "Resources";
    const QString          BINARIES_FOLDER         = RESOURCE_FOLDER + "\\Binaries";
    const QString          TRANSLATIONS_FOLDER     = RESOURCE_FOLDER + "/Translations";
    const QString          ICONS_FOLDER            = RESOURCE_FOLDER + "/Icons";
    const QString          THEME_FOLDER            = RESOURCE_FOLDER + "/Theme";
    const QString          QT_ICONS_FOLDER         = ":/icons";
    
    // Resource files
    const QString          TECH_TREE_FILE          = RESOURCE_FOLDER + "/TechTree.json";
    const QString          SETTINGS_FILE           = RESOURCE_FOLDER + "/Settings.json";
    const QString          STYLES_SHEET_FILE       = THEME_FOLDER    + "/Styles.css";

    // Build-in files
    const QString          MISSING_ICON_FILE       = QT_ICONS_FOLDER + "/NoImageSmall.webp";
    const QString          EDITOR_ICON_FILE        = QT_ICONS_FOLDER + "/EditorIconSmall.webp";
    const QString          EDITOR_BIG_ICON_FILE    = QT_ICONS_FOLDER + "/EditorIconBig.webp";
    const QString          GEARS_ICON_FILE         = QT_ICONS_FOLDER + "/Gears.webp";

    // Window titles
    const QString          COMMON_TITLE            = "C&C: Generals Zero Hour Hotkey Editor";
    const QString          SHORT_COMMON_TITLE      = "C&C: GZH Hotkey Editor";
    const QString          EDITOR_TITLE            = SHORT_COMMON_TITLE + " — Editor";
    const QString          LOAD_TITLE              = SHORT_COMMON_TITLE + " — Load";
    const QString          CREATE_TITLE            = SHORT_COMMON_TITLE + " — New Set Up";

    // Magic numbers that become known
    const double           START_WIDGET_SIZE_RATIO = 3./7.;
    const QSize            START_BUTTON_SIZE       = QSize(230, 110);
    const QSize            LANGUAGE_CHANGE_SIZE    = QSize(250, 100);
    const int              ICON_MIN_HEIGHT         = 80;
    const int              ICON_SCALING_HEIGHT     = 25;
    const int              KEYBOARD_KEY_WIDTH      = 50;
    const int              EMPTY_KEY_WIDTH         = 25;

    // Errors
    const char*            SETTINGS_NO_FOUND       = "Unable to find \"Settings.json\" in \"Resource\" folder.";
    const char*            TECH_TREE_NO_FOUND      = "Unable to find \"TechTree.json\" in \"Resource\" folder.";
    const char*            THEME_FOLDER_NO_FOUND   = "Unable to find \"Resource/Theme\" folder.";
    const char*            ICONS_FOLDER_NO_FOUND   = "Unable to find \"Resource/Icons\" folder.";
    const char*            TRANSLATIONS_NO_FOUND   = "Unable to find \"Resource/Translations\" folder.";
    const char*            UNKNOWN_ERROR           = "Unknown error has been occured.";

    const QString          CSF_ERROR_HEADER        = QObject::tr("Error with CSF file");
    const QString          CSF_EMPTY_STRING_ERROR  = QObject::tr("Cannot process the empty file.");
    const QString          CSF_DOESNT_EXIST_ERROR  = QObject::tr("Unable to find selected CSF file.");
    const QString          CSF_NO_CTLBAR_ERROR     = QObject::tr("Choosen CSF file doesn't have CONTROLBAR category. Make sure that you are load correct file.");
    const QString          CSF_NO_OBJECT_ERROR     = QObject::tr("Choosen CSF file doesn't have OBJECT category. Make sure that you are load correct file.");
    const QString          CSF_EMPTY_DATA_ENGLISH  = QObject::tr("Unable find \"generals.csf\" file in \"Game/Data/English\" folder.");

    // Other constants
    const QString          HOTKEY_CSF_CATEGORY     = "CONTROLBAR";
    const QString          OBJECT_CSF_CATEGORY     = "OBJECT";
    const QVector<QString> GLA_SHORT_NAMES         = {"GLA", "TOX", "STL", "DML"};
    const QVector<QString> USA_SHORT_NAMES         = {"USA", "SWG", "AIR", "LSR"};
    const QVector<QString> PRC_SHORT_NAMES         = {"PRC", "TNK", "INF", "NUK"};

    const QSet<Qt::Key> DEFAULT_ALLOWED_KEYS =
    {
        Qt::Key_R, Qt::Key_T, Qt::Key_Y, Qt::Key_U, Qt::Key_O, Qt::Key_I, Qt::Key_P,
        Qt::Key_A, Qt::Key_S, Qt::Key_D, Qt::Key_F, Qt::Key_G, Qt::Key_H, Qt::Key_J, Qt::Key_K, Qt::Key_L,
        Qt::Key_Z, Qt::Key_X, Qt::Key_C, Qt::Key_V, Qt::Key_B, Qt::Key_N, Qt::Key_M
    };

    const QMap<QChar, Qt::Key> KEYBOARD_KEYS = 
    {
        {'Q', Qt::Key_Q}, {'W', Qt::Key_W}, {'E', Qt::Key_E}, {'R', Qt::Key_R}, {'T', Qt::Key_T}, {'Y', Qt::Key_Y}, {'U', Qt::Key_U}, {'I', Qt::Key_I}, {'O', Qt::Key_O}, {'P', Qt::Key_P},
        {'A', Qt::Key_A}, {'S', Qt::Key_S}, {'D', Qt::Key_D}, {'F', Qt::Key_F}, {'G', Qt::Key_G}, {'H', Qt::Key_H}, {'J', Qt::Key_J}, {'K', Qt::Key_K}, {'L', Qt::Key_L}, 
        {'Z', Qt::Key_Z}, {'X', Qt::Key_X}, {'C', Qt::Key_C}, {'V', Qt::Key_V}, {'B', Qt::Key_B}, {'N', Qt::Key_N}, {'M', Qt::Key_M}
    };

    const QMap<Languages, QPair<QString, QString>> LANGUAGES_STRINGS =
    {
        {Languages::English, {"en", "English"}},
        {Languages::Russian, {"ru", "Русский"}}
    };

    const QMap<GameObjectTypes, QString> INGAME_ENTITIES_STRINGS =
    {
        {GameObjectTypes::Buildings, QObject::tr("Buildings")},
        {GameObjectTypes::Infantry,  QObject::tr("Infantry")},
        {GameObjectTypes::Vehicles,  QObject::tr("Vehicles")},
        {GameObjectTypes::Aircrafts, QObject::tr("Aircrafts")}
    };

public: // Methods
    ProgramConstants();
    /// @brief Parse `Resource\Settings.json`.
    void InitializeFileSettings();
    /// @brief Returns `QSet` of available keys from `QWEWRTY` keyboard to choice by user.
    const QSet<Qt::Key> GetAllowedKeys();
    /// @brief Returns field status for console from settings file.
    const bool IsConsoleEnabled();
};
