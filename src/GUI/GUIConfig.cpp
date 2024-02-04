#include <QDir>
#include <QImage>
#include <QPixmap>

#include "../../libwebp/src/webp/decode.h"
#include "../Logger.hpp"
#include "GUIConfig.hpp"

QImage GUIConfig::decodeWebpIcon(const QString& iconName)
{
    // If it there, get the image from cache
    const auto it = imagesCache.constFind(iconName);
    if (it != imagesCache.constEnd()) return it.value();

    // Find
    const QFileInfo targetIconFile = findIconFile(ICONS_FOLDER, iconName);

    if (targetIconFile.exists())
    {
        // Get the image
        const QImage targetImage = decodeWebpIconPath(targetIconFile.absoluteFilePath());
        // Save the image in the cache
        imagesCache.insert(iconName, targetImage);
        // Return the image
        return targetImage;
    }
    else
    {
        return decodeDefaultWebpIcon();
    }
}

QImage GUIConfig::decodeDefaultWebpIcon()
{
    return decodeWebpIconPath(DEFAULT_ICON_PATH);
}

QPixmap GUIConfig::getEntityTypePixmap(Config::EntitiesTypes entityType)
{
    return QPixmap{QT_ICONS_FOLDER + "/" + QString{"%1.png"}.arg(Config::ENTITIES_STRINGS.value(entityType))};
}

QFileInfo GUIConfig::findIconFile(const QString& pathToIconsDir, const QString& fileBaseName)
{
    // Find all files and dirs in current directory
    QFileInfoList fileInfoList = QDir{pathToIconsDir}.entryInfoList(QDir::Filter::Files |
                                                                    QDir::Filter::Dirs  |
                                                                    QDir::Filter::NoDotAndDotDot);

    for (const auto & fileInfo : fileInfoList)
    {
        // if dir -> recursive find
        if (fileInfo.isDir())
        {
            QFileInfo foundFile = findIconFile(fileInfo.absoluteFilePath(), fileBaseName);

            // Return if it's a complete match
            if (foundFile.baseName() == fileBaseName) return foundFile;
        }
        // else if it is a matching file -> return it
        else
        {
            if (fileInfo.baseName() == fileBaseName) return fileInfo;
        }
    }

    return QFileInfo{};
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
