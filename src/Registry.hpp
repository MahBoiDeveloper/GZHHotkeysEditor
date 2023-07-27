#pragma once
#include <string>
#include <map>

class Registry final
{
public: // Data types declarations
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

    enum class RootFolder
    {
        HKLM = 0,
        HKCU
    };
public: // Data
    inline static const std::map<Games, std::map<WindowsBit, std::string>> PATHS_TO_GAMES =
    {
        {Games::Generals,         {{WindowsBit::Win32, "SOFTWARE\\Electronic Arts\\EA Games\\Generals"},
                                   {WindowsBit::Win64, "SOFTWARE\\WOW6432Node\\Electronic Arts\\EA Games\\Generals"}}},
        {Games::GeneralsZeroHour, {{WindowsBit::Win32, "SOFTWARE\\Electronic Arts\\EA Games\\Command and Conquer Generals Zero Hour"},
                                   {WindowsBit::Win64, "SOFTWARE\\WOW6432Node\\Electronic Arts\\EA Games\\Command and Conquer Generals Zero Hour"}}},
    };

public: // Methods
    Registry() = delete;

    static std::string ToString(Games game);
    static WindowsBit  GetWindowsBit();
    
    static std::string GetTextFromKey(const RootFolder Folder, const char* pPathToFolder, const char* pKeyName);

    static bool IsWindow64bit();
    static bool IsWindow32bit();

    static std::string GetPathToGame(const Games game);
    static std::string GetCurrentUserLanguage();
    static std::string GetWindowsVersion();
    static std::string GetProcessorInfo();
};
