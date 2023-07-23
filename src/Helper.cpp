#include <sstream>
#include <windows.h>

#include "Helper.hpp"

using namespace std;

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
#pragma endregion
