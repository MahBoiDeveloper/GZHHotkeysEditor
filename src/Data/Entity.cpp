#include "Entity.hpp"

Entity::Entity(const QString& name, const QString& iconName, const QVector<QVector<QSharedPointer<EntityAction>>>& actionPanels)
    : name{name}
    , iconName{iconName}
    , actionPanels{actionPanels}
{}

const QString& Entity::getName() const
{
    return name;
}

const QString& Entity::getIconName() const
{
    return iconName;
}

const QVector<QVector<QSharedPointer<EntityAction>>>& Entity::getActionPanels() const
{
    return actionPanels;
}

int Entity::getPanelsCount() const
{
    return actionPanels.size();
}
