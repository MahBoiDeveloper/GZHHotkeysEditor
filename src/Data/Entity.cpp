#include "Entity.hpp"

Entity::Entity(const QString& name, const QString& iconName, const QVector<EntityAction>& actions)
    : name{name}
    , iconName{iconName}
    , actions{actions}
{
}

const QString& Entity::getName() const
{
    return name;
}

const QString& Entity::getIconName() const
{
    return iconName;
}

const QVector<EntityAction>& Entity::getActions() const
{
    return actions;
}
