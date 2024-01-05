#pragma once

#include <string>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>

class JSONFile final
{
public: // Methods
    JSONFile(const char* filePath);
    JSONFile(const std::string& filePath);
    JSONFile(const QString& filePath);

    QJsonObject       GetMainObject();
    QJsonValue        Query(const char* strQuery) const;
    QJsonValue        Query(const std::string& strQuery) const;
    QJsonValue        Query(const QString& strQuery) const;
    static QJsonValue Query(const QJsonObject&, const char* strQuery);
    static QJsonValue Query(const QJsonObject&, const std::string& strQuery);
    static QJsonValue Query(const QJsonObject&, const QString& strQuery);

private:
    std::string FileName;
    QJsonObject JsonMainObject;
};
