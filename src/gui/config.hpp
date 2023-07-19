#pragma once
#include <QString>

class Config
{
public:
    Config() = delete;

    enum class Languages {
        English = 0,
        Russian = 1
    };
    static QString langEnumToString(const Languages& lang);
};
