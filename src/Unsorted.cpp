#pragma comment(lib, "rpcrt4.lib")
#include <sstream>
#include <windows.h>

#include <QDebug>

#include "Unsorted.hpp"
#include "JSONFile.hpp"

using namespace std;

/// @brief Returns universal unique identifier as a string. 
string Unsorted::GetUUID()
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
string Unsorted::GetMemoryInfo()
{
    stringstream ss;
    MEMORYSTATUSEX MemStat;
    MemStat.dwLength = sizeof (MemStat);
    GlobalMemoryStatusEx(&MemStat);
        
    ss << (MemStat.ullTotalPhys/1024)/1024 << "MiB";
    return ss.str();
}

/// @brief  
vector<Unsorted::FactionInfo> Unsorted::GetFactionsInfo()
{
    vector<FactionInfo> tmp;
    JSONFile file(string("Resources\\TechTree.json"));

    for (const auto& elem : file.Query(string("$.TechTree")).toArray())
    {
        string ShortName               = elem.toObject().value("ShortName").toString().trimmed().toStdString();
        string DisplayName             = elem.toObject().value("DisplayName").toString().trimmed().toStdString();
        string DisplayNameDesctiontion = elem.toObject().value("DisplayNameDesctiontion").toString().trimmed().toStdString();
        tmp.push_back({ShortName, DisplayName, DisplayNameDesctiontion});
    }

    return tmp;
}
