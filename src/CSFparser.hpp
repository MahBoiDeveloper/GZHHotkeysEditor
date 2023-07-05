#pragma once

#include <string>
#include <sstream>
#include <cstring>
#include <fstream>
#include <list>
#include <memory>

#include "Helper.hpp"

#define EMPTY_WSTRING to_wstring('\0')
#define EMPTY_STRING  to_string ('\0')

using namespace std;

struct CompiledString
{
public:
    string  Name;
    wstring Value;
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

class CSFparser
{
public: // Data
	static inline unique_ptr<CSFparser> Instance;

private:
    const uint8_t FSC[4]  {' ', 'F', 'S', 'C'}; // Begining of any CSF file header
    const uint8_t LBL[4]  {' ', 'L', 'B', 'L'}; // Begining of any string name aka "label"
    const uint8_t RTS[4]  {' ', 'R', 'T', 'S'}; // Begining of any string value aka "string"
    const uint8_t WRTS[4] {'W', 'R', 'T', 'S'}; // Begining of any string with extra value
    const uint32_t CNC_CSF_VERSION = 3;         // Standart file format. Legacy by WW

    string Path;
    CSFHeader Header;

    list<CompiledString>* pTable;

private: // Methods
    void Parse();
    void ReadHeader(ifstream* csfFile);
    void ReadBody(ifstream* csfFile);

    void WriteHeader(ofstream* csfFile);
    void WriteBody(ofstream* csfFile);

public:
    CSFparser(const string& strFilePath);
	~CSFparser();
    
    void Save();
    void Save(string strFileName);

    void AddString(CompiledString csString);
    void AddString(list<CompiledString> csList);
    void AddEmptyString(string strName);

    list<string>* GetStringNames();
    wstring GetStringValue(string strName);
    list<string>* GetCategories();
    list<string>* GetCategoryStrings(string strCategoryname);

    void ChangeStringName(string strOldName, string strNewName);
    void ChangeStringValue(string strOldValue, string strNewValue);
    
    void DeleteString(string strName);
    void DeleteString(CompiledString csString);
};
