#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <memory>

#include <windows.h>
#include <tchar.h>
#pragma comment(lib, "rpcrt4.lib")

#include "info.hpp"

using namespace std;

// Class Helper uses for collect all unsorted methods and functions
class Helper
{
public:
    inline static unique_ptr<Helper> Instance;
private:
    bool   Win32;
    string PathG;
    string PathGZH;

public:
	Helper();

    // Uses in Logger
    string GetCurrentTime();
    string GetProcessorInfo();
    string GetMemoryInfo();
    string GetWindowsBit();
    string GetWindowsVersion();
    string GetPathToCNCG();
    string GetPathToCNCGZH();

    // Uses in CSFparser
	string  GetUUID();

    bool    IsWindow64bit();
    bool    IsWindow32bit();
private:
    string GetRegTextValue(const char* pPathToFolder, const char* pKeyName);
    string SetPathToCNCG();
    string SetPathToCNCGZH();
    bool   SetWindowsBit();
};
