#include "Helper.hpp"

#pragma region ctor and dtor
    Helper::Helper()
    {
        PathG   = Helper::SetPathToCNCG();
        PathGZH = Helper::SetPathToCNCGZH();
        Win32   = Helper::SetWindowsBit();
	}
#pragma endregion

#pragma region Setters
    string Helper::SetPathToCNCG()
    {
        HKEY rKey;
        string Path, Key = "InstallPath";
    
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\WOW6432Node"), 0, KEY_QUERY_VALUE, &rKey) == ERROR_SUCCESS)
            Path = "SOFTWARE\\WOW6432Node\\Electronic Arts\\EA Games\\Generals";
        else
            Path = "SOFTWARE\\Electronic Arts\\EA Games\\Generals";
    
        RegCloseKey(rKey);
    
        return Helper::GetRegTextValue(Path.c_str(), Key.c_str());
    }

    string Helper::SetPathToCNCGZH()
    {
        HKEY rKey;
        string Path, Key = "InstallPath";
    
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\WOW6432Node"), 0, KEY_QUERY_VALUE, &rKey) == ERROR_SUCCESS)
            Path = "SOFTWARE\\WOW6432Node\\Electronic Arts\\EA Games\\Command and Conquer Generals Zero Hour";
        else
            Path = "SOFTWARE\\Electronic Arts\\EA Games\\Command and Conquer Generals Zero Hour";
    
        RegCloseKey(rKey);

        return Helper::GetRegTextValue(Path.c_str(), Key.c_str());
    }

    bool Helper::SetWindowsBit()
    {
        HKEY rKey;
        bool returnValue;
    
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\WOW6432Node"), 0, KEY_QUERY_VALUE, &rKey) != ERROR_SUCCESS)
            returnValue = false;
        else
            returnValue = true;
    
        RegCloseKey(rKey);
    
        return returnValue;
    }
#pragma endregion

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
    
    string Helper::GetWindowsBit()
    {
        if (Win32)
            return "32-bit";
        else
            return "64-bit";
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
        return PathG;
    }
    
    string Helper::GetPathToCNCGZH()
    {
        return PathGZH;
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
#pragma endregion

#pragma region Checks and array merging
    bool Helper::IsWindow64bit()
    {
        return !Win32;
    }
    
    bool Helper::IsWindow32bit()
    {
        return Win32;
	}
#pragma endregion
