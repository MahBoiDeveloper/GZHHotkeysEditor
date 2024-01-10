#include "gui_config.hpp"

#include <QFile>
#include <QDir>
#include <QDebug>

#include <config.hpp>
#include <webp/decode.h>
#include "../Logger.hpp"

QImage GuiConfig::decodeWebpIconPath(const QString& iconPath)
{
    QFile iconFile(iconPath);

    if(iconPath.isEmpty() || !iconFile.open(QIODevice::ReadOnly))
    {
        QString defaultIconFile = Config::defaultIconFile;

        LOGMSG("No icon file [" + iconFile.fileName() + "] was found");
        iconFile.setFileName(defaultIconFile);
        if (!iconFile.open(QIODevice::ReadOnly))
        {
            LOGMSG("No default icon file [" + defaultIconFile + "] was found");
            return QImage{};
        }
    }

    QByteArray imageData = iconFile.readAll();
    iconFile.close();

    int width, height;
    uint8_t* decodedImage = WebPDecodeRGBA(reinterpret_cast<const uint8_t*>(imageData.constData()), // amogus
                                           imageData.size(),
                                           &width,
                                           &height);
    return QImage{decodedImage, width, height, QImage::Format_RGBA8888};
}

QImage GuiConfig::decodeWebpIcon(const QString& iconName)
{
    QStringList allMatchIconFiles = findAllMatchingFiles(Config::iconsPath, iconName);
    QString iconPath;
    if (!allMatchIconFiles.isEmpty())
    {
        iconPath = allMatchIconFiles.first();
    }

    return decodeWebpIconPath(iconPath);
}

QStringList GuiConfig::findAllMatchingFiles(const QString& pathToDir, const QString& nameFilter)
{
    QStringList files;

    // find all files and dirs in current directory
    QFileInfoList fileInfoList = QDir{pathToDir}.entryInfoList(QDir::Filter::Files |
                                                               QDir::Filter::Dirs |
                                                               QDir::Filter::NoDotAndDotDot);

    // if dir -> recursive find, if file -> remember path
    for (const auto & fileInfo : fileInfoList)
    {
        if (fileInfo.isDir())
        {
            files.append(findAllMatchingFiles(fileInfo.absoluteFilePath(), nameFilter));
        }
        else
        {
            if (fileInfo.fileName().contains(nameFilter))
            {
                files.append(fileInfo.absoluteFilePath());
            }
        }
    }

    return files;
}
