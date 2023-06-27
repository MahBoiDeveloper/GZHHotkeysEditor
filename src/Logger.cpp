#include "Logger.hpp"

#pragma region Constructors and destructor
Logger::Logger()
{
}

Logger::Logger(const string& fileName) : LogFilePath(fileName)
{
    LogFilePath = fileName;
    LogFile.open(LogFilePath);
}

Logger::~Logger()
{
    if (LogFile.is_open())
        LogFile.close();
}
#pragma endregion

string Logger::GetCurrentTime()
{
    time_t timeStomp = time(nullptr);
    tm timeNow;
    localtime_s(&timeNow, &timeStomp);

    char currentTime[128];
    strftime(currentTime, sizeof(currentTime), "%X %Y-%m-%d", &timeNow);

    stringstream ss;
    ss << currentTime;

    return ss.str();
}

ofstream&& Logger::GetStream()
{
    return move(LogFile);
}

#pragma region Log methods
void Logger::Log(stringstream const& msg)
{
    LogFile << "[" << GetCurrentTime().c_str() << "] " << msg.str() << endl;
}

void Logger::Log(string const& msg)
{
    LogFile << "[" << GetCurrentTime().c_str() << "] " << msg << endl;
}

void Logger::Log(char* msg)
{
    LogFile << "[" << GetCurrentTime().c_str() << "] " << *msg << endl;
}

void Logger::Log(char msg)
{
    LogFile << "[" << GetCurrentTime().c_str() << "] " << msg << endl;
}

void Logger::Log(wstringstream const& msg)
{
    LogFile << "[" << GetCurrentTime().c_str() << "] " << msg.str().c_str() << endl;
}

void Logger::Log(wstring const& msg)
{
    LogFile << "[" << GetCurrentTime().c_str() << "] " << msg.c_str() << endl;
}

void Logger::Log(wchar_t* msg)
{
    LogFile << "[" << GetCurrentTime().c_str() << "] " << *msg << endl;
}

void Logger::Log(wchar_t msg)
{
    LogFile << "[" << GetCurrentTime().c_str() << "] " << msg << endl;
}
#pragma endregion

#pragma region Operators overloading
ofstream operator << (Logger* pLogger, stringstream const& msg)
{
    pLogger->GetStream() << '[' << pLogger->GetCurrentTime() << "] " << msg.str();
    return pLogger->GetStream();
}

ofstream operator << (Logger* pLogger, string msg)
{
    pLogger->GetStream() << '[' << pLogger->GetCurrentTime() << "] " << msg;
    return pLogger->GetStream();
}

ofstream operator << (Logger* pLogger, wstringstream const& msg)
{
    pLogger->GetStream() << "[ " << pLogger->GetCurrentTime() << "] " << msg.str().c_str();
    return pLogger->GetStream();
}

ofstream operator << (Logger* pLogger, wstring msg)
{
    pLogger->GetStream() << '[' << pLogger->GetCurrentTime() << "] " << msg.c_str();
    return pLogger->GetStream();
}
#pragma endregion
