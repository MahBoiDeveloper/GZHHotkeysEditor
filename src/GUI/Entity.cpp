#include "Entity.hpp"

Entity::Entity(const QString& name, const QString& iconName, const QVector<QVector<QSharedPointer<EntityAction>>>& actionPanels)
    : name{name}
    , iconName{iconName}
    , actionPanels{actionPanels}
{}

const QString& Entity::GetName() const
{
    return name;
}

const QString& Entity::GetIconName() const
{
    return iconName;
}

const QVector<QVector<QSharedPointer<EntityAction>>>& Entity::GetActionPanels() const
{
    return actionPanels;
}

int Entity::GetPanelsCount() const
{
    return actionPanels.size();
}
