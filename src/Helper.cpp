#include "Helper.hpp"

#include <windows.h>
#include <tchar.h>
#include <sstream>

#pragma region ctor and dtor
#pragma endregion

#pragma region Setters

	string Helper::pathToGame(GAMES game)
	{
		string Key = "InstallPath";
		// get path from map
		string Path = pathsToGamesMap.find(game)->second.find(winBit())->second;
        return Helper::GetRegTextValue(Path.c_str(), Key.c_str());
	}

	Helper::WINDOWS_BIT Helper::GetWindowsBit()
    {
        HKEY rKey;
		WINDOWS_BIT returnValue;
    
		if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\WOW6432Node"), 0, KEY_QUERY_VALUE, &rKey) == ERROR_SUCCESS)
			returnValue = WINDOWS_BIT::WIN_64;
        else
			returnValue = WINDOWS_BIT::WIN_32;
        RegCloseKey(rKey);

        return returnValue;
    }
#pragma endregion

#pragma region Getters
	// reading from reg
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
    
	string Helper::GetWindowsVersion() const
    {
        const char Path[]  = {"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"};
        const char Value[] = {"ProductName"};
        return Helper::GetRegTextValue(&Path[0], &Value[0]);
    }
    
	string Helper::GetWindowsBitString() const
    {
		if (winBit() == WINDOWS_BIT::WIN_32)
            return "32-bit";
        else
			return "64-bit";
	}

	Helper::WINDOWS_BIT Helper::winBit()
	{
		return WinBit;
	}
    
	string Helper::GetProcessorInfo() const
    {
        const char Path[]  = {"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"};
        const char Value[] = {"ProcessorNameString"};
        return Helper::GetRegTextValue(&Path[0], &Value[0]);
    }
    
	string Helper::GetMemoryInfo() const
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
#pragma endregion

#pragma region Checks and array merging
    bool Helper::IsWindow64bit()
    {
		return winBit() == WINDOWS_BIT::WIN_64;
    }
    
    bool Helper::IsWindow32bit()
    {
		return winBit() == WINDOWS_BIT::WIN_32;
	}
#pragma endregion
