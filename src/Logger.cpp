#include "Logger.hpp"
#include "Helper.hpp"
#include "info.hpp"
#include <ctime>

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
					  << Helper::Instance->GetWindowsVersion()   << ' '
					  << Helper::Instance->GetWindowsBitString() << endl;
		Logger::Log() << "Processor  : " << Helper::Instance->GetProcessorInfo() << endl;
		Logger::Log() << "Memory	 : " << Helper::Instance->GetMemoryInfo() << endl << endl;

		Logger::Log() << "Software information" << endl;

		// log all games paths
		for (const auto & game : {Helper::Games::Generals, Helper::Games::GeneralsZeroHour})
		{
			if (Helper::PathToGame(game).empty())
				Logger::Log() << "C&C: " << Helper::GameEnumToString(game) << " not installed" << endl;
			else
				Logger::Log() << "C&C: " << Helper::GameEnumToString(game) << " installed at ["
							  << Helper::PathToGame(game) << ']' << endl;
		}
		LogFile << endl;
	}

    /// @brief Get current time in yyyy-MM-dd format
    string Logger::GetCurrentTime() const
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

	// log methods
	ofstream& Logger::Log()
	{
		LogFile << "[" << Logger::GetCurrentTime().c_str() << "]\t";
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
