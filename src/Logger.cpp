#include "Logger.hpp"

#pragma region Constructors and destructor
    Logger::Logger(const string& fileName)
    {
	    LogFile.open(fileName);
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

    void inline Logger::Log(const stringstream& msg)
    {
        Logger::Log() << msg.str() << endl;
    }

    void inline Logger::Log(string const& msg)
    {
        Logger::Log() << msg << endl;
    }

    void inline Logger::Log(wstringstream const& msg)
    {
        Logger::Log() << msg.str().c_str() << endl;
    }

    void inline Logger::Log(wstring const& msg)
    {
        Logger::Log() << msg.c_str() << endl;
    }
#pragma endregion
