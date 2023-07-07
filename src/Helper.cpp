#include "Helper.hpp"

string Helper::GetRegTextValue(const char* pPathToFolder, const char* pKeyName)
{
    HKEY rKey;
    DWORD Size = 256;
    TCHAR Reget[Size] = { 0 };

    RegOpenKeyExA(HKEY_LOCAL_MACHINE, pPathToFolder, 0, KEY_READ, &rKey);
    RegQueryValueExA(rKey, pKeyName, NULL, NULL, (LPBYTE)&Reget, &Size);
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

string Helper::GetPathToCNCG()
{
    int windowsBit;
    string Path, Key = "InstallPath";

    if (Helper::GetWindowsBit() == "32-bit")
        windowsBit = 0;
    else
        windowsBit = 1;

    switch (windowsBit)
    {
    case 0: // 32-bit
        Path = "SOFTWARE\\Electronic Arts\\EA Games\\Generals";
        break;

    case 1: // 64-bit
        Path = "SOFTWARE\\WOW6432Node\\Electronic Arts\\EA Games\\Generals";
        break;
    }

    return Helper::GetRegTextValue(Path.c_str(), Key.c_str());
}

string Helper::GetPathToCNCGZH()
{
    int windowsBit;
    string Path, Key = "UserDataLeafName";

    if (Helper::GetWindowsBit() == "32-bit")
        windowsBit = 0;
    else
        windowsBit = 1;

    switch (windowsBit)
    {
    case 0: // 32-bit
        Path = "SOFTWARE\\Electronic Arts\\EA Games\\Command and Conquer Generals Zero Hour";
        break;

    case 1: // 64-bit
        Path = "SOFTWARE\\WOW6432Node\\Electronic Arts\\EA Games\\Command and Conquer Generals Zero Hour";
        break;
    }

    std::wcout << "Try to get access to " << Key.c_str() <<" in " << Path.c_str() << std::endl;
    std::wcout << Helper::GetRegTextValue(Path.c_str(), Key.c_str()).c_str() << std::endl;

    const char* _path = Path.c_str();
    const char* _key  = Key.c_str();

    return Helper::GetRegTextValue(_path, _key);
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
