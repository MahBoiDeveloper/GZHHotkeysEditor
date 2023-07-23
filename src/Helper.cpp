#pragma comment(lib, "rpcrt4.lib")
#include <sstream>
#include <windows.h>

#include "Helper.hpp"

using namespace std;

/// @brief Returns universal unique identifier as a string. 
string Helper::GetUUID()
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
string Helper::GetMemoryInfo()
{
    stringstream ss;
    MEMORYSTATUSEX MemStat;
    MemStat.dwLength = sizeof (MemStat);
    GlobalMemoryStatusEx(&MemStat);
        
    ss << (MemStat.ullTotalPhys/1024)/1024 << "MiB";
    return ss.str();
}
