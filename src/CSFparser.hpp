#pragma once

#include <string>
#include <sstream>
#include <cstring>
#include <fstream>
#include <list>
#include <memory>

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
	const uint32_t CNC_CSF_VERSION = 3;		    // Standart file format. Legacy by WW

	string Path;
	CSFHeader Header;

    list<CompiledString> Table;

private: // Methods
	void Parse();
	void ReadHeader(ifstream* csfFile);
	void ReadBody(ifstream* csfFile);

	void WriteHeader(ofstream* csfFile);
	void WriteBody(ofstream* csfFile);

public:
    CSFparser(const string& strFilePath);

	void Save();
	void Save(string strFileName);

    list<string> GetStringNames();
    wstring      GetStringValue(const string& strName);
    list<string> GetCategories();
    list<string> GetCategoryStrings(const string& strCategoryName);
    list<string> GetCategoryStringsWithFullNames(const string& strCategoryName);
    list<string> GetStringsContainsSymbol(const wchar_t& wch);
    list<string> GetStringsContainsSymbol(const wchar_t& wch, const string& strCategoryName);
    list<CompiledString> GetStringsByNameList(const list<string>& lstNames);

    void SetStringValue(const string& strName, const wstring& wstrValue);
    void SetStringValue(const CompiledString& stString);
    void SetStringsValue(const list<CompiledString>& lstChanges);
};
