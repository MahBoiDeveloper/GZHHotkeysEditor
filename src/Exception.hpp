#pragma once

#include <string>
#include <exception>

class Exception : public std::exception
{
private:
    std::string message;
public:
    Exception(const std::string& msg) : message{msg}
    {
    }

    inline const char* what() const noexcept override
    {
        return message.c_str();
    }
};
