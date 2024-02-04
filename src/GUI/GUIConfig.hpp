#pragma once
#include <QSize>
#include <QFileInfo>
#include "../Config.hpp"

class GUIConfig
{
public:
    inline static const QSize   START_BUTTON_SIZE   = QSize(230, 110);
    inline static const int     ICON_MIN_HEIGHT     = 80;
    inline static const int     ICON_SCALING_HEIGHT = 25;
    inline static const QString QT_ICONS_FOLDER     = ":/my/icons";
    inline static const QString DEFAULT_ICON_PATH   = QT_ICONS_FOLDER + "/NoImageSmall.webp";
    inline static const QString ICONS_FOLDER        = Config::RESOURCE_FOLDER + "/Icons";

public:
    GUIConfig() = delete;

    static QImage decodeWebpIcon(const QString& iconName);
    static QImage decodeDefaultWebpIcon();
    static QPixmap getEntityTypePixmap(Config::EntitiesTypes entityType);

private:
    static QFileInfo findIconFile(const QString& pathToIconsDir, const QString& fileBaseName);
    static QImage decodeWebpIconPath(const QString& iconPath);
    static QImage decodeImageFromData(const QByteArray& iconData);

private:
    inline static QMap<QString, QImage> imagesCache;
};
