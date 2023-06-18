#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class CSFparser
{
private: // Data
    const char* FSC {" FSC"};           // Begining of CSF file header
    const char* LBL {" LBL"};           // Begining of any string name aka "label"
    const char* LBL {" RTS"};           // Begining of any string value aka "string"
    const char* LBL {"WRTS"};           // Begining of extra string value
    const uint32_t CNC_CSF_VERSION = 3; // Standart file format. Legacy by WW

    vector<string> Table;
    vector<string> ExtraTable;
private: // Private methods
    void Parse();
    void ParseHeader();
    void ParseBody();

    bool InvertAllBytesInArray(uint8_t* array);
    bool IsASCII(string strSample);
public: // Public methods
    CSFparser();
    CSFparser(string strFilePath);
    ~CSFparser();
    
    void Save();
    void Save(string strFileName);
};
