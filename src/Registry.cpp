#pragma comment(lib, "rpcrt4.lib")
#include <sstream>
#include <windows.h>
#include <tchar.h>

#include "Registry.hpp"

using namespace std;

Registry::WindowsBit Registry::GetWindowsBit()
{
    HKEY rKey;
    WindowsBit windowsBit;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\WOW6432Node"), 0, KEY_QUERY_VALUE, &rKey) == ERROR_SUCCESS)
        windowsBit = WindowsBit::Win64;
    else
        windowsBit = WindowsBit::Win32;

    RegCloseKey(rKey);

    return windowsBit;
}

string Registry::GetTextFromKey(const Registry::RootFolder Folder, const char* pPathToFolder, const char* pKeyName)
{
    HKEY  rKey;
    DWORD Size = 256;
    TCHAR Reget[Size] = { 0 };

    switch (Folder)
    {
        case Registry::RootFolder::HKCU :
            RegOpenKeyExA(HKEY_CURRENT_USER, pPathToFolder, 0, KEY_READ, &rKey);
            break;
        
        case Registry::RootFolder::HKLM :
            RegOpenKeyExA(HKEY_LOCAL_MACHINE, pPathToFolder, 0, KEY_READ, &rKey);
            break;
    }

    RegQueryValueExA(rKey, pKeyName, NULL, NULL, (LPBYTE)&Reget, &Size);
    RegCloseKey(rKey);
    
    string returnValue(Reget);
    returnValue.shrink_to_fit();
         
    return returnValue;
}

string Registry::GetPathToGame(const Games game)
{
    string Key  = "InstallPath";
    string Path = Registry::PATHS_TO_GAMES.find(game)->second.find(GetWindowsBit())->second;
    return GetTextFromKey(Registry::RootFolder::HKLM, Path.c_str(), Key.c_str());
}

string Registry::ToString(Games game)
{
    string returnValue;

    switch (game)
    {
        case Games::Generals:
            returnValue = "Generals";
            break;
        case Games::GeneralsZeroHour:
            returnValue = "Generals Zero Hour";
            break;
    }

    return returnValue;
}

bool Registry::IsWindow64bit()
{
    return GetWindowsBit() == WindowsBit::Win64;
}

bool Registry::IsWindow32bit()
{
    return GetWindowsBit() == WindowsBit::Win32;
}

#pragma region Logger methods
    string Registry::GetCurrentUserLanguage()
    {
        const char Path[] = {"Control Panel\\International\\Geo"};
        const char Key[]  = {"Name"};
        return GetTextFromKey(Registry::RootFolder::HKCU, &Path[0], &Key[0]);
    }

    string Registry::GetWindowsVersion()
    {
        const char Path[] = {"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"};
        const char Key[]  = {"ProductName"};
        return GetTextFromKey(Registry::RootFolder::HKLM, &Path[0], &Key[0]);
    }

    string Registry::GetProcessorInfo()
    {
        const char Path[]  = {"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"};
        const char Value[] = {"ProcessorNameString"};
        return GetTextFromKey(Registry::RootFolder::HKLM, &Path[0], &Value[0]);
    }

    string Registry::GetMemoryInfo()
    {
        stringstream ss;
        MEMORYSTATUSEX MemStat;
        MemStat.dwLength = sizeof (MemStat);
        GlobalMemoryStatusEx(&MemStat);

        ss << (MemStat.ullTotalPhys/1024)/1024 << "MiB";
        return ss.str();
    }

    string Registry::GetUUID()
    {
        // Magic code by stackoverflow: https://stackoverflow.com/questions/24365331/how-can-i-generate-uuid-in-c-without-using-boost-library
        stringstream ss;

        UUID uuid;
        auto tmpUuidCreate = UuidCreate(&uuid);
        char* str;
        auto tmpUuidToStringA = UuidToStringA(&uuid, reinterpret_cast<RPC_CSTR*>(&str));
        ss << str;
        RpcStringFreeA(reinterpret_cast<RPC_CSTR*>(&str));

        return ss.str();
    }
#pragma endregion
