#pragma once
#include <QSize>
#include <QFileInfo>
#include "../ProgramConstants.hpp"

class GUIConfig
{
private: // Data
    inline static QMap<QString, QImage> ImagesCache;
public:
    inline static const QSize   START_BUTTON_SIZE    = QSize(230, 110);
    inline static const int     ICON_MIN_HEIGHT      = 80;
    inline static const int     ICON_SCALING_HEIGHT  = 25;
    inline static const int     KEYBOARD_KEY_WIDTH   = 50;
    inline static const int     EMPTY_KEY_WIDTH      = 25;
    inline static const QString ICONS_FOLDER         = RESOURCE_FOLDER + "/Icons";
    inline static const QString STYLES_SHEET         = RESOURCE_FOLDER + "/Theme/Styles.css";
    inline static const QString QT_ICONS_FOLDER      = ":/icons";
    inline static const QString MISSING_ICON_PATH    = QT_ICONS_FOLDER + "/NoImageSmall.webp";
    inline static const QString EDITOR_ICON_PATH     = QT_ICONS_FOLDER + "/EditorIconSmall.webp";
    inline static const QString EDITOR_BIG_ICON_PATH = QT_ICONS_FOLDER + "/EditorIconBig.webp";

private: // Methods
    /// @brief Search recursively icons in folders.
    static QFileInfo FindIconFile(const QString& pathToIconsDir, const QString& fileBaseName);
    /// @brief Decode WEBP image from path to the icon.
    static QImage    DecodeWebpIconPath(const QString& iconPath);
    /// @brief Decode WEBP image from byte array.
    static QImage    DecodeImageFromData(const QByteArray& iconData);
public:
    GUIConfig() = delete;

    /// @brief Decode WEBP image icon name.
    static QImage  DecodeWebpIcon(const QString& iconName);
    /// @brief Get image if needed file cannot be found.
    static QImage  DecodeMissingWebpIcon();
    /// @brief Return image of the main executable WEBP icon.
    static QImage  DecodeEditorWebpIcon();
    /// @brief Return project's official WEBP image.
    static QImage  DecodeBigEditorWebpIcon();
    /// @brief Return pixel map by object type.
    static QPixmap GetGameObjectTypePixmap(GameObjectTypes goType);
};
