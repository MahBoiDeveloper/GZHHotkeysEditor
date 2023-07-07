#include "Helper.hpp"

string Helper::GetRegTextValue(const char* pPathToFolder, const char* pKeyName)
{
    HKEY rKey;
    DWORD Size = 256;
    TCHAR Reget[Size] = { 0 };

    RegOpenKeyExA(HKEY_LOCAL_MACHINE, pPathToFolder, 0, KEY_READ, &rKey);
    RegQueryValueExA(rKey, pKeyName, NULL, NULL, (LPBYTE)&Reget, NULL);
    RegCloseKey(rKey);

    string returnValue(Reget);
    returnValue.shrink_to_fit();

    return returnValue;
}

string Helper::GetWindowsVersion()
{
    const char Path[]  = {"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"};
    const char Value[] = {"ProductName"};
    return Helper::GetRegTextValue(&Path[0], &Value[0]);
}

string Helper::GetWindowsBit()
{
    HKEY rKey;
    int result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\WOW6432Node"), 0, KEY_QUERY_VALUE, &rKey);
    RegCloseKey(rKey);

    if (result != ERROR_SUCCESS)
    {
        return "32-bit";
    }
    else
    {
        return "64-bit";
    }
}

string Helper::GetProcessorInfo()
{
    const char Path[]  = {"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"};
    const char Value[] = {"ProcessorNameString"};
    return Helper::GetRegTextValue(&Path[0], &Value[0]);
}

string Helper::GetMemoryInfo()
{
    stringstream ss;
    MEMORYSTATUSEX MemStat;
    MemStat.dwLength = sizeof (MemStat);
    GlobalMemoryStatusEx(&MemStat);

    ss << (MemStat.ullTotalPhys/1024)/1024 << "MB";
    return ss.str();
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
