#pragma once
#include <string>
#include <vector>

#define EMPTY_WSTRING std::wstring()
#define EMPTY_STRING  std::string()

class Unsorted final
{
public:
    static std::string              GetUUID();
    static std::string              GetMemoryInfo();
    static std::vector<std::string> GetFactions();
    // static std::map<std::string, std::string> GetBuildingsList
};
