#include "Faction.hpp"

Faction::Faction(const QString& shortName, const QString& displayName, const QString& displayNameDescription)
    : shortName{shortName}
    , displayName{displayName}
    , displayNameDescription{displayNameDescription}
{}

void Faction::addEntities(Config::EntitiesTypes entityType, const QVector<Entity>& newEntities)
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

const QString& Faction::getDisplayNameDescription() const
{
    return displayNameDescription;
}

const QMap<Config::EntitiesTypes, QVector<Entity>>& Faction::getEntitiesMap() const
{
    return entities;
}
