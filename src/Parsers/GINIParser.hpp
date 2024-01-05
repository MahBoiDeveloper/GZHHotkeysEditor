#pragma once
#include <vector>
#include <memory>
#include <QString>

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
        std::string          Name;
        std::vector<GINIKey> Keys;
    };

public: // Data
    inline static std::unique_ptr<GINIParser> Instance;
private:
    std::string Path;
    std::vector<GINISection> Sections;

public: // Methods
    GINIParser() = delete;
    GINIParser(const char* strFileSample);
    GINIParser(const std::string& strFileSample);
    GINIParser(const QString& strFileSample);

    void Save();
    void Save(const std::string& strFileSample);
    void Save(const char* strFileSample);
    void Save(const QString& strFileSample);

    std::vector<std::string> GetSectionsNames()                                                                    const;
    std::vector<std::string> GetSectionKeys  (const char* strSectionName)                                          const;
    std::vector<std::string> GetSectionKeys  (const std::string& strSectionName)                                   const;
    std::vector<std::string> GetSectionKeys  (const QString& strSectionName)                                       const;
    std::string              GetSectionValue (const char* strSectionName, const char* strSectionKey)               const;
    std::string              GetSectionValue (const std::string& strSectionName, const std::string& strSectionKey) const;
    QString                  GetSectionValue (const QString& strSectionName, const QString& strSectionKey)         const;

    void SetSectionValue(const std::string& strName, const std::string& strKey, const std::string& strValue);
    void SetSectionValue(const char* strName, const char* strKey, const char* strValue);
    void SetSectionValue(const QString& strName, const QString& strKey, const QString& strValue);
private:
    void Parse();
};
