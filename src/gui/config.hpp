#pragma once
#include <QString>
#include <QMap>
#include <QSize>
#include <QFile>
#include <QDebug>
#include <QImage>

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

    inline static const QString translationsPath = "Resources/Translations";
    inline static const QString iconsPath        = "Resources/Icons";

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
    };
    static Languages GetLangEnumByLocale(QString locale)
    {
        for(auto it = LANGUAGES_STRINGS.constBegin(); it != LANGUAGES_STRINGS.constEnd(); ++it)
        {
            if (GetLocaleFromLangEnum(it.key()) == locale)
                return it.key();
        }
        return Languages::English;
    };
    static QString GetStringFromLangEnum(Languages language)
    {
        return LANGUAGES_STRINGS.find(language)->second;
    };

    inline static QImage decodeWebpIcon(const QString& iconName)
    {
        const QString iconPostfix   = ".webp";
        QFile iconFile(iconsPath + "/" + iconName + iconPostfix);
        if(iconFile.open(QIODevice::ReadOnly))
        {
            QByteArray imageData = iconFile.readAll();
            iconFile.close();
            int width, height;
            uint8_t* decodedImage = WebPDecodeRGBA((const uint8_t*)imageData.constData(),
                                                   imageData.size(),
                                                   &width,
                                                   &height);
            return QImage(decodedImage, width, height, QImage::Format_RGBA8888);
        }
        else
        {
            qDebug() << "File not opened!";
            return QImage();
        }
    }
};
