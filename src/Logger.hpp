#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <concepts>
#include <QString>

#define LOGGER      Logger::Instance
#define LOGSTM      Logger::Instance->Log()
#define LOGMSG(msg) Logger::Instance->Log(QString("")+msg);Logger::Instance->LogToConsole(QString("")+msg)

class Logger final
{
public: // Data
    inline const static std::unique_ptr<Logger> Instance = std::make_unique<Logger>();
    inline const static QString EXCEPTION_HEADER = "I'VE GOT A PRESENT FOR YA";
private:
    std::ofstream LogFile;

public: // Methods
    Logger();
    ~Logger();

    /// @brief Write [DATE-TIME] and return stream to write other data. Needs to be ended with `endl`
    std::ofstream& Log();
    
    /// @brief Write message to the console.
    void LogToConsole(const char* msg) const;
    /// @brief Write message to the console.
    void LogToConsole(const std::string& msg) const;
    /// @brief Write message to the console.
    void LogToConsole(const QString& msg) const;
    /// @brief Write message to the console.
    void LogToConsole(const std::stringstream& msg) const;
    /// @brief Write message to the console.
    void LogToConsole(const std::wstringstream& msg) const;
    /// @brief Write message to the console.
    void LogToConsole(const std::wstring& msg) const;
    /// @brief Write message to the console.
    void LogToConsole(const wchar_t* msg) const;

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
    const char* GetExceptionHeader();
private:
    /// @brief Write system information from Windows registry to .log file
    void LogSystemInformation();
    /// @brief Get file name like "Logs\\Log YYYY-mm-dd hh-MM-ss.log"
    const std::string GetLogFileName() const;
    /// @brief Get current time in yyyy-MM-dd hh:mm:ss format
    const std::string GetCurrentTime() const;
    /// @brief Returns Windows bit as a string.
    const std::string GetWindowsBit()  const;
};

#pragma region QString extension
template<class T>
concept IsSymbol = std::same_as<T, char> || std::same_as<T, wchar_t> || std::same_as<T, QChar>;

template<class T>
concept IsCString = std::same_as<T, const char*> || std::same_as<T, const wchar_t*>;

template<class T>
concept IsNumber = std::same_as<T, int> || std::same_as<T, size_t> || std::same_as<T, std::size_t>;

template<IsNumber N> inline QString operator+ (const QString& str,        const N& num)              { return QString(str).append(QString::number(num)); }
template<IsNumber N> inline QString operator+ (const N& num,              const QString& str)        { return QString::number(num).append(str); }
template<IsNumber N> inline QString operator+ (const N& num,              const std::string& str)    { return QString::number(num).append(QString::fromStdString(str)); }
template<IsNumber N> inline QString operator+ (const std::string& str,    const N& num)              { return QString::fromStdString(str).append(QString::number(num)); }
template<IsSymbol C> inline QString operator+ (const C& char1,            const C& char2)            { return QString(char1).append(char2); }
template<IsSymbol C> inline QString operator+ (const QString& str,        const C& ch)               { return QString(str).append(ch); }
template<IsSymbol C> inline QString operator+ (const C& ch,               const QString& str)        { return QString(ch).append(str); }
                     inline QString operator+ (const QString& qstr,       const wchar_t* wstr)       { return QString(qstr).append(QString::fromStdWString(std::wstring(wstr))); }
                     inline QString operator+ (const QString& qstr,       const std::string& stdstr) { return QString(qstr).append(QString::fromStdString(stdstr)); }
                     inline QString operator+ (const std::string& stdstr, const QString& qstr)       { return QString::fromStdString(stdstr).append(qstr); }
#pragma endregion
