#pragma once

#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>

using namespace std;

class Logger
{
public:
	static inline unique_ptr<Logger> Instance;
private:
    ofstream LogFile;

private:
    string GetCurrentTime();
public:
	Logger() = delete;
	Logger(const string& logFilePath);
	~Logger();

    ofstream& Log();

    void inline Log(const stringstream& msg);
    void inline Log(const string& msg);

    void inline Log(const wstringstream& msg);
    void inline Log(const wstring& msg);
};
