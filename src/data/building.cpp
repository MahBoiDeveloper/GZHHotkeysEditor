#include "building.hpp"

Building::Building(const std::string& iconName, const std::string& csfString)
    : iconName{iconName}
    , csfString{csfString}
{
}

const std::string& Building::getIconName() const
{
    return iconName;
}

const std::string& Building::getCsfString() const
{
    return csfString;
}
