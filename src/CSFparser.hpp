#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <list>
using namespace std;

struct CompiledString
{
public:
    string Name;
    string Value;
};

struct ExtraCompiledString : CompiledString
{
public:
    string ExtraValue;
};

struct CSFHeader
{
public:
    //uint8_t  space;
    //uint8_t  f;
    //uint8_t  s;
    //uint8_t  c;
    uint8_t csfChars[4];
    uint32_t formatVersion;
    uint32_t numberOfLabels;
    uint32_t numberOfStrings;
    uint32_t uselessBytes;
    uint32_t languageCode;
};

class CSFparser
{
private: // Data
    const uint8_t FSC[4]  {' ', 'F', 'S', 'C'}; // Begining of CSF file header
    const uint8_t LBL[4]  {' ', 'L', 'B', 'L'}; // Begining of any string name aka "label"
    const uint8_t RTS[4]  {' ', 'R', 'T', 'S'}; // Begining of any string value aka "string"
    const uint8_t WRTS[4] {'W', 'R', 'T', 'S'}; // Begining of extra string value
    const uint32_t CNC_CSF_VERSION = 3;         // Standart file format. Legacy by WW

    string Path;
    CSFHeader Header;

    list<CompiledString>* pTable;
    list<ExtraCompiledString>* pExtraTable;
private: // Private methods
    void Parse();
    void ParseHeader(ifstream* openedCSF);
    void ParseBody(ifstream* openedCSF);

    bool IsASCII(string strSample);
public: // Public methods
    CSFparser();
    CSFparser(const string& strFilePath);
    ~CSFparser();
    
    void Save();
    void Save(string strFileName);

    void AddString(CompiledString csString);
    void AddString(list<CompiledString> csList);
    void AddString(ExtraCompiledString csString);
    void AddString(list<ExtraCompiledString> csList);
    void AddEmptyString(string strName);

    list<string> GetStringNames();
    string GetStringValue(string strName);
    list<string> GetExtraStringNames();
    string GetExtraStringValue(string strName);

    void ChangeStringName(string strOldName, string strNewName);
    void ChangeStringValue(string strOldValue, string strNewValue);
    
    void DeleteString(string strName);
    void DeleteString(CompiledString csString);

    void ConvertExtraStringsToNormal();
};
