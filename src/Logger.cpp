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

#pragma region Log methods
    ofstream& Logger::Log()
    {
        LogFile << "[" << Helper::Instance->GetCurrentTime().c_str() << "]\t";
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

	void Logger::Log(wstringstream const& msg)
    {
        Logger::Log() << msg.str().c_str() << endl;
    }

	void Logger::Log(wstring const& msg)
    {
        Logger::Log() << msg.c_str() << endl;
    }
#pragma endregion
