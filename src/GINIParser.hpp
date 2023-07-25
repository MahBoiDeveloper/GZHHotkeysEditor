#pragma once
#include <string>
#include <memory>
#include <list>

struct GINISection final
{
    std::string            Name;
    std::list<std::string> Keys;
};

class GINIParser final
{
public: // Data
    inline static std::unique_ptr<GINIParser> Instance;
private:
    std::list<GINISection> Sections;
    std::string Path;

public: // Methods
    GINIParser() = delete;
    GINIParser(std::string strFileSample);

    void Save();
    void Save(std::string strFileSample);

    std::list<std::string> GetSectionsName();
    std::list<std::string> GetSectionKeys(std::string strSectionName);
    std::string            GetSectionValue(std::string strSectionName, std::string strSectionKey);

    void SetSectionValue(std::string strSectionName, std::string strSectionKey, std::string strSectionValue);
private:
    void Parse();
};
