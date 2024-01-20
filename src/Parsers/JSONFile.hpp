#pragma once
#include <string>
#include <QString>
#include <QJsonObject>

class JSONFile final
{
private: // Data
    QJsonObject JsonMainObject;

public:
    JSONFile(const QString&     filePath);
    JSONFile(const std::string& filePath);
    JSONFile(const char*        filePath);

    const QJsonObject&  GetMainObject();
    QJsonValue          Query(const QString&     strQuery) const;
    QJsonValue          Query(const std::string& strQuery) const;
    QJsonValue          Query(const char*        strQuery) const;
    static QJsonValue   Query(const QJsonObject&, const char*    strQuery);
    static QJsonValue   Query(const QJsonObject&, const QString& strQuery);
};
