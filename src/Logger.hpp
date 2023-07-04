﻿#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <memory>

#include "Helper.hpp"

using namespace std;

class Logger
{
public:
	static inline unique_ptr<Logger> Instance;
private:
    ofstream LogFile;

public:
	Logger() = delete;
	Logger(const string& logFilePath);
	~Logger();

    ofstream& Log();

	void Log(const stringstream& msg);
	void Log(const string& msg);

	void Log(const wstringstream& msg);
	void Log(const wstring& msg);
};
