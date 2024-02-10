#pragma once
#include <QSize>
#include <QFileInfo>
#include "../Config.hpp"

class GUIConfig
{
private: // Data
    inline static QMap<QString, QImage> ImagesCache;
public:
    inline static const QSize   START_BUTTON_SIZE   = QSize(230, 110);
    inline static const int     ICON_MIN_HEIGHT     = 80;
    inline static const int     ICON_SCALING_HEIGHT = 25;
    inline static const QString QT_ICONS_FOLDER     = ":/my/icons";
    inline static const QString DEFAULT_ICON_PATH   = QT_ICONS_FOLDER + "/NoImageSmall.webp";
    inline static const QString ICONS_FOLDER        = Config::RESOURCE_FOLDER + "/Icons";

private: // Methods
    static QFileInfo FindIconFile(const QString& pathToIconsDir, const QString& fileBaseName);
    static QImage    DecodeWebpIconPath(const QString& iconPath);
    static QImage    DecodeImageFromData(const QByteArray& iconData);
public:
    GUIConfig() = delete;

    static QImage  DecodeWebpIcon(const QString& iconName);
    static QImage  DecodeDefaultWebpIcon();
    static QPixmap GetEntityTypePixmap(Config::GameObjectTypes entityType);

};
