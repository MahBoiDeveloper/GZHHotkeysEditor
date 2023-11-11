#pragma once

#include <string>
#include <QJsonObject>
#include <QJsonArray>

class JSONFile final
{
public: // Data
    inline const static std::string SETTINGS  = "Resources\\Settings.json";
    inline const static std::string TECH_TREE = "Resources\\TechTree.json";
private:
    std::string FileName;
    QJsonObject JsonMainObject;

public: // Methods
    JSONFile() = delete;
    JSONFile(const std::string& filePath);

    QJsonObject       GetMainObject();
    QJsonValue        Query(const std::string& strQuery)                    const;
    static QJsonValue Query(const QJsonObject&, const std::string& strQuery);
};
