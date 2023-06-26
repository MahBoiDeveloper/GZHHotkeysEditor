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

ofstream* Logger::GetStream()
{
    return &(this->LogFile);
}

#pragma region Log methods
void Logger::Log(stringstream const& msg)
{
    LogFile << "[" << GetCurrentTime().c_str() << "] " << msg.str() << endl;
}

void Logger::Log(string msg)
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

void Logger::Log(wstring msg)
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
// ofstream& operator << (Logger* pLogger, stringstream const& msg)
// {
//     ofstream* tmp = pLogger->GetStream();
//     *tmp << msg.str();
//     return *tmp;
// }

// ofstream& operator << (Logger* pLogger, string msg)
// {
//     ofstream* tmp = pLogger->GetStream();
//     *tmp << msg;
//     return *tmp;
// }

// ofstream& operator << (Logger* pLogger, wstringstream const& msg)
// {
//     ofstream* tmp = pLogger->GetStream();
//     *tmp << msg.str().c_str();
//     return *tmp;
// }

// ofstream& operator << (Logger* pLogger, wstring msg)
// {
//     ofstream* tmp = pLogger->GetStream();
//     *tmp << msg.c_str();
//     return *tmp;
// }
#pragma endregion
