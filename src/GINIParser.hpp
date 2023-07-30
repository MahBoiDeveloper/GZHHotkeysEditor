#pragma once
#include <string>
#include <memory>
#include <list>

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
        std::list<GINIKey> Keys;
    };

public: // Data
    inline static std::unique_ptr<GINIParser> Instance;
private:
    std::string Path;
    std::list<GINISection> Sections;

public: // Methods
    GINIParser() = delete;
    GINIParser(std::string strFileSample);

    void Parse();

    void Save();
    void Save(std::string strFileSample);

    std::list<std::string> GetSectionsName() const;
    std::list<std::string> GetSectionKeys(const std::string& strSectionName) const;
    std::string            GetSectionValue(const std::string& strSectionName, const std::string& strSectionKey) const;

    void SetSectionValue(const string& strName, const string& strKey, const string& strValue);
private:
    void Parse();
};
