#pragma once

#include <list>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>
#include <QStringList>

class CSFParser final
{
public: // Data types declarations
    struct CompiledString
    {
    public:
        std::string  Name;
        std::wstring Value;
    };

    struct HotkeyAssociation
    {
    public:
        std::string StringName;
        wchar_t HotkeyLetter;
    };

    struct CSFHeader
    {
    public:
        uint8_t  csfChars[4];
        uint32_t formatVersion;
        uint32_t numberOfLabels;
        uint32_t numberOfStrings;
        uint32_t uselessBytes;
        uint32_t languageCode;
    };
public: // Data
    inline static std::unique_ptr<CSFParser> Instance;

private:
    const uint8_t  FSC[4]  {' ', 'F', 'S', 'C'}; // Begining of any CSF file header
    const uint8_t  LBL[4]  {' ', 'L', 'B', 'L'}; // Begining of any string name aka "label"
    const uint8_t  RTS[4]  {' ', 'R', 'T', 'S'}; // Begining of any string value aka "string"
    const uint8_t  WRTS[4] {'W', 'R', 'T', 'S'}; // Begining of any string with extra value
    const uint32_t CNC_CSF_VERSION = 3;          // Standart file format. Legacy by WW

    std::string Path;
    CSFHeader Header;

    std::list<CompiledString> Table;

private: // Methods
    void Parse();
    void ReadHeader(std::ifstream* csfFile);
    void ReadBody(std::ifstream* csfFile);

    void WriteHeader(std::ofstream* csfFile);
    void WriteBody(std::ofstream* csfFile);

public:
    CSFParser(const char* strFilePath);
    CSFParser(const std::string& strFilePath);
    CSFParser(const QString& strFilePath);

    void Save();
    void Save(const char* strFileName);
    void Save(const std::string& strFileName);
    void Save(const QString& strFileName);

    QString                   GetStringValue(const QString& strName)                                           const;
    QStringList               GetCategoryStrings(const QString& strCategoryName)                               const;
    QStringList               GetCategoryStringsWithFullNames(const QString& strCategoryName)                  const;
    std::wstring              GetStringValue(const std::string& strName)                                       const;
    std::list<std::string>    GetStringNames()                                                                 const;
    std::list<std::string>    GetCategories()                                                                  const;
    std::list<std::string>    GetCategoryStrings(const std::string& strCategoryName)                           const;
    std::list<std::string>    GetCategoryStringsWithFullNames(const std::string& strCategoryName)              const;
    std::list<std::string>    GetStringsContainsSymbol(const wchar_t& wch)                                     const;
    std::list<std::string>    GetStringsContainsSymbol(const wchar_t& wch, const std::string& strCategoryName) const;
    std::list<CompiledString> GetStringsByNameList(const std::list<std::string>& lstNames)                     const;

    wchar_t GetHotkey(const char* strName)                                                                     const;
    wchar_t GetHotkey(const QString& strName)                                                                  const;
    wchar_t GetHotkey(const std::string& strName)                                                              const;
    std::list<HotkeyAssociation> GetHotkeys(const std::list<std::string>& lstStringNames)                      const;

    void SetHotkey(const char* strName, const wchar_t& wchLetter);
    void SetHotkey(const QString& strName, const wchar_t& wchLetter);
    void SetHotkey(const std::string& strName, const wchar_t& wchLetter);
    void SetStringValue(const std::string& strName, const std::wstring& wstrValue);
    void SetStringValue(const CompiledString& stString);
    void SetStringsValue(const std::list<CompiledString>& lstChanges);
private:
    std::string  CharArrayToString(const size_t& arrayLength, const char* pArray)     const;
    std::wstring WharArrayToWstring(const size_t& arrayLength, const wchar_t* pArray) const;
};
