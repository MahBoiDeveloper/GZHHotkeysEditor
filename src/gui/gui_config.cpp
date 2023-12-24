#include "gui_config.hpp"
#include <config.hpp>

#include <QFile>
#include <QDir>
#include <QDebug>

#include <webp/decode.h>

QImage GuiConfig::decodeWebpIconPath(const QString& iconPath)
{
    QFile iconFile(iconPath);

    if(!iconFile.open(QIODevice::ReadOnly))
    {
        QString defaultIconFile = QString::fromStdString(Config::defaultIconFile);

        qDebug() << "No icon file.";
        iconFile.setFileName(defaultIconFile);
        if (!iconFile.open(QIODevice::ReadOnly))
        {
            qDebug() << "No default icon file." << defaultIconFile;
            return QImage{};
        }
    }

    QByteArray imageData = iconFile.readAll();
    iconFile.close();

    int width, height;
    uint8_t* decodedImage = WebPDecodeRGBA((const uint8_t*)imageData.constData(),
                                           imageData.size(),
                                           &width,
                                           &height);
    return QImage(decodedImage, width, height, QImage::Format_RGBA8888);
}

QImage GuiConfig::decodeWebpIcon(const QString& iconName)
{
    QStringList allMatchIconFiles = findAllMatchingFiles(QString::fromStdString(Config::iconsPath), iconName);
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

    // if dir -> recursive find, file -> remember path
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
                qDebug() << "USA file name " << fileInfo.fileName();
                files.append(fileInfo.absoluteFilePath());
            }
        }
    }

    return files;
}
