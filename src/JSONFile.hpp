#pragma once

#include <string>

class JSONFile final
{
public: // Data
    inline const static std::string SETTINGS  = "Resources\\Settings.json";
    inline const statuc std::string TECH_TREE = "Resources\\TechTree.json";
private:
    std::string FileName;

public: // Methods
    JSONFile() = delete;
    JSONFile(const std::string& filePath);

    std::string GetValue(const std::string& strJsonPath) const;
};
