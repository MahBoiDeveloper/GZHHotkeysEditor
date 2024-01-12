#pragma once
#include <QImage>
#include "../config.hpp"

class GUIConfig
{
public: // Data
    inline static const QSize startButtonsSize = QSize(230, 110);
    inline static const int entityIconMinimumHeight = 80;
    inline static const QString defaultIconFile = ":/my/icons/NoImageSmall.webp";
    inline static const QString iconsPath = Config::resourcesFolder + "/Icons";

public: // Method
    GUIConfig() = delete;

    static QImage decodeWebpIcon(const QString& iconName);
    static QImage decodeDefaultWebpIcon();
private:
    static QStringList findAllMatchingFiles(const QString& pathToDir, const QString& nameFilter);
    static QImage decodeWebpIconPath(const QString& iconPath);
    static QImage decodeImageFromData(const QByteArray& iconData);
};
