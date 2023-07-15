#pragma once
#pragma comment(lib, "rpcrt4.lib")

#include <map>
#include <list>
#include <string>
#include <memory>
#include <iostream>

#define EMPTY_WSTRING to_wstring('\0')
#define EMPTY_STRING  to_string ('\0')

using namespace std;

// Class Helper uses for collect all unsorted methods and functions
class Helper
{
public:
	enum class WINDOWS_BIT
	{
		WIN_32 = 0,
		WIN_64 = 1
	};

	enum class GAMES
	{
		GENERALS = 0,
		GENERALS_ZERO_HOUR = 1
	};

	inline static string GameEnumToString(GAMES game)
	{
		string returnValue = EMPTY_STRING;

		switch (game)
		{
			case GAMES::GENERALS:
				returnValue = "Generals";
				break;
			case GAMES::GENERALS_ZERO_HOUR:
				returnValue = "Generals Zero Hour";
				break;
		}

		return returnValue;
	}

	inline static const map<GAMES,map<WINDOWS_BIT,string>> pathsToGamesMap =
	{
		{GAMES::GENERALS,           {{WINDOWS_BIT::WIN_32, "SOFTWARE\\Electronic Arts\\EA Games\\Generals"},
									 {WINDOWS_BIT::WIN_64, "SOFTWARE\\WOW6432Node\\Electronic Arts\\EA Games\\Generals"}}},
		{GAMES::GENERALS_ZERO_HOUR,	{{WINDOWS_BIT::WIN_32, "SOFTWARE\\Electronic Arts\\EA Games\\Command and Conquer Generals Zero Hour"},
									 {WINDOWS_BIT::WIN_64, "SOFTWARE\\WOW6432Node\\Electronic Arts\\EA Games\\Command and Conquer Generals Zero Hour"}}},
	};

	static string PathToGame(GAMES game);

	inline static unique_ptr<Helper> Instance;

private:
	static WINDOWS_BIT GetWindowsBit();
	inline static WINDOWS_BIT WinBit = {GetWindowsBit()};

public:
	// Uses in Logger
	string GetProcessorInfo();
	string GetMemoryInfo();
	string GetWindowsBitString();
	static WINDOWS_BIT winBit();
	string GetWindowsVersion();

    // Uses in CSFparser
	string  GetUUID();
    string  CharArrayToString(const int& arrayLength, const char* pArray);
    wstring WharArrayToWstring(const int& arrayLength, const wchar_t* pArray);

	// Functions for general use
	bool    IsWindow64bit();
    bool    IsWindow32bit();
private:
	static string GetRegTextValue(const char* pPathToFolder, const char* pKeyName);
};
