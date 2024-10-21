#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <concepts>
#include <QString>

#define LOGGER      Logger::Instance
#define LOGSTM      Logger::Instance->Log()
#define LOGMSG(msg) Logger::Instance->Log(msg);Logger::Instance->LogToConsole(msg)

class Logger final
{
public: // Data
    inline const static std::unique_ptr<Logger> Instance = std::make_unique<Logger>();
private:
    std::ofstream LogFile;

public: // Methods
    Logger();
    ~Logger();

    /// @brief Write [DATE-TIME] and return stream to write other data. Needs to be ended with `endl`
    std::ofstream& Log();
    
    /// @brief Write message to the console.
    void LogToConsole(const char* msg);
    /// @brief Write message to the console.
    void LogToConsole(const std::string& msg);
    /// @brief Write message to the console.
    void LogToConsole(const QString& msg);
    /// @brief Write message to the console.
    void LogToConsole(const std::stringstream& msg);
    /// @brief Write message to the console.
    void LogToConsole(const std::wstringstream& msg);
    /// @brief Write message to the console.
    void LogToConsole(const std::wstring& msg);
    /// @brief Write message to the console.
    void LogToConsole(const wchar_t* msg);

    /// @brief Write message to the log file.
    void Log(const char* msg);
    /// @brief Write message to the log file.
    void Log(const std::string& msg);
    /// @brief Write message to the log file.
    void Log(const QString& msg);
    /// @brief Write message to the log file.
    void Log(const std::stringstream& msg);
    /// @brief Write message to the log file.
    void Log(const std::wstringstream& msg);
    /// @brief Write message to the log file.
    void Log(const std::wstring& msg);
    /// @brief Write message to the log file.
    void Log(const wchar_t* msg);

    /// @brief Write text "I'VE GOT A MESSAGE FOR YA" to the log file with text of the exception.
    void LogException(const char* msg);
private:
    /// @brief Write system information from Windows registry to .log file
    void LogSystemInformation();
    /// @brief Get file name like "Logs\\Log YYYY-mm-dd hh-MM-ss.log"
    std::string GetLogFileName() const;
    /// @brief Get current time in yyyy-MM-dd hh:mm:ss format
    std::string GetCurrentTime() const;
    /// @brief Returns Windows bit as a string.
    std::string GetWindowsBit()  const;
};

template<class T>
concept IsNumber = std::same_as<T, int> || std::same_as<T, size_t> || std::same_as<T, std::size_t>;

template<IsNumber N>
QString& operator+ (QString str, N num)
{
    return str.append(QString::number(num));
}

template<IsNumber N>
QString& operator+ (N num, QString str)
{
    return QString::number(num).append(str);
}

template<IsNumber N>
QString& operator+ (N num, std::string str)
{
    return QString::number(num).append(QString::fromStdString(str));
}

template<IsNumber N>
QString& operator+ (std::string str, N num)
{
    return QString::fromStdString(str).append(QString::number(num));
}
