#include <sstream>
#include <windows.h>
#include <tchar.h>

#include "Helper.hpp"

#pragma region Getters
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
    
    string Helper::GetWindowsBitString()
    {
        if (GetWinBit() == WindowsBit::Win32)
            return "32-bit";
        else
            return "64-bit";
    }

    Helper::WindowsBit Helper::GetWinBit()
    {
       return WinBit;
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
        ss << str;
        RpcStringFreeA((RPC_CSTR*)(&str));
    
        return ss.str();
    }
#pragma endregion

#pragma region Setters
    string Helper::PathToGame(Games game)
    {
        string Key = "InstallPath";
        string Path = pathsToGamesMap.find(game)->second.find(GetWinBit())->second;
        return Helper::GetRegTextValue(Path.c_str(), Key.c_str());
    }

    Helper::WindowsBit Helper::GetWindowsBit()
    {
        HKEY rKey;
        WindowsBit returnValue;
    
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\WOW6432Node"), 0, KEY_QUERY_VALUE, &rKey) == ERROR_SUCCESS)
            returnValue = WindowsBit::Win64;
        else
            returnValue = WindowsBit::Win32;

        RegCloseKey(rKey);

        return returnValue;
    }
#pragma endregion

#pragma region Checks and array merging
    string Helper::CharArrayToString(const int& arrayLength, const char* pArray)
    {
        stringstream ss;
        
        for(int i = 0 ; i < arrayLength; i++)
            ss << pArray[i];
    
        return ss.str();
    }
    
    wstring Helper::WharArrayToWstring(const int& arrayLength, const wchar_t* pArray)
    {
        wstringstream wss;
        
        for(int i = 0 ; i < arrayLength; i++)
            wss << pArray[i];
    
        return wss.str();
    }

    bool Helper::IsWindow64bit()
    {
        return GetWinBit() == WindowsBit::Win64;
    }
    
    bool Helper::IsWindow32bit()
    {
        return GetWinBit() == WindowsBit::Win32;
    }
#pragma endregion
