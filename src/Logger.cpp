#include "Logger.hpp"

#pragma region ctor and dtor
    Logger::Logger(const string& fileName)
    {
	    LogFile.open(fileName);
        
	    Logger::Log() << "C&C Generals and Generals Zero Hour hotkey editor" << endl; 
	    Logger::Log() << "Version: " << VERSION << endl;
	    Logger::Log() << "Authors: " << AUTHORS << endl << endl;

	    Logger::LogSystemInformation();
    }

    Logger::~Logger()
    {
		if (LogFile.is_open()) LogFile.close();
    }
#pragma endregion

#pragma region Log methods
    void Logger::LogSystemInformation()
    {
        Logger::Log() << "Hardware information" << endl;
        Logger::Log() << "OS version : "
                      << Helper::Instance->GetWindowsVersion() << ' '
                      << Helper::Instance->GetWindowsBit()     << endl;
        Logger::Log() << "Processor  : " << Helper::Instance->GetProcessorInfo() << endl;
        Logger::Log() << "Memory     : " << Helper::Instance->GetMemoryInfo() << endl << endl;

        Logger::Log() << "Software information" << endl;

        if (Helper::Instance->GetPathToCNCG() == "")
            Logger::Log() << "C&C: Generals not installed" << endl;
        else
            Logger::Log() << "C&C: Generals installed at              ["<< Helper::Instance->GetPathToCNCG() << ']' << endl;

        if (Helper::Instance->GetPathToCNCGZH() == "")
           Logger::Log() << "C&C: Generals Zero Hour not installed" << endl;
        else
            Logger::Log() << "C&C: Generals Zero Hour installed at    ["<< Helper::Instance->GetPathToCNCGZH() << ']' << endl;

        LogFile << endl;
    }

    ofstream& Logger::Log()
    {
		LogFile << "[" << Helper::Instance->GetCurrentTime().c_str() << "]\t";
		return LogFile;
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
