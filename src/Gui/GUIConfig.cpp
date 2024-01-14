#include <QFile>
#include <QDir>
#include <QDebug>

#include "../Logger.hpp"
#include "libwebp/src/webp/decode.h"
#include "GUIConfig.hpp"

QImage GUIConfig::decodeWebpIcon(const QString& iconName)
{
    QStringList allMatchIconFiles = findAllMatchingFiles(iconsPath, iconName);

    if (!allMatchIconFiles.isEmpty())
    {
        // Take the first match
        return decodeWebpIconPath(allMatchIconFiles.first());
    }
    else
    {
        return decodeDefaultWebpIcon();
    }
}

QImage GUIConfig::decodeDefaultWebpIcon()
{
    return decodeWebpIconPath(defaultIconFile);
}

QStringList GUIConfig::findAllMatchingFiles(const QString& pathToDir, const QString& nameFilter)
{
    QStringList files;

    // find all files and dirs in current directory
    QFileInfoList fileInfoList = QDir{pathToDir}.entryInfoList(QDir::Filter::Files |
                                                               QDir::Filter::Dirs  |
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
            // Return if it's a complete match
            if (nameFilter == fileInfo.baseName())
            {
                return {fileInfo.absoluteFilePath()};
            }
            // Else remember this file
            else if (fileInfo.fileName().contains(nameFilter))
            {
                files.append(fileInfo.absoluteFilePath());
            }
        }
    }

    return files;
}

QImage GUIConfig::decodeWebpIconPath(const QString& iconPath)
{
    QFile iconFile(iconPath);

    if(iconPath.isEmpty() || !iconFile.open(QIODevice::ReadOnly))
    {
        if (!iconPath.isEmpty())
        {
            LOGMSG("No icon file [" + iconFile.fileName() + "] was found");
        }
        return decodeDefaultWebpIcon();
    }

    return decodeImageFromData(iconFile.readAll());
}

QImage GUIConfig::decodeImageFromData(const QByteArray& iconData)
{
    int width, height;
    uint8_t* decodedImage = WebPDecodeRGBA(reinterpret_cast<const uint8_t*>(iconData.constData()), // amogus
                                           iconData.size(),
                                           &width,
                                           &height);
    return QImage{decodedImage, width, height, QImage::Format_RGBA8888};
}
