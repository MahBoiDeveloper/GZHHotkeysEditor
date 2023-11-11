#pragma once
#include <string>
#include <vector>

#define EMPTY_WSTRING std::wstring()
#define EMPTY_STRING  std::string()

class Unsorted final
{
public:// Types
    struct FactionInfo
    {
        std::string ShortName;
        std::string DisplayName;
        std::string DisplayNameDesctiontion;
    };
public: // Methods
    static std::string                        GetUUID();
    static std::string                        GetMemoryInfo();
    static std::vector<Unsorted::FactionInfo> GetFactionsInfo();
};
