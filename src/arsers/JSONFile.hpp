#pragma once

#include <string>
#include <QJsonObject>
#include <QJsonArray>

class JSONFile final
{
public: // Methods
    JSONFile(const std::string& filePath);

    QJsonObject       GetMainObject();
    QJsonValue        Query(const std::string& strQuery) const;
    static QJsonValue Query(const QJsonObject&, const std::string& strQuery);

private:
    std::string FileName;
    QJsonObject JsonMainObject;
};
