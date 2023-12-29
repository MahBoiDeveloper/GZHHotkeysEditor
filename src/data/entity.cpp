#include "entity.hpp"

Entity::Entity(const std::string& name, const std::string& ingameName, const std::vector<EntityAction>& actions)
    : name{name}
    , ingameName{ingameName}
    , actions{actions}
{
}

const std::string& Entity::getName() const
{
    return name;
}

const std::string& Entity::getIngameName() const
{
    return ingameName;
}

const std::vector<EntityAction>& Entity::getActions() const
{
    return actions;
}
