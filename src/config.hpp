#pragma once
#include <QString>
#include <QMap>
#include <QSize>
#include <QFile>
#include <QDebug>
#include <QImage>
#include <QDir>

#include "webp/decode.h"

class Config
{
public:
    enum class Languages
    {
        English = 0,
        Russian,
        Count
    };

    inline static const QString resourcesFolder  = "Resources";
    inline static const QString translationsPath = "Resources/Translations";
    inline static const QString iconsPath        = "Resources/Icons";
    static inline const QString defaultIconFile  = QString("%1/NoImageSmall.webp").arg(iconsPath);

    inline static const QSize startButtonsSize = QSize(230, 110);
    inline static const double recomendedStartWidgetSizeRatio = 3./7.;

public:
    Config() = delete;

    inline static const QMap<Languages, QPair<QString, QString>> LANGUAGES_STRINGS =
    {
        {Languages::English, {"en", "English"}},
        {Languages::Russian, {"ru", "Русский"}}
    };

    static QString GetLocaleFromLangEnum(Languages language)
    {
        return LANGUAGES_STRINGS.find(language)->first;
    }

    static Languages GetLangEnumByLocale(const QString& locale)
    {
        for(auto it = LANGUAGES_STRINGS.constBegin(); it != LANGUAGES_STRINGS.constEnd(); ++it)
        {
            if (GetLocaleFromLangEnum(it.key()) == locale)
                return it.key();
        }
        return Languages::English;
    }

    static QString GetStringFromLangEnum(Languages language)
    {
        return LANGUAGES_STRINGS.find(language)->second;
    }

    inline static QImage decodeWebpIcon(const QString& iconName)
    {
        QString iconPath;
        QStringList allMatchIconFiles = findAllMatchingFiles(iconsPath, iconName);
        if (!allMatchIconFiles.isEmpty())
        {
            iconPath = allMatchIconFiles.first();
        }

        QFile iconFile(iconPath);

        if(!iconFile.open(QIODevice::ReadOnly))
        {
            qDebug() << "No icon file.";
            iconFile.setFileName(Config::defaultIconFile);
            if (!iconFile.open(QIODevice::ReadOnly))
            {
                qDebug() << "No default icon file." << Config::defaultIconFile;
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

private:
    inline static QStringList findAllMatchingFiles(const QString& pathToDir, const QString& nameFilter)
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
};
