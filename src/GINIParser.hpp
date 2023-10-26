#pragma once
#include <vector>
#include <memory>

class GINIParser final
{
public: // Data types declaration
    struct GINIKey final
    {
        std::string Name;
        std::string Value;
    };

    struct GINISection final
    {
        std::string        Name;
        std::vector<GINIKey> Keys;
    };

public: // Data
    inline static std::unique_ptr<GINIParser> Instance;
private:
    std::string Path;
    std::vector<GINISection> Sections;

public: // Methods
    GINIParser() = delete;
    GINIParser(const std::string& strFileSample);

    void Save();
    void Save(std::string strFileSample);

    std::vector<std::string> GetSectionsName() const;
    std::vector<std::string> GetSectionKeys(const std::string& strSectionName) const;
    std::string              GetSectionValue(const std::string& strSectionName, const std::string& strSectionKey) const;

    void SetSectionValue(const std::string& strName, const std::string& strKey, const std::string& strValue);
private:
    void Parse();
};
