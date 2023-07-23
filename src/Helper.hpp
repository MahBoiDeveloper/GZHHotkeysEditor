#pragma once
#pragma comment(lib, "rpcrt4.lib")

#include <string>
#include <memory>

#define EMPTY_WSTRING std::wstring()
#define EMPTY_STRING  std::string()

class Helper final
{
public:
    inline static std::unique_ptr<Helper> Instance;

public:
    // Uses in CSFparser
    std::string  GetUUID()                                                         const;
    std::string  GetMemoryInfo()                                                   const;
    std::string  CharArrayToString(const int& arrayLength, const char* pArray)     const;
    std::wstring WharArrayToWstring(const int& arrayLength, const wchar_t* pArray) const;
};
