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
	enum class WindowsBit
	{
		Win32 = 0,
		Win64 = 1
	};

	enum class Games
	{
		Generals		 = 0,
		GeneralsZeroHour = 1
	};

	inline static const map<Games,map<WindowsBit,string>> pathsToGamesMap =
	{
		{Games::Generals,		 {{WindowsBit::Win32, "SOFTWARE\\Electronic Arts\\EA Games\\Generals"},
								   {WindowsBit::Win64, "SOFTWARE\\WOW6432Node\\Electronic Arts\\EA Games\\Generals"}}},
		{Games::GeneralsZeroHour, {{WindowsBit::Win32, "SOFTWARE\\Electronic Arts\\EA Games\\Command and Conquer Generals Zero Hour"},
								   {WindowsBit::Win64, "SOFTWARE\\WOW6432Node\\Electronic Arts\\EA Games\\Command and Conquer Generals Zero Hour"}}},
	};

	inline static unique_ptr<Helper> Instance;

private:
	static WindowsBit GetWindowsBit();
	inline static WindowsBit WinBit = {GetWindowsBit()};

public:
	// Uses in Logger
	string GetProcessorInfo();
	string GetMemoryInfo();
	string GetWindowsBitString();
	static WindowsBit GetWinBit();
	string GetWindowsVersion();
	static string PathToGame(Games game);

	inline static string GameEnumToString(Games game)
	{
		string returnValue = EMPTY_STRING;

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

	// Uses in CSFparser
	string  GetUUID();
	string  CharArrayToString(const int& arrayLength, const char* pArray);
	wstring WharArrayToWstring(const int& arrayLength, const wchar_t* pArray);

	// Functions for general use
	bool	IsWindow64bit();
	bool	IsWindow32bit();
private:
	static string GetRegTextValue(const char* pPathToFolder, const char* pKeyName);
};
