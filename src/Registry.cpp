#include <sstream>
#include <windows.h>
#include <tchar.h>

#include "Registry.hpp"

using namespace std;

Registry::Registry()
{
    ThisWindowsBit = SetWindowsBit();
}

/// @brief Uses for set Windows bit information.
Registry::WindowsBit Registry::SetWindowsBit()
{
    HKEY rKey;
    WindowsBit wbFoundBit;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\WOW6432Node"), 0, KEY_QUERY_VALUE, &rKey) == ERROR_SUCCESS)
        wbFoundBit = WindowsBit::Win64;
    else
        wbFoundBit = WindowsBit::Win32;

    RegCloseKey(rKey);

    return wbFoundBit;
}

/// @brief Returns actual Windows bit like a enum value.
Registry::WindowsBit Registry::GetWindowsBit()
{
    return ThisWindowsBit;
}
    
/// @brief Returns REG_SZ string value from HKEY_LOCAL_MACHINE.
string Registry::GetTextFromKeyInHKLM(const char* pPathToFolder, const char* pKeyName)
{
    HKEY rKey;
    DWORD Size = 256;
    TCHAR Reget[Size] = { 0 };
        
    RegOpenKeyExA(HKEY_LOCAL_MACHINE, pPathToFolder, 0, KEY_READ, &rKey);
    RegQueryValueExA(rKey, pKeyName, NULL, NULL, (LPBYTE)&Reget, &Size);
    RegCloseKey(rKey);
    
    string returnValue(Reget);
    returnValue.shrink_to_fit();
         
    return returnValue;
}

/// @brief Returns REG_SZ string value from HKEY_CURRENT_USER.
string Registry::GetTextFromKeyInHKCU(const char* pPathToFolder, const char* pKeyName)
{
    HKEY  rKey;
    DWORD Size = 256;
    TCHAR Reget[Size] = { 0 };
        
    RegOpenKeyExA(HKEY_CURRENT_USER, pPathToFolder, 0, KEY_READ, &rKey);
    RegQueryValueExA(rKey, pKeyName, NULL, NULL, (LPBYTE)&Reget, &Size);
    RegCloseKey(rKey);
    
    string returnValue(Reget);
    returnValue.shrink_to_fit();
         
    return returnValue;
}

/// @brief Sets paths to all games (C&C: Generals and C&C: Generals - Zero Hour).
string Registry::GetPathToGame(Games game)
{
    string Key  = "InstallPath";
    string Path = Registry::PATHS_TO_GAMES.find(game)->second.find(GetWindowsBit())->second;
    return GetTextFromKeyInHKLM(Path.c_str(), Key.c_str());
}

string Registry::GameEnumToString(Games game)
{
    string returnValue;

    switch (game)
    {
        case Games::Generals:
            returnValue = "Generals";
            break;
        case Games::GeneralsZeroHour:
            returnValue = "Generals Zero Hour";
            break;
    }

    return returnValue;
}

/// @brief Checks if Windows is 64-bit.
bool Registry::IsWindow64bit()
{
    return GetWindowsBit() == WindowsBit::Win64;
}
    
/// @brief Checks if Windows is 32-bit.
bool Registry::IsWindow32bit()
{
    return GetWindowsBit() == WindowsBit::Win32;
}
