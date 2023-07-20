#pragma once

#include <string>
#include <exception>

class ExceptionMessage : public std::exception
{
private:
    std::string message;
public:
    ExceptionMessage(const std::string& msg) : message{msg}
    {
    }

    inline const char* what() const noexcept override
    {
        return message.c_str();
    }
};
