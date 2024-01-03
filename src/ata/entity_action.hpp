#pragma once

#include <string>

/// @brief class for storing building data
class EntityAction
{
public:
    EntityAction(const std::string& name, const std::string& csfString);
    const std::string& getName() const;
    const std::string& getCsfString() const;

private:
    std::string name;
    std::string csfString;
};
