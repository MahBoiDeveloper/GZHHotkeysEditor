#pragma once
#include <exception>
#include <string>
#include <QString>

class Exception : public std::exception
{
private:
    std::string message;
public:
    Exception(const std::string& msg) : message{msg}
    {
    }

    Exception(const char* msg) : message{std::string(msg)}
    {
    }

    Exception(const QString& msg) : message{msg.toStdString()}
    {
    }

    /// @brief Get normal text context of the error 
    inline const char* what() const noexcept override
    {
        return message.c_str();
    }
};
