#pragma once
#include <QString>

class Config
{
public: // Data
    enum class Languages
    {
        English = 0,
        Russian
    };

    static QString LangEnumToString(const Languages& lang);

public: // Methods
    Config() = delete;
};
