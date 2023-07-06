#include "Logger.hpp"

#pragma region Constructors and destructor
    Logger::Logger(const string& fileName)
    {
	    LogFile.open(fileName);
        
	    Logger::Log() << "C&C Generals and Generals Zero Hour hotkey editor" << endl; 
	    Logger::Log() << "Version: " << VERSION << endl;
	    Logger::Log() << "Authors: " << AUTHORS << endl << endl;

	    Logger::LogSystemInformation();
        LogFile << endl;
    }

    Logger::~Logger()
    {
	    if (LogFile.is_open()) 
            LogFile.close();
    }
#pragma endregion

#pragma region Log methods
    void Logger::LogSystemInformation()
    {
        LogFile << "[" << Helper::GetCurrentTime().c_str() << "]\t"
                << "OS version: "
                << Helper::GetWindowsVersion().c_str() << endl;

        LogFile << "[" << Helper::GetCurrentTime().c_str() << "]\t"
                << Helper::GetProcessorInfo().c_str() << endl;

        LogFile << "[" << Helper::GetCurrentTime().c_str() << "]\t"
                << Helper::GetMemoryInfo().c_str() << endl;
    }

    ofstream& Logger::Log()
    {
        LogFile << "[" << Helper::GetCurrentTime().c_str() << "]\t";
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
