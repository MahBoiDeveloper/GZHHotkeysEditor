#include "Logger.hpp"

#pragma region Constructors and destructor
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

    void Logger::Dispose()
    {
        delete(Logger::Instance);
    }
#pragma endregion

string Logger::GetCurrentTime()
{
    time_t timeStomp = time(nullptr);
    tm timeNow;
    localtime_s(&timeNow, &timeStomp);

    char currentTime[128];
    strftime(currentTime, sizeof(currentTime), "%Y-%m-%d %X", &timeNow);

    stringstream ss;
    ss << currentTime;

    return ss.str();
}

#pragma region Log methods
    ofstream& Logger::Log()
    {
        LogFile << "[" << GetCurrentTime().c_str() << "]\t";
        ofstream& tmpStream = LogFile;
        return tmpStream;
    }

    void Logger::Log(const stringstream& msg)
    {
        Logger::Log() << msg.str() << endl;
    }

    void Logger::Log(string const& msg)
    {
        Logger::Log() << msg << endl;
    }

    void Logger::Log(char* msg)
    {
        Logger::Log() << *msg << endl;
    }

    void Logger::Log(char msg)
    {
        Logger::Log() << msg << endl;
    }

    void Logger::Log(wstringstream const& msg)
    {
        Logger::Log() << msg.str().c_str() << endl;
    }

    void Logger::Log(wstring const& msg)
    {
        Logger::Log() << msg.c_str() << endl;
    }

    void Logger::Log(wchar_t* msg)
    {
        Logger::Log() << *msg << endl;
    }

    void Logger::Log(wchar_t msg)
    {
        Logger::Log() << msg << endl;
    }
#pragma endregion
