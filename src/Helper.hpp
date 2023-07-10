#pragma once
#pragma comment(lib, "rpcrt4.lib")

#include <map>
#include <list>
#include <string>
#include <memory>

using namespace std;

// Class Helper uses for collect all unsorted methods and functions
class Helper
{
public:
	enum class WINDOWS_BIT {
		WIN_32 = 0,
		WIN_64 = 1
	};

	enum class GAMES {
		GENERALS = 0,
		GENERALS_ZERO_HOUR = 1
	};
	static inline string gameEnumToString(GAMES game)
	{
		switch (game) {
		case GAMES::GENERALS:
			return "Generals";
			break;
		case GAMES::GENERALS_ZERO_HOUR:
			return "Generals Zero Hour";
			break;
		default:
			return gameEnumToString(GAMES::GENERALS);
			break;
		}
	}

	static inline const map<GAMES,map<WINDOWS_BIT,string>> pathsToGamesMap =
	{
		{GAMES::GENERALS,           {{WINDOWS_BIT::WIN_32, "SOFTWARE\\Electronic Arts\\EA Games\\Generals"},
									 {WINDOWS_BIT::WIN_64, "SOFTWARE\\WOW6432Node\\Electronic Arts\\EA Games\\Generals"}}},
		{GAMES::GENERALS_ZERO_HOUR,	{{WINDOWS_BIT::WIN_32, "SOFTWARE\\Electronic Arts\\EA Games\\Command and Conquer Generals Zero Hour"},
									 {WINDOWS_BIT::WIN_64, "SOFTWARE\\WOW6432Node\\Electronic Arts\\EA Games\\Command and Conquer Generals Zero Hour"}}},
	};
	static string pathToGame(GAMES game);

	inline static unique_ptr<Helper> Instance;

private:
	static WINDOWS_BIT GetWindowsBit();
	inline static WINDOWS_BIT WinBit = {GetWindowsBit()};

public:
	// Uses in Logger
	string GetProcessorInfo() const;
	string GetMemoryInfo() const;
	string GetWindowsBitString() const;
	static WINDOWS_BIT winBit();
	string GetWindowsVersion() const;
    // Uses in CSFparser
	string  GetUUID();
	bool    IsWindow64bit();
    bool    IsWindow32bit();
private:
	static string GetRegTextValue(const char* pPathToFolder, const char* pKeyName);
};
