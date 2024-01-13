#include "Faction.hpp"

Faction::Faction(const QString& shortName, const QString& displayName, const QString& displayNameDesctiontion)
    : shortName{shortName}
    , displayName{displayName}
    , displayNameDesctiontion{displayNameDesctiontion}
{
}

void Faction::addEntities(Config::Entities entityType, const QVector<Entity>& newEntities)
{
    entities.insert(entityType, newEntities);
}

const QString& Faction::getShortName() const
{
    return shortName;
}

const QString& Faction::getDisplayName() const
{
    return displayName;
}

const QString& Faction::getDisplayNameDesctiontion() const
{
    return displayNameDesctiontion;
}

const QMap<Config::Entities, QVector<Entity>>& Faction::getEntitiesMap() const
{
    return entities;
}

QVector<Entity> Faction::getEntitiesByType(Config::Entities entityType)
{
    return entities.value(entityType);
}
