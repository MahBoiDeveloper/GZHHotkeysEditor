#include "entity.hpp"

Entity::Entity(const QString& name, const QString& ingameName, const QVector<EntityAction>& actions)
    : name{name}
    , ingameName{ingameName}
    , actions{actions}
{
}

const QString& Entity::getName() const
{
    return name;
}

const QString& Entity::getIngameName() const
{
    return ingameName;
}

const QVector<EntityAction>& Entity::getActions() const
{
    return actions;
}
