#pragma once
#include <string>
#include <map>
#include <memory>

class Registry final
{
public: // Data
    enum class WindowsBit
    {
        Win32 = 0,
        Win64
    };

    enum class Games
    {
        Generals = 0,
        GeneralsZeroHour
    };

    inline static const std::map<Games, std::map<WindowsBit, std::string>> PATHS_TO_GAMES =
    {
        {Games::Generals,         {{WindowsBit::Win32, "SOFTWARE\\Electronic Arts\\EA Games\\Generals"},
                                   {WindowsBit::Win64, "SOFTWARE\\WOW6432Node\\Electronic Arts\\EA Games\\Generals"}}},
        {Games::GeneralsZeroHour, {{WindowsBit::Win32, "SOFTWARE\\Electronic Arts\\EA Games\\Command and Conquer Generals Zero Hour"},
                                   {WindowsBit::Win64, "SOFTWARE\\WOW6432Node\\Electronic Arts\\EA Games\\Command and Conquer Generals Zero Hour"}}},
    };

    WindowsBit ThisWindowsBit;
    inline static std::unique_ptr<Registry> Instance;

public: // Methods
    Registry();

    static std::string GameEnumToString(Games game);
    WindowsBit         GetWindowsBit();
    
    std::string GetTextFromKeyInHKLM(const char* pPathToFolder, const char* pKeyName);
    std::string GetTextFromKeyInHKCU(const char* pPathToFolder, const char* pKeyName);

    bool IsWindow64bit();
    bool IsWindow32bit();

    std::string GetPathToGame(Games game);
private:
    WindowsBit SetWindowsBit();
};
