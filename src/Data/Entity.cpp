#include "Entity.hpp"

Entity::Entity(const QString& name, const QString& iconName, const QVector<QSharedPointer<EntityAction>>& actions)
    : Name{name}
    , IconName{iconName}
    , Actions{actions}
{}

const QString& Entity::GetName() const
{
    return Name;
}

const QString& Entity::GetIconName() const
{
    return IconName;
}

const QVector<QSharedPointer<EntityAction>>& Entity::GetActions() const
{
    return Actions;
}
