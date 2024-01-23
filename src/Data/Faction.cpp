#include "Faction.hpp"

Faction::Faction(const QString& shortName, const QString& displayName, const QString& displayNameDescription)
    : ShortName{shortName}
    , DisplayName{displayName}
    , DisplayNameDescription{displayNameDescription}
{}

void Faction::AddEntities(Config::EntitiesTypes entityType, QVector<QSharedPointer<const Entity>>& newEntities)
{
    Entities.insert(entityType, newEntities);
}

const QString& Faction::GetShortName() const
{
    return ShortName;
}

const QString& Faction::GetDisplayName() const
{
    return DisplayName;
}

const QString& Faction::GetDisplayNameDescription() const
{
    return DisplayNameDescription;
}

const QMap<Config::EntitiesTypes, QVector<QSharedPointer<const Entity>>>& Faction::GetEntitiesMap() const
{
    return Entities;
}
