#pragma once

#include <entity_action.hpp>

#include <vector>

class Entity
{
public:
    Entity(const std::string& name, const std::string& ingameName, const std::vector<EntityAction>& actions);

    const std::string& getName() const;

    const std::string& getIngameName() const;

    const std::vector<EntityAction>& getActions() const;

private:
    std::string name;
    std::string ingameName;
    std::vector<EntityAction> actions;
};
