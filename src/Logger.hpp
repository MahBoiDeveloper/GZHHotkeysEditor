#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <QString>

#define LOGSTM      Logger::Instance->Log()
#define LOGMSG(msg) Logger::Instance->Log(msg)

class Logger final
{
public:
    static inline std::unique_ptr<Logger> Instance;

public:
    Logger();
    ~Logger();

    std::ofstream& Log();

    void Log(const QString& msg);

    void Log(const std::stringstream& msg);
    void Log(const std::string& msg);
    void Log(const char* msg);

    void Log(const std::wstringstream& msg);
    void Log(const std::wstring& msg);
    void Log(const wchar_t* msg);

    void LogException();

private:
    void LogSystemInformation();
    std::string GetLogFileName() const;
    std::string GetCurrentTime() const;
    std::string GetWindowsBit()  const;

private:
    std::ofstream LogFile;
};
