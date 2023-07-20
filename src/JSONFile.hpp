#pragma once

#include <string>
#include <QJsonObject>

class JSONFile final
{
public: // Data
    inline const static std::string SETTING = "Resources\\Settings.json";
private:
    std::string FileName;
    QJsonObject ParsedData;

public: // Methods
    JSONFile() = delete;
    JSONFile(const std::string& filePath);

    std::string GetKeyValue(const std::string& keyName) const;
    QJsonObject GetObject(const std::string& keyName) const;
};
