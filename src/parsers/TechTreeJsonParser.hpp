#pragma once

#include <string>
#include <vector>

class TechTreeJsonParser
{

public:// Types
    struct FactionInfo
    {
        std::string ShortName;
        std::string DisplayName;
        std::string DisplayNameDesctiontion;
    };

public: // Methods
    static std::vector<FactionInfo> GetFactionsInfo();
};
