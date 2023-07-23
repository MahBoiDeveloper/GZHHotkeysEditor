#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <memory>

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

public:
    Logger();
    ~Logger();

    std::ofstream& Log();

    void Log(const std::stringstream& msg);
    void Log(const std::string& msg);

    void Log(const std::wstringstream& msg);
    void Log(const std::wstring& msg);
private:
    std::string GetCurrentUserLanguage() const;
    std::string GetWindowsVersion()      const;
    std::string GetProcessorInfo()       const;
    std::string GetWindowsBit()          const;
};
