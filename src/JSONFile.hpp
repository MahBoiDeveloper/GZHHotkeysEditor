#pragma once

#include <string>
#include <QJsonObject>

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

    std::string GetValue(const std::string& strThisLayoutParameter) const;
    QJsonValue GetObject(const std::string& strThisLayoutParameter) const;
    // QJsonObject Query(const std::string& strQuery)                  const;
    // bool EvaluateQuery(const std::string& strQuerySample)           const;
};
