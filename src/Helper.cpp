#include "Helper.hpp"
#include <iostream>

string Helper::GetWindowsVersion()
{
    wstring returnValue = EMPTY_WSTRING;

    HKEY rKey;
    DWORD Size = 256;
    TCHAR Reget[Size] = { 0 };
    DWORD RegetPath = sizeof(Reget);
    RegOpenKeyExA(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"), NULL, KEY_QUERY_VALUE, &rKey);
    RegQueryValueExA(rKey, _T("ProductName"), NULL, NULL, (LPBYTE)&Reget, &RegetPath);
    RegCloseKey(rKey);
    // RegGetValueW
    // (
    //     HKEY_LOCAL_MACHINE,
    //     _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion")
    //     _T("ProductName"),
    //     RRF_RT_REG_SZ,
    //     NULL,
    //     (PVOID)&Reget[0],
    //     &Size
    // );

    std::wcout << Reget << std::endl;

    return Helper::CharArrayToString(sizeof(Reget), &Reget[0]);
}

wstring Helper::GetProcessorInfo()
{
    wstring returnValue = EMPTY_WSTRING;

    return returnValue;
}

wstring Helper::GetMemoryInfo()
{
    wstring returnValue = EMPTY_WSTRING;
    
    return returnValue;
}

string Helper::GetUUID()
{
	stringstream ss;

	// Magic code by stackoverflow: https://stackoverflow.com/questions/24365331/how-can-i-generate-uuid-in-c-without-using-boost-library
	UUID uuid;
	auto tmpUuidCreate = UuidCreate(&uuid);
	char* str;
	auto tmpUuidToStringA = UuidToStringA(&uuid, (RPC_CSTR*)(&str));
	ss << str << endl;
	RpcStringFreeA((RPC_CSTR*)(&str));

	return ss.str();
}

string Helper::GetCurrentTime()
{
    time_t timeStomp = time(nullptr);
    tm timeNow;
    localtime_s(&timeNow, &timeStomp);

    char currentTime[128];
    strftime(currentTime, sizeof(currentTime), "%Y-%m-%d %X", &timeNow);

    stringstream ss;
    ss << currentTime;

    return ss.str();
}

bool Helper::IsASCII(string strSample)
{
    return false;
}

string Helper::CharArrayToString(int arrayLength, char* pArray)
{
    stringstream ss;
    
    for(int i = 0 ; i < arrayLength; i++)
        ss << pArray[i];

    return ss.str();
}

wstring Helper::WharArrayToWstring(int arrayLength, wchar_t* pArray)
{
    wstringstream wss;
    
    for(int i = 0 ; i < arrayLength; i++)
        wss << pArray[i];

    return wss.str();
}
