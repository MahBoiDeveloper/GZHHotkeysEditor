#include <ctime>
#include <QMessageBox>

#include "Logger.hpp"
#include "Registry.hpp"
#include "Info.hpp"

using namespace std;

#pragma region ctor and dtor
    Logger::Logger()
    {
        LogFile.open(GetLogFileName());
        
        if (!LogFile.is_open()) QMessageBox::critical(nullptr, "I'VE GOT A PRESENT FOR YA", "Unable to create log file; make sure \"Logs\" folder are exists.");

        Log() << "C&C Generals and Generals Zero Hour hotkey editor" << endl; 
        Log() << "Version: " << VERSION << endl;
        Log() << "Authors: " << AUTHORS << endl << endl;

        LogSystemInformation();
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
        Log() << "Operation System Information"               << endl;
        Log() << "Version   : "
                                << Registry::GetWindowsVersion()              << ' '
                                << GetWindowsBit()                            << endl;
        Log() << "Language  : " << Registry::GetCurrentUserLanguage() << endl << endl;

        // Write to log all information about processor type and memory size
        Log() << "Hardware Information"                         << endl;
        Log() << "Processor : " << Registry::GetProcessorInfo() << endl;
        Log() << "Memory    : " << Registry::GetMemoryInfo()      << endl << endl;

        // Write to log all games paths
        Log() << "Software Information" << endl;

        for (const auto& game : {Registry::Games::Generals, Registry::Games::GeneralsZeroHour})
        {
            if (Registry::GetPathToGame(game).empty())
                Log() << "C&C: " << Registry::ToString(game)  << " not installed" << endl;
            else
                Log() << "C&C: " << Registry::ToString(game)  << " installed at ["
                                 << Registry::GetPathToGame(game) << ']' << endl;
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

    /// @brief Writes [DATE-TIME] and return stream to write other data. Needs to be ended with `endl`
    ofstream& Logger::Log()
    {
        LogFile << "[" << Logger::GetCurrentTime().c_str() << "]\t";
        return LogFile;
    }

    void Logger::Log(const char* msg)
    {
         Log() << msg << endl;
    }

    void Logger::Log(const string& msg)
    {
        Log(msg.c_str());
    }

    void Logger::Log(const QString& msg)
    {
        Log(msg.toStdString());
    }

    void Logger::Log(const stringstream& msg)
    {
        Log(msg.str());
    }

    void Logger::Log(const wstringstream& msg)
    {
        Log(msg.str());
    }

    void Logger::Log(const wstring& msg)
    {
        Log(msg.c_str());
    }

    void Logger::Log(const wchar_t* msg)
    {
        Log() << msg << endl;
    }

    void Logger::LogException()
    {
        LogFile << endl << endl;
        Log() << "\t\t\t\tI'VE GOT A PRESENT FOR YA" << endl;
    }
#pragma endregion

#pragma region Support methods
    /// @brief Returns Windows bit as a string.
    string Logger::GetWindowsBit() const
    {
        if (Registry::GetWindowsBit() == Registry::WindowsBit::Win32)
            return "32-bit";
        else
            return "64-bit";
    }
#pragma endregion
