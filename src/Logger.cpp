#include <ctime>

#include "Logger.hpp"
#include "Helper.hpp"
#include "Info.hpp"

#pragma region ctor and dtor
    Logger::Logger()
    {
        LogFile.open(GetLogFileName());
        
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
    /// @brief Write system information from Windows registry to .log file
    void Logger::LogSystemInformation()
    {
        // Write to log all necessary information about MS Windows
        Logger::Log() << "Operation System Information" << endl;
        Logger::Log() << "Version   : "
                      << Helper::Instance->GetWindowsVersion()   << ' '
                      << Helper::Instance->GetWindowsBitString() << endl;
        Logger::Log() << "Language  : " << Helper::Instance->GetCurrentUserLanguage() << endl;
        LogFile << endl;

        // Write to log all information about processor type and memory size
        Logger::Log() << "Hardware Information" << endl;
        Logger::Log() << "Processor : " << Helper::Instance->GetProcessorInfo() << endl;
        Logger::Log() << "Memory    : " << Helper::Instance->GetMemoryInfo() << endl << endl;

        // Write to log all games paths
        Logger::Log() << "Software Information" << endl;

        for (const auto& game : {Helper::Games::Generals, Helper::Games::GeneralsZeroHour})
        {
            if (Helper::PathToGame(game).empty())
                Logger::Log() << "C&C: " << Helper::GameEnumToString(game) << " not installed" << endl;
            else
                Logger::Log() << "C&C: " << Helper::GameEnumToString(game) << " installed at ["
                              << Helper::PathToGame(game) << ']' << endl;
        }

        LogFile << endl;
    }

    /// @brief Get current time in yyyy-MM-dd hh:mm:ss format
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

    /// @brief Get file name like "Logs\\Log YYYY-mm-dd hh-MM-ss.log"
    string Logger::GetLogFileName() const
    {
        time_t timeStomp = time(nullptr);
        tm timeNow;
        localtime_s(&timeNow, &timeStomp);

        char currentTime[128];
        strftime(currentTime, sizeof(currentTime), "%Y-%m-%d %H-%M-%S", &timeNow);

        stringstream ss;
        ss << "Logs\\Log " << currentTime << ".log";

        return ss.str();
    }

    // @brief Writes [DATE-TIME] and return stream to write other data. Needs to be ended with `endl`
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
