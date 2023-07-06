#pragma once

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
    // Uses in Logger
    static string  GetCurrentTime();
    static wstring GetProcessorInfo();
    static wstring GetMemoryInfo();
    static string GetWindowsVersion();

    // Uses in CSFparser
    static string  GetUUID();
    static bool    IsASCII(string strSample);
    static string  CharArrayToString(int arrayLength, char* pArray);
    static wstring WharArrayToWstring(int arrayLength, wchar_t* pArray);
};
