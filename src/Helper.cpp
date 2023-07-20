#include <sstream>
#include <windows.h>
#include <tchar.h>

#include "Helper.hpp"

#pragma region Getters
    /// @brief Returns universal unique identifier as a string. 
    string Helper::GetUUID() const
    {
        // Magic code by stackoverflow: https://stackoverflow.com/questions/24365331/how-can-i-generate-uuid-in-c-without-using-boost-library

        stringstream ss;
        
        UUID uuid;
        auto tmpUuidCreate = UuidCreate(&uuid);
        char* str;
        auto tmpUuidToStringA = UuidToStringA(&uuid, (RPC_CSTR*)(&str));
        ss << str;
        RpcStringFreeA((RPC_CSTR*)(&str));
        
        return ss.str();
    }

    /// @brief Returns REG_SZ string value from registry.
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
    
    /// @brief Returns current user language from HKCU\\Control Panel\\International\\Geo\\Name.
    string Helper::GetCurrentUserLanguage() const
    {
        HKEY rKey;
        DWORD Size = 256;
        TCHAR Reget[Size] = { 0 };
        char Path[] = "Control Panel\\International\\Geo";
        char Key[]  = "Name";
        
        RegOpenKeyExA(HKEY_CURRENT_USER, &Path[0], 0, KEY_READ, &rKey);
        RegQueryValueExA(rKey, &Key[0], NULL, NULL, (LPBYTE)&Reget, &Size);
        RegCloseKey(rKey);
        
        string returnValue(Reget);
        returnValue.shrink_to_fit();
         
        return returnValue;
    }

    /// @brief Returns Windows version from HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\ProductName.
    string Helper::GetWindowsVersion() const
    {
        const char Path[]  = {"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"};
        const char Value[] = {"ProductName"};
        return Helper::GetRegTextValue(&Path[0], &Value[0]);
    }
    
    /// @brief Returns Windows bit as a string.
    string Helper::GetWindowsBitString() const
    {
        if (GetWinBit() == WindowsBit::Win32)
            return "32-bit";
        else
            return "64-bit";
    }

    /// @brief Returns actual Windows bit like a enum value.
    Helper::WindowsBit Helper::GetWinBit()
    {
        return WinBit;
    }
    
    /// @brief Returns processor vendor infomation from HKLM\\HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0\\ProcessorNameString.
    string Helper::GetProcessorInfo() const
    {
        const char Path[]  = {"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"};
        const char Value[] = {"ProcessorNameString"};
        return Helper::GetRegTextValue(&Path[0], &Value[0]);
    }
    
    /// @brief Returns current all memory size information in Mebibytes.
    string Helper::GetMemoryInfo() const
    {
        stringstream ss;
        MEMORYSTATUSEX MemStat;
        MemStat.dwLength = sizeof (MemStat);
        GlobalMemoryStatusEx(&MemStat);
        
        ss << (MemStat.ullTotalPhys/1024)/1024 << "MiB";
        return ss.str();
    }
#pragma endregion

#pragma region Setters
    /// @brief Sets paths to all games (C&C: Generals and C&C: Generals - Zero Hour).
    string Helper::PathToGame(Games game)
    {
        string Key = "InstallPath";
        string Path = pathsToGamesMap.find(game)->second.find(GetWinBit())->second;
        return Helper::GetRegTextValue(Path.c_str(), Key.c_str());
    }

    /// @brief Uses for set Windows bit information in Helper class.
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
    /// @brief Pure function-convertor from char array to std::string.
    string Helper::CharArrayToString(const int& arrayLength, const char* pArray) const
    {
        stringstream ss;
       
        for(int i = 0 ; i < arrayLength; i++)
            ss << pArray[i];
    
        return ss.str();
    }
    
    /// @brief Pure function-convertor from wchar_t array to std::wstring.
    wstring Helper::WharArrayToWstring(const int& arrayLength, const wchar_t* pArray) const
    {
        wstringstream wss;
       
        for(int i = 0 ; i < arrayLength; i++)
            wss << pArray[i];
    
        return wss.str();
    }

    /// @brief Returns Windows bit as bool value.
    bool Helper::IsWindow64bit() const
    {
        return GetWinBit() == WindowsBit::Win64;
    }
    
    /// @brief Returns Windows bit as bool value.
    bool Helper::IsWindow32bit() const
    {
        return GetWinBit() == WindowsBit::Win32;
    }
#pragma endregion
