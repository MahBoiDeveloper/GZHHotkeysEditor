#pragma once

#include <string>
#include <sstream>
#include <ctime>
#include <memory>
#include <Windows.h>
#pragma comment(lib, "rpcrt4.lib")

using namespace std;

class Helper
{
public:
    static inline unique_ptr<Helper> Instance;

    Helper();
    ~Helper();

    string GetCurrentTime();
    bool IsASCII(string strSample);
    string CharArrayToString(int arrayLength, char* pArray);
    wstring WharArrayToWstring(int arrayLength, wchar_t* pArray);
    string GetUUID();
};
