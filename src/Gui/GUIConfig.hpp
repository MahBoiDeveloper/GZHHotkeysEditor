#pragma once

#include <QImage>
#include <QFileInfoList>

#include "../Config.hpp"

class GUIConfig
{
public:
    inline static const QSize startButtonsSize = QSize(230, 110);
    inline static const int entityIconMinimumHeight = 80;
    inline static const QString defaultIconFile = ":/my/icons/NoImageSmall.webp";
    inline static const QString iconsDirPath = Config::resourcesFolder + "/Icons";
    // Images cache
    inline static QMap<QString, QImage> imagesCache;

public:
    GUIConfig() = delete;

    static QImage decodeWebpIcon(const QString& iconName);
    static QImage decodeDefaultWebpIcon();

private:
    static QFileInfo findIconFile(const QString& pathToIconsDir, const QString& fileBaseName);
    static QImage decodeWebpIconPath(const QString& iconPath);
    static QImage decodeImageFromData(const QByteArray& iconData);
};
