#pragma once

#include <QImage>

class GuiConfig
{

public:
    inline static const QSize startButtonsSize = QSize(230, 110);

public:
    GuiConfig() = delete;

    static QImage decodeWebpIconPath(const QString& iconPath);
    static QImage decodeWebpIcon(const QString& iconName);

private:
    static QStringList findAllMatchingFiles(const QString& pathToDir, const QString& nameFilter);
};
