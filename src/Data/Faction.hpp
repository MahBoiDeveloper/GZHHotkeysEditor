#pragma once
#include <QMap>
#include "../Config.hpp"
#include "Entity.hpp"

class Faction
{
public:
    Faction(const QString& shortName, const QString& displayName, const QString& displayNameDescription);
    void AddEntities(Config::EntitiesTypes entityType, QVector<QSharedPointer<const Entity>>& newEntities);

    const QString& GetShortName() const;
    const QString& GetDisplayName() const;
    const QString& GetDisplayNameDescription() const;
    const QMap<Config::EntitiesTypes, QVector<QSharedPointer<const Entity>>>& GetEntitiesMap() const;

   QSet<QSharedPointer<const Entity>> GetAllEntities() const;

private:
    QString ShortName;
    QString DisplayName;
    QString DisplayNameDescription;

    QMap<Config::EntitiesTypes, QVector<QSharedPointer<const Entity>>> Entities;
};
