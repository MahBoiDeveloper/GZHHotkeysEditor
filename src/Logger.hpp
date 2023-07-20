#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <memory>

using namespace std;

class Logger final
{
public:
    static inline unique_ptr<Logger> Instance;
private:
    ofstream LogFile;

private:
    void LogSystemInformation();
    string GetLogFileName() const;
    string GetCurrentTime() const;

public:
    Logger();
    ~Logger();

    ofstream& Log();

    void Log(const stringstream& msg);
    void Log(const string& msg);

    void Log(const wstringstream& msg);
    void Log(const wstring& msg);
};
