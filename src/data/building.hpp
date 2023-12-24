#pragma once

#include <string>

/// @brief class for storing building data
class Building
{
public:
    Building(const std::string& iconName, const std::string& csfString);
    const std::string& getIconName() const;
    const std::string& getCsfString() const;

private:
    std::string iconName;
    std::string csfString;
};
