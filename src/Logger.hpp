#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <memory>

#define LOGSTM      Logger::Instance->Log()
#define LOGMSG(msg) Logger::Instance->Log(msg)

class Logger final
{
public:
    static inline std::unique_ptr<Logger> Instance;
private:
    std::ofstream LogFile;

private:
    void LogSystemInformation();
    std::string GetLogFileName() const;
    std::string GetCurrentTime() const;
    std::string GetWindowsBit() const;

public:
    Logger();
    ~Logger();

    std::ofstream& Log();

    void Log(const std::stringstream& msg);
    void Log(const std::string& msg);

    void Log(const std::wstringstream& msg);
    void Log(const std::wstring& msg);

    void LogException();
};
