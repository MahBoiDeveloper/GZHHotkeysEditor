#pragma once
#include <string>
#include <QString>
#include <QJsonObject>

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
    static QJsonValue Query(const QJsonObject&, const QString& strQuery);

private:
    QString FileName;
    QJsonObject JsonMainObject;
};
