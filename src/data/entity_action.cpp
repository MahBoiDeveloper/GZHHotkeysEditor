#include "entity_action.hpp"

EntityAction::EntityAction(const std::string& name, const std::string& csfString)
    : name{name}
    , csfString{csfString}
{
}

const std::string& EntityAction::getName() const
{
    return name;
}

const std::string& EntityAction::getCsfString() const
{
    return csfString;
}
